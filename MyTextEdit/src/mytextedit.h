#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>

class MyTextEdit : public QTextEdit {
public:
    MyTextEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *e) override;

private:
    static const QString vowels;
    static const QList<int> navigationKeys;
};

#endif // MYTEXTEDIT_H
