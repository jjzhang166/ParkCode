#include "iteminfoadmin.h"
#include <QDebug>

ItemInfoAdmin::ItemInfoAdmin()
{
}

ItemInfoAdmin::ItemInfoAdmin(QString id, QString name, QString comments, QString pid, QString type)
{
    g_id.append( id );
    g_name.append( name );
    g_comments.append( comments );
    g_pid.append( pid );
    g_type.append( type );
}

const QString &ItemInfoAdmin::getId() const
{
    return g_id;
}

const QString &ItemInfoAdmin::getName() const
{
    return g_name;
}

const QString &ItemInfoAdmin::getComments() const
{
    return g_comments;
}

const QString &ItemInfoAdmin::getPid() const
{
    return g_pid;
}

const QString &ItemInfoAdmin::getType() const
{
    return g_type;
}

void ItemInfoAdmin::setId(QString id)
{
    g_id.append( id );
}

void ItemInfoAdmin::setName(QString name)
{
    g_name.append( name );
}

void ItemInfoAdmin::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoAdmin::setPid(QString pid)
{
    g_pid.append( pid );
}

void ItemInfoAdmin::setType( QString type )
{
    g_type.append( type );
}

void ItemInfoAdmin::PrintInfo() const
{
    qDebug() << "id" << g_id;
}

