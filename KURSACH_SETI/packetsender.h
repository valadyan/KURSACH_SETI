#ifndef PACKETSENDER_H
#define PACKETSENDER_H

#include <QUdpSocket>
#include <QThread>
#include <QList>

class PacketSender: public QThread
{
    Q_OBJECT
public:
    int port=7755;
    PacketSender(QObject* obj): QThread(obj){}
    void run() override{}
public slots:
    void sendSocket();
private:
    QUdpSocket* udpSocket;
};

#endif // PACKETSENDER_H
