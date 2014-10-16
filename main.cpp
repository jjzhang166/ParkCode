#include <QtGui/QApplication>
#include <QTextCodec>
#include <QtPlugin>
#include "mainwindow.h"
#include "Common/commonfunction.h"

//Q_IMPORT_PLUGIN(qjpeg)
//Q_IMPORT_PLUGIN(qgif)
//Q_IMPORT_PLUGIN(qkrcodecs)

/*
  存储过程采用一个调用入口方式
  SpEntance( in xmlParam, out xmlInfo )
<Params>
<Host>127.0.0.1</Host>
<User></User>
<-- Call SP -->
<SubSP>Test</SubSP> switch call sub SP
<Operation>Insert Update Delete</Operation> switch
<Data>
<p0>...</p0>
</Data>
</Params>
*/

// FusionCharts HightCharts JSCharts ---> Web Report
//QPixmap 图片显示优化 QBitmap
//QImage IO优化
//QPicture  记录与播放QPainter命令

// SMTP(25) 邮件发送协议  SMTP Client---->SMTP Server
// 邮件管理协议
// POP3 IMAP(143)

/*
  查询月租卡收费明细
select d.cardno 卡号, d.feetime 收费时间, d.feenumb 收费金额, d.feeoperator 收费员,
a.starttime 月租起始时间, a.endtime 月租截至时间,
b.username 月租用户, b.userphone 月租用户电话,
c.carcp 车牌号码, c.carmodel 车型
from parkadmin.monthcard a, parkadmin.userinfo b, parkadmin.carinfo c, parkadmin.feerd d
where a.cardno = b.cardindex and a.cardno = c.cardindex and a.cardno = d.cardno
and d.feekind = '月租卡续费' and feetime between '2014-08-01 00:00:00' and '2014-09-10 23:59:59';
  */
// Intel AMD ARM PPC(Apple IBM Motorola) Alpha DEC SPARC MIPS
// Unix Linux Windows 稳定 可靠 安全
// OpenStack CloudStack CloudPlatform
// Install DVD UEFI USB(UntraISO)
// Linux Redhat(RHEL) CentOS Ubuntu

// OpenWrt( route OS ) Linksys 类似Android可更改

// 要完善的功能
//修改车牌日志 报表增加  月租卡按时间续费 按金额续费

// 界面要适应不同大小的屏幕，可以采用Layout方式，来动态布局
// 比如手机，可以把主窗口的Size设置为QDeskpWindget的屏幕尺寸
// Qt for android
// Necessitas(Qt与Android结合平台) Ministro(动态安装QT环境在安卓)
// 1 QT环境与APK一起 2 最小APK 通过Ministro动态安装QT环境
// QT App-->Qt Runtime--->Necessitas--->Android

// Intranet(LAN VLAN ) / Firewall  外部不能直接访问
// Extranet对Intranet的扩展 外部可以受限的访问 VPN就是基于Extranet的WAN网 / VPS

// VPN利用公网来有限的访问私网(Extranet) 一般采用拨号( VPN Client----VPN Server/软硬实现方式 )
// 在IP网络上模拟传统专网的技术 虚拟 专用 把物理网络进行逻辑上的隔离(逻辑上形成了多个独立网络) VLAN
// 这样可以实现各地分公司 各地部门互连
// MPLS(Multiprotocol Label Switching)VPN 最看好的VPN技术
// 开源实现 OpenVPN

// LAN/WLAN/VLAN(Local Area Network) WAN(Wide) MAN(Metropolitan) 地理区域范围的区别
// ISP ICP NSP(Network Service Provider)

// Android ADT(Java) QT(C/C++ QML) Xamarin(C# Mono .Net) HTML5
// AVD调试 物理手机调试(USB连接 安装驱动 开启调试模式)

// ANDROID_TARGET_ARCH=
// ABI Application Binary Interface二进制兼容性 APP--OS APP--APP APP--LIB
// EBAI Embedded
// OABI Old

// Necessitas/KDE
// Ministro is a system wide libraries installer/provider for Android.

// Desktop
// Mobile
// Embeded

// APK( ZIP Format )

// extjs.org.cn

// Lan 物理技术Ethernet 光网 物理技术 PDH/SONET/SDH/OTN
// PTN (Packet Transport Network)
// 光 微波 卫星

// FTTH(Fiber To The Home)/ PON(Passive Optical Network) APON BPON EPON GPON

// MS(Mobile Station )--BTS(Base Transceiver Station)--BTC(Base Station Controller)
//--MSC(Mobile Switch Center)(HLR VLR EIR) MSC BTC BTS MS

// 无线网络
// SSID Service Set ID 无线网络标识符 BSSID/Basic(AP的MAC地址) ESSID/Extended(无线网络)
// WDS Wireless Distribution System 无线桥接
// AP Access Point 接入点

// OpenStack CloudStack 两大开源平台 OpenAPI /Restful WebService
// 云服务器(HPC HAC LBC) / VPS(虚拟机)
// ECS(Elastic Computing Service) 虚拟云服务器
// OSS(Open Storage Service) 海量云存储
// SLB(Server Load Balancer) 云负载均衡
// RDS(Relational Database Service) 云数据库

// Brickstream ShopperTrak

MainWindow* pMainWindow;

int main(int argc, char *argv[])
{
    //Android 开发建环境变量
    //ANDROID_TARGET_ARCH=default/armeabi-v7a
    CMySqlDatabase::MySQLLibraryInit( 0, NULL );

    QApplication a(argc, argv);

    // MBCS(DBCS) UCS
    // ASCI ANSI ISO14060 GB2313 GBK GB18030 GB13000 BIG5 CJK
    //GBK、GB2312 GB18030－－Unicode－－UTF8
    //UTF8－－Unicode－－GBK、GB2312 GB18030
    QTextCodec *pCodec = CCommonFunction::GetTextCodec( );// QTextCodec::codecForName( "GB18030" );    //System//获取系统编码

    QTextCodec::setCodecForLocale( pCodec );
    QTextCodec::setCodecForCStrings( pCodec );
    QTextCodec::setCodecForTr( pCodec );

    //CCommonFunction::GetSyncPass( ).lock( );

   CCommonFunction::StartupSplash( );
    MainWindow w;
    w.show();
    pMainWindow = &w;
    CCommonFunction::CleanupSplash( &w );

    //CMySqlDatabase::MySQLLibrayEnd( );

    return a.exec( );
}
