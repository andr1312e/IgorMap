#include "bMath.h"
#include <QtMath>

double CorrectPlus(double az1, double az2)
{
    double out = az1 + az2;
    if(out >= 360)
    {
        out -= 360;
    }
    if(out < 0)
    {
        out += 360;
    }
    if(out == 360)
    {
        out = 0;
    }
    return out;
}

double FindDistance3(double x, double y, double z)
{
    return double(sqrt(x * x + y * y + z * z));
}

double FindDistance3(Coor3 coor)
{
    return coor.Module();
}

double FindDistance2(double x, double y)
{
    return double(sqrt(x * x + y * y));
}

double FindDistance2(Coor2 coor)
{
    return double(coor.x * coor.x + coor.y * coor.y);
}

Coor3 ChangeSistemCoor_L2G_AzUm_Fast(Coor3 Ray, double Az, double Um)
{
    double angleY = Um * M_PI / 180; //углы в обратную сторону поворота %угол диаграммы направленности
    double angleZ = -Az * M_PI / 180; //азимут
    double cosY = cos(angleY);
    double cosZ = cos(angleZ);
    double sinY = sin(angleY);
    double sinZ = sin(angleZ);

    double x1 = Ray.x * cosY - Ray.h * sinY;
    Coor3 Out(x1 * cosZ + Ray.y * sinZ, Ray.y * cosZ - x1 * sinZ, Ray.x * sinY + Ray.h * cosY);

    return Out;
}

Coor3 Polar2Coor3(Polar pol)
{
    Coor3 coor;
    coor.h = pol.D * sin(pol.Um * M_PI / 180);
    double flat = pol.D * cos(pol.Um * M_PI / 180);
    coor.x = flat * cos(pol.Az * M_PI / 180);
    coor.y = flat * sin(pol.Az * M_PI / 180);

    return coor;
}

kta ktaFirst2ktaSecond(kta Kta_f)
{
    kta Kta_s = Kta_f;
    double Rsign = 6370000.0 / (1 - 6370000.0 / 8500000.0); // радиус по которому распространяется сигнал // м
    double angle_arc = Kta_f.Pol.D / (2 * M_PI * Rsign) * 360;
//    Kta_s.D = Rsign * sqrt(2 * (1 - cos(angle_arc * M_PI / 180)));
    Kta_s.Pol.D = 2 * Rsign * sin(Kta_f.Pol.D / (2 * Rsign));
    double angle = (180 - angle_arc) / 2;
    Kta_s.Pol.Um = Kta_f.Pol.Um - (90 - angle);
//    double angle_vr = Kta_f.Um - angle_arc;
//    Kta_s.Vr = Kta_f.Vr * cos(fabs(angle_vr - Kta_s.Um) * M_PI / 180);

    return Kta_s;
}

Polar Coor2Polar(Coor3 coor)
{
    Polar pol;
    pol.D = FindDistance3(coor);
    pol.Az = CorrectPlus(atan2(coor.y, coor.x) * 180 / M_PI, 360);
    pol.Um = atan2(coor.h, FindDistance2(coor.x, coor.y)) * 180 / M_PI;

    return pol;
}

bool Conversion::CheckDifZone(double dist, double angle, QPointF Gauss_point)
{
    bool ansver = false;
    double distY = fmod(Gauss_point.y(), 1000000);
    double dist_min = 165000;
    if(angle <= 180)
    {
        if(distY + dist * sin(angle / 180 * M_PI) >= 1000000 - dist_min)
        {
            ansver = true;
        }
    }
    else
    {
        if(distY + dist * sin(angle / 180 * M_PI) <= dist_min)
        {
            ansver = true;
        }
    }
    if(!ansver)
    {
        QPointF new_point = GaussToGeo(QPointF(Gauss_point.x() + dist * cos(angle / 180 * M_PI), Gauss_point.y() + dist * sin(angle / 180 * M_PI)));
        QPointF new_new_point = GeoToGauss(new_point.x(), new_point.y());
        if(qFloor(new_new_point.y() / 1000000) != qFloor(Gauss_point.y() / 1000000))
        {
            ansver = true;
        }
    }

    return ansver;
}

