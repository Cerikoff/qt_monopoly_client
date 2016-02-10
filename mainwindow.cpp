#include "mainwindow.h"

#define BUF_SIZE 1024

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Включаем наш QML
    ui = new QDeclarativeView;
    ui->setSource(QUrl("qrc:/main.qml"));
    setCentralWidget(ui);
    ui->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    //Находим корневой элемент
    Root = ui->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент window
    ui->rootContext()->setContextProperty("window", this);


    /*delete*/
    QString xmlpath = "C://Users/rondo/Desktop/config.xml";
    Parserxml* parser = new Parserxml;
    parser->parse(xmlpath);
}

MainWindow::~MainWindow()
{
    //Удаляем QML
    delete ui;
}

void MainWindow::Quit()
{
    #ifdef WIN32
        WSACleanup();
        closesocket(s);
    #else
        ::close(s);
    #endif
}

void MainWindow::throwCubes()
{
    char *mes = "1";
    send(s , mes , strlen(mes) , 0);
}

void MainWindow::changePlayer()
{
    char *mes = "2";
    send(s , mes , strlen(mes) , 0);
}

bool MainWindow::RecieveFiles()
{
    maindir = "/my_app_folder";
    dir = "/my_app_folder/ui_folder";

    QString path =  QDir().currentPath();

    maindir = path + maindir;
    dir = path + dir;

    qDebug() << maindir << endl;
    qDebug() << dir << endl;


    if(!QDir(maindir).exists())
        QDir().mkdir(maindir);
    if(!QDir(dir).exists())
        QDir().mkdir(dir);

    char buf[2];
    if (recv(s, buf, 2, 0) == 0)
    {
        return false;
    }

    int amount = atoi(buf);

    char fname[128];
    for (int i = 0; i < amount; i++)
    {
        // Принимаем имя файла
        if (recv(s, fname, sizeof(fname), 0) == 0)
        {
            return false;
        }
        // Ошибка передачи
        if (strcmp(fname, "Error") == 0)
        {
            return false;
        }
        else
        {
            char tmp[BUF_SIZE];
            QByteArray tempDir;
            tempDir = dir.toUtf8();
            char *dir_ch=tempDir.data();
            chdir(dir_ch);

            FILE *file = fopen(fname, "wb");
            if (file == NULL)
            {      
                return false;
            }
            int  from_len = 0;
            while ((from_len = recv(s, tmp, BUF_SIZE,0))>0)
            {
                fwrite(tmp, sizeof(char), from_len, file);

                #ifdef WIN32
                    ::Sleep(0.005);
                #else
                    ::usleep(5);
                #endif
                qDebug() << tmp << endl;

                if(from_len<BUF_SIZE)
                    break;
            }
            fclose(file);
        }
    }
    //принять main.qml
    // Принимаем имя файла
    if (recv(s, fname, sizeof(fname), 0) == 0)
    {
        return false;
    }
    // Ошибка передачи
    if (strcmp(fname, "Error") == 0)
    {
        return false;
    }
    else
    {
        char tmp[BUF_SIZE];
        QByteArray tempMainDir;             //TODO в отдельную функцию
        tempMainDir = maindir.toUtf8();
        char *maindir_ch=tempMainDir.data();
        qDebug() << maindir_ch << endl;

        chdir(maindir_ch);

        FILE *file = fopen(fname, "wb");
        if (file == NULL)
        {      
            return false;
        }
        int  from_len = 0;
        while ((from_len = recv(s, tmp, BUF_SIZE,0))>0)
        {
            fwrite(tmp, sizeof(char), from_len, file);
            write(1, tmp, from_len);

            if(from_len<BUF_SIZE)
                break;
        }
        fclose(file);
    }
    return true;
}

void MainWindow::change_interface(QString addr)
{
    QByteArray tempAddr;             //TODO в отдельную функцию
    tempAddr = addr.toUtf8();
    char *address=tempAddr.data();

    startClient(address);

    char *mes = "3";
    send(s , mes , strlen(mes) , 0);

    RecieveFiles();

    //QString xmlpath = "C://Users/rondo/Desktop/config.xml";
    //parser.parse(xmlpath);


    QDeclarativeView *view;
    view = new QDeclarativeView;

    QString temp = maindir + "/first.qml";
    view->setSource(QUrl::fromLocalFile(temp));

    setCentralWidget(view);
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    //Находим корневой элемент
    Root = view->rootObject();
    //Соединяем C++ и QML, делая видимым функции С++ через элемент window
    view->rootContext()->setContextProperty("window", this);

    view->show();
}

void MainWindow::startClient(char *address)
{
    #ifdef WIN32
        WSAStartup(MAKEWORD(2,2),&wsa);
    #endif

    s = socket(AF_INET , SOCK_STREAM , 0);

   //server.sin_addr.s_addr = inet_addr("127.0.0.1");
   //server.sin_addr.s_addr = inet_addr("192.168.1.101");
   server.sin_addr.s_addr = inet_addr(address);
   server.sin_family = AF_INET;
   server.sin_port = htons( 8020 );

   ::connect(s , (struct sockaddr *)&server , sizeof(server));
}


