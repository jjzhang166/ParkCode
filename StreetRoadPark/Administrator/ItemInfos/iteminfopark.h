#ifndef ITEMINFOPARK_H
#define ITEMINFOPARK_H

#include <QString>
#include <QMetaType>


class ItemInfoPark
{
public:
    ItemInfoPark();
    ItemInfoPark( QString id, QString name, quint16 space, quint16 usedSpace,
                  QString selfNumber, QString comments, QString parkParentID, QString pid);

    const QString &getId( ) const;
    const QString &getName( ) const;
    const quint16 &getSpace( ) const;
    const quint16 &getUsedSpace( ) const;
    const QString &getSelfNumber( ) const;
    const QString &getComments( ) const;
    const QString &getParkParentID( ) const;
    const QString &getPid( ) const;  

    void setId( QString id );
    void setName( QString name );
    void setSpace( quint16 space );
    void setUsedSpace( quint16 userdSpace );
    void setSelfNumber( QString selfNumber );
    void setComments( QString comments );
    void setParkParentID( QString parkParentID );
    void setPid(QString pid );
    void PrintInfo( )const;

private:
    QString g_id;
    QString g_name;

    quint16 g_space;
    quint16 g_usedSpace;
    QString g_selfNumber;
    QString g_comments;
    QString g_parkParentID;
    QString g_pid; // UnitID
   // ItemType g_itemType;
};
Q_DECLARE_METATYPE( ItemInfoPark )

#endif // ITEMINFOPARK_H