void Conversion::RemovePointToNearZone(double *dist, double *angle, QPointF *gen_point_loc, double pointY)
{
    QPointF gen_point_loc2 = *gen_point_loc;
    double step = 165000;
    QPointF point_gradus = QPointF(0,0);
    while(step >= 0.01)
    {
        double distX = step * cos(*angle / 180 * M_PI);
        double distY = step * sin(*angle / 180 * M_PI);
        QPointF gen_point_loc3 = QPointF(gen_point_loc2.x() + distX, gen_point_loc2.y() + distY);
        point_gradus = GaussToGeo(QPointF(gen_point_loc3.x(), gen_point_loc3.y()));
        QPointF point_new_gen = GeoToGauss(point_gradus.x(), point_gradus.y());
        if(qFloor(gen_point_loc2.y() / 1000000) != qFloor(point_new_gen.y() / 1000000))
        {
            step /= 2;
        }
        else
        {
            gen_point_loc2 = gen_point_loc3;
        }
    }
    *dist -= sqrt(pow(gen_point_loc2.x() - (*gen_point_loc).x(), 2) + pow(gen_point_loc2.y() - (*gen_point_loc).y(), 2));
    *gen_point_loc = gen_point_loc2;
    (*gen_point_loc).ry() = qFloor(gen_point_loc2.y() / 1000000) * 1000000 + 1000000 - fmod(gen_point_loc2.y(), 1000000);
    if(pointY >= 0)
    {
        (*gen_point_loc).ry() += 1000000;
        jump_angle_now = 3 * sin(point_gradus.x() / 180 * M_PI) * 2;
    }
    else
    {
        (*gen_point_loc).ry() -= 1000000;
        jump_angle_now = -3 * sin(point_gradus.x() / 180 * M_PI) * 2;
    }
    *angle = CorrectPlus(*angle, jump_angle_now);
}

QPointF Conversion::Loc2Gauss(QPointF point)
{
    QPointF gen_point_loc = Gen_point_gauss;
    double dist = sqrt(point.x() * point.x() + point.y() * point.y());
    double angle = CorrectPlus(atan2(point.y(), point.x()) * 180 / M_PI, 360);
    while(CheckDifZone(dist, angle, gen_point_loc))
    {
        RemovePointToNearZone(&dist, &angle, &gen_point_loc, point.y());
    }
    gen_point_loc = QPointF(gen_point_loc.x() + dist * cos(angle / 180 * M_PI), gen_point_loc.y() + dist * sin(angle / 180 * M_PI));

    return QPointF(gen_point_loc.x(), gen_point_loc.y());
}

bool Conversion::Loc2GaussCheck(QPointF point)
{
    bool in3zone = true;
    QPointF gen_point_loc = Gen_point_gauss;
    double dist = sqrt(point.x() * point.x() + point.y() * point.y());
    double angle = CorrectPlus(atan2(point.y(), point.x()) * 180 / M_PI, 360);
    int count = 0;
    while(CheckDifZone(dist, angle, gen_point_loc))
    {
        if(count > 0)
        {
            in3zone = false;
            break;
        }
        RemovePointToNearZone(&dist, &angle, &gen_point_loc, point.y());
        count++;
    }

    return in3zone;
}

