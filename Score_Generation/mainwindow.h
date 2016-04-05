#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setScorePlot();


private:
    Ui::MainWindow *ui;
    QThread *generateScoreThread;

    QCPBars *locaBars;
    QCPBars *magBars;
    QCPBars *voiceBars;
    QCPBars *lipsBars;
    QCPBars *avgScoreBars;

public slots:
    void updateScores(double loca, double mag, double voice, double lips);

signals:
    void genScoresSig(QString refLoca, QString refMag, QString refAudio, QString refLips,
                      QString subLoca, QString subMag, QString subAudio, QString subLips);
private slots:
    void on_genScoresButton_clicked();
};

#endif // MAINWINDOW_H
