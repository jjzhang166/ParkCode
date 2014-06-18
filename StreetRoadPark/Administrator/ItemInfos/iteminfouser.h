#ifndef ITEMINFOUSER_H
#define ITEMINFOUSER_H

#include <QString>
#include <QMetaType>

class ItemInfoUser
{
public:
    ItemInfoUser();

    const quint64 &getId( ) const;
    const QString &getName( ) const;
    const QString &getComments( ) const;
    const quint64 &getPid( ) const;
    const QString &getPassword( ) const;

    void setId( quint64 id );
    void setName( QString name );
    void setComments( QString comments );
    void setPid( quint64 pid );
    void setPassword( QString password );

private:
    quint64 g_id;
    QString g_name;
    QString g_comments;
    quint64 g_pid; // groupID;
    QString g_password;
};

Q_DECLARE_METATYPE( ItemInfoUser )

#endif // ITEMINFOUSER_H
