#ifndef ARROWS_H
#define ARROWS_H

#include <QGraphicsScene>
#include "direction.h"

#include "graphicsnode.h"

class Arrows
{
public:

    static void line(QGraphicsScene* scene, GraphicsNode* from, GraphicsNode* to, const QColor& color);
    static void line(QGraphicsScene* scene, const QPointF& from, const QPointF& to, const QColor& color);

    static void arrow(QGraphicsScene* scene, const Direction& direction, const QPointF& p1, const QPointF& p2, const QColor& color);

    static void zArrow(QGraphicsScene* scene, const Direction& direction, const QPointF& p1, const QPointF& p2, qreal midX, const QColor& color);
};

#endif // ARROWS_H
