#ifndef TOOLBARDOCKWIDGET_H
#define TOOLBARDOCKWIDGET_H

#include <QDockWidget>
#include <QCloseEvent>

namespace Ui {
    class CToolbarDockWidget;
}

class CToolbarDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CToolbarDockWidget(QWidget *parent = 0);
    ~CToolbarDockWidget();

protected:
    void  closeEvent ( QCloseEvent * event );

private:
    Ui::CToolbarDockWidget *ui;
};

#endif // TOOLBARDOCKWIDGET_H
