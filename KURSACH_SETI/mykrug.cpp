#include "mykrug.h"
#include<QDebug>
myKrug::myKrug(int radius, int width, int hight)
{
    HIGHT=hight;
    WIDTH=width;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(radius, WIDTH-radius);
    a=dist(mt);
    std::uniform_real_distribution<double> dist2(radius, HIGHT-radius);
    b=dist2(mt);

    b2=1; a2=1;
    r=radius;
    kef_a=1;
    kef_b=1;
}

myKrug::myKrug(const myKrug& k){
    HIGHT=k.HIGHT;
    WIDTH=k.WIDTH;
    a=k.a;
    b=k.b;
    b2=1; a2=1;
    r=k.r;
    kef_a=1;
    kef_b=1;
}

bool myKrug::operator !=(const myKrug& k){
    return (a!=k.a && b!=k.b)? 1:0;
}

//myKrug::myKrug(myKrug&& k){
//    HIGHT=k.HIGHT;
//    WIDTH=k.WIDTH;
//    a=k.a;
//    b=k.b;
//    b2=1; a2=1;
//    r=k.r;
//    kef_a=1;
//    kef_b=1;
//}

void myKrug::editab()
{
 if ((a>a2) && (b>b2) && !((b>=WIDTH-r) || (a>=HIGHT-r)) && !((b>=WIDTH-r) && (a>=HIGHT-r)))
  {
    a2=a;
    b2=b;
    downr();

  }
 if ((a>a2) && (b<b2) && !((b<=r) || (a>=HIGHT-r)) && !((b<=r) && (a>=HIGHT-r)))
  {
    a2=a;
    b2=b;
    upr();

  }
 if ((a<a2) && (b<b2) && !((b<=r) || (a<=r)) && !((b<=r) && (a<=r)))
  {
    a2=a;
    b2=b;
    upl();

  }
 if ((a<a2) && (b>b2) && !((a<=r) || (b>=WIDTH-r)) && !((b>=WIDTH-r) && (a<=r)))
  {
    a2=a;
    b2=b;
    downl();

  }
if ((a>a2) && (b==b2) && (a<=HIGHT-r))
  {
    a2=a;
    right();

  }
 if ((a<a2) && (b==b2) && (a>=r))
  {
    a2=a;
    left();

  }
 if ((b>b2) && (a==a2) && (b<=HIGHT-r))
  {
    b2=b;
    down();

  }
 if ((b<b2) && (a==a2) && (b>=r))
  {
    b2=b;
    up();

  }
   if ((b>b2) && (a==a2) && (b>=HIGHT-r))
  {
    b2=b;
    up();

  }
   if ((b<b2) && (a==a2) && (b<=r))
  {
    b2=b;
    down();

  }
  if ((a<a2) && (b==b2) && (a<=r))
  {
    a2=a;
    right();

  }
 if ((a>a2) && (b==b2) && (a>=HIGHT-r))
  {
    a2=a;
    left();

  }
  if (((b>=WIDTH-r) && (a<a2)) || ((a>=HIGHT-r) && (b<b2)))
  {
    a2=a;
    b2=b;
    upl();

  }
  if (((b>=WIDTH-r) && (a>a2)) || ((a<=r) && (b<b2)))
  {
    a2=a;
    b2=b;
    upr();

  }
  if (((b<=r) && (a<a2)) || ((a>=HIGHT-r) && (b>b2)))
  {
    a2=a;
    b2=b;
    downl();

  }
  if (((b<=r) && (a>a2)) || ((a<=r) && (b>b2)))
  {
    a2=a;
    b2=b;
    downr();

  }

 if ((b>=WIDTH-r) && (a>=HIGHT-r))
  {
    a2=a;
    b2=b;
    upl();

  }
 if ((b>=WIDTH-r) && (a<=r))
  {
    a2=a;
    b2=b;
    upr();

  }
 if ((b<=r) && (a<=r))
  {
    a2=a;
    b2=b;
    downr();

  }
 if ((b<=r) && (a>=HIGHT-r))
  {
    a2=a;
    b2=b;
    downl();

  }
}