QPointF Conversion::Gauss2Loc(QPointF ver)
{
    QPointF point_loc;
    if(qFloor(ver.y() / 1000000) != qFloor(Gen_point_gauss.y() / 1000000))
    {
        double mode = -1;
        if(qFloor(ver.y() / 1000000) > qFloor(Gen_point_gauss.y() / 1000000))
        {
            mode = 1;
        }
        QPointF point = QPointF(Gen_point_grad.x(), Gen_point_grad.y() + 3 * mode);
        double sign_angle = DeltaAngle(ver, point, mode);
        double step = 5;
        while(step > 0.000001)
        {
            QPointF point_new = QPointF(point.x() + sign_angle * step, point.y());
            double sign_angle_new = DeltaAngle(ver, point_new, mode);
            if(sign_angle_new == sign_angle)
            {
                point = point_new;
            }
            else
            {
                step /= 2;
            }
        }
        QPointF point_gauss1 = GeoToGauss(point.x(), point.y());
        QPointF point_gauss2 = QPointF(point_gauss1.x(), (qFloor(point_gauss1.y() / 1000000) - 1) * 1000000 + 1000000 - fmod(point_gauss1.y(), 1000000));
        if(mode == 1)
        {
            QPointF poi = QPointF(point_gauss1.x(), point_gauss1.y());
            point_gauss1 = QPointF(point_gauss2.x(), point_gauss2.y());
            point_gauss2 = poi;
        }
        double angle2 = CorrectPlus(atan2(point_gauss1.y() - Gen_point_gauss.y(), point_gauss1.x() - Gen_point_gauss.x()) * 180 / M_PI, 360);
        double dist = sqrt(pow(point_gauss2.x() - ver.x(), 2) + pow(point_gauss2.y() - ver.y(), 2)) + sqrt(pow(point_gauss1.x() - Gen_point_gauss.x(), 2) + pow(point_gauss1.y() - Gen_point_gauss.y(), 2));
        point_loc = QPointF(dist * cos(angle2 / 180 * M_PI), dist * sin(angle2 / 180 * M_PI));
    }
    else
    {
        point_loc = QPointF(ver.x() - Gen_point_gauss.x(), ver.y() - Gen_point_gauss.y());
    }

    return point_loc;
}

double Conversion::DeltaAngle(QPointF ver, QPointF point_gradus, double mode)
{
    QPointF point_gauss1 = GeoToGauss(point_gradus.x(), point_gradus.y());
    QPointF point_gauss2 = QPointF(point_gauss1.x(), (qFloor(point_gauss1.y() / 1000000) - 1) * 1000000 + 1000000 - fmod(point_gauss1.y(), 1000000));
    if(mode == 1)
    {
        QPointF poi = QPointF(point_gauss1.x(), point_gauss1.y());
        point_gauss1 = QPointF(point_gauss2.x(), point_gauss2.y());
        point_gauss2 = poi;
    }
    double angle1 = CorrectPlus(atan2(point_gauss2.y() - ver.y(), point_gauss2.x() - ver.x()) * 180 / M_PI, 360);
    double correct_angle = 3 * sin(point_gradus.x() / 180 * M_PI) * 2;
    double angle2 = CorrectPlus(angle1, - mode * correct_angle);
    double angle_real = CorrectPlus(atan2(Gen_point_gauss.y() - point_gauss1.y(), Gen_point_gauss.x() - point_gauss1.x()) * 180 / M_PI, 360);

    return - mode * sign(angle2 - angle_real);
}

QPointF Conversion::GeoToGauss(double B, double L)
{
    B = B * M_PI/180.0;

    double n = trunc((6 + L) / 6);
    double l = (L - (3 + 6 * (n - 1))) / 57.29577951, l2 = pow(l, 2);
    double sin2B = pow(sin(B), 2), sin4B = pow(sin(B), 4), sin6B = pow(sin(B), 6);

    double x = 6367558.4968 * B  - sin(2*B) * (16002.89 + 66.9607 * sin2B + 0.3515 * sin4B
                                 - l2 * (1594561.25 + 5336.535 * sin2B + 26.79 * sin4B + 0.149 * sin6B
                                 + l2 * (672483.4 - 811219.9 * sin2B + 5420 * sin4B - 10.6 * sin6B
                                 + l2 * (278194 - 830174 * sin2B + 572434 * sin4B - 16010 * sin6B
                                 + l2 * (109500 - 574700 * sin2B + 863700 * sin4B - 398699 * sin6B)))));

    double y = (5.0 + 10.0 * n) * pow(10.0, 5) + l * cos(B)  * (6378245 + 21346.1415 * sin2B + 107.159 * sin4B + 0.5977 * sin6B
                                               + l2 * (1070204.16 - 2136826.66 * sin2B + 17.98 * sin4B - 11.99 * sin6B
                                               + l2 * (270806 - 1523417 * sin2B + 1327645 * sin4B - 21701 * sin6B
                                               + l2 * (79690 - 866190 * sin2B + 1730360 * sin4B - 945460 * sin6B))));

    return QPointF(x,y);
}

