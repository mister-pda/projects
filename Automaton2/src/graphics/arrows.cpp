#include "arrows.h"

#include <QGraphicsLineItem>

void Arrows::line(QGraphicsScene* scene,
                  GraphicsNode* from,
                  GraphicsNode* to,
                  const QColor& color)
{
    QPointF p1(
        from->getX() + from->getWidth()/2,
        from->getY() + from->getHeight()
    );

    QPointF p2(
        to->getX() + to->getWidth()/2,
        to->getY()
    );

    QPen pen(color);

    pen.setWidth(3);

    scene->addLine(QLineF(p1, p2), pen);
}


void Arrows::line(QGraphicsScene* scene, const QPointF& from, const QPointF& to, const QColor& color) {
    QPen pen(color);
    pen.setWidth(3);

    scene->addLine(QLineF(from, to), pen);
}


void Arrows::arrow(QGraphicsScene* scene, const Direction& direction, const QPointF& p1, const QPointF& p2, const QColor& color) {
    QPen pen(color);
    pen.setWidth(3);

    scene->addLine(QLineF(p1, p2), pen);

    constexpr qreal arrowSize = 10;

    QPolygonF triangle;

    pen.setWidth(2);
    if (direction == Direction::Down) {
        triangle << QPointF(0, 0)
                 << QPointF(-arrowSize/2, -arrowSize)
                 << QPointF( arrowSize/2, -arrowSize);
    }
    else if (direction == Direction::Left) {
        triangle << QPointF(0, 0)
                 << QPointF(arrowSize, -arrowSize/2)
                 << QPointF(arrowSize, arrowSize/2);
    }
    else {
        triangle << QPointF(0, 0)
                 << QPointF(-arrowSize, -arrowSize/2)
                 << QPointF(-arrowSize, arrowSize/2);
    }

    auto* arrowHead = scene->addPolygon(triangle, pen, QBrush(color));

    arrowHead->setPos(p2);
}


void Arrows::zArrow(QGraphicsScene* scene, const Direction& direction, const QPointF& p1, const QPointF& p2, qreal midX, const QColor& color)
{
    QPen pen(color);

    pen.setWidth(3);

    scene->addLine(QLineF(
                       p1,
                       QPointF(midX, p1.y())),
                   pen);

    scene->addLine(QLineF(
                       QPointF(midX, p1.y()),
                       QPointF(midX, p2.y())),
                   pen);

    arrow(scene,
          direction,
          QPointF(midX, p2.y()),
          p2,
          color);
}
