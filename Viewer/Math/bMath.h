#ifndef STRUCT_H
#define STRUCT_H
#include <math.h>
#include <QPointF>

const qreal Radian = M_PI / 180.;

struct Coor2
{
    double x;
    double y;
    Coor2(): x(0), y(0) {}
    Coor2(double X, double Y): x(X), y(Y) {}
};

struct Coor3
{
    double x;
    double y;
    double h;
    Coor3(): x(0), y(0), h(0) {}
    Coor3(double X, double Y, double H): x(X), y(Y), h(H) {}
    Coor3 operator+(Coor3 coor) {return Coor3(x + coor.x, y + coor.y, h + coor.h);}
    Coor3 operator-(Coor3 coor) {return Coor3(x - coor.x, y - coor.y, h - coor.h);}
    Coor3 operator*(Coor3 coor) {return Coor3(y * coor.h - h * coor.y, x * coor.h - h * coor.x, x * coor.y - y * coor.x);} // векторное произведение
    Coor3 operator*(double k) {return Coor3(x * k, y * k, h * k);}
    Coor3 operator/(double k) {return Coor3(x / k, y / k, h / k);}
    double Module() {return sqrt(x * x + y * y + h * h);}
};

struct Polar2
{
    double Az;
    double Um;
    Polar2(): Az(0), Um(0) {}
    Polar2(double az, double um): Az(az), Um(um) {}
    Polar2& operator= (const Polar2 &polar)
    {
        Az = polar.Az;
        Um = polar.Um;

        return *this;
    }
};

struct Polar
{
    double D;
    double Az;
    double Um;
    Polar(): D(0), Az(0), Um(0) {}
    Polar(double d, double az, double um):  D(d), Az(az), Um(um) {}
    Polar(double d, Polar2 pol): D(d), Az(pol.Az), Um(pol.Um) {}
};

struct kta
{
    double time;
    double Amp;
    Polar Pol;
    double Vr;
    kta(): time(0), Amp(0), Pol(), Vr(0) {}
    kta(double Time, double amp, Polar pol, double vr): time(Time), Amp(amp), Pol(pol), Vr(vr) {}
};

struct Point {
    double x;
    double y;
    Point(): x(0), y(0) {}
    Point(double X, double Y): x(X), y(Y) {}
    Point operator+(Point point) {return Point(x + point.x, y + point.y);}
    Point operator-(Point point) {return Point(x - point.x, y - point.y);}
    Point operator*(double k) {return Point(x * k, y * k);}
    Point operator/(double k) {return Point(x / k, y / k);}
    double Module() {return sqrt(x * x + y * y);} // модуль (длина)
};

Coor3 Polar2Coor3(Polar pol); // перевод из Polar в Coor3
kta ktaFirst2ktaSecond(kta Kta_f); // перевод из кта первички в кта вторички
Polar Coor2Polar(Coor3 coor);
Polar2 Coor2Polar2(Coor3 coor);
Coor3 SistemCoor_L2G_fast(Coor3 Ray, Polar2 inc, Polar2 ant);
double CorrectPlus(double az1, double az2);
double FindDistance3(double x, double y, double z);
double FindDistance3(Coor3 coor);
double FindDistance2(double x, double y);
double FindDistance2(Coor2 coor);

class Conversion
{
public:
    QPointF Gen_point_grad = QPointF(0,0);
    QPointF Gen_point_gauss = QPointF(0,0);
    double jump_angle_now = 0;

    Conversion() {}
    QPointF Loc2Gauss(QPointF point);
    bool Loc2GaussCheck(QPointF point);
    QPointF Gauss2Loc(QPointF ver);
    void RemovePointToNearZone(double* dist, double* angle, QPointF* gen_point_loc, double pointY);
    bool CheckDifZone(double dist, double angle, QPointF Gauss_point);
    double DeltaAngle(QPointF ver, QPointF point_gradus, double mode);

    QPointF GeoToGauss(double B, double L);
    QPointF GaussToGeo(QPointF point);
    float CorrectPlus(float az1, float az2);
    double CorrectPlus(double az1, double az2);
    double sign(double A);
    quint32 DegToSec(float deg);
    float SecToDeg(quint32 sec);

    QPointF Gauss2LocUpdate(QPointF ver);
};

#endif // STRUCT_H
