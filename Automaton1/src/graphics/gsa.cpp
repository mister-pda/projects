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
    OperateNode* y0 = new OperateNode;
    OperateNode* y1 = new OperateNode;
    CondNode* x0 = new CondNode;
    OperateNode* y2 = new OperateNode;
    CondNode* x1 = new CondNode;
    OperateNode* y3 = new OperateNode;
    CondNode* x2 = new CondNode;
    TerminalNode* ye = new TerminalNode;

    ys->setStart(true);
    ye->setEnd(true);

    ys->setNext(y0);
    y0->setNext(y1);
    y1->setNext(x0);
    x0->setNextList(y0, y2);
    y2->setNext(x1);
    y3->setNext(ye);
    x1->setNextList(y3, x2);
    x2->setNextList(ye, y1);

    nodes = {
        ys,
        y0,
        y1,
        x0,
        y2,
        x1,
        y3,
        x2,
        ye
    };

    GraphicsTerminalNode* ysView = new GraphicsTerminalNode(ys, "Yн");
    GraphicsOperateNode* y0View = new GraphicsOperateNode(y0, "Y0");
    GraphicsOperateNode* y1View = new GraphicsOperateNode(y1, "Y1");
    GraphicsCondNode* x0View = new GraphicsCondNode(x0, "X0");
    GraphicsOperateNode* y2View = new GraphicsOperateNode(y2, "Y2");
    GraphicsCondNode* x1View = new GraphicsCondNode(x1, "X1");
    GraphicsOperateNode* y3View = new GraphicsOperateNode(y3, "Y3");
    GraphicsCondNode* x2View = new GraphicsCondNode(x2, "X2");
    GraphicsTerminalNode* yeView = new GraphicsTerminalNode(ye, "Yк");

    x0View->setOuts(Direction::Right, Direction::Down);
    x1View->setOuts(Direction::Down, Direction::Left);
    x2View->setOuts(Direction::Down, Direction::Left);

    ysView->setPos(200, 20);
    y0View->setPos(200, 110);
    y1View->setPos(200, 200);
    x0View->setPos(200, 290);
    y2View->setPos(200, 380);
    x1View->setPos(200, 470);
    y3View->setPos(200, 560);
    x2View->setPos(20, 560);
    yeView->setPos(200, 650);

    graphicsNodes = {
        ysView,
        y0View,
        y1View,
        x0View,
        y2View,
        x1View,
        y3View,
        x2View,
        yeView
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
                 graphicsNodes[1], // Y0
                 connectionColor(nodes[0], nodes[1]));
    Arrows::line(m_scene,
                 graphicsNodes[1], // Y0
                 graphicsNodes[2],   // Y1
                 connectionColor(nodes[1], nodes[2]));

    Arrows::line(m_scene,
                 graphicsNodes[2], // Y1// X0
                 graphicsNodes[3],
                 connectionColor(nodes[2], nodes[3]));

    Arrows::line(m_scene,
                 graphicsNodes[3], // X0
                 graphicsNodes[4], // Y2
                 connectionColor(nodes[3], nodes[4]));

    Arrows::line(m_scene,
                 graphicsNodes[4], // Y2
                 graphicsNodes[5], // X1
                 connectionColor(nodes[4], nodes[5]));

    Arrows::line(m_scene,
                 graphicsNodes[5], // X1
                 graphicsNodes[6], // Y3
                 connectionColor(nodes[5], nodes[6]));

    Arrows::line(m_scene,
                 graphicsNodes[6], // Y3
                 graphicsNodes[8], // Ye
                 connectionColor(nodes[6], nodes[8]));

    // X0 -> Y0
    Arrows::zArrow(
        m_scene,
        Direction::Left,

        QPointF(
            graphicsNodes[3]->getX() + graphicsNodes[3]->getWidth(),
            graphicsNodes[3]->getY() + graphicsNodes[3]->getHeight()/2
        ),

        QPointF(
            graphicsNodes[1]->getX() + graphicsNodes[1]->getWidth()/2,
            graphicsNodes[1]->getY() - 20
        ),

        graphicsNodes[3]->getX()+ graphicsNodes[3]->getWidth()+ 80,
        connectionColor(nodes[3], nodes[1])
    );

    //X1 -> X2
    QPointF from(
        graphicsNodes[5]->getX(),
        graphicsNodes[5]->getY() + graphicsNodes[5]->getHeight() / 2
    );

    QPointF mid(
        graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth() / 2,
        graphicsNodes[5]->getY() + graphicsNodes[5]->getHeight() / 2
    );

    QPointF to(
        graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth() / 2,
        graphicsNodes[7]->getY()
    );

    Arrows::line(m_scene, from, mid, connectionColor(nodes[5], nodes[7]));
    Arrows::line(m_scene, mid, to, connectionColor(nodes[5], nodes[7]));


    //X2 -> Y1
    Arrows::zArrow(
        m_scene,
        Direction::Right,

        QPointF(
            graphicsNodes[7]->getX(),

            graphicsNodes[7]->getY()
                + graphicsNodes[7]->getHeight()/2
        ),

        QPointF(
            graphicsNodes[2]->getX()
                + graphicsNodes[2]->getWidth()/2,

            graphicsNodes[2]->getY() - 20
        ),

        graphicsNodes[7]->getX() - 80,
        connectionColor(nodes[7], nodes[2])
    );

    //X2 -> Ye

    Arrows::line(m_scene,
                 QPointF(
                     graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth() / 2,
                     graphicsNodes[7]->getY() + graphicsNodes[7]->getHeight()
                 ),
            QPointF(
                graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth() / 2,
                graphicsNodes[8]->getY() - 20
            ),
            connectionColor(nodes[7], nodes[8]));

    Arrows::line(m_scene,
                 QPointF(
                     graphicsNodes[7]->getX() + graphicsNodes[7]->getWidth() / 2,
                     graphicsNodes[8]->getY() - 20
                 ),
            QPointF(
                graphicsNodes[8]->getX() + graphicsNodes[8]->getWidth() / 2,
                graphicsNodes[8]->getY() - 20
            ),
            connectionColor(nodes[7], nodes[8]));
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
