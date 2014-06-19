#include "Header/picturescale.h"
#include "windows.h"

CPictureScale::CPictureScale(int nIndex, const QRect& rect, QWidget* scaleParent, QWidget *parent) :
    QLabel(parent)
{
    setScaledContents( true );
    bSwitch = true;
    recRawSize = rect;
    nLblIndex = nIndex;

    pParent = parent;
    pScaleParent = scaleParent;

    setFrameShape( Panel );
    setFrameShadow( Sunken );
    setLineWidth( 4 );

    QString strStyle = "background-image:url(none);\r\nbackground-color: rgb(255, 255, 255);";
    setStyleSheet( strStyle );

    setGeometry( rect );
}

void CPictureScale::mouseDoubleClickEvent( QMouseEvent * )
{
    if ( NULL == pixmap( ) || pixmap( )->isNull( ) ) {
        return;
    }

    emit HideCtrl( !bSwitch );

    setParent( bSwitch ? pScaleParent : pParent );
    setVisible( true );
#if false
    HWND hVidWnd = winId( );

    if ( bSwitch ) {
        BOOL bRet = ::BringWindowToTop( hVidWnd );
        bRet = FALSE;
    }
#endif
    QRect rec = bSwitch ? pScaleParent->geometry( ) : recRawSize;
    setGeometry( rec );

    if ( !bSwitch ) {
        rec.setWidth( recRawSize.width( ) );
        rec.setHeight( recRawSize.height( ) );
        rec.setX( 0 );
        rec.setY( 0 );
    } else {
        rec = geometry( );
        rec.setHeight( 731 );
        rec.setWidth( rec.width( ) - 49 );
        setGeometry( rec );
    }

    bSwitch = !bSwitch;
}
