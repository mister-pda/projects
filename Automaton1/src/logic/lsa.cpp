#include "lsa.h"
#include "logic/operatenode.h"
#include "logic/condnode.h"
#include "logic/terminalnode.h"

void LSA::createLSA()
{
    TerminalNode* ys = new TerminalNode;
    OperateNode* y0 = new OperateNode;
    ys->setNext(y0);
    OperateNode* y1 = new OperateNode;
    y0->setNext(y1);
    CondNode* x0 = new CondNode;
    y1->setNext(x0);
    OperateNode* y2 = new OperateNode;
    x0->setNextList(y0, y2);
    CondNode* x1 = new CondNode;
    y2->setNext(x1);
    OperateNode* y3 = new OperateNode;
    CondNode* x2 = new CondNode;
    x1->setNextList(y3, x2);
    TerminalNode* ye = new TerminalNode;
    x2->setNextList(ye, y1);

    nodes = {ys, y0, y1, x0, y2, x1, y3, x2, ye};
}


