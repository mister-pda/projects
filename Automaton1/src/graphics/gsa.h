#ifndef GSA_H
#define GSA_H

#include <QObject>

#include <QList>
#include <QTimer>
#include <QGraphicsScene>

#include "../logic/node.h"

#include "graphicsnode.h"

class GSA : public QObject
{
    Q_OBJECT

public:
    explicit GSA(QGraphicsScene* scene);

    void createGraph();
    void start();
    void nextNode();
    void chooseBranch(bool branch);

signals:
    void logMessage(const QString& msg);

private:
    void redraw();

private:
    QGraphicsScene* m_scene = nullptr;

    QList<Node*> nodes;
    QList<GraphicsNode*> graphicsNodes;

    Node* currentNode = nullptr;
    QList<Node*> previousNodes;

    QTimer* timer = nullptr;

    QString nodeTypeName(Node* node) const;
    QString nodeName(Node* node) const;

    QColor connectionColor(Node* from, Node *to) const;
};

#endif // GSA_H
