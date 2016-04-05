#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "generatescores.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
}

MainWindow::~MainWindow()
{
    generateScoreThread->exit();
    delete ui;
}
