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


int main(int argc, char *argv[])
{
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
    CCommonFunction::CleanupSplash( &w );

    //CMySqlDatabase::MySQLLibrayEnd( );

    return a.exec( );
}
