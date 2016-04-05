#ifndef GENERATESCORES_H
#define GENERATESCORES_H

#include <QObject>

class GenerateScores : public QObject
{
    Q_OBJECT

public:
    explicit GenerateScores(QObject *parent = 0);
    ~GenerateScores();

signals:
    void scores(double loca, double mag, double voice, double lips);

public slots:   
    void init();
    void computeScores(QString refLoca, QString refMag, QString refAudio, QString refLips,
                       QString subLoca, QString subMag, QString subAudio, QString subLips);


};

#endif // GENERATESCORES_H
