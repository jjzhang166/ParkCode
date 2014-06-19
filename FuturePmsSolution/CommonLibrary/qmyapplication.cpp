#include "qmyapplication.h"

QMyApplication::QMyApplication(int &argc, char **argv) : QApplication( argc, argv )
{
}

QMyApplication::QMyApplication( int &argc, char **argv, bool GUIenabled ) :
    QApplication( argc, argv, GUIenabled )
{
}

QMyApplication::QMyApplication( int &argc, char **argv, Type type ) :
    QApplication( argc, argv, type )
{
}

QMyApplication::~QMyApplication( )
{

}

bool QMyApplication::winEventFilter( MSG *msg, long *result )
{
    return QCoreApplication::winEventFilter( msg, result );
}
