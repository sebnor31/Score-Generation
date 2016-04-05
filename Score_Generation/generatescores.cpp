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
    // Create the QString type of file paths
    QString refTrajFileQStr     = "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_loca.txt";
    QString subTrajFileQStr     = "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_loca.txt";

    QString refAudioFileQStr    = "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_audio1.wav";
    QString subAudioFileQStr    = "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_audio1.wav";

    QString refMagFileQStr      = "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_raw_sensor.txt";
    QString subMagFileQStr      = "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_raw_sensor.txt";

    QString refVideoFileQStr    = "C:/TTS_Data/NEU/Sub1/word/angry/angry_1/angry_1_video.avi";
    QString subVideoFileQStr    = "C:/TTS_Data/NEU/Sub1/word/angry/angry_2/angry_2_video.avi";
    QString trainModelQStr      = QString(QCoreApplication::applicationDirPath() + "/trainedModel.mat");
    QString uniformLBP8QStr     = QString(QCoreApplication::applicationDirPath() + "/UniformLBP8.txt");

    // Convert QString type to Matlab mwArray type
    mwArray refTrajFile(refTrajFileQStr.toLatin1().constData());
    mwArray subTrajFile(subTrajFileQStr.toLatin1().constData());

    mwArray refAudioFile(refAudioFileQStr.toLatin1().constData());
    mwArray subAudioFile(subAudioFileQStr.toLatin1().constData());

    mwArray refMagFile(refMagFileQStr.toLatin1().constData());
    mwArray subMagFile(subMagFileQStr.toLatin1().constData());

    mwArray refVideoFile(refVideoFileQStr.toLatin1().constData());
    mwArray subVideoFile(subVideoFileQStr.toLatin1().constData());
    mwArray videoTrainingModelFile(trainModelQStr.toLatin1().constData());
    mwArray videoUniformLBP8File(uniformLBP8QStr.toLatin1().constData());

    // Perform score generation
    mwArray locaScoreML;
    locaScoreMain(1, locaScoreML, refTrajFile, subTrajFile, refAudioFile, subAudioFile);
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
