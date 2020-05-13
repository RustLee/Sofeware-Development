#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QString>

class MyLabel:public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget*parent = nullptr);
    ~MyLabel(){}
signals:
    void clicked(bool,QString);
    void mouseMoved(QString);
public slots:
    void slotClicked(bool m_bLeftPress,QString accessibleDescription);
    void slotmouseMoved(QString accessibleDescription);
protected:
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseMoveEvent( QMouseEvent * event );
private:
    bool m_bLeftPress;
};

#endif // MYLABEL_H
