#ifndef ITEMINFORECEIVER_H
#define ITEMINFORECEIVER_H
#include <QString>
#include <QMetaType>


class ItemInfoReceiver
{
public:
    ItemInfoReceiver();
    ItemInfoReceiver( QString pid, QString name, QString id, quint8 channelID, QString comments, QString parkReceiverID );

    const QString &getId( ) const;
    const QString &getName( ) const;
    const quint8 &getChannelID() const;
    const QString &getComments( ) const;
    const QString &getParkReceiverID( ) const;
    const QString &getPid( ) const;

    void setId( QString id );
    void setName( QString name );
    void setChannelID( quint8 channelID );
    void setComments( QString comments );
    void setParkReceiverID( QString parkReceiverID );
    void setPid(QString pid );
    void PrintInfo( )const;

private:
    QString g_pid; // ParkID
    QString g_name;
    QString g_id;
    quint8 g_channelID;
    QString g_comments;
    QString g_parkReceiverID;
};
Q_DECLARE_METATYPE( ItemInfoReceiver )

#endif // ITEMINFORECEIVER_H
