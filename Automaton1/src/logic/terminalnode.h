#ifndef TERMINALNODE_H
#define TERMINALNODE_H

#include "operatenode.h"

class TerminalNode : public OperateNode
{
public:
    TerminalNode() = default;
    ~TerminalNode() = default;

    NodeType getNodeType() const override { return NodeType::Terminal; }

    void setStart(bool flag) { start = flag; }
    void setEnd(bool flag) { end = flag; }

    bool isStart() const { return start; }
    bool isEnd() const { return end; }

private:
    bool start = false;
    bool end = false;
};

#endif // TERMINALNODE_H
