#include "widget.h"

#include<QDebug>

Widget::Widget(QApplication* app)
{
    socket = new QUdpSocket(this);
    setGeometry(800,0,600,600);

    dataBuf=new DataBuf();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(40, 150);
    for(int i=0; i<num_of_circles; i++){//
        circles.append(std::shared_ptr<myKrug>(new myKrug(dist(mt), geometry().width(), geometry().height())));
    }

    workerThread=new myWorkThread(this, &circles, dataBuf);
    connect(workerThread, SIGNAL(drawSignal()), this, SLOT(update()));

    connect(workerThread, SIGNAL(sendSocket()), this, SLOT(sendSocket()));
    connect(this, SIGNAL(ready()), workerThread, SLOT(socketReady()));
    connect(this, SIGNAL(swapBuf()), dataBuf, SLOT(swapSlot()));
    connect(workerThread, SIGNAL(swapBuf()), dataBuf, SLOT(swapSlot()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    connect(this, &Widget::destroyed, workerThread, &myWorkThread::quit);
//    connect(this, &Widget::destroyed, app, &QApplication::exit);

    workerThread->start();
}
void Widget::sendSocket(){
//    int k;
//    QDataStream in(dataBuf->getBufferPoint(), QIODevice::ReadOnly);
//    in>>k;

//    qDebug()<<k;
//    qDebug()<<"suka2";
    socket->writeDatagram(dataBuf->getBuffer(), QHostAddress::LocalHost, port);
    emit ready();
//    if(!workerThread->ready)
//        emit swapBuf();
}
Widget::~Widget()
{
    workerThread->quit();
    workerThread->wait();
    delete workerThread;
    delete socket;
    delete dataBuf;
}

void Widget::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setPen(Qt::blue);
//    painter.setFont(QFont("Arial", 30));
//    painter.drawText(rect(), Qt::AlignCenter, "Qt");
    auto iter=circles.constBegin();
    while(iter!=circles.constEnd()){
        painter.drawEllipse((*iter++)->getRect());
    }

}
