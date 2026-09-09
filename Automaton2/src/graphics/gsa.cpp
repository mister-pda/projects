#include "gsa.h"

#include <QColor>

#include "graphicsoperatenode.h"
#include "graphicscondnode.h"
#include "graphicsterminalnode.h"

#include "../logic/operatenode.h"
#include "../logic/condnode.h"
#include "../logic/terminalnode.h"

#include "arrows.h"


GSA::GSA(QGraphicsScene* scene)
    : m_scene(scene)
{
    timer = new QTimer(this);

    connect(timer,
            &QTimer::timeout,
            this,
            &GSA::nextNode);
}

void GSA::createGraph()
{
    TerminalNode* ys = new TerminalNode;
    OperateNode* y1 = new OperateNode;
    CondNode* p = new CondNode;
    CondNode* x1 = new CondNode;
    CondNode* px1 = new CondNode;
    CondNode* x2 = new CondNode;
    OperateNode* y2 = new OperateNode;
    OperateNode* y0 = new OperateNode;
    CondNode* x0 = new CondNode;
    OperateNode* y4 = new OperateNode;
    OperateNode* y3 = new OperateNode;
    TerminalNode* ye = new TerminalNode;

    ys->setStart(true);
    ye->setEnd(true);

    ys->setNext(y1);
    y1->setNext(p);
    p->setNextList(x1, px1);
    x1->setNextList(y3, y0);
    y0->setNext(x0);
    x0->setNextList(y4, y3);
    y4->setNext(y3);
    px1->setNextList(x2, y3);
    x2->setNextList(y3, y2);
    y2->setNext(y3);
    y3->setNext(ye);

    nodes = {ys, y0, y1, y2, y3, y4, ye, x0, x1, px1, x2, p};

    GraphicsTerminalNode* ysView = new GraphicsTerminalNode(ys, "Yн");
    GraphicsOperateNode* y0View = new GraphicsOperateNode(y0, "Y0");
    GraphicsOperateNode* y1View = new GraphicsOperateNode(y1, "Y1");
    GraphicsCondNode* pView = new GraphicsCondNode(p, "P");
    GraphicsCondNode* x0View = new GraphicsCondNode(x0, "X0");
    GraphicsOperateNode* y2View = new GraphicsOperateNode(y2, "Y2");
    GraphicsCondNode* x1View = new GraphicsCondNode(x1, "X1");
    GraphicsOperateNode* y3View = new GraphicsOperateNode(y3, "Y3");
    GraphicsCondNode* x2View = new GraphicsCondNode(x2, "X2");
    GraphicsCondNode* px1View = new GraphicsCondNode(px1, "X1");
    GraphicsOperateNode* y4View = new GraphicsOperateNode(y4, "Y4");
    GraphicsTerminalNode* yeView = new GraphicsTerminalNode(ye, "Yк");

    pView->setOuts(Direction::Left, Direction::Right);
    x1View->setOuts(Direction::Right, Direction::Down);
    x0View->setOuts(Direction::Down, Direction::Right);
    px1View->setOuts(Direction::Down, Direction::Left);
    x2View->setOuts(Direction::Left, Direction::Down);

    ysView->setPos(300, 60);
    y1View->setPos(300, 130);
    pView->setPos(300, 200);
    x1View->setPos(150, 290);
    px1View->setPos(450, 290);
    y0View->setPos(150, 380);
    x0View->setPos(150, 470);
    y4View->setPos(150, 560);
    x2View->setPos(450, 380);
    y2View->setPos(450, 470);
    y3View->setPos(300, 670);
    yeView->setPos(300, 740);

    graphicsNodes = {
        ysView,
        y0View,
        y1View,
        y2View,
        y3View,
        y4View,
        yeView,
        x0View,
        x1View,
        px1View,
        x2View,
        pView
    };

    redraw();
}

QColor GSA::connectionColor(Node* from, Node* to) const
{
    if (to == currentNode && previousNodes.contains(from)){
        return Qt::red;
    }
    if (previousNodes.contains(to) && previousNodes.contains(from)){
        return Qt::yellow;
    }

    return Qt::black;
}

