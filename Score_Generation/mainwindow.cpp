/*****************************************
 * This class manages the UI elements,
 * specifically the score plots.
 *
 * Author: Nordine Sebkhi
 ****************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "generatescores.h"
#include <QVector>
#include <QDebug>

/**
 * @brief Constructor of MainWindow that creates a score generating thread
 * and initialize field values and score plot
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Start score generating thread
    generateScoreThread = new QThread(this);

    GenerateScores *genScores = new GenerateScores();
    genScores->moveToThread(generateScoreThread);

    connect(this, SIGNAL(genScoresSig(QString,QString,QString,QString,QString,QString,QString,QString)),
            genScores, SLOT(computeScores(QString,QString,QString,QString,QString,QString,QString,QString)));
    connect(genScores, SIGNAL(scores(double,double,double,double)), this, SLOT(updateScores(double,double,double,double)));
    connect(generateScoreThread, SIGNAL(started()), genScores, SLOT(init()));
    connect(generateScoreThread, SIGNAL(finished()), genScores, SLOT(deleteLater()));

    generateScoreThread->start();

    // Init file path values
    ui->refLocaPathEdit->setText(   "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_loca.txt"      );
    ui->refMagPathEdit->setText(    "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_raw_sensor.txt");
    ui->refVoicePathEdit->setText(  "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_audio1.wav"    );
    ui->refLipsPathEdit->setText(   "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_video.avi"     );

    ui->subLocaPathEdit->setText(   "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_loca.txt"      );
    ui->subMagPathEdit->setText(    "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_raw_sensor.txt");
    ui->subVoicePathEdit->setText(  "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_audio1.wav"    );
    ui->subLipsPathEdit->setText(   "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_video.avi"     );

    // Initialize the score plot with 5 trials
    numTrials = 5;
    currentTrial = 1;
    setScorePlot();
}

/**
 * @brief Set the layout and axis of the score plot.
 * Initialize score bars to 0.0 with number of trials.
 */
void MainWindow::setScorePlot()
{
    // Always clear default layout
    ui->scorePlot->plotLayout()->clear();

    // MarginGroup is used to align subplots for better appearance
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->scorePlot);
    QCPRange barRangeX(0, numTrials + 1);
    QCPRange barRangeY(0, 10);

    // Initiialize an axis for each modality
    QCPAxisRect *locaAxis = new QCPAxisRect(ui->scorePlot);
    QCPAxisRect *magAxis = new QCPAxisRect(ui->scorePlot);
    QCPAxisRect *voiceAxis = new QCPAxisRect(ui->scorePlot);
    QCPAxisRect *lipsAxis = new QCPAxisRect(ui->scorePlot);
    QCPAxisRect *avgScoreAxis = new QCPAxisRect(ui->scorePlot);

    QVector<QCPAxisRect*> scoreAxes;
    scoreAxes << locaAxis << magAxis << voiceAxis << lipsAxis << avgScoreAxis;

    foreach (QCPAxisRect* axis, scoreAxes) {
        axis->setupFullAxesBox(true);
        axis->axis(QCPAxis::atTop)->setLabelColor(QColor(Qt::blue));
        axis->axis(QCPAxis::atBottom)->setRange(barRangeX);
        axis->axis(QCPAxis::atBottom)->setAutoTickStep(false);
        axis->axis(QCPAxis::atBottom)->setTickStep(1);
        axis->axis(QCPAxis::atBottom)->setAutoSubTicks(false);
        axis->axis(QCPAxis::atBottom)->setSubTickCount(0);
        axis->axis(QCPAxis::atLeft)->setRange(barRangeY);
        axis->axis(QCPAxis::atLeft)->setAutoTickStep(false);
        axis->axis(QCPAxis::atLeft)->setTickStep(1);
        axis->setMarginGroup(QCP::msLeft, marginGroup);
    }

    locaAxis->axis(QCPAxis::atTop)->setLabel("Localization");
    magAxis->axis(QCPAxis::atTop)->setLabel("Magnetic");
    voiceAxis->axis(QCPAxis::atTop)->setLabel("Voice");
    lipsAxis->axis(QCPAxis::atTop)->setLabel("Lips");
    avgScoreAxis->axis(QCPAxis::atTop)->setLabel("Average");

    ui->scorePlot->plotLayout()->addElement(0, 0, avgScoreAxis);
    ui->scorePlot->plotLayout()->addElement(1, 0, locaAxis);
    ui->scorePlot->plotLayout()->addElement(1, 1, magAxis);
    ui->scorePlot->plotLayout()->addElement(2, 0, voiceAxis);
    ui->scorePlot->plotLayout()->addElement(2, 1, lipsAxis);

    // To enable color mapping of bars to its value on a same bar axis,
    // a bar group should be created for each trial that contains 0.0 for all trials than current
    for (int i = 0; i <= numTrials; i++) {
        locaBars.append(new QCPBars(locaAxis->axis(QCPAxis::atBottom), locaAxis->axis(QCPAxis::atLeft)));
        magBars.append(new QCPBars(magAxis->axis(QCPAxis::atBottom), magAxis->axis(QCPAxis::atLeft)));
        voiceBars.append(new QCPBars(voiceAxis->axis(QCPAxis::atBottom), voiceAxis->axis(QCPAxis::atLeft)));
        lipsBars.append(new QCPBars(lipsAxis->axis(QCPAxis::atBottom), lipsAxis->axis(QCPAxis::atLeft)));
        avgScoreBars.append(new QCPBars(avgScoreAxis->axis(QCPAxis::atBottom), avgScoreAxis->axis(QCPAxis::atLeft)));
    }

    QVector<QVector<QCPBars*>> scoreBars;
    scoreBars << locaBars << magBars << voiceBars << lipsBars << avgScoreBars;

    foreach (QVector<QCPBars*> bars, scoreBars) {

        foreach(QCPBars* bar, bars) {
            bar->setWidth(0.2);
            bar->setPen(QPen(QColor(Qt::black)));

            QVector<double> keys(numTrials+2);
            QVector<double> values(keys.size(), 0.0);

            for (int key = 0; key < keys.size(); key++) {
                keys[key] = key;
            }
            bar->setData(keys, values);

            ui->scorePlot->addPlottable(bar);
        }
    }

    // Set Color Gradient and Scale
    colorGrad.loadPreset(QCPColorGradient::gpIon);
    QCPColorScale *colorScale = new QCPColorScale(ui->scorePlot);
    colorScale->setGradient(colorGrad);
    colorScale->setDataRange(barRangeY);
    colorScale->setMarginGroup(QCP::msLeft, marginGroup);
    colorScale->axis()->setAutoTickStep(false);
    colorScale->axis()->setTickStep(1);
    colorScale->axis()->setAutoSubTicks(false);
    colorScale->axis()->setSubTickCount(0);

    ui->scorePlot->plotLayout()->addElement(0, 2, colorScale);
}

