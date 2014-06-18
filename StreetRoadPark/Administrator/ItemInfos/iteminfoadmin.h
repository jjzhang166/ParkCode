#ifndef ITEMINFOADMIN_H
#define ITEMINFOADMIN_H
#include <QString>
#include <QMetaType>

//#include "ItemType.h"

typedef enum __AdminType
{
    Province,
    City,
    District
} AdminType;

class ItemInfoAdmin
{
public:
    ItemInfoAdmin();
    ItemInfoAdmin( QString id, QString name, QString comments, QString pid, QString type );

    const QString &getId( ) const;
    const QString &getName( ) const;
    const QString &getComments( ) const;
    const QString &getPid( ) const;
    const QString &getType( ) const;
    //const ItemType &getItemType() const;

    void setId( QString id );
    void setName( QString name );
    void setComments( QString comments );
    void setPid(QString pid );
    void setType(QString type );
    void PrintInfo( )const;
    //void setItemType( ItemType itemType );

private:
    QString g_id;
    QString g_name;
    QString g_comments;
    QString g_pid;
    QString g_type;

    //ItemType g_itemType;
};

//可以注册QVariant变体，（联合体）也可以注册函数类型，如信号 槽函数
Q_DECLARE_METATYPE( ItemInfoAdmin )

#endif // ITEMINFOADMIN_H
