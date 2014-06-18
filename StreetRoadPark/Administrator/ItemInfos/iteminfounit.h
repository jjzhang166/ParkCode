#ifndef ITEMINFOUNIT_H
#define ITEMINFOUNIT_H
#include <QString>
#include <QMetaType>

//#include "ItemType.h"

class ItemInfoUnit
{
public:
    ItemInfoUnit();
    ItemInfoUnit( QString id, QString name, QString comments, QString pid, QString address );

    const QString &getId( ) const;
    const QString &getName( ) const;
    const QString &getComments( ) const;
    const QString &getPid( ) const;
    const QString &getAddress( ) const;
   // const ItemType &getItemType() const;

    void setId( QString id );
    void setName( QString name );
    void setComments( QString comments );
    void setPid(QString pid );
    void setAddress( QString address );
    void PrintInfo( )const;
   // void setItemType( ItemType itemType );

private:
    QString g_id;
    QString g_name;
    QString g_comments;
    QString g_pid; // AdminstrativeID
    QString g_address;
   // ItemType g_itemType;
};

//可以注册QVariant变体，（联合体）也可以注册函数类型，如信号 槽函数
Q_DECLARE_METATYPE( ItemInfoUnit )

#endif // ITEMINFOUNIT_H
