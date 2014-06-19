#ifndef CHANNELATTRIBUTE_H
#define CHANNELATTRIBUTE_H

#include <QDialog>

namespace Ui {
    class CChannelAttribute;
}

class CChannelAttribute : public QDialog
{
    Q_OBJECT

public:
    explicit CChannelAttribute(QWidget *parent = 0);
    ~CChannelAttribute();

    void CANAddr( int& nAddr, bool bGet );
    void ChannelName( QString& strName, bool bGet );
    void HostIP( QString& strIP, bool bGet );
    void IPCIP( QString& strIP, bool bGet );

private:
    Ui::CChannelAttribute *ui;

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
};

#endif // CHANNELATTRIBUTE_H
