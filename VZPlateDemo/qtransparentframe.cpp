#include "qtransparentframe.h"
#include "ui_qtransparentframe.h"

QHash< HWND, QTransparentFrame* > QTransparentFrame::objHwndFrameHash;

QTransparentFrame::QTransparentFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QTransparentFrame)
{
    ui->setupUi(this);

    setWindowOpacity( 0.3 );
    setWindowFlags( Qt::FramelessWindowHint );

    hFrame = winId( );
    hVideoDc = GetDC( hFrame );
    hMyPen = CreatePen( PS_SOLID, 5, RGB( 255,0,0 ) );

    //A tool window does not appear in the taskbar
    LONG nRet = ::GetWindowLong( hFrame, GWL_EXSTYLE );
    nRet = nRet | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
    nRet = ::SetWindowLong( hFrame, GWL_EXSTYLE, nRet);

    //setAttribute(Qt::WA_TranslucentBackground);
    return;
    //HWND hFrame = winId( );
    //setWindowFlags( windowFlags( ) & ( ~Qt::WindowTitleHint ) );
    //setWindowFlags( Qt::FramelessWindowHint );
    //LONG nRet = ::GetWindowLong( hFrame, GWL_EXSTYLE);
    //nRet = nRet | WS_EX_LAYERED;
    //nRet = ::SetWindowLong( hFrame, GWL_EXSTYLE, nRet);
    //nRet = ::SetLayeredWindowAttributes( hFrame, 0, 10, LWA_ALPHA);
}

QTransparentFrame::~QTransparentFrame()
{
    Clearup( );
    delete ui;
}

void QTransparentFrame::DestroyFrame( )
{
    foreach ( QTransparentFrame* pFrame, objHwndFrameHash.values() ) {
        if ( NULL == pFrame ) {
            continue;
        }

        HWND hVideo = objHwndFrameHash.key( pFrame );
        objHwndFrameHash.remove( hVideo );
        pFrame->close( );
        delete pFrame;
    }
}

void QTransparentFrame::CreateFrame( HWND hVideoWnd, QRect& rectPlate, QRect& rectVideo )
{
    QTransparentFrame* pFrame = objHwndFrameHash.value( hVideoWnd, NULL );

    if ( NULL == pFrame ) {
        pFrame = new QTransparentFrame( );
        objHwndFrameHash.insert( hVideoWnd, pFrame );
    }

    pFrame->ShowWnd( hVideoWnd, rectPlate, rectVideo );
}

void QTransparentFrame::Clearup( )
{
    BOOL bRet = DeleteObject( hMyPen );
    bRet = ReleaseDC( hFrame, hVideoDc );
}

void QTransparentFrame::ShowWnd( HWND hVideoWnd, QRect& rectPlate, QRect& rectVideo  )
{
    if ( rectPlate.left( ) <= 0 || rectPlate.top( ) <= 0 ||
         rectPlate.right( ) <= 0 || rectPlate.bottom( ) <= 0 ) {
        hide( );
        return;
    }

    RECT sClientWnd;
    BOOL bRet = ::GetClientRect( hVideoWnd, &sClientWnd );

    double dXFactor = ( sClientWnd.right - sClientWnd.left ) * 1.0F / rectVideo.width( );
    double dYFactor = ( sClientWnd.bottom - sClientWnd.top ) * 1.0F / rectVideo.height( );

    sPlatePos.x = ( rectPlate.x( ) - 3 ) * dXFactor;
    sPlatePos.y = ( rectPlate.y( ) - 2 ) * dYFactor;
    bRet = ::ClientToScreen( hVideoWnd, &sPlatePos );
    setParent( NULL );

    int nWidth = ( rectPlate.width( ) + 5 ) * dXFactor;
    int nHeight = ( rectPlate.height( ) + 9 ) * dYFactor;

    sRectPos.setLeft( sPlatePos.x - 5 );
    sRectPos.setTop( sPlatePos.y - 5 );
    sRectPos.setWidth( nWidth + 10 );
    sRectPos.setHeight( nHeight + 10 );
    setGeometry( sRectPos );

    HGDIOBJ hRawObj = SelectObject( hVideoDc, hMyPen );

    int nStart = 2;
    sPoplyPoint[ 0 ].x = nStart;
    sPoplyPoint[ 0 ].y = nStart;

    sPoplyPoint[ 1 ].x = nWidth;
    sPoplyPoint[ 1 ].y = nStart;

    sPoplyPoint[ 2 ].x = nWidth;
    sPoplyPoint[ 2 ].y = nHeight;

    sPoplyPoint[ 3 ].x = nStart;
    sPoplyPoint[ 3 ].y = nHeight;

    sPoplyPoint[ 4 ].x = nStart;
    sPoplyPoint[ 4 ].y = nStart;

    bRet = Polyline( hVideoDc, sPoplyPoint, POLY_POINT_COUNT );
    hRawObj = SelectObject( hVideoDc, hRawObj );

    if ( !isVisible( ) ) {
        show( );
    }

    //::BringWindowToTop( hFrame );
}
