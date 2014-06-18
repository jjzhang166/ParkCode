#ifndef QDIRECORYEVENT_H
#define QDIRECORYEVENT_H

#include <QEvent>
#include <QString>

class QDirectoryEvent : public QEvent
{
public:
    typedef enum __DirectoryEventType {
        DirectoryTraverse = User
    } DirectoryEventType;

public:
    QDirectoryEvent( Type evtType );

    void SetDirectory( QString& strDir );
    QString& GetDirectory( );

private:
    QString strDirectory;
};

#endif // QDIRECORYEVENT_H
