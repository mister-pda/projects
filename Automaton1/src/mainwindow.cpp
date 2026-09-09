#include "mainwindow.h"

#include "graphics/gsa.h"
#include "graphics/graphicsview.h"

#include <QGraphicsScene>

#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_scene(new QGraphicsScene(this))
{
    GraphicsView* view = new GraphicsView(this);

    view->setScene(m_scene);
    view->setMinimumSize(700, 700);

    m_scene->setSceneRect(-300, -100, 1400, 1400);

    GSA* gsa = new GSA(m_scene);

    gsa->createGraph();

    QPushButton* startBtn = new QPushButton("Старт");
    QPushButton* zeroBtn = new QPushButton("0");
    QPushButton* oneBtn = new QPushButton("1");
    startBtn->setMinimumHeight(40);
    zeroBtn->setMinimumHeight(40);
    oneBtn->setMinimumHeight(40);

    QTextEdit* logs = new QTextEdit;

    logs->setReadOnly(true);

    connect(gsa, &GSA::logMessage, logs, &QTextEdit::append);

    connect(startBtn, &QPushButton::clicked, this, [=]()
    {
        gsa->start();
        startBtn->setText("Рестарт");
    });

    connect(zeroBtn, &QPushButton::clicked, this, [=]()
    {
        gsa->chooseBranch(false);
    });

    connect(oneBtn, &QPushButton::clicked, this, [=]()
    {
        gsa->chooseBranch(true);
    });

    QVBoxLayout* leftLayout = new QVBoxLayout;

    leftLayout->addWidget(startBtn);
    leftLayout->addWidget(zeroBtn);
    leftLayout->addWidget(oneBtn);
    leftLayout->addWidget(logs);

    QWidget* leftWidget = new QWidget;

    leftWidget->setLayout(leftLayout);

    QSplitter* splitter = new QSplitter;

    splitter->addWidget(leftWidget);
    splitter->addWidget(view);
    splitter->setSizes({250, 900});

    QWidget* central = new QWidget(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QLabel* lsaLabel = new QLabel;

    lsaLabel->setText(
        "ЛСА: "
        "Y<sub>н</sub>"
        "↓<sup>1</sup>"
        "Y<sub>0</sub>"
        "↓<sup>4</sup>"
        "Y<sub>1</sub>"
        "X<sub>0</sub>"
        "↑<sup>1</sup>"
        "Y<sub>2</sub>"
        "X<sub>1</sub>"
        "↑<sup>2</sup>"
        "X<sub>2</sub>"
        "↑<sup>3</sup>"
        "W"
        "↑<sup>4</sup>"
        "↓<sup>2</sup>"
        "Y<sub>3</sub>"
        "↓<sup>3</sup>"
        "Y<sub>к</sub>"
    );

    lsaLabel->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setPointSize(14);

    lsaLabel->setFont(font);

    QWidget* headerWidget = new QWidget();
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->addWidget(lsaLabel);
    headerLayout->setAlignment(Qt::AlignCenter);
    headerWidget->setMaximumHeight(50);

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(splitter);

    setCentralWidget(central);
}

MainWindow::~MainWindow() {}
