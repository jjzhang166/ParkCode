#include "reporter.h"
#include "Common/commonfunction.h"
#include "Common/logicinterface.h"
#include <QDebug>
#include <QFile>
#include <windows.h>
#include <psapi.h>
#include <QFile>

CReporter::CReporter(QObject *parent) :
    QObject(parent)
{
    bPersonTime = false;
}

void CReporter::SetWhere( QStringList &lstWhere )
{
    lstWheres = lstWhere;
}

void CReporter::SetPersonTime( bool bPerson )
{
    bPersonTime = bPerson;
}

void CReporter::Print( CommonDataType::ReportType rType, QWebView& wvReport )
{
    if ( !GetAdboeExePath( strAdobeExe ) ) {
        return;
    }

    KillAdobeProcess( strAdobeExe );

    printer.setPageSize( QPrinter::A4 );
    printer.setOutputFormat( QPrinter::PdfFormat );

    QString strFile;
    CCommonFunction::GetPath( strFile, CommonDataType::PathSnapshot );
    strFile += "reporter.pdf";
    if ( QFile::exists( strFile ) ) {
        QFile::remove( strFile );
        Sleep( 1000 );
    }

    printer.setOutputFileName( strFile );
    wvReport.print( &printer );

    //Call Adobe Reader print pdf
    PrintPdf( strFile );
}

void CReporter::KillAdobeProcess( QString &strExe )
{
    DWORD dwProcID[ 1024 ] = { 0 };
    DWORD dwRealByte = 0;

    if ( !::EnumProcesses( dwProcID, sizeof ( dwProcID ), &dwRealByte ) ) {
        return;
    }

    DWORD dwProcCount = dwRealByte / sizeof ( DWORD );
    HANDLE hProc = NULL;
    DWORD dwProc = 0;
    WCHAR wImgPath[ 512 ] = { 0 };
    QString strTargetPath;

    for ( DWORD dwIndex = 0; dwIndex < dwProcCount; dwIndex++ ) {
        dwProc = dwProcID[ dwIndex ];
        if ( 0 == dwProc ) {
            continue;
        }

        hProc = ::OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwProc );
        if ( NULL == hProc ) {
            continue;
        }

        //if ( !::GetProcessImageFileName( hProc, wImgPath, sizeof ( wImgPath ) / sizeof ( WCHAR ) ) ) {
        if ( !::GetModuleFileNameEx( hProc, NULL, wImgPath, sizeof ( wImgPath ) / sizeof ( WCHAR ) ) ) {
            ::CloseHandle( hProc );
            continue;
        }

        strTargetPath = QString::fromWCharArray( wImgPath );
        if ( strTargetPath == strExe ) {
            ::TerminateProcess( hProc, 0 );
            ::WaitForSingleObject( hProc, 5000 ); // INFINITE
            ::CloseHandle( hProc );
            break;
        }

        ::CloseHandle( hProc );
    }
}

bool CReporter::GetAdboeExePath( QString &strExe )
{
    QString strReg = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Adobe\\Acrobat Reader";//\\10.0\\InstallPath";
    QSettings settings( strReg, QSettings::NativeFormat );
    QStringList lstKeys = settings.allKeys( );
    QString strTarget = "InstallPath";
    QString strKey = "";

    for ( int nIndex = 0; nIndex < lstKeys.count( ); nIndex++ ) {
        strKey = lstKeys[ nIndex ];
        if ( strKey.contains( strTarget ) ) { // 10.0/InstallPath/.
            strKey = strKey.left( strKey.count( ) - 1 );
            break;
        }
    }

    strExe = settings.value( strKey + "Default", "" ).toString( ) + "\\AcroRd32.exe";
    strExe.replace( QRegExp( "\\" ), "/" );

    bool bRet = false;
    if ( !QFile::exists( strExe ) ) {
        CCommonFunction::MsgBox( NULL, CCommonFunction::GetMsgTitle( QMessageBox::Information ), "请安装【Adobe Acrobat Reader】.", QMessageBox::Information );
        return bRet;
    }

    return true;
}

void CReporter::PrintPdf( QString &strFile )
{
    QStringList lstArgs;
    lstArgs << strFile;
    QProcess::startDetached( strAdobeExe, lstArgs );
}

