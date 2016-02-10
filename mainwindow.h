#ifdef WIN32
#include <winsock2.h>
#include <direct.h>
#include <windows.h>
#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <QGraphicsObject>
#include <QtGui>
#include <QDeclarativeContext>
#include <QDir>
#include <QFileDialog>
#include <QtDebug>
#include <QTextStream>

#include <string.h>

#include <parserxml.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startClient(char *addr);

    Q_INVOKABLE void throwCubes();
    Q_INVOKABLE void changePlayer();
    Q_INVOKABLE void change_interface(QString addr);
    Q_INVOKABLE bool RecieveFiles();
    Q_INVOKABLE void Quit();

private:
#ifdef WIN32
    WSADATA wsa;
    SOCKET s;
#else
    int s;
#endif
    QString maindir;
    QString dir;
    struct sockaddr_in server;

    QDeclarativeView *ui;
    QObject *Root;//корневой элемент QML модели

    //Parserxml parser;
};

#endif // MAINWINDOW_H
