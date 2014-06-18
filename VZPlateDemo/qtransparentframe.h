#ifndef QTRANSPARENTFRAME_H
#define QTRANSPARENTFRAME_H

#include <QFrame>
#include <QRect>
#include <windows.h>
#include <QHash>
#include <QRect>

#define POLY_POINT_COUNT 5

namespace Ui {
class QTransparentFrame;
}

class QTransparentFrame : public QFrame
{
    Q_OBJECT
    
public:
    ~QTransparentFrame();
    static void DestroyFrame( );
    static void CreateFrame( HWND hVideoWnd, QRect& rectPlate, QRect& rectVideo );
    void ShowWnd( HWND hVideoWnd, QRect& rectPlate , QRect& rectVideo );

private:
    explicit QTransparentFrame(QWidget *parent = 0);
    void Clearup( );
    
private:
    Ui::QTransparentFrame *ui;
    static QHash< HWND, QTransparentFrame* > objHwndFrameHash;
    POINT sPlatePos;

    HWND hFrame;
    HDC hVideoDc;
    HPEN hMyPen;
    POINT sPoplyPoint[ POLY_POINT_COUNT ];
    QRect sRectPos;
};

#endif // QTRANSPARENTFRAME_H
