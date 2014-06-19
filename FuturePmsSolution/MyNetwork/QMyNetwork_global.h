#ifndef QMYNETWORK_GLOBAL_H
#define QMYNETWORK_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>

#if defined(QMYNETWORK_LIBRARY)
#  define QMYNETWORKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMYNETWORKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMYNETWORK_GLOBAL_H
