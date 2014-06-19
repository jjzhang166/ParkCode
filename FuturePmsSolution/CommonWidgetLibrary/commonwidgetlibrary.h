#ifndef COMMONWIDGETLIBRARY_H
#define COMMONWIDGETLIBRARY_H

#include "CommonWidgetLibrary_global.h"
#include "Dialog/qdlglogbrowser.h"

class COMMONWIDGETLIBRARYSHARED_EXPORT QCommonWidgetLibrary : public QObject
{
    Q_OBJECT

public:
    QCommonWidgetLibrary();
    virtual ~QCommonWidgetLibrary( );

    void BrowseLog( const QManipulateIniFile::LogFileNames file  );

signals:

public slots:

};

#endif // COMMONWIDGETLIBRARY_H
