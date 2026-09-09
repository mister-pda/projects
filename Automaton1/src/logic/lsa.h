#ifndef LSA_H
#define LSA_H

#include <QList>
#include "node.h"


class LSA
{
public:
    LSA() = default;
    ~ LSA();

    void createLSA();

    const QList<Node*>& getLSA() {return nodes;};

private:
    QList<Node*> nodes;
};

#endif // LSA_H
