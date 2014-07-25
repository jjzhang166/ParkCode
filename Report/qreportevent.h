#ifndef QREPORTEVENT_H
#define QREPORTEVENT_H

#include <QEvent>
#include <QString>

class QMyReportEvent : public QEvent
{
public:
    typedef enum __ReportEvent {
      MoneyYearly = User, //自定义事件必须从User开始
      MoneyMonthly,
      MoneyDaily,
      MoneyClerk,
      MoneyTimeDetail,
      ChannelDetail,
      CountryReport,
      ProvinceReport,
      MonthCardInfo,
      MonthCardTimes,
      ExecuteSQL
    } MyReportEvent;

    static QMyReportEvent* CreateInstance( MyReportEvent eEvent );

    void SetXmlParams( const QString& strXml );
    const QString& GetXmlParams( );

private:
    QMyReportEvent( Type eEvent );

private:
    QString strXmlValue;
};

#endif // QREPORTEVENT_H
