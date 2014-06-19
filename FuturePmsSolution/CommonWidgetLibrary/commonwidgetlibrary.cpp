#include "commonwidgetlibrary.h"


QCommonWidgetLibrary::QCommonWidgetLibrary()
{
}

QCommonWidgetLibrary::~QCommonWidgetLibrary( )
{

}

void QCommonWidgetLibrary::BrowseLog( const QManipulateIniFile::LogFileNames file )
{
    static QDlgLogBrowser dlg;
    dlg.BrowseLog( file );
}
