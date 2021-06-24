#ifndef DETECTIONSECTORWIDGET_H
#define DETECTIONSECTORWIDGET_H

#include "basewidget.h"

class DetectionSectorWidget : public BaseWidget
{
    Q_OBJECT

public:
    DetectionSectorWidget(BaseWidget *parent = 0);
    virtual ~DetectionSectorWidget();
    void Init();

};

#endif // DETECTIONSECTORWIDGET_H
