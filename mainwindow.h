#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QMouseEvent>
#include <QTime>

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
    int currentMap; // which map we're on in the set
    QVector<QString> maps; // list of mapfiles to use in this game
    QVector<QPixmap> mapImages; // list of images to use for challenges
    QNetworkAccessManager *nam; // for fetching URLs
    int fetchedMap = 0;

    // connection info
    QString dbHostname;
    QString dbUsername;
    QString dbDbname;
    QString baseMapUrl;

    QSqlDatabase db;
    QTime measureTimer; // keep track of how long it takes user to click map

private slots:
    void notificationReceived();
    void updateName(QString n);
    void nextMap();
    void rcvMap(QNetworkReply *r);
public slots:
    void mapClicked(QMouseEvent *e);
};

#endif // MAINWINDOW_H
