#ifndef PATCHABLE_H
#define PATCHABLE_H

#include <QObject>

class Patchable : public QObject
{
    Q_OBJECT
public:
    explicit Patchable(QObject *parent = 0);

signals:

public slots:

};

#endif // PATCHABLE_H
