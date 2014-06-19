#ifndef QMYSPLITTER_H
#define QMYSPLITTER_H

#include <QSplitter>

class QMySplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit QMySplitter(QWidget* parent = 0);
    explicit QMySplitter(Qt::Orientation direction, QWidget* parent = 0);
    ~QMySplitter();

protected:
    void resizeEvent( QResizeEvent * event );

private:
    void ResizeLogWidget( QResizeEvent * event );
    
signals:
    
public slots:
    
};

#endif // QMYSPLITTER_H
