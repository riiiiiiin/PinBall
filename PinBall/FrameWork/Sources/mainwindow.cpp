#include "FrameWork/Headers/mainwindow.h"

MainWindow::MainWindow(QWidget* parent):QMainWindow(parent){
    _manager = new GameWidgetManager(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(960,540);
    setCentralWidget(_manager->StackedWidget());
    setWindowIcon(QIcon(":/window_icons/bing_icon_1.png"));
    QFile slogan_resource(":/slogans/.slogans");
    if(slogan_resource.open(QIODevice::ReadOnly | QIODevice::Text)){
        QVector<QString> slogans;
        slogans.clear();
        
        QTextStream is(&slogan_resource);
        while(not is.atEnd()){
            QString slogan=is.readLine();
            slogans.push_back(slogan);
        }
        int index=QRandomGenerator::global()->bounded(0,slogans.size());
        setWindowTitle("PinBall : "+slogans[index]);
        slogan_resource.close();
    }
    else
    {
        qDebug() << "Failed to open file";
    }
}

MainWindow::~MainWindow(){
    delete _manager;
}