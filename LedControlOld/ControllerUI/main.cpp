#include <QtGui/QApplication>
#include "mainwindow.h"
#include "../ControllerCommon/qcontrollercommon.h"

// Doxygen Document generator

//-----------------------------------------------------------------------------
// Function: SaveIdentityInfo
//
// Purpose:  Saves the information for an identity to a file.
//           Displays a message if there was an error.
//
// Parameters:
// @Param0: Test0
// @Param1: Test1
//
// Returns:  HRESULT
//


int main(int argc, char *argv[])
{
    QTextCodec *pCodec = QControllerCommon::GetTextCodec( );

    QTextCodec::setCodecForLocale( pCodec );
    QTextCodec::setCodecForCStrings( pCodec );
    QTextCodec::setCodecForTr( pCodec );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec( );
}
