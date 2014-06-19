#ifndef PICTURESCALE_H
#define PICTURESCALE_H

#include <QMouseEvent>
#include <QLabel>

class CPictureScale : public QLabel
{
    Q_OBJECT
public:
    explicit CPictureScale(int nIndex, const QRect& rect, QWidget* scaleParen, QWidget *parent = 0);

protected:
    void mouseDoubleClickEvent( QMouseEvent * );

private:
    int nLblIndex;
    bool bSwitch;
    QRect recRawSize;
    QWidget* pParent;
    QWidget* pScaleParent;

signals:
    void HideCtrl( bool );

public slots:

};

#endif // PICTURESCALE_H