/**
 * @brief Generate Scores button clicked
 * Get file paths and emit signal to generate scores
 */
void MainWindow::on_genScoresButton_clicked()
{
    // Get reference paths
    QString refLocaPath     = ui->refLocaPathEdit->text();
    QString refMagPath      = ui->refMagPathEdit->text();
    QString refVoicePath    = ui->refVoicePathEdit->text();
    QString refLipsPath     = ui->refLipsPathEdit->text();

    // Get subject paths
    QString subLocaPath     = ui->subLocaPathEdit->text();
    QString subMagPath      = ui->subMagPathEdit->text();
    QString subVoicePath    = ui->subVoicePathEdit->text();
    QString subLipsPath     = ui->subLipsPathEdit->text();

    // Emit signal to generate scores to the thread
    emit genScoresSig(refLocaPath, refMagPath, refVoicePath, refLipsPath,
                      subLocaPath, subMagPath, subVoicePath,subLipsPath);
}

/**
 * @brief Update bar plots according to generateds scores
 * @param loca  localization score
 * @param mag   magnetic data score
 * @param voice voice score
 * @param lips  video score
 */
void MainWindow::updateScores(double loca, double mag, double voice, double lips)
{
    // Show numerical display of the scores
    ui->locaScoreEdit->setText(QString::number(loca));
    ui->magScoreEdit->setText(QString::number(mag));
    ui->voiceScoreEdit->setText(QString::number(voice));
    ui->lipScoreEdit->setText(QString::number(lips));

    // Compute the average of scores from all modalities
    // May need to change it to a weighted average in future studies
    double avgScore = (loca + mag + voice + lips) / 4.0;

    // Get the colors associated with the score values
    double scores[5] = {loca, mag, voice, lips, avgScore};
    QRgb colors[5];
    colorGrad.colorize(scores, QCPRange(0.0, 10.0), colors, 5);

    // Update bars and their color
    locaBars[currentTrial]->addData(currentTrial, loca);
    locaBars[currentTrial]->setBrush(QBrush(QColor(colors[0])));

    magBars[currentTrial]->addData(currentTrial, mag);
    magBars[currentTrial]->setBrush(QBrush(QColor(colors[1])));

    voiceBars[currentTrial]->addData(currentTrial, voice);
    voiceBars[currentTrial]->setBrush(QBrush(QColor(colors[2])));

    lipsBars[currentTrial]->addData(currentTrial, lips);
    lipsBars[currentTrial]->setBrush(QBrush(QColor(colors[3])));

    avgScoreBars[currentTrial]->addData(currentTrial, avgScore);
    avgScoreBars[currentTrial]->setBrush(QBrush(QColor(colors[4])));

    ui->scorePlot->replot();
    currentTrial++;
}

/**
 * @brief Destructor of MainWindow
 * Perform a clean exit of the score generating thread
 */
MainWindow::~MainWindow()
{
    generateScoreThread->exit();
    delete ui;
}
