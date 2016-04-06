#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QVector>
#include <QNetworkAccessManager>
#include <QImage>

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

    int state; // 1 = waiting to start, 2 = in progress, 3 = done
    int player; // number of player, from environment variable
    int game; // game number; this selects the set of questions
    QVector<QString> maps; // list of mapfiles to use in this game
    QVector<QImage> mapImages; // list of images to use for challenges
    QNetworkAccessManager *nam; // for fetching URLs
    int fetchedMap = 0;

    // connection info
    QString dbHostname;
    QString dbUsername;
    QString dbDbname;
    QString baseMapUrl;

    QSqlDatabase db;

private slots:
    void notificationReceived();
    void updateName(QString n);
    void nextMap();
    void rcvMap(QNetworkReply*);
};

#endif // MAINWINDOW_H
