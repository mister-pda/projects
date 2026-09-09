#include "operatenode.h"

#include <stdexcept>

void OperateNode::setNextList(const QList<Node*>& nextNodesList)
{
    if (nextNodesList.length() > 1) {
        throw std::logic_error( "OperateNode can only have one next node.");
    }

    Node::setNextList(nextNodesList);
}
