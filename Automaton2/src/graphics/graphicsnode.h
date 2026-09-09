#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include <QObject>

#include <QRectF>

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

#include "../logic/node.h"

class GraphicsNode : public QObject
{
    Q_OBJECT

public:
    GraphicsNode(Node* node, const QString& textIn) : logicNode(node), text(textIn), rect(0, 0, width, height) {}

    virtual ~GraphicsNode() = default;

    void setPos(int x, int y) {rect.moveTo(x, y);}

    qreal getX() const {return rect.x();}
    qreal getY() const {return rect.y();}

    int getWidth() const {return width;}
    int getHeight() const {return height;}

    const QString& getText() const {return text;}
    Node* getNode() const {return logicNode;}

    virtual void drawNode(QGraphicsScene* scene) = 0;

protected:

    void drawText(QGraphicsItem* parent)
    {
        textItem = new QGraphicsTextItem(text, parent);

        textItem->setPos(
            parent->boundingRect().center().x() - textItem->boundingRect().width()/2,
            parent->boundingRect().center().y() - textItem->boundingRect().height()/2
        );
    }

protected:
    Node* logicNode = nullptr;

    QString text;

    QRectF rect;

    int width = 100;
    int height = 40;

    QGraphicsItem* item = nullptr;
    QGraphicsTextItem* textItem = nullptr;
};

#endif // GRAPHICSNODE_H
