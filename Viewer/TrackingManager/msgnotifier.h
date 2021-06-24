#ifndef MSGNOTIFIER_H
#define MSGNOTIFIER_H

#include <QObject>
#include <QTimer>


class DataModelNotifier : public QObject
{
    Q_OBJECT

public:
    DataModelNotifier(QObject *parent = 0);
    void addTrack(int id);
    void deleteTrack(int id);
    void updateTrackInfo(int id);
    void cleanModel();
    void updateIndicator();

signals:
    void newTrack(int id);
    void eraseTrack(int id);
    void trackMarkUpdated(int id);
    void modelCleaned();
    void onUpdateIndicator();

};

#endif // MSGNOTIFIER_H
