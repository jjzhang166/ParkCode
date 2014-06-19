#ifndef FTPEVENT_H
#define FTPEVENT_H

#include <QEvent>
#include <QStringList>

class CFtpEvent : public QEvent
{
public:
    typedef enum __FtpEvent {
        FtpPut = User,
    } FtpEvent;

    CFtpEvent( FtpEvent event);
    void SetParams( QStringList lstParam );
    QStringList& GetParams( );

private:
    QStringList lstParams;
};

#endif // FTPEVENT_H
