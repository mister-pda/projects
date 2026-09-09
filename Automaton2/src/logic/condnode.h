#ifndef CONDNODE_H
#define CONDNODE_H

#include "node.h"

class CondNode : public Node
{
public:
    CondNode() {Node::setNextList({nullptr, nullptr});}
    ~CondNode() = default;

    NodeType getNodeType() const override {return NodeType::Cond;}

    void setNextList(const QList<Node*>& nextList) override;
    void setNextList(Node* falseBranch, Node* trueBranch) {
        Node::setNextList({falseBranch, trueBranch});
    }
};

#endif // CONDNODE_H
