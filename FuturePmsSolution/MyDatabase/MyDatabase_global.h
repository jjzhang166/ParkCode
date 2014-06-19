#ifndef MYDATABASE_GLOBAL_H
#define MYDATABASE_GLOBAL_H

#include <QObject>
#include <QtCore/qglobal.h>

#if defined(MYDATABASE_LIBRARY)
#  define MYDATABASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MYDATABASESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYDATABASE_GLOBAL_H
