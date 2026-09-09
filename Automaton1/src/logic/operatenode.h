#ifndef OPERATENODE_H
#define OPERATENODE_H

#include "node.h"

class OperateNode : public Node
{
public:
    OperateNode() = default;

    virtual ~OperateNode() = default;

    NodeType getNodeType() const override {
        return NodeType::Operate;
    }

    void setNextList(const QList<Node*>&) override;

    virtual void setNext(Node* nextNode) {
        setNextList({nextNode});
    }

    Node* getNext() const override {
        return getNextList().isEmpty() ? nullptr : getNextList()[0];
    }
};

#endif // OPERATENODE_H
