#include "widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(0,0,600,600);

    listKrug=new QList<Krug>;
    datagram=new QByteArray;
    socket=new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 7755);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readD()));
}

void Widget::readD(){
    int num,a,b,r;
    listKrug->clear();
    do{
        datagram->resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram->data(), datagram->size());
    }while(socket->hasPendingDatagrams());
    QDataStream in(datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_3);
    in>>num;
    qDebug()<<num;
    for(int i=0; i<num; i++){
        in>>a>>b>>r;
        qDebug()<<a;
        listKrug->push_back(Krug(a,b,r));
    }
    emit update();
}

void Widget::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.setPen(Qt::blue);

    for(auto k: *listKrug)
        painter.drawEllipse(k.a, k.b, k.r, k.r);
}


Widget::~Widget()
{

}
