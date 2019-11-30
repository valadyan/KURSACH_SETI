#ifndef DATABUF_H
#define DATABUF_H

#include <QByteArray>
#include <QObject>
#include <memory>
#include <QDebug>

class DataBuf: public QObject
{Q_OBJECT
    std::shared_ptr<QByteArray> buffers1/*{std::shared_ptr<QByteArray>(),std::shared_ptr<QByteArray>()}*/;
    std::shared_ptr<QByteArray> buffers2;
    std::shared_ptr<std::shared_ptr<QByteArray>> current_/*&buffers_*/;
    std::shared_ptr<std::shared_ptr<QByteArray>> next_/*&(buffers_+1)*/;
    void swap() {
      std::shared_ptr<std::shared_ptr<QByteArray>> temp = current_;
      current_ = next_;
      next_ = temp;
    }
public:
    explicit DataBuf()/*:current_(&buffers_[0]), next_(&buffers_[1])*/{
        buffers1=std::shared_ptr<QByteArray>(new QByteArray());
        buffers2=std::shared_ptr<QByteArray>(new QByteArray());
        current_= std::shared_ptr<std::shared_ptr<QByteArray>>(new std::shared_ptr<QByteArray>(buffers1.get()));
        next_=std::shared_ptr<std::shared_ptr<QByteArray>>(new std::shared_ptr<QByteArray>(buffers2.get()));
    }
    QByteArray getBuffer() { return **current_; }//for socket
    QByteArray* getBufferPoint(){ return (*current_).get(); }//for thread
public slots:
    void swapSlot(){swap();qDebug()<<"swaped";}
};

//class DataBuf: public QObject
//{Q_OBJECT
//    QByteArray* buffers_/*{std::shared_ptr<QByteArray>(),std::shared_ptr<QByteArray>()}*/;
//    QByteArray** current_/*{&buffers_[0]}*/;
//    QByteArray** next_/*{&buffers_[1]}*/;
//    void swap() {
//      QByteArray** temp = current_;
//      current_ = next_;
//      next_ = temp;
//    }
//public:
//    explicit DataBuf():current_(&buffers_), next_(&(buffers_+1)){
//        buffers_=new QByteArray[2];
//        buffers_[0]= QByteArray();
//        buffers_[1]= QByteArray();
////        current_=&buffers_;
////        next_=&(buffers_+1);
//    }
//    QByteArray getBuffer() { return **current_; }
//    QByteArray* getBufferPoint(){ return *current_; }
//public slots:
//    void swapSlot(){swap();}
//};


#endif // DATABUF_H
