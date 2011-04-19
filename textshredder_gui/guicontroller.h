#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>

class GuiController : public QObject
{
    Q_OBJECT
public:
    explicit GuiController(QObject *parent = 0);

signals:

public slots:

};

#endif // GUICONTROLLER_H
