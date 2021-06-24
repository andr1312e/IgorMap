//#include "rlscontroller.h"
//#include <ConfigurationManager/cfgmanager.h>

/*RLSController::RLSController()
{
}

void RLSController::assignTrackToKTAMark(KTAMark *mark) {
    AssignTrackMessage msg;
    msg.Amp = mark->amp;
    msg.E = mark->pointAngle;
    msg.Az = mark->az;
    msg.D = mark->dist;
    msg.PlotType = mark->type;
    msg.skoEvaluation = mark->limit;
    msg.Vr = mark->rSpeed;

    QByteArray datagram;
    QUdpSocket socket;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << qint8(0);
    out << quint8(ASSIGN_TRACK_MESSAGE);
    out.writeRawData((char*) &msg, sizeof(AssignTrackMessage));
    out.device()->seek(0);
    out << quint8(datagram.size() - sizeof(quint8));
    socket.writeDatagram(datagram, QHostAddress::LocalHost, 2424);
    socket.flush();
}*/
