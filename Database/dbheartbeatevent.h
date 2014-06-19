#ifndef DBHEARTBEATEVENT_H
#define DBHEARTBEATEVENT_H

#include <QEvent>
#include <QString>

class CDbHeartbeatEvent : public QEvent
{
public:
    typedef enum __SqlHB {
        SqlData = User
    } SqlHB;

public:
    CDbHeartbeatEvent( QString& strDbSql, SqlHB event );
    QString& GetSql( );
private:
    QString strSql;
};

#endif // DBHEARTBEATEVENT_H
