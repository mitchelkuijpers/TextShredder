#ifndef CLIENTREPRESENTATION_H
#define CLIENTREPRESENTATION_H

#include <QObject>
#include "../textshredder_synchronization_lib/textshredderconnection.h"

class ClientRepresentation : public QObject
{
    Q_OBJECT
public:
    explicit ClientRepresentation(QObject *parent = 0);

private:


signals:

public slots:

};

#endif // CLIENTREPRESENTATION_H
