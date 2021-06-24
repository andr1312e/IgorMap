#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <program.h>
class QThread;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(Program &program, QObject *parent = 0);
    ~Server();
public slots:
    void login();
    void jsonGet();
    void logout();
    void error();
    void jsonSend(QStringList &data);
private:
    Program* m_program;
    QByteArray *m_jsonData;
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
    QJsonObject* m_object;
    QJsonParseError* m_parseError;
    void execute(const QJsonObject &message);
    QJsonObject makeJson(QStringList &data);
};

#endif // SERVER_H
