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
    QString trainModelQStr      = QString(QCoreApplication::applicationDirPath() + "/trainedModel.mat");
    QString uniformLBP8QStr     = QString(QCoreApplication::applicationDirPath() + "/UniformLBP8.txt");

    // Convert QString type to Matlab mwArray type
    mwArray refTrajFile(refLoca.toLatin1().constData());
    mwArray subTrajFile(subLoca.toLatin1().constData());

    mwArray refAudioFile(refAudio.toLatin1().constData());
    mwArray subAudioFile(subAudio.toLatin1().constData());

    mwArray refMagFile(refMag.toLatin1().constData());
    mwArray subMagFile(subMag.toLatin1().constData());

    mwArray refVideoFile(refLips.toLatin1().constData());
    mwArray subVideoFile(subLips.toLatin1().constData());
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
