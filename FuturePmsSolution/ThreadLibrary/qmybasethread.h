#ifndef QMYBASETHREAD_H
#define QMYBASETHREAD_H

#include <Qt/QtGui>
#include <QThread>
#include <QDebug>
#include "../CommonLibrary/qcommonfunction.h"
#include "../CommonLibrary/CommonMacro.h"
#include "../CommonLibrary/CommonEnum.h"
#include "../ManipulateIniFile/qmanipulateinifile.h"
#include "../CommonLibrary/CommonDataStruct.h"
#include "../MyNetwork/qmynetwork.h"

// run( )
// The starting point for the thread.
// After calling start(), the newly created thread calls this function.
// The default implementation simply calls exec(). // event loop
// You can reimplemented this function to do other useful work.
// Returning from this method will end the execution of the thread.
class QMyBaseThread : public QThread
{
    Q_OBJECT
public:
    explicit QMyBaseThread(QObject *parent = 0);
    ~QMyBaseThread( );
    void InitializeThread( );

protected:
    virtual void InitializeSubThread( ) = 0;
    void LaunchThreadExit( );

protected:
    QManipulateIniFile      manipulateFile;
    QCommonFunction     commonFunction;
    QMyNetwork                network;
    
signals:
    void NotifyMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );

protected slots:
    void ExitThread( );
    void HandleMessage( void* pstrMsg, QManipulateIniFile::LogTypes type );
};

#endif // QMYBASETHREAD_H
