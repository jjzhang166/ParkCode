#include "iteminfogroup.h"

ItemInfoGroup::ItemInfoGroup()
{
}

const quint64 &ItemInfoGroup::getId() const
{
    return g_id;
}

const QString &ItemInfoGroup::getName() const
{
    return g_name;
}

const QString &ItemInfoGroup::getComments() const
{
    return g_comments;
}

const quint64 &ItemInfoGroup::getParentID() const
{
    return g_parentID;
}

const quint64 &ItemInfoGroup::getGroupRight() const
{
    return g_groupRight;
}

const QString &ItemInfoGroup::getPid() const
{
    return g_pid;
}

void ItemInfoGroup::setId(quint64 id)
{
    g_id = id;
}

void ItemInfoGroup::setName(QString name)
{
    g_name.append( name );
}

void ItemInfoGroup::setComments(QString comments)
{
    g_comments.append( comments );
}

void ItemInfoGroup::setParentID(quint64 parentID)
{
    g_parentID = parentID;
}

void ItemInfoGroup::setGroupRight(quint64 groupRight)
{
    g_groupRight = groupRight;
}

void ItemInfoGroup::setPid(QString pid)
{
    g_pid.append( pid ); //
}
