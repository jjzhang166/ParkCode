#ifndef QDIRECTORYTHREAD_H
#define QDIRECTORYTHREAD_H

#include <QThread>
#include "qdirectoryevent.h"
#include <QStringList>

class QDirectoryThread : public QThread
{
    Q_OBJECT
public:
    static QDirectoryThread* GetInstance( );
    void PostDirectoryTraverse( QString& strDir );

protected:
    void run( );
    void customEvent( QEvent *e );

private:
    explicit QDirectoryThread(QObject *parent = 0);
    inline void PostEvent( QDirectoryEvent* pEvent );
    void TraverseEvent( QDirectoryEvent* pEvent  );
    void Traverse( QString& strDir );

private:
    static QDirectoryThread* pThreadInstance;
    QStringList lstFileType;
    
signals:
    
public slots:
    
};

#endif // QDIRECTORYTHREAD_H
