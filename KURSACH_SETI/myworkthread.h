#ifndef MYWORKTHREAD_H
#define MYWORKTHREAD_H

#include <QThread>
#include <mykrug.h>
#include <QList>
#include <memory>
#include <QDebug>
#include <QDataStream>
#include <databuf.h>

auto kchek=[](QList<std::shared_ptr<myKrug>> *_circles)
{
auto iter1=_circles->begin();
auto pre_end_itr=_circles->end();
pre_end_itr--;
for(auto i=iter1; i<pre_end_itr; i++)
    for(auto w=++i; w<_circles->end(); w++)
        if ( (*i)!=(*w) && ((*i)->r+(*w)->r)>=(sqrt(pow(((*i)->a-(*w)->a), 2)+pow(((*i)->b-(*w)->b), 2))))
        {
           int ia2=(*i)->a;
           int ib2=(*i)->b;
           int wa2=(*w)->a;
           int wb2=(*w)->b;
           (*i)->a=((*i)->a-(*i)->a2+(*w)->r/(*i)->r*sqrt(pow((*w)->kef_a, 2)+pow((*w)->kef_b, 2))*((*i)->a-(*w)->a)/((*w)->r+(*i)->r)+(*i)->a);
           (*i)->b=((*i)->b-(*i)->b2+(*w)->r/(*i)->r*sqrt(pow((*w)->kef_a, 2)+pow((*w)->kef_b, 2))*((*i)->b-(*w)->b)/((*w)->r+(*i)->r)+(*i)->b);
            (*i)->a2=ia2;
            (*i)->b2=ib2;
           (*w)->a=((*w)->a-(*w)->a2+(*i)->r/(*w)->r*sqrt(pow((*i)->kef_a, 2)+pow((*i)->kef_b, 2))*((*w)->a-ia2)/((*i)->r+(*w)->r)+(*w)->a);
           (*w)->b=((*w)->b-(*w)->b2+(*i)->r/(*w)->r*sqrt(pow((*i)->kef_a, 2)+pow((*i)->kef_b, 2))*((*w)->b-ib2)/((*i)->r+(*w)->r)+(*w)->b);
            (*w)->a2=wa2;
            (*w)->b2=wb2;
           qDebug()<<"INkchek";
            (*i)->kef_a=abs((*i)->a-ia2);
            (*i)->kef_b=abs((*i)->b-ib2);
            (*w)->kef_a=abs((*w)->a-wa2);
            (*w)->kef_b=abs((*w)->b-wb2);
//                while (((*i)->r+(*w)->r)>=(sqrt(pow(((*i)->a-(*w)->a), 2)+pow(((*i)->b-(*w)->b), 2))))
//                {
//                    (*i)->editab();
//                    (*w)->editab();
//                }
        }
};

class myWorkThread : public QThread
{
    Q_OBJECT
    QList<std::shared_ptr<myKrug>> *circles;
    DataBuf* buf;
public:
    bool ready=1;
    myWorkThread(QObject* obj, QList<std::shared_ptr<myKrug>> *_circles, DataBuf* _data): QThread(obj), circles(_circles), buf(_data){}
    void run() override{
        for(;;)
        {
            QDataStream out(buf->getBufferPoint(), QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_3);
            buf->getBufferPoint()->clear();
            out<<circles->size();
            emit drawSignal();
            for(auto i: *circles){
                i->editab();
                out<<i->a;
                qDebug()<<i->a;
                out<<i->b;
                out<<i->r;
            }
            int k,x;
            QDataStream in(buf->getBufferPoint(), QIODevice::ReadOnly);
            in>>k>>x;
            qDebug()<<k<<"  "<<x;
            emit sendSocket();
            if(ready){
                emit swapBuf();
                ready=0;
            }
            kchek(circles);

            msleep(40);
        }
    }
public slots:
    void socketReady(){ready=1;}
signals:
    void drawSignal();
    void sendSocket();
    void swapBuf();
};

#endif // MYWORKTHREAD_H
