#include <QProcessEnvironment>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QTimer>
#include <QUrl>
#include <QNetworkRequest>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showFullScreen();

    // use environment variables to configure connections
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    dbHostname = env.value("DBHOSTNAME");
    dbUsername = env.value("DBUSERNAME");
    dbDbname = env.value("DBDBNAME");
    baseMapUrl = env.value("BASEMAPURL");
    player = env.value("PLAYER").toInt();
    game = env.value("GAME").toInt();

    // connect to DB
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(dbHostname);
    db.setDatabaseName(dbDbname);
    db.setUserName(dbUsername);
    db.open();

    // database notifications
    db.driver()->subscribeToNotification("next");
    connect(db.driver(), SIGNAL(notification(const QString&)), this, SLOT(notificationReceived()));

    // other general setup
    state = 1;
    connect(ui->txtName, SIGNAL(textChanged(QString)), this, SLOT(updateName(QString)));

    // get list of challenges
    QSqlQuery challenges;
    challenges.prepare("SELECT mapfile FROM challenges WHERE qset=:game ORDER BY qorder");
    challenges.bindValue(":game", game);
    challenges.exec();
    while (challenges.next())
        maps << challenges.value(0).toString();

    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(nextMap()));
    QTimer::singleShot(50, this, SLOT(nextMap()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nam;
}

void MainWindow::notificationReceived()
{
    qDebug() << QString("signal!");
}

void MainWindow::updateName(QString n)
{
    QSqlQuery update;
    update.prepare("UPDATE players SET name=:name where num=:num");
    update.bindValue(":name", n);
    update.bindValue(":num", player);
    update.exec();
}

void MainWindow::nextMap()
{
    if (fetchedMap < maps.size()) {
        nam->get(QNetworkRequest(QUrl(baseMapUrl + maps[fetchedMap])));
        fetchedMap++;
    }
}

void MainWindow::rcvMap(QNetworkReply *)
{

    QTimer::singleShot(50, this, SLOT(nextMap()));
}
