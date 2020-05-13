#include "mylabel.h"

MyLabel::MyLabel(QWidget*parent):QLabel (parent)
{
    m_bLeftPress = true;
    setMouseTracking(true);
}

void MyLabel::slotClicked(bool,QString)
{
    qDebug()<<"Clicked";
}

void MyLabel::slotmouseMoved(QString)
{
    qDebug()<<"slotmouseMoved";
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
// 如果单击了就触发clicked信号
    if ( event->button() == Qt::LeftButton )
    {
        m_bLeftPress = true;
        emit clicked(m_bLeftPress, this->accessibleDescription());
    }
    else
    {
        m_bLeftPress = false;
        emit clicked(m_bLeftPress, this->accessibleDescription());
    }
    QLabel::mousePressEvent(event);
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(this->accessibleDescription());
    QLabel::mouseMoveEvent(event);
}