QPointF Conversion::GaussToGeo(QPointF point)
{
    double n = trunc(point.y() * pow(10.0, -6));
    double betta = point.x() / 6367558.4968;

    double B0 = betta + sin(2 * betta) * (0.00252588685 - 0.0000149186 * pow(sin(betta), 2) + 0.00000011904 * pow(sin(betta), 4));
    double sin2B0 = pow(sin(B0), 2), sin4B0 = pow(sin(B0), 4), sin6B0 = pow(sin(B0), 6);
    double z0 = (point.y() - (10 * n + 5) * pow(10.0, 5)) / (6378245 * cos(B0)), z02 = pow(z0, 2);

    double dB = - z02 * sin(2 * B0) * (0.251684631 - 0.003369263 * sin2B0 + 0.000011276 * sin4B0
                - z02 * (0.10500614 - 0.04559916 * sin2B0 + 0.00228901 * sin4B0 - 0.00002987 * sin6B0
                - z02 * (0.042858 - 0.025318 * sin2B0 + 0.014346 * sin4B0 - 0.001264 * sin6B0
                - z02 * (0.01672 - 0.0063 * sin2B0 + 0.01188 * sin4B0 - 0.00328 * sin6B0))));
    double B1 = B0 + dB;

    double l = z0 * (1 - 0.0033467108 * sin2B0 - 0.0000056002 * sin4B0 - 0.0000000187 * sin6B0
               - z02 * (0.16778975 + 0.16273586 * sin2B0 - 0.0005249 * sin4B0 - 0.00000846 * sin6B0
               - z02 * (0.0420025 + 0.1487407 * sin2B0 + 0.005942 * sin4B0 - 0.0000150 * sin6B0
               - z02 * (0.01225 + 0.09477 * sin2B0 + 0.03282 * sin4B0 - 0.00034 * sin6B0
               - z02 * (0.0038 + 0.0524 * sin2B0 + 0.0482 * sin4B0 + 0.0032 * sin6B0)))));
    double L1 = 6 * (n - 0.5) / 57.29577951 + l;

    B1 = B1/M_PI * 180;
    L1 = L1/M_PI * 180;
    //qDebug() << B1/M_PI * 180 << L1/M_PI*180;
    return QPointF(B1,L1);
}

double Conversion::CorrectPlus(double az1, double az2)
{
    double out = az1 + az2;
    if(out >= 360)
    {
        out -= 360;
    }
    if(out < 0)
    {
        out += 360;
    }
    if(out == 360)
    {
        out = 0;
    }
    return out;
}

float Conversion::CorrectPlus(float az1, float az2)
{
    float out = az1 + az2;
    if(out >= 360)
    {
        out -= 360;
    }
    if(out < 0)
    {
        out += 360;
    }
    if(out == 360)
    {
        out = 0;
    }
    return out;
}

double Conversion::sign(double A)
{
    if(A < 0)
    {
        return (-1);
    }
    else
    {
        return (1);
    }
}

quint32 Conversion::DegToSec(float deg)
{
    return (deg * 3600.);
}

float Conversion::SecToDeg(quint32 sec)
{
    return (sec / 3600.);
}

