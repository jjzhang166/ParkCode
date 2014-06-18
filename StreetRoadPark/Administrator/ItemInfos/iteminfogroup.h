#ifndef ITEMINFOGROUP_H
#define ITEMINFOGROUP_H

#include <QString>
#include <QMetaType>

class ItemInfoGroup
{
public:
    ItemInfoGroup();
    const quint64 &getId( ) const;
    const QString &getName( ) const;
    const QString &getComments( ) const;
    const quint64 &getParentID( ) const;
    const quint64 &getGroupRight( ) const;
    const QString &getPid( ) const;

    void setId( quint64 id );
    void setName( QString name );
    void setComments( QString comments );
    void setParentID( quint64 parentID );
    void setGroupRight( quint64 groupRight );
    void setPid( QString pid );

private:
    quint64 g_id;
    QString g_name;
    QString g_comments;
    quint64 g_parentID; // like id
    quint64 g_groupRight;
    QString g_pid; // UnitID
};

Q_DECLARE_METATYPE( ItemInfoGroup )

#endif // ITEMINFOGROUP_H
