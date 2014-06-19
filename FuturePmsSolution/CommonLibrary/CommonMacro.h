#ifndef COMMONMACRO_H
#define COMMONMACRO_H

#include <QDebug>

namespace MyMacros {
//
// QT_NO_DEBUG_OUTPUT // qDebug
//

#ifndef QT_NO_DEBUG
    #define OutputMsg( strMsg ) qDebug( ) << Q_FUNC_INFO << ":" << strMsg << endl
#else
    #define OutputMsg( strMsg ) // strMsg
#endif

    #define LogText( strText ) ( Q_FUNC_INFO + QString( ": " ) + strText )
    #define HANDSHAKE "Success"
}

#endif // COMMONMACRO_H
