#include "condnode.h"

#include <stdexcept>

void CondNode::setNextList(const QList<Node*>& nextList)
{
    if (nextList.length() != 2) { throw std::logic_error( "CondNode must have exactly 2 next nodes.");}

    Node::setNextList(nextList);
}
