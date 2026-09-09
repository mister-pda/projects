#include "graphicsterminalnode.h"

#include <QGraphicsScene>

void GraphicsTerminalNode::drawNode(QGraphicsScene *scene)
{
    QPainterPath path;

    QRectF r(getX(),
             getY(),
             getWidth(),
             getHeight());

    path.addRoundedRect(r, rad, rad);

    QPen pen;
    pen.setWidth(3);

    QBrush brush;

    if (logicNode->activationState()
            == Node::ActivationState::Current)
    {
        brush.setColor(Qt::red);
    }
    else if (logicNode->activationState()
             == Node::ActivationState::Previous)
    {
        brush.setColor(Qt::yellow);
    }
    else
    {
        brush.setColor(Qt::white);
    }

    brush.setStyle(Qt::SolidPattern);

    item = scene->addPath(path, pen, brush);

    drawText(item);
}
