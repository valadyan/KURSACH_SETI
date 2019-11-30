#ifndef MYKRUG_H
#define MYKRUG_H

#include <cmath>
#include <QList>
#include <memory>
#include <random>

#include <QDebug>

class myKrug
{
public:
    int a;
    int b;
    int a2;
    int b2;
    int r;
    short int kef_a;
    short int kef_b;
    int WIDTH;
    int HIGHT;
    myKrug(int radius, int width=600, int hight=600);
    myKrug(const myKrug& k);
    myKrug(myKrug&& k);
    void editab();
    QRect getRect() {return QRect(a, b, r, r);} //for ellipse func
    void downr(){a+=kef_a; b+=kef_b;}
    void downl(){a-=kef_a; b+=kef_b;}
    void upr(){a+=kef_a; b-=kef_b;}
    void upl(){a-=kef_a; b-=kef_b;}
    void up(){b-=kef_b;}
    void down(){b+=kef_b;}
    void left(){a-=kef_a;}
    void right(){a+=kef_a;}
    bool operator !=(const myKrug& k);
};



#endif // MYKRUG_H
