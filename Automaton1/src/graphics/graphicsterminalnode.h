#ifndef GRAPHICSTERMINALNODE_H
#define GRAPHICSTERMINALNODE_H

#include "graphicsnode.h"

class GraphicsTerminalNode : public GraphicsNode
{
public:
    explicit GraphicsTerminalNode(Node* node, const QString& textIn) : GraphicsNode(node, textIn) {}

    void drawNode(QGraphicsScene* scene) override;

private:
    qreal rad = 20.0;
};

#endif // GRAPHICSTERMINALNODE_H