void CReporter::GetSQL( QString &strSql, CommonDataType::ReportType rType, QDateTime& dtStart, QDateTime& dtEnd )
{
    QString strMonthCard = "月租卡";
    QString strTimeCard = "计时卡";
    QString strValueCard = "储值卡";
    QString strValue = "储值卡充值";

    QDate dStart = dtStart.date( );
    QDate dEnd = dtEnd.date( );
    QString strStart;
    QString strEnd;

    QTime time;
    time.setHMS( 23, 59, 59 );
    QDateTime dtTimeEnd = dtEnd;
    dtEnd.setTime( time );

    CCommonFunction::DateTime2String( dtStart, strStart );
    CCommonFunction::DateTime2String( dtEnd, strEnd );

    QString yBegin = QString::number( dStart.year( ) ) + "-01-01 00:00:00";
    QString yEnd = QString::number( dEnd.year( ) + 1 ) + "-01-01 00:00:00";

    QString mBegin = QString::number( dStart.year( ) ) + "-" + QString::number( dStart.month( ) ) + "-01 00:00:00";
    QString mEnd = QString::number( dEnd.year( ) ) + "-" + QString::number( dEnd.month( ) + 1 ) + "-01 00:00:00";

    switch ( rType ) {
    case CommonDataType::ReportYearly :
        strSql = "select f1,f2,sum( f3 ),sum(f4), sum(f5), sum(f6), sum(f7), sum(f8) from ( select year( intime ) f1, month( intime ) f2, count( cardno ) as f3, null as f4, null as f5, null as f6, null as f7, null as f8 from stoprd a where  ( '";
        strSql += yBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += yEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strMonthCard;
        strSql += "' group by year( a.intime ), month( a.intime ) union all select year( feetime ) f1, month( feetime ) f2, null as f3, sum( feenumb ) f4, null as f5, null as f6, null as f7, null as f8  from feerd where ('";
        strSql += yBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += yEnd;
        strSql += "') and feekind like '";
        strSql += strMonthCard;
        strSql += "%' group by year( feetime ), month( feetime ) union all select year( intime ) f1, month( intime ) f2, count( cardno ) f3, null as f4, null as f5, null as f6, null as f7, null as f8 from stoprd a where  ( '";
        strSql += yBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += yEnd,
        strSql += "' ) and a.cardkind = '";
        strSql += strTimeCard;
        strSql += "' group by year( a.intime ), month( a.intime ) union all select year( feetime ) f1, month( feetime ) f2, null as f3, sum( feenumb ) f4, null as f5, null as f6, null as f7, null as f8 from feerd where ('";
        strSql += yBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += yEnd;
        strSql += "') and feekind like '";
        strSql += strTimeCard;
        strSql += "%' group by year( feetime ), month( feetime ) union all select year( intime ) f1, month( intime ) f2, count( cardno ) f3, null as f4, null as f5, null as f6, null as f7, null as f8 from stoprd a where  ( '";
        strSql += yBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += yEnd,
        strSql += "' ) and a.cardkind = '";
        strSql += strValueCard;
        strSql += "' group by year( a.intime ), month( a.intime ) union all select year( feetime ) f1, month( feetime ) f2, null as f3, sum( feenumb ) f4, null as f5, null as f6, null as f7, null as f8 from feerd where ('";
        strSql += yBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += yEnd;
        strSql += "') and feekind like '";
        strSql += strValue;
        strSql += "%' group by year( feetime ), month( feetime ), day( feetime ) ) x group by f1, f2";
        break;

    case CommonDataType::ReportMonthly :
        strSql = "select f1,f2,f3,sum(f4), sum(f5), sum(f6), sum(f7), sum(f8), sum(f9) from ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4, null as f5, null as f6, null as f7, null as f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += mEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strMonthCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";///////////
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, sum( feenumb ) f5, null as f6, null as f7, null as f8, null as f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += mEnd;
        strSql += "') and feekind like '";
        strSql += strMonthCard;
        strSql += "%'  group by year( feetime ), month( feetime ), day( feetime ) ";
        strSql += "union all ";//////////
        strSql += "select year( intime ) f1, month( intime ) f2, day( intime ) f3, null as f4, null as f5, count( cardno ) f6, null as f7, null as f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += mEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strTimeCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, null as f5, null as f6, sum( feenumb ) f7,null as f8, null as f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += mEnd;
        strSql += "') and feekind like '";
        strSql += strTimeCard;
        strSql += "%' group by year( feetime ), month( feetime ), day( feetime ) ";
        strSql += "union all ";//////////
        strSql += "select year( intime ) f1, month( intime ) f2, day( intime ) f3, null as f4, null as f5, null as f6, null as f7, count( cardno ) f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= a.intime and a.intime < '";
        strSql += mEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strValueCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, null as f5, null as f6, null as f7, null as f8, sum( feenumb ) f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += mBegin;
        strSql += "' <= feetime and feetime < '";
        strSql += mEnd;
        strSql += "') and feekind like '";
        strSql += strValueCard;
        strSql += "%' group by year( feetime ), month( feetime ), day( feetime ) ) x group by f1, f2, f3";
        break;

    case CommonDataType::ReportDaily :
        strSql = "select f1,f2,f3,sum(f4), sum(f5), sum(f6), sum(f7), sum(f8), sum(f9)  from ( select year( intime ) f1, month( intime ) f2, day( intime ) f3, count( cardno ) f4, null as f5, null as f6, null as f7, null as f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= a.intime and a.intime < '";
        strSql += strEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strMonthCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, sum( feenumb ) f5, null as f6, null as f7, null as f8, null as f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= feetime and feetime < '";
        strSql += strEnd;
        strSql += "') and feekind like '";
        strSql += strMonthCard;
        strSql += "%'  group by year( feetime ), month( feetime ), day( feetime ) ";
        strSql += "union all ";
        strSql += "select year( intime ) f1, month( intime ) f2, day( intime ) f3, null as f4, null as f5, count( cardno ) f6, null as f7, null as f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= a.intime and a.intime < '";
        strSql += strEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strTimeCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, null as f5, null as f6, sum( feenumb ) f7,null as f8, null as f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= feetime and feetime < '";
        strSql += strEnd;
        strSql += "') and feekind like '";
        strSql += strTimeCard;
        strSql += "%' group by year( feetime ), month( feetime ), day( feetime ) ";
        strSql += "union all ";
        strSql += "select year( intime ) f1, month( intime ) f2, day( intime ) f3, null as f4, null as f5, null as f6, null as f7, count( cardno ) f8, null as f9 ";
        strSql += "from stoprd a ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= a.intime and a.intime < '";
        strSql + strEnd;
        strSql += "' ) and a.cardkind = '";
        strSql += strValueCard;
        strSql += "' group by year( a.intime ), month( a.intime ), day( intime ) ";
        strSql += "union all ";
        strSql += "select year( feetime ) f1, month( feetime ) f2, day( feetime ) f3, null as f4, null as f5, null as f6, null as f7, null as f8, sum( feenumb ) f9 ";
        strSql += "from feerd ";
        strSql += "where  ( '";
        strSql += strStart;
        strSql += "' <= feetime and feetime < '";
        strSql += strEnd;
        strSql += "') and feekind like '";
        strSql += strValueCard;
        strSql += "%' group by year( feetime ), month( feetime ), day( feetime ) ) x group by f1, f2, f3";
        break;

    case CommonDataType::ReportPerson :
        if ( bPersonTime ) {
            CCommonFunction::DateTime2String( dtTimeEnd, strEnd );
        }

        strSql = "select feeoperator f1, sum( feenumb ) f2 from feerd where feetime between '";
        strSql += strStart;
        strSql += "' and '";
        strSql += strEnd;
        strSql += "' group by feeoperator";
        break;

    case CommonDataType::ReportChannel :
#if false
        ( select  date( intime ) a, inshebeiname b , cardkind c, count( cardno ) d from stoprd
        where intime between '2011-01-01 00:00:00' and '2012-01-01 00:00:00'
        group by date( intime ), inshebeiname, cardkind
        order by date( intime ), inshebeiname, cardkind ) t1
        -- inner join / cross full inner left right // union //union all
         union
        select * from ( select  date( outtime ) a, outshebeiname b, cardkind c, count( cardno ) d from stoprd
        where outtime between '2011-01-01 00:00:00' and '2012-01-01 00:00:00'
        group by date( outtime ), outshebeiname, cardkind
        order by date( outtime ), outshebeiname, cardkind ) t2
        order by a,b,c;
#endif
        strSql = "select * from ";
        strSql += "( select  date( intime ) a, inshebeiname b , cardkind c, count( cardno ) d from stoprd ";
        strSql += "where intime between '";
        strSql += strStart;
        strSql += "' and '";
        strSql += strEnd;
        strSql += "' group by date( intime ), inshebeiname, cardkind ";
        strSql += "order by date( intime ), inshebeiname, cardkind ) t1 ";
        strSql += "union ";
        strSql += "select * from ( select  date( outtime ) a, outshebeiname b, cardkind c, count( cardno ) d from stoprd ";
        strSql += "where outtime between '";
        strSql += strStart;
        strSql += "' and '";
        strSql += strEnd;
        strSql += "' group by date( outtime ), outshebeiname, cardkind ";
        strSql += "order by date( outtime ), outshebeiname, cardkind ) t2 ";
        strSql += "order by a,b,c";
        break;

    case CommonDataType::ReportTimeCardDetail :
        CCommonFunction::DateTime2String( dtTimeEnd, strEnd );
        strSql = "select date( feetime ) ftime, feeoperator, feekind, feezkyy, sum( feenum ), ";
        strSql += "sum( feefactnum ), sum( feenum - feefactnum ) from stoprd ";
        strSql += "where feenum >= feefactnum and cardkind = '";
        strSql += strTimeCard;
        strSql += "' and ( feetime between '";
        strSql += strStart;
        strSql += "' and '";
        strSql += strEnd;
        strSql += "' ) group by date( feetime ), feeoperator, feekind, feezkyy having ( sum( feenum ) + sum( feefactnum ) ) <> 0 ";
        strSql += "union all ";
        strSql += "select '合计' ftime, '', '', '', sum( feenum ), sum( feefactnum ), sum( feenum - feefactnum ) from stoprd ";
        strSql += "where feenum >= feefactnum and feetime between '";
        strSql += strStart;
        strSql += "' and '";
        strSql += strEnd;
        strSql += "' order by ftime desc";
        break;

    case CommonDataType::ReportProvince :
        strSql = "select case substring( carcp, 1, 1 ) \
                                   when '川' then '四川省'  \
                                   when '渝' then '重庆市' \
                                   when '京' then '北京市' \
                                   when '津' then '天津市' \
                                   when '沪' then '上海市' \
                                   when '冀' then '河北省' \
                                   when '豫' then '河南省' \
                                   when '云' then '云南省' \
                                   when '辽' then '辽宁省' \
                                   when '黑' then '黑龙江省' \
                                   when '湘' then '湖南省' \
                                   when '皖' then '安徽省' \
                                   when '鲁' then '山东省' \
                                   when '新' then '新疆维吾尔族自治区' \
                                   when '苏' then '江苏省' \
                                   when '浙' then '浙江省' \
                                   when '赣' then '江西省' \
                                   when '鄂' then '湖北省' \
                                   when '桂' then '广西壮族自治区' \
                                   when '甘' then '甘肃省' \
                                   when '晋' then '山西省' \
                                   when '蒙' then '内蒙古自治区' \
                                   when '陕' then '陕西省' \
                                   when '吉' then '吉林省' \
                                   when '闽' then '福建省' \
                                   when '贵' then '贵州省' \
                                   when '粤' then '广东省' \
                                   when '青' then '青海省' \
                                   when '藏' then '西藏自治区' \
                                   when '宁' then '宁夏回族自治区' \
                                   when '琼' then '海南省' \
                                   else '未知' end  as 车辆所属辖区, \
                                   IFNULL( feekind, '未离开' ) as 车型, \
                                   count( carcp ) as 车辆数 \
                                   from stoprd \
                                   where intime between '"
                                   + strStart +
                                   "' and '"
                                   + strEnd +
                                   "' and cardkind = '计时卡' and feekind is not null group by substring( carcp, 1, 1 ) with rollup";
        break;

    case CommonDataType::ReportInProvince :
        strSql =  "select case UPPER( substring( carcp, 2, 1 ) )  \
                                   when 'A' then '成都市' \
                                   when 'B' then '绵阳市' \
                                   when 'C' then '自贡市' \
                                   when 'D' then '攀枝花市' \
                                   when 'E' then '泸州市' \
                                   when 'F' then '德阳市' \
                                   when 'H' then '广元市' \
                                   when 'J' then '遂宁市' \
                                   when 'K' then '内江市' \
                                   when 'L' then '乐山市' \
                                   when 'M' then '资阳市' \
                                   when 'Q' then '宜宾市' \
                                   when 'R' then '南充市' \
                                   when 'S' then '达州市' \
                                   when 'T' then '雅安市' \
                                   when 'U' then '阿坝藏族羌族自治州' \
                                   when 'V' then '甘孜藏族自治州' \
                                   when 'W' then '凉山彝族自治州' \
                                   when 'X' then '广安市' \
                                   when 'Y' then '巴中市' \
                                   when 'Z' then '眉山市' \
                                   else '未知' end  as 车辆所属辖区,  \
                                   IFNULL( feekind, '未离开' ) as 车型, \
                                   count( carcp ) as 车辆数 \
                                   from stoprd \
                                   where intime between '"
                                   + strStart +
                                   "' and '"
                                   + strEnd +
                                   "' and cardkind = '计时卡' and feekind is not null and substring( carcp, 1, 1 ) = '川' \
                                   group by substring( carcp, 2, 1 ) with rollup";
        break;

    case CommonDataType::ReportMonth :
        strSql = "select a.cardno, a.cardselfno , \
            case a.EnterMustCard when 0 then '否' when 1 then '是' end as EnterMustCard,  \
            case a.LeaveMustCard when 0 then '否' when 1 then '是' end as LeaveMustCard, \
            case a.MIMO when 0 then '否' when 1 then '是' end as MIMO, \
            case a.Inside when 0 then '否' when 1 then '是' end as Inside, \
            a.cardstate, a.starttime, a.endtime, b.carcp, c.username, c.userphone, \
            IF ( a.starttime > a.endtime, '是', '否' ) as Expire \
            from monthcard as a, carinfo as b, userinfo as c \
                where a.cardno = b.cardindex and a.cardno = c.cardindex ";

        if ( 3 <= lstWheres.count( ) ){
            int nIndex = lstWheres.at( 0 ).toInt( );
            QString strDateRange = "";
            switch ( nIndex ) {
            case 0 :
                strDateRange = QString( " And StartTime >='%1' And EndTime <= '%2' " ).arg( lstWheres.at( 1 ), lstWheres.at( 2 ) );
                break;

            case 1 :
                strDateRange = QString( " And StartTime between '%1' And '%2' " ).arg( lstWheres.at( 1 ), lstWheres.at( 2 ) );
                break;

            case 2 :
                strDateRange = QString( " And EndTime between '%1' And '%2' " ).arg( lstWheres.at( 1 ), lstWheres.at( 2 ) );
                break;
            }

            strSql += strDateRange;
        }

        strSql += " order by Expire";
    break;

   case CommonDataType::ReportMonthInOut :
        if (  2 != lstWheres.length( ) ) {
            CCommonFunction::MsgBox( NULL, "提示", "请选择查询条件。", QMessageBox::Information );
            return;
        }

        const QString& strWhere1 = lstWheres.at( 0 );
        const QString& strWhere2 = lstWheres.at( 1 );
         strSql = QString( "select m.cardno, m.cardselfno, m.carcp, m.username, m.userphone, s.counter from  \
                 ( select a.cardno, a.cardselfno, b.carcp, c.username, c.userphone from  \
                 monthcard as a, carinfo as b, userinfo as c \
                 where a.cardno = b.cardindex and a.cardno = c.cardindex  \
                 %1) m, ( select cardno, count( cardno ) as counter from stoprd where \
                 %2 intime >= '%3' and outtime <= '%4' group by cardno  \
                 order by cardno ) s  where m.cardno = s.cardno" ).arg( strWhere1, strWhere2, strStart, strEnd );
        break;
    }

#ifdef QT_NO_DEBUG
    QFile file( "d:/sql.txt" );
    if ( !file.exists( ) || !file.open( QIODevice::WriteOnly ) ) {
        return;
    }

    // QDataStream
    QTextStream stream( &file );
    stream << strSql;
    stream.flush( );
    file.close( );
#endif

}

