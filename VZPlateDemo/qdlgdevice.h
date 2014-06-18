#ifndef QDLGDEVICE_H
#define QDLGDEVICE_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class QDlgDevice;
}

class QDlgDevice : public QDialog
{
    Q_OBJECT
    
public:
    explicit QDlgDevice(QWidget *parent = 0);
    ~QDlgDevice();

    int GetDeviceIndex( );
    void AddDevice( QStringList& lstDevice );
    
private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::QDlgDevice *ui;
    int nDeviceIndex;
};

#endif // QDLGDEVICE_H
