#ifndef LOCKABLE_H
#define LOCKABLE_H

#include <QObject>

class Lockable : public QObject
{
    Q_OBJECT
public:
    explicit Lockable(QObject *parent = 0);

signals:

public slots:

};

#endif // LOCKABLE_H
