#include "mainwindow.h"
#include "mytextedit.h"

#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* widget = new QWidget(this);
    widget->setStyleSheet("background-color: lightgray;");
    setCentralWidget(widget);

    MyTextEdit* textEdit = new MyTextEdit(this);
    textEdit->setMaximumWidth(700);
    textEdit->setMinimumWidth(350);
    textEdit->setFixedHeight(50);
    textEdit->setWordWrapMode(QTextOption::NoWrap);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setStyleSheet("background-color: white;");

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(16);

    textEdit->setFont(font);

    QSpacerItem* leftSpacer = new QSpacerItem(50, 0);
    QSpacerItem* rightSpacer = new QSpacerItem(50, 0);
    QSpacerItem* upSpacer = new QSpacerItem(0, 50);
    QSpacerItem* downSpacer = new QSpacerItem(0, 50);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addSpacerItem(leftSpacer);
    layout->addWidget(textEdit, 1);
    layout->addSpacerItem(rightSpacer);

    QVBoxLayout* vLayout = new QVBoxLayout(widget);
    vLayout->addSpacerItem(upSpacer);
    vLayout->addLayout(layout, 1);
    vLayout->addSpacerItem(downSpacer);

}

MainWindow::~MainWindow()
{

}

