#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "mclmcrrt.h"
#include "LocalizationScore.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mclmcrInitialize();

    bool mclInitApp = mclInitializeApplication(NULL, 0);
    qDebug() << "MCL Init App: " << mclInitApp;


    bool success = LocalizationScoreInitialize();
    qDebug() << "Sucess " << success;

    mwArray trajFile1("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_loca.txt");
    mwArray trajFile2("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_loca.txt");

    mwArray audioFile1("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_audio1.wav");
    mwArray audioFile2("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_audio1.wav");

    mwArray score;

    locaScoreMain(1, score, trajFile1, trajFile2, audioFile1, audioFile2);

    double locaScore = score(1,1);

    qDebug() << "SCore: " << locaScore;

    LocalizationScoreTerminate();
    mclTerminateApplication();

}


MainWindow::~MainWindow()
{
    delete ui;
}
