#ifndef DBHEARTBEAT_H
#define DBHEARTBEAT_H

#include <QThread>
#include <QEvent>

class CDbHeartbeat : public QThread
{
    Q_OBJECT
public:
    static CDbHeartbeat* GetInstance( );
    void PostSql( QString& strSql );

protected:
    void run( );
    void customEvent( QEvent* e);

private:
    void ExecSql( QString& strSql );

private:
    explicit CDbHeartbeat(QObject *parent = 0);
    static CDbHeartbeat* pThreadInstance;

    
signals:
    
public slots:
    
};

#endif // DBHEARTBEAT_H