void CReporter::BuildHtmlDoc( QDateTime& dtStart, QDateTime& dtEnd, CommonDataType::ReportType rType, QWebView& wvReport )
{
    QStringList lstData;
    QString strStart;
    QString strEnd;
    //QString strType = QString::number( rType );
    CCommonFunction::DateTime2String( dtStart, strStart );
    CCommonFunction::DateTime2String( dtEnd, strEnd );
    QString strSql;// = QString( "call GenerateReport( '%1', '%2', %3 )" ).arg( strStart, strEnd, strType );
    QDateTime dtTimeEnd = dtEnd;
    GetSQL( strSql, rType, dtStart, dtEnd );

    if ( strSql.isEmpty( ) ) {
        return;
    }

    CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    //strSql= "Select @f1,@f2,@f3,@f4,@f5,@f6,@f7,@f8";
    //CLogicInterface::GetInterface( )->ExecuteSql( strSql, lstData );

    QDate dStart = dtStart.date( );
    QDate dEnd = dtEnd.date( );

    CCommonFunction::Date2String( dStart, strStart );
    CCommonFunction::Date2String( dEnd, strEnd );

    QString strTitle;
    QString strFooter;
    QString strTableBody;
    GetHtml( rType, strTitle, strFooter, strTableBody, lstData );

    QString strTitleDate;
    GetTitle( rType, dtStart, dtTimeEnd, strTitleDate );


    QString strHtml = QString( "<HTML>\
                                <BODY>\
                                    <H3 ALIGN = \"CENTER\">报表日期：%1</H1>\
                                    <br><br>\
                                    <TABLE ALIGN = \"CENTER\" BORDER = \"1\" frame=\"box\" rules=\"all\"CELLPADDING = \"2\">\
                                        %2\
                                        %3\
                                    </TABLE>\
                                </BODY>\
                                </HTML>" ).arg( strTitleDate, strTitle, strTableBody + strFooter );

    wvReport.setHtml( strHtml );
}

