#include "graphicscondnode.h"

#include <QGraphicsScene>

void GraphicsCondNode::drawNode(QGraphicsScene *scene)
{
    item = nullptr;
    textItem = nullptr;

    QPolygonF diamond;

    diamond << QPointF(getX(), getY() + getHeight()/2)
            << QPointF(getX() + getWidth()/2, getY())
            << QPointF(getX() + getWidth(),
                       getY() + getHeight()/2)
            << QPointF(getX() + getWidth()/2,
                       getY() + getHeight());

    QPen pen;

    pen.setWidth(3);

    QBrush brush;

    if (logicNode->activationState() == Node::ActivationState::Current)
    {
        brush.setColor(Qt::red);
    }
    else if (logicNode->activationState() == Node::ActivationState::Previous)
    {
        brush.setColor(Qt::yellow);
    }
    else
    {
        brush.setColor(Qt::white);
    }

    brush.setStyle(Qt::SolidPattern);

    item = scene->addPolygon(diamond,
                             pen,
                             brush);

    drawText(item);

    auto* zeroText = scene->addText("0");
    auto* oneText  = scene->addText("1");

    switch (zeroPos)
    {
    case Direction::Right:
        zeroText->setPos(getX() + getWidth() + 5,
                         getY() + getHeight()/2 + 5);
        break;

    case Direction::Left:
        zeroText->setPos(getX() - 10,
                         getY() + getHeight()/2 + 5);
        break;

    case Direction::Down:
        zeroText->setPos(getX() + getWidth()/2,
                         getY() + getHeight() + 5);
        break;
    }

    switch (onePos)
    {
    case Direction::Right:
        oneText->setPos(getX() + getWidth() + 5,
                        getY() + getHeight()/2 + 5);
        break;

    case Direction::Left:
        oneText->setPos(getX() - 5,
                        getY() + getHeight()/2 + 5);
        break;

    case Direction::Down:
        oneText->setPos(getX() + getWidth()/2,
                        getY() + getHeight() + 5);
        break;
    }
}
