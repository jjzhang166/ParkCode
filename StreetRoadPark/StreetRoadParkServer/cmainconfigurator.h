#ifndef CMAINCONFIGURATOR_H
#define CMAINCONFIGURATOR_H

#include <QObject>
#include <QSettings>
#include <QComboBox>
#include <QTextCodec>
#include <QSpinBox>
#include <QLineEdit>

class CMainConfigurator : public QObject
{
    Q_OBJECT
public:
    static CMainConfigurator* GetConfigurator( );
    ~CMainConfigurator( );

    QTextCodec* GetTextCodec( );

    void ReadComM77R( QComboBox& comboBox, QStringList& lstCom );
    void WriteComM77R( qint32 nIndex, qint32 nReceiverID );

    void ReadPortMaxConn( QSpinBox& sbPort, QSpinBox& sbMaxConn );
    void WritePortMaxConn( quint16 nPort, qint32 nMaxConn );

    void ReadIPPort( QLineEdit& edtIP, QSpinBox& sbPort );
    void WriteIPPort( QString& strIP, quint16 nPort );

    void GetPorts( QStringList &lstPorts );

private:
    CMainConfigurator(QObject *parent = 0);

private:
    QSettings* pSettings;
    
signals:
    
public slots:
    
};

#endif // CMAINCONFIGURATOR_H
