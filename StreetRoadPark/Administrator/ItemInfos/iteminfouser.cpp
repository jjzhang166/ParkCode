#include "iteminfouser.h"

ItemInfoUser::ItemInfoUser()
{
}

const quint64 &ItemInfoUser::getId() const
{
    return g_id;
}

const QString &ItemInfoUser::getName() const
{
    return g_name;
}

const QString &ItemInfoUser::getComments() const
{
    return g_comments;
}

const quint64 &ItemInfoUser::getPid() const
{
    return g_pid;
}

const QString &ItemInfoUser::getPassword() const
{
    return g_password;
}

void ItemInfoUser::setId(quint64 id)
{
    g_id = id;
}

void ItemInfoUser::setName(QString name)
{
    g_name.append( name );
}

void ItemInfoUser::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoUser::setPid(quint64 pid)
{
    g_pid = pid;
}

void ItemInfoUser::setPassword(QString password)
{
    g_password.append( password );
}
