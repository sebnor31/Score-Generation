#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    QThread *generateScoreThread;

public slots:
    void updateScores(double loca, double mag, double voice, double lips);

signals:
    void genScoresSig(QString refLoca, QString refMag, QString refAudio, QString refLips,
                      QString subLoca, QString subMag, QString subAudio, QString subLips);
private slots:
    void on_genScoresButton_clicked();
};

#endif // MAINWINDOW_H
