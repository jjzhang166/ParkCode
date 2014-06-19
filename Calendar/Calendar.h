/***************************************************************************
   致看到这些源代码的兄弟:
       你好!
       这本来是我为一个商业PDA产品开发的日历程序,最近移植于PC机上, 所以算法
   和数据部分是用纯C++写的,不涉及MFC,所有的代码都是以短节省存储空间为主要目
   的.
	   很高兴你对这些代码有兴趣,你可以随意复制和使用些代码,唯一有一点小小的
   愿望:在你使用和复制给别人时,别忘注明这些代码作者:-)。程序代码也就罢了,后
   面的数据可是我辛辛苦苦从万年历上找出来输进去的。
	   如果你有什么好的意见不妨Mail给我。

       wangfei@hanwang.com.cn
	   或
	   wangfei@engineer.com.cn
                                                                 2000年3月
****************************************************************************/
#if !defined(AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_)
#define AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Calendar1.h : header file
/////////////////////////////////////////////////////////////////////////////
// CCalendar window
extern const WORD START_YEAR;
extern const WORD END_YEAR;

//define user message select changed
#define UM_SELCHANGE  (WM_USER+101)

class CCalendar : public CWnd
{
private:
	WORD    m_iYear, m_iMonth, m_iDay;
	CBitmap m_oBitMapList[42];
	CMenu   m_oPopMenu;

public:
	COLORREF m_dwBackColor,  m_dwForeColor;
	COLORREF m_dwSelColor,   m_dwSelForeColor;
	COLORREF m_dwTitleBkColor, m_dwTitleColor;

public:
	CCalendar(WORD iYear, WORD iMonth, WORD iDay);
	CCalendar();
	virtual BOOL Create(RECT &rect, CWnd * pParentWnd, UINT nID);

public:
	WORD GetYear(){return m_iYear;}
	WORD GetMonth(){return m_iMonth;}
	WORD GetDay(){return m_iDay;}
	void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);
	BOOL SetDate(WORD iYear, WORD iMonth, WORD iDay);

protected:
	CButton m_obutToday;
	//{{AFX_MSG(CCalendar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void OnTitleBkColor();
	afx_msg void OnTitleColor();
	afx_msg void OnSelColor();
	afx_msg void OnForeColor();
	DECLARE_MESSAGE_MAP()


public:
	//判断iYear是不是闰年
    static BOOL IsLeapYear(WORD iYear)
	{return !(iYear%4)&&(iYear%100) || !(iYear%400);}

	//计算iYear,iMonth,iDay对应是星期几 1年1月1日 --- 65535年12月31日
	static WORD WeekDay(WORD iYear, WORD iMonth, WORD iDay);

	//返回iYear年iMonth月的天数 1年1月 --- 65535年12月
	static WORD MonthDays(WORD iYear, WORD iMonth);

	//返回阴历iLunarYer年阴历iLunarMonth月的天数，如果iLunarMonth为闰月，
	//高字为第二个iLunarMonth月的天数，否则高字为0 
	// 1901年1月---2050年12月
	static LONG LunarMonthDays(WORD iLunarYear, WORD iLunarMonth);

	//返回阴历iLunarYear年的总天数
	// 1901年1月---2050年12月
	static WORD LunarYearDays(WORD iLunarYear);

	//返回阴历iLunarYear年的闰月月份，如没有返回0
	// 1901年1月---2050年12月
	static WORD GetLeapMonth(WORD iLunarYear);

	//把iYear年格式化成天干记年法表示的字符串
	static void FormatLunarYear(WORD  iYear, char *pBuffer);

	//把iMonth格式化成中文字符串
	static void FormatMonth(WORD iMonth, char *pBuffer, BOOL bLunar = TRUE);

    //把iDay格式化成中文字符串
	static void FormatLunarDay(WORD  iDay, char *pBuffer);

	//计算公历两个日期间相差的天数  1年1月1日 --- 65535年12月31日
	static LONG CalcDateDiff(WORD iEndYear, WORD iEndMonth, WORD iEndDay,
		                     WORD iStartYear = START_YEAR, 
							 WORD iStartMonth =1, WORD iStartDay =1);

	//计算公历iYear年iMonth月iDay日对应的阴历日期,返回对应的阴历节气 0-24
	//1901年1月1日---2050年12月31日
	static WORD GetLunarDate(WORD iYear, WORD iMonth, WORD iDay,
		                     WORD &iLunarYear, WORD &iLunarMonth, WORD &iLunarDay);

public:
	virtual ~CCalendar();

private:
	void   l_InitData();

	//计算从1901年1月1日过iSpanDays天后的阴历日期
	static void   l_CalcLunarDate(WORD &iYear, WORD &iMonth ,WORD &iDay, LONG iSpanDays);
    //计算公历iYear年iMonth月iDay日对应的节气 0-24，0表不是节气
	static WORD   l_GetLunarHolDay(WORD iYear, WORD iMonth, WORD iDay);

	WORD l_CalcSelectDay(POINT * pt);
	void l_PaintTitle(CPaintDC &dc);
	void l_PaintDate(CPaintDC &dc);
	inline void l_PaintOneDay(CPaintDC &dc, CDC &imgdc, WORD &iDay, 
		                        WORD &iLunarYear,
		                        WORD &iLunarMonth, WORD &iLuanrDay, 
								LONG startx, LONG starty);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_)