void CReporter::GetTitle( CommonDataType::ReportType rType, QDateTime &dtStart, QDateTime &dtEnd, QString& strTitle )
{
    QDate dStart = dtStart.date( );
    QDate dEnd = dtEnd.date( );

    QString strSYear = QString::number( dStart.year( ) );
    QString strEYear = QString::number( dEnd.year( ) );

    QString strSMonth = QString::number( dStart.month( ) );
    QString strEMonth = QString::number( dEnd.month( ) );

    QString strStart;
    CCommonFunction::Date2String( dStart, strStart );
    QString strEnd;
    CCommonFunction::Date2String( dEnd, strEnd );

    switch ( rType ) {
    case CommonDataType::ReportPerson :
        if ( bPersonTime ) {
            {
                QString strStart;
                CCommonFunction::DateTime2String( dtStart, strStart );
                QString strEnd;
                CCommonFunction::DateTime2String( dtEnd, strEnd );

                 strTitle = strStart + " 至 " + strEnd;
            }
        } else {
            if ( strStart == strEnd ) {
                strTitle = strStart + "日";
            } else {
                strTitle = strStart + "日 至 " + strEnd + "日";
            }
        }
        break;

    case CommonDataType::ReportYearly :
        if ( strSYear == strEYear ) {
            strTitle = strSYear + "年";
        } else {
            strTitle = strSYear + "年 至 " + strEYear + "年";
        }
        break;

    case CommonDataType::ReportMonthly :
        if ( strSYear == strEYear ) {
            if ( strSMonth == strEMonth ) {
                strTitle = strSYear + "年" + strSMonth + "月";
            } else {
                strTitle = strSYear + "年" + strSMonth + "月 至 " + strEMonth + "月";
            }
        } else {
            strTitle = strSYear + "年" + strSMonth + "月 至 " + strEYear + "年" + strEMonth + "月";
        }
        break;

    case CommonDataType::ReportDaily :
    case CommonDataType::ReportChannel :
    case CommonDataType::ReportProvince :
    case CommonDataType::ReportInProvince :
    case CommonDataType::ReportMonth :
    case CommonDataType::ReportMonthInOut :
        if ( strStart == strEnd ) {
            strTitle = strStart + "日";
        } else {
            strTitle = strStart + "日 至 " + strEnd + "日";
        }
        break;
    case CommonDataType::ReportTimeCardDetail :
    {
        QString strStart;
        CCommonFunction::DateTime2String( dtStart, strStart );
        QString strEnd;
        CCommonFunction::DateTime2String( dtEnd, strEnd );

         strTitle = strStart + " 至 " + strEnd;
    }
        break;
    }
}

