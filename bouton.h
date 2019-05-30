#ifndef BOUTON_H
#define BOUTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>


class Bouton:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:

    Bouton(QString name, QGraphicsItem * parent = nullptr);

    QGraphicsTextItem *text;

    //public methods
    void getText();
    //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    //QGraphicsTextItem *text;
};
#endif // bouton_H

