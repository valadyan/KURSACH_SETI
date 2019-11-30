#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QList>
#include <krug.h>

#include <QUdpSocket>

class Widget : public QWidget
{
    Q_OBJECT
    QList<Krug>* listKrug;
    QUdpSocket* socket;
    QByteArray* datagram;
public slots:
    void readD();
public:
    void paintEvent(QPaintEvent* event);

    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
