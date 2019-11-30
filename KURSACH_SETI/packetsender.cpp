#include "packetsender.h"

PacketSender::PacketSender()
{
    udpSocket=new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, port);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void PacketSender::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        udpSocket->readDatagram(_udpData, sizeof(_udpData));
    }
}

void PacketSender::sendSocket(){
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

}
