#ifndef DONGLE_GLOBAL_H
#define DONGLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DONGLE_LIBRARY)
#  define DONGLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define DONGLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DONGLE_GLOBAL_H
