#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <QMetaType>
#include <QString>

typedef enum __ItemType
{
    AdminItem,
    UnitItem,
    ParkItem,
    ReceiverItem,
    DetectorItem,
    GroupItem,
    UserItem
} ItemType;

//Q_DECLARE_METATYPE( ItemType )

#endif // ITEMTYPE_H
