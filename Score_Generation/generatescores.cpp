/********************************************************************
 * This class generates the scores of the speech modalities.
 * It requires reference and subject file paths to generate scores.
 * It also manages the matlab runtime engine.
 *
 * Author: Nordine Sebkhi
 *********************************************************************/

#include "generatescores.h"
#include <QDebug>
#include <QCoreApplication>

/* Matlab Headers */
#include "LocalizationScore.h"
#include "AudioScore.h"
#include "MagneticScore.h"
#include "VideoScore.h"

/**
 * @brief Constructor
 * Empty constructor as it is moved in a QThread
 * @param parent
 */
GenerateScores::GenerateScores(QObject *parent) : QObject(parent)
{}

/**
 * @brief Start the matlab runtime engine
 */
void GenerateScores::init()
{

    mclmcrInitialize();

    bool mclInitApp         = mclInitializeApplication(NULL, 0);
    bool locaInitSuccess    = LocalizationScoreInitialize();
    bool audioInitSuccess   = AudioScoreInitialize();
    bool magInitSuccess     = MagneticScoreInitialize();
    bool videoInitSuccess   = VideoScoreInitialize();

    qDebug() << QString("Matlab Init. Status : MCL = %1 , Loca = %2 , Audio = %3 , Mag = %4 , Video = %5")
                .arg(mclInitApp).arg(locaInitSuccess).arg(audioInitSuccess).arg(magInitSuccess).arg(videoInitSuccess);
}

/**
 * @brief Compute the scores for all speech modalities
 * @param refLoca   file path to reference localization
 * @param refMag    file path to reference magnetic data
 * @param refAudio  file path to reference voice
 * @param refLips   file path to reference video
 * @param subLoca   file path to subject localization
 * @param subMag    file path to subject magnetic data
 * @param subAudio  file path to subject voice
 * @param subLips   file path to subject video
 */
void GenerateScores::computeScores(QString refLoca, QString refMag, QString refAudio, QString refLips, QString subLoca, QString subMag, QString subAudio, QString subLips)
{
    // Get file path to training models from machine learning results
    // TODO: should be set as instance variable and set values once in constructor
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

    // Perform score generation for all speech modalities
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

    // Emit results to GUI manager
    emit scores(locaScore, magScore, audioScore, lipsScore);
}

/**
 * @brief Destructor
 * Close matlab runtime engine
 * Note: This is a slow process
 */
GenerateScores::~GenerateScores()
{
    LocalizationScoreTerminate();
    AudioScoreTerminate();
    MagneticScoreTerminate();
    VideoScoreTerminate();
    mclTerminateApplication();
}