void CReporter::GetRowHtml( QString &strRow, QStringList& lstData )
{
    if ( 0 == lstData.count( ) ) {
        return;
    }

    strRow = "<TR>";

    for ( int nIndex = 0; nIndex < lstData.count( ); nIndex++ ) {
       strRow += QString( "<TD HEIGHT = \"5\">%1</TD>" ).arg( lstData[ nIndex ] );
    }

    strRow += "</TR>";
    qDebug( ) << strRow << endl;
}

void CReporter::GetHtml( CommonDataType::ReportType rType, QString& strTitle, QString& strFooter,
                         QString& strTableBody, QStringList& lstData )
{
   QString strRow;
   int nCols = 0;

   switch ( rType ) {
   case CommonDataType::ReportYearly :
       strTitle = "<tr><th rowspan=\"2\">年</th><th rowspan=\"2\">月</th>\
                   <th colspan=\"2\">月租卡</th><th colspan=\"2\">计时卡</th><th colspan=\"2\">储值卡</th><th colspan=\"2\">\
                   合计</th></tr>\
                   <tr>\
                   <td >车辆数</td>\
                   <td >续费</td>\
                   <td >车辆数</td>\
                   <td >收费</td>\
                   <td >车辆数</td>\
                   <td>充值</td>\
                   <td>车辆数</td>\
                   <td>收费</td>\
                   </tr>";
       strFooter = " <tr><td colspan=\"2\">合计</td> \
                   <td>%1</td><td>%2</td><td>%3</td> \
                   <td>%4</td><td>%5</td><td>%6</td> \
                   <td>%7</td><td>%8</td></tr>";
       nCols = 8;
       break;

   case CommonDataType::ReportMonthly :
   case CommonDataType::ReportDaily :
       strTitle = "<tr><th rowspan=\"2\">年</th><th rowspan=\"2\">月</th><th rowspan=\"2\" >日</th>\
                   <th colspan=\"2\">月租卡</th><th colspan=\"2\">计时卡</th><th colspan=\"2\">储值卡</th><th colspan=\"2\">\
                   合计</th></tr>\
                   <tr>\
                   <td >车辆数</td>\
                   <td >续费</td>\
                   <td >车辆数</td>\
                   <td >收费</td>\
                   <td >车辆数</td>\
                   <td>充值</td>\
                   <td>车辆数</td>\
                   <td>收费</td>\
                   </tr>";
       strFooter = " <tr><td colspan=\"3\">合计</td> \
                   <td>%1</td><td>%2</td><td>%3</td> \
                   <td>%4</td><td>%5</td><td>%6</td> \
                   <td>%7</td><td>%8</td></tr>";
       nCols = 9;
       break;

   case CommonDataType::ReportPerson :
       strTitle = "<tr><th>收费员</th><th>金额</th><tr>";
       strFooter = "<tr><th>合计</th><th>%1</th><tr>";
       nCols = 2;
       break;

   case CommonDataType::ReportChannel :
       strTitle = "<tr><th>日期</th><th>通道名</th><th>卡类型</th><th>车辆数</th><tr>";
       //strFooter = "<tr><th>%1</th><th>%2</th><th>%3</th><th>%4</th><tr>";
       strFooter = "";
       nCols = 4;
       break;

   case CommonDataType::ReportTimeCardDetail :
       strTitle = "<tr><th>日期</th><th>收费员</th><th>费率类型</th><th>优惠类型</th>\
                        <th>应收总额</th><th>实收总额</th><th>收费差额</th><tr>";
       //strFooter = "<tr><th>%1</th><th>%2</th><th>%3</th><th>%4</th><tr>";
       strFooter = "";
       nCols = 7;
       break;

  case CommonDataType::ReportProvince :
  case CommonDataType::ReportInProvince :
       strTitle = "<tr><th>车辆所属辖区</th><th>车型</th><th>车辆数</th></tr>";
       strFooter = "";
       nCols = 3;
       break;
  case CommonDataType::ReportMonth :
       strTitle = "<tr><th>卡号</th><th>自编号</th>\
                       <th>进刷卡</th>\
                       <th>出刷卡</th> \
                       <th>多进多出</th>\
                       <th>已入场</th>\
                       <th>卡状态</th>\
                       <th>开始时间</th>\
                       <th>截止时间</th>\
                       <th>车牌</th>\
                       <th>业主</th>\
                       <th>联系电话</th>\
                       <th>过期</th></tr>";
       strFooter = "";
       nCols = 13;
       break;

   case CommonDataType::ReportMonthInOut :
        strTitle = "<tr><th>卡号</th><th>自编号</th>\
                        <th>车牌</th>\
                        <th>业主</th>\
                        <th>联系电话</th>\
                        <th>进出次数</th></tr>";
        strFooter = "";
        nCols = 6;
        break;
   }

   int nRows = lstData.count( ) / nCols;
   int nTotal1 = 0;
   int nTotal2 = 0;

   QStringList lstTmp;

   QString strTotal1;
   QString strTotal2;
   int nSum[ 8 ] = { 0 };

   for ( int nRow = 0; nRow < nRows; nRow++ ) {
       int nField = nRow * nCols;
       lstTmp.clear( );
       strTotal1.clear( );
       strTotal2.clear( );
       nTotal1 = 0;
       nTotal2 = 0;

       if ( CommonDataType::ReportYearly == rType ) {
           nTotal1 = lstData[ nField + 2 ].toInt( ) + lstData[ nField + 4 ].toInt( ) + lstData[ nField + 6 ].toInt( );
           if ( 0 != nTotal1 ) {
               strTotal1 = QString::number( nTotal1 );
           }

           nTotal2 = lstData[ nField + 3 ].toInt( ) +lstData[ nField + 5 ].toInt( ) + lstData[ nField + 7 ].toInt( );
           if ( 0 != nTotal2) {
               strTotal2 = QString::number( nTotal2 );
           }

           lstTmp << lstData[ nField ]
                  << lstData[ nField + 1 ];
           RowData( nSum, lstTmp, lstData, nField, strTotal1, strTotal2, 2, nCols );
       } else if ( CommonDataType::ReportMonthly == rType || CommonDataType::ReportDaily == rType ) {
           nTotal1 = lstData[ nField + 3 ].toInt( ) +lstData[ nField + 5 ].toInt( ) + lstData[ nField + 7 ].toInt( );
           if ( 0 != nTotal1 ) {
               strTotal1 = QString::number( nTotal1 );
           }

           nTotal2 = lstData[ nField + 4 ].toInt( ) +lstData[ nField + 6 ].toInt( ) + lstData[ nField + 8 ].toInt( );
           if ( 0 != nTotal2 ) {
               strTotal2 = QString::number( nTotal2 );
           }

           lstTmp << lstData[ nField ]
                  << lstData[ nField + 1 ]
                  << lstData[ nField + 2 ];
           RowData( nSum, lstTmp, lstData, nField, strTotal1, strTotal2, 3, nCols );
       } else if ( CommonDataType::ReportPerson == rType ) {
           lstTmp << lstData[ nField ]
                  << lstData[ nField + 1 ];
           nSum[ 0 ] += lstData[ nField + 1 ].toInt( );
       } else if ( CommonDataType::ReportChannel == rType ) {
           lstTmp << lstData[ nField ]
                  << lstData[ nField + 1 ]
                  << lstData[ nField + 2 ]
                  << lstData[ nField + 3 ];
       } else if ( CommonDataType::ReportTimeCardDetail == rType ) {
           lstTmp << lstData[ nField ]
                  << lstData[ nField + 1 ]
                  << lstData[ nField + 2 ]
                  << lstData[ nField + 3 ]
                  << lstData[ nField + 4 ]
                  << lstData[ nField + 5 ]
                  << lstData[ nField + 6 ];
       } else if ( CommonDataType::ReportProvince == rType ||
                      CommonDataType::ReportInProvince == rType ) {
           lstTmp << lstData[ nField ]
                       << lstData[ nField + 1 ]
                       << lstData[ nField + 2 ];

           if ( nRow + 1 == nRows ) {
               lstTmp[ 0 ] = "全部总计";
           }
       } else if ( CommonDataType::ReportMonth == rType ) {
           lstTmp << lstData[ nField ]
                   << lstData[ nField + 1 ]
                   << lstData[ nField + 2 ]
                   << lstData[ nField + 3 ]
                   << lstData[ nField + 4 ]
                   << lstData[ nField + 5 ]
                   << lstData[ nField + 6 ]
                   << lstData[ nField + 7 ]
                   << lstData[ nField + 8 ]
                   << lstData[ nField + 9 ]
                   << lstData[ nField + 10 ]
                   << lstData[ nField + 11 ]
                   << lstData[ nField + 12 ];
       } else if ( CommonDataType::ReportMonthInOut == rType ) {
           lstTmp << lstData[ nField ]
                   << lstData[ nField + 1 ]
                   << lstData[ nField + 2 ]
                   << lstData[ nField + 3 ]
                   << lstData[ nField + 4 ]
                   << lstData[ nField + 5 ];
       }

       GetRowHtml( strRow, lstTmp );
       strTableBody += strRow;
   }

   switch ( rType ) {
   case CommonDataType::ReportYearly :
   case CommonDataType::ReportMonthly :
   case CommonDataType::ReportDaily :
       GetSumData( nSum, 8, strFooter );
       break;

   case CommonDataType::ReportPerson :
       GetSumData( nSum, 1, strFooter );
       break;

   case CommonDataType::ReportChannel :
   case CommonDataType::ReportTimeCardDetail :
   case CommonDataType::ReportInProvince :
   case CommonDataType::ReportProvince :
   case CommonDataType::ReportMonth  :
   case CommonDataType::ReportMonthInOut :
       break;
   }
}

void CReporter::GetSumData( int nSum[], int nCounter, QString &strFooter )
{
    for ( int nIndex = 0; nIndex < nCounter; nIndex++ ) {
        strFooter = strFooter.arg( 0 == nSum[ nIndex ] ? "" : QString::number( nSum[ nIndex ] ) );
    }
}

void CReporter::RowData( int nSum[ ], QStringList& lstReslut, QStringList& lstData,
                         int nField, QString& strTotal1, QString& strTotal2, int nStartIndex, int nCols )
{
    for ( int nIndex = nStartIndex; nIndex < nCols; nIndex++ ) {
        lstReslut << lstData[ nField + nIndex ];
        nSum[ nIndex - nStartIndex ] += lstData[ nField + nIndex ].toInt( );
    }

    lstReslut << strTotal1
              << strTotal2;

    nStartIndex = nCols - nStartIndex;
    nSum[ nStartIndex ] += strTotal1.toInt( );
    nSum[ ++nStartIndex ] += strTotal2.toInt( );
}

