#include "generatescores.h"
#include <QDebug>
#include <QCoreApplication>

/* Matlab Headers */
#include "LocalizationScore.h"
#include "AudioScore.h"
#include "MagneticScore.h"
#include "VideoScore.h"


GenerateScores::GenerateScores(QObject *parent) : QObject(parent)
{}

void GenerateScores::init()
{
    mclmcrInitialize();

    bool mclInitApp         = mclInitializeApplication(NULL, 0);
    bool locaInitSuccess    = LocalizationScoreInitialize();
    bool audioInitSuccess   = AudioScoreInitialize();
    bool magInitSuccess     = MagneticScoreInitialize();
    bool videoInitSuccess   = VideoScoreInitialize();
    qDebug() << QString("Init: MCL = %1 , Loca = %2 , Audio = %3 , Mag = %4 , Video = %5")
                .arg(mclInitApp).arg(locaInitSuccess).arg(audioInitSuccess).arg(magInitSuccess).arg(videoInitSuccess);
}

void GenerateScores::computeScores(QString refLoca, QString refMag, QString refAudio, QString refLips, QString subLoca, QString subMag, QString subAudio, QString subLips)
{
    mwArray trajFile1("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_loca.txt");
    mwArray trajFile2("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_loca.txt");

    mwArray refAudioFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_audio1.wav");
    mwArray subAudioFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_audio1.wav");

    mwArray refMagFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_raw_sensor.txt");
    mwArray subMagFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_raw_sensor.txt");

    mwArray refVideoFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_video.avi");
    mwArray subVideoFile("C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_video.avi");

    mwArray videoTrainingModelFile("C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/bin/Qt_5_5_1_MSVC2013_64bit/release/trainedModel.mat");
    mwArray videoUniformLBP8File("C:/Users/nsebkhi3/GitHub/Perso/Score-Generation/bin/Qt_5_5_1_MSVC2013_64bit/release/UniformLBP8.txt");


    mwArray locaScoreML;
    locaScoreMain(1, locaScoreML, trajFile1, trajFile2, refAudioFile, subAudioFile);
    double locaScore = locaScoreML(1,1);

    mwArray audioScoreML;
    audioScoreMain(1, audioScoreML, refAudioFile, subAudioFile);
    double audioScore = audioScoreML(1,1);

    mwArray magScoreML;
    magneticScoreMain(1, magScoreML, refMagFile, subMagFile, refAudioFile, subAudioFile);
    double magScore = magScoreML(1,1);

    mwArray videoScoreML;
    videoScoreMain(1, videoScoreML, videoTrainingModelFile, videoUniformLBP8File, refVideoFile, subVideoFile);
    double lipsScore = videoScoreML(1,1);
//    double lipsScore = 0.0;

    emit scores(locaScore, magScore, audioScore, lipsScore);
}

GenerateScores::~GenerateScores()
{
    LocalizationScoreTerminate();
    AudioScoreTerminate();
    MagneticScoreTerminate();
    VideoScoreTerminate();
    mclTerminateApplication();
}
