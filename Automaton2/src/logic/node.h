#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QObject>

class Node : public QObject
{
    Q_OBJECT

public:

    enum class NodeType
    {
        Terminal,
        Operate,
        Cond
    };

    enum class ActivationState : uint8_t
    {
        Inactive = 0,
        Current,
        Previous
    };

    explicit Node(QObject* parent = nullptr) : QObject(parent) {}

    virtual ~Node() = default;

    virtual NodeType getNodeType() const = 0;

    void setActivationState(ActivationState state) {
        m_activationState = state;
        emit stateChanged();
    }

    ActivationState activationState() const {
        return m_activationState;
    }

    virtual void setNextList(const QList<Node*>& nextNodes);

    const QList<Node*>& getNextList() const {
        return next;
    }

    virtual Node* getNext() const {
        return nullptr;
    }

signals:

    void stateChanged();

private:
    QList<Node*> next;

    ActivationState m_activationState = ActivationState::Inactive;
};

#endif // NODE_H
