#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "generatescores.h"
#include <QVector>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    setScorePlot();
}

void MainWindow::setScorePlot()
{
    ui->scorePlot->plotLayout()->clear();

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
        axis->axis(QCPAxis::atBottom)->setRange(0,3);
        axis->axis(QCPAxis::atBottom)->setAutoTickStep(false);
        axis->axis(QCPAxis::atBottom)->setTickStep(1);
        axis->axis(QCPAxis::atBottom)->setAutoSubTicks(false);
        axis->axis(QCPAxis::atBottom)->setSubTickCount(0);
        axis->axis(QCPAxis::atLeft)->setRange(0,10);
        axis->axis(QCPAxis::atLeft)->setAutoTickStep(false);
        axis->axis(QCPAxis::atLeft)->setTickStep(1);
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


    locaBars = new QCPBars(locaAxis->axis(QCPAxis::atBottom), locaAxis->axis(QCPAxis::atLeft));
    magBars = new QCPBars(magAxis->axis(QCPAxis::atBottom), magAxis->axis(QCPAxis::atLeft));
    voiceBars = new QCPBars(voiceAxis->axis(QCPAxis::atBottom), voiceAxis->axis(QCPAxis::atLeft));
    lipsBars = new QCPBars(lipsAxis->axis(QCPAxis::atBottom), lipsAxis->axis(QCPAxis::atLeft));
    avgScoreBars = new QCPBars(avgScoreAxis->axis(QCPAxis::atBottom), avgScoreAxis->axis(QCPAxis::atLeft));

    QVector<QCPBars*> scoreBars;
    scoreBars << locaBars << magBars << voiceBars << lipsBars << avgScoreBars;

    foreach (QCPBars* bars, scoreBars) {
        bars->setWidth(0.2);
    }

    ui->scorePlot->addPlottable(locaBars);
    ui->scorePlot->addPlottable(magBars);
    ui->scorePlot->addPlottable(voiceBars);
    ui->scorePlot->addPlottable(lipsBars);
    ui->scorePlot->addPlottable(avgScoreBars);
}

void MainWindow::on_genScoresButton_clicked()
{
    QString refLocaPath     = ui->refLocaPathEdit->text();
    QString refMagPath      = ui->refMagPathEdit->text();
    QString refVoicePath    = ui->refVoicePathEdit->text();
    QString refLipsPath     = ui->refLipsPathEdit->text();

    QString subLocaPath     = ui->subLocaPathEdit->text();
    QString subMagPath      = ui->subMagPathEdit->text();
    QString subVoicePath    = ui->subVoicePathEdit->text();
    QString subLipsPath     = ui->subLipsPathEdit->text();

    emit genScoresSig(refLocaPath, refMagPath, refVoicePath, refLipsPath,
                      subLocaPath, subMagPath, subVoicePath,subLipsPath);
}

void MainWindow::updateScores(double loca, double mag, double voice, double lips)
{
    ui->locaScoreEdit->setText(QString::number(loca));
    ui->magScoreEdit->setText(QString::number(mag));
    ui->voiceScoreEdit->setText(QString::number(voice));
    ui->lipScoreEdit->setText(QString::number(lips));

    locaBars->addData(1, loca);
    magBars->addData(1, mag);
    voiceBars->addData(1, voice);
    lipsBars->addData(1, lips);

    double avgScore = (loca + mag + voice + lips) / 4.0;
    avgScoreBars->addData(1, avgScore);


    ui->scorePlot->replot();

}

MainWindow::~MainWindow()
{
    generateScoreThread->exit();
    delete ui;
}
