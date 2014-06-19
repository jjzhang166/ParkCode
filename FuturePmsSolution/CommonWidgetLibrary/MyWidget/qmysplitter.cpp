#include "MyWidget\qmysplitter.h"
#include <QTableWidget>
#include <QHeaderView>

QMySplitter::QMySplitter( QWidget *parent ) :
    QSplitter(parent)
{
}

QMySplitter::QMySplitter( Qt::Orientation direction, QWidget *parent ) :
    QSplitter( direction, parent )
{
}

QMySplitter::~QMySplitter( )
{

}

void QMySplitter::resizeEvent( QResizeEvent *event )
{
    ResizeLogWidget( event );
}

void QMySplitter::ResizeLogWidget( QResizeEvent *event )
{
    QTableWidget* pTable =  qobject_cast< QTableWidget* >(  widget( 1 ) );
    QHeaderView* pView = pTable->horizontalHeader( );
    pView->setResizeMode( QHeaderView::Fixed );
    pView->resizeSection( 0, pTable->width( ) );
}
