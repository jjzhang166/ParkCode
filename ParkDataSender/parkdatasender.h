#ifndef PARKDATASENDER_H
#define PARKDATASENDER_H

#include <QThread>

class CParkDataSender : public QThread
{
    Q_OBJECT
public:
    explicit CParkDataSender(QObject *parent = 0);

protected:
    void run( );

signals:

public slots:

};

#endif // PARKDATASENDER_H
