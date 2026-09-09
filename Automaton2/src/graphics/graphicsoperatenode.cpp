#include "graphicsoperatenode.h"

#include <QGraphicsScene>

void GraphicsOperateNode::drawNode(QGraphicsScene *scene)
{
    QPen pen;
    pen.setWidth(3);

    QBrush brush;

    if (logicNode->activationState()
            == Node::ActivationState::Current)
    {
        QColor green(51, 255, 51);
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

    item = scene->addRect(
                getX(),
                getY(),
                getWidth(),
                getHeight(),
                pen,
                brush);

    drawText(item);
}