void GSA::redraw()
{
    m_scene->clear();

    for (GraphicsNode* node : graphicsNodes)
    {
        node->drawNode(m_scene);
    }


    Arrows::line(m_scene,
                 graphicsNodes[0], // Ys
                 graphicsNodes[2], // Y1
                 connectionColor(nodes[0], nodes[1]));

    Arrows::line(m_scene,
                 graphicsNodes[2], // Y1
                 graphicsNodes[11],   // p
                 connectionColor(nodes[1], nodes[11]));

    Arrows::line(m_scene,
                 graphicsNodes[8], // x1
                 graphicsNodes[1], // y0
                 connectionColor(nodes[8], nodes[1]));

    Arrows::line(m_scene,
                 graphicsNodes[1], // y0
                 graphicsNodes[7], // x0
                 connectionColor(nodes[1], nodes[7]));

    Arrows::line(m_scene,
                 graphicsNodes[7], // x0
                 graphicsNodes[5], // y4
                 connectionColor(nodes[7], nodes[5]));

    Arrows::line(m_scene,
                 graphicsNodes[9], // px1
                 graphicsNodes[10], // x2
                 connectionColor(nodes[9], nodes[10]));

    Arrows::line(m_scene,
                 graphicsNodes[10], // x2
                 graphicsNodes[3], // y2
                 connectionColor(nodes[10], nodes[3]));

    Arrows::line(m_scene,
                 graphicsNodes[4], //y3
                 graphicsNodes[6], //ye
                 connectionColor(nodes[4], nodes[6]));


    // P -> X1
    QPointF from(
            graphicsNodes[11]->getX(),
            graphicsNodes[11]->getY() + graphicsNodes[11]->getHeight() / 2
    );
    QPointF mid(
            graphicsNodes[8]->getX()+graphicsNodes[8]->getWidth() / 2,
            graphicsNodes[11]->getY() + graphicsNodes[11]->getHeight() / 2
    );

    QPointF to(
            graphicsNodes[8]->getX()+graphicsNodes[8]->getWidth() / 2,
            graphicsNodes[8]->getY()
    );
    Arrows::line(m_scene, from, mid, connectionColor(nodes[11], nodes[8]));
    Arrows::line(m_scene, mid, to, connectionColor(nodes[11], nodes[8]));


    // P -> PX1
    QPointF fromPtoPX1(
        graphicsNodes[11]->getX() + graphicsNodes[11]->getWidth(),
        graphicsNodes[11]->getY() + graphicsNodes[11]->getHeight() / 2
    );
    QPointF midPtoPX1(
        graphicsNodes[9]->getX() + graphicsNodes[9]->getWidth() / 2,
        graphicsNodes[11]->getY() + graphicsNodes[11]->getHeight() / 2
    );
    QPointF toPtoPX1(
        graphicsNodes[9]->getX() + graphicsNodes[9]->getWidth() / 2,
        graphicsNodes[9]->getY()
    );
    Arrows::line(m_scene, fromPtoPX1, midPtoPX1, connectionColor(nodes[11], nodes[9]));
    Arrows::line(m_scene, midPtoPX1, toPtoPX1, connectionColor(nodes[11], nodes[9]));


    // Y4 -> Y3
    QPointF y4bot(
        graphicsNodes[5]->getX() + graphicsNodes[5]->getWidth() / 2,
        graphicsNodes[5]->getY() + graphicsNodes[5]->getHeight()
    );
    QPointF y4bus(
        graphicsNodes[5]->getX() + graphicsNodes[5]->getWidth() / 2,
        650
    );

    QPointF Y3bus(
        graphicsNodes[4]->getX()+graphicsNodes[4]->getWidth() / 2,
        650
    );
    QPointF Y3Top(
        graphicsNodes[4]->getX()+graphicsNodes[4]->getWidth() / 2,
        graphicsNodes[4]->getY()
    );

    Arrows::line(m_scene, y4bot, y4bus, connectionColor(nodes[5], nodes[4]));
    Arrows::line(m_scene, y4bus, Y3bus, connectionColor(nodes[5], nodes[4]));
    Arrows::line(m_scene, Y3bus, Y3Top, connectionColor(nodes[5], nodes[4]));


    // X1 -> Y3
    QPointF X1right(
        graphicsNodes[8]->getX() + graphicsNodes[8]->getWidth(),
        graphicsNodes[8]->getY() + graphicsNodes[8]->getHeight() / 2
    );
    QPointF X1mid(
        300,
        graphicsNodes[8]->getY() + graphicsNodes[8]->getHeight() / 2
    );
    QPointF X1bus(
        300,
        650
    );


    Arrows::line(m_scene, X1right, X1mid, connectionColor(nodes[8], nodes[4]));
    Arrows::line(m_scene, X1mid, X1bus, connectionColor(nodes[8], nodes[4]));
    if (connectionColor(nodes[8], nodes[4]) != Qt::black){
        Arrows::line(m_scene, X1bus, Y3bus, connectionColor(nodes[8], nodes[4]));
        Arrows::line(m_scene, Y3bus, Y3Top, connectionColor(nodes[8], nodes[4]));
    }


    // X0 -> Y3
    QPointF x0right(
        graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth(),
        graphicsNodes[7]->getY() + graphicsNodes[7]->getHeight() / 2
    );
    QPointF x0mid(
        270,
        graphicsNodes[7]->getY() + graphicsNodes[7]->getHeight() / 2
    );
    QPointF x0bus(
        270,
        650
    );

    QColor conColor;
    if (previousNodes.contains(nodes[5]))
        conColor = Qt::black;
    else
        conColor =  connectionColor(nodes[7], nodes[4]);

    Arrows::line(m_scene, x0right, x0mid, conColor);
    Arrows::line(m_scene, x0mid, x0bus, conColor);
    if (conColor != Qt::black){
        Arrows::line(m_scene, x0bus, Y3bus, conColor);
        Arrows::line(m_scene, Y3bus, Y3Top, conColor);
    }


    // Y2 -> Y3
    QPointF y2bot(
        graphicsNodes[3]->getX() + graphicsNodes[3]->getWidth() / 2,
        graphicsNodes[3]->getY() + graphicsNodes[3]->getHeight()
    );
    QPointF y2bus(
        graphicsNodes[3]->getX() + graphicsNodes[3]->getWidth() / 2,
        650
    );

    Arrows::line(m_scene, y2bot, y2bus, connectionColor(nodes[3], nodes[4]));
    Arrows::line(m_scene, y2bus, Y3bus, connectionColor(nodes[3], nodes[4]));
    if (connectionColor(nodes[3], nodes[4]) != Qt::black)
        Arrows::line(m_scene, Y3bus, Y3Top, connectionColor(nodes[3], nodes[4]));


    // PX1 -> Y3
    QPointF px1left(
        graphicsNodes[9]->getX(),
        graphicsNodes[9]->getY() + graphicsNodes[9]->getHeight() / 2
    );
    QPointF px1mid(
        400,
        graphicsNodes[9]->getY() + graphicsNodes[9]->getHeight() / 2
    );
    QPointF px1busCon(
        400,
        650
    );

    Arrows::line(m_scene, px1left, px1mid, connectionColor(nodes[9], nodes[4]));
    Arrows::line(m_scene, px1mid, px1busCon, connectionColor(nodes[9], nodes[4]));
    if (connectionColor(nodes[9], nodes[4]) != Qt::black){
        Arrows::line(m_scene, px1busCon, Y3bus, connectionColor(nodes[9], nodes[4]));
        Arrows::line(m_scene, Y3bus, Y3Top, connectionColor(nodes[9], nodes[4]));
    }



    // X2 -> Y3
    QPointF x2left(
        graphicsNodes[10]->getX(),
        graphicsNodes[10]->getY() + graphicsNodes[10]->getHeight() / 2
    );
    QPointF x2mid(
        430,
        graphicsNodes[10]->getY() + graphicsNodes[10]->getHeight() / 2
    );
    QPointF x2busCon(
        430,
        650
    );

    if (previousNodes.contains(nodes[3]))
        conColor = Qt::black;
    else
        conColor = connectionColor(nodes[10], nodes[4]);

    Arrows::line(m_scene, x2left, x2mid, conColor);
    Arrows::line(m_scene, x2mid, x2busCon, conColor);
    if (conColor != Qt::black){
        Arrows::line(m_scene, x2busCon, Y3bus, conColor);
        Arrows::line(m_scene, Y3bus, Y3Top, conColor);
    }

}

