#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <mykrug.h>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <memory>
#include <myworkthread.h>
#include <random>
#include <databuf.h>

#include <QUdpSocket>
#include <QDataStream>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QApplication* app);
    ~Widget();
    void paintEvent(QPaintEvent* event);
signals:
    void ready();
    void swapBuf();
public slots:
    void sendSocket();
private:
    int port=7755;
    int num_of_circles=4;
    QList<std::shared_ptr<myKrug>> circles;
    myWorkThread* workerThread;
    QUdpSocket* socket;
    DataBuf* dataBuf;
};

#endif // WIDGET_H
