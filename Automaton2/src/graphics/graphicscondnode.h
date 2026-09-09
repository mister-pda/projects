#ifndef GRAPHICSCONDNODE_H
#define GRAPHICSCONDNODE_H

#include "graphicsnode.h"

#include "direction.h"

class GraphicsCondNode : public GraphicsNode
{
public:
    explicit GraphicsCondNode(Node* node, const QString& textIn) : GraphicsNode(node, textIn) {}

    void drawNode(QGraphicsScene* scene) override;
    Direction getZeroPos() const {return zeroPos;}
    Direction getOnePos() const {return onePos;}

    void setOuts(const Direction& zero, const Direction& one) {
        zeroPos = zero;
        onePos = one;
    }

private:
    Direction zeroPos;
    Direction onePos;
};

#endif // GRAPHICSCONDNODE_H