QString GSA::nodeTypeName(Node* node) const
{
    switch(node->getNodeType())
    {
    case Node::NodeType::Terminal:
        return "терминальной";

    case Node::NodeType::Operate:
        return "операторной";

    case Node::NodeType::Cond:
        return "условной";
    }

    return "";
}

QString GSA::nodeName(Node* node) const
{
    for (GraphicsNode* gNode : graphicsNodes)
    {
        if (gNode->getNode() == node)
        {
            return gNode->getText();
        }
    }

    return "";
}

void GSA::start()
{
    timer->stop();

    for (Node* node : nodes)
    {
        node->setActivationState(
                    Node::ActivationState::Inactive);
    }

    previousNodes.clear();

    currentNode = nodes[0];

    currentNode->setActivationState(
                Node::ActivationState::Current);

    redraw();

    emit logMessage("СТАРТ");

    timer->start(900);
}

void GSA::nextNode()
{
    if (!currentNode)
        return;

    if (currentNode->getNodeType()
            == Node::NodeType::Cond)
    {
        timer->stop();

        emit logMessage(
                    "ожидание условия 0/1");

        return;
    }

    if (currentNode->getNodeType() == Node::NodeType::Terminal)
        {
            TerminalNode* terminal = static_cast<TerminalNode*>(currentNode);

            if (terminal->isEnd())
            {
                timer->stop();
                emit logMessage("Достигнута конечная вершина \"Yк\"");
                return;
            }
        }

    previousNodes.append(currentNode);

    currentNode->setActivationState(
                Node::ActivationState::Previous);

    Node* next = currentNode->getNext();

    currentNode = next;

    currentNode->setActivationState(
                Node::ActivationState::Current);

    redraw();

    emit logMessage(
        QString("Переход от %1 вершины \"%2\" к %3 вершине \"%4\"")
            .arg(nodeTypeName(previousNodes.isEmpty()
                              ? currentNode
                              : previousNodes.last()))
            .arg(nodeName(previousNodes.isEmpty()
                          ? currentNode
                          : previousNodes.last()))
            .arg(nodeTypeName(currentNode))
            .arg(nodeName(currentNode))
    );
}

void GSA::chooseBranch(bool branch)
{
    if (!currentNode)
        return;

    if (currentNode->getNodeType()
            != Node::NodeType::Cond)
    {
        return;
    }

    for (Node* node : previousNodes)
    {
        node->setActivationState(Node::ActivationState::Inactive);
    }

    previousNodes.clear();

    currentNode->setActivationState(Node::ActivationState::Previous);

    CondNode* cond = static_cast<CondNode*>(currentNode);

    Node* next =
            branch
            ? cond->getNextList()[1]
            : cond->getNextList()[0];

    previousNodes.append(currentNode);

    currentNode = next;

    currentNode->setActivationState(Node::ActivationState::Current);

    redraw();

    emit logMessage(
        QString("Переход по ветке %1 от условной вершины \"%2\" к %3 вершине \"%4\"")
            .arg(branch ? "1" : "0")
            .arg(nodeName(cond))
            .arg(nodeTypeName(currentNode))
            .arg(nodeName(currentNode))
    );

    timer->start(900);
}
