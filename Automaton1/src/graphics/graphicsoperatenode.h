#ifndef GRAPHICSOPERATENODE_H
#define GRAPHICSOPERATENODE_H

#include "graphicsnode.h"

class GraphicsOperateNode : public GraphicsNode
{
public:
    explicit GraphicsOperateNode(Node* node, const QString& textIn) : GraphicsNode(node, textIn) {}

    void drawNode(QGraphicsScene* scene) override;
};

#endif // GRAPHICSOPERATENODE_H
