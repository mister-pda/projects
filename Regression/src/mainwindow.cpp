#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_graphRegress{new QCustomPlot}
    , m_regPol{1}
{
    //ui->setupUi(this);
    //this->layout()->addWidget(m_graphRegress);

    setCentralWidget(m_graphRegress);

    m_graphRegress->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    m_graphRegress->addGraph();
    m_graphRegress->addGraph();

    graph1FromTable();

    QToolButton *lockBtn = new QToolButton(m_graphRegress);

    lockBtn->setCheckable(true);
    lockBtn->setAutoRaise(true);
    lockBtn->setIcon(QIcon(":/icons/icons/lock-grey.svg"));
    lockBtn->setToolTip("Lock aspect ratio");
    lockBtn->resize(30, 30);
    lockBtn->move(40, 10);
    lockBtn->raise();
    lockBtn->setStyleSheet(R"(
        QToolButton {
            background: rgba(255, 255, 255, 160);
            border-radius: 8px;
            border: 2px solid #737373;
            padding: 0px;
        }
        QToolButton:hover {
            border: 2px solid #585858;
            background: rgba(228, 228, 228, 160);
        }
    )");

    connect(lockBtn, &QToolButton::toggled, this, [=](bool checked){
        if (checked == true){
            lockBtn->setIcon(QIcon(":/icons/icons/lock-open-grey.svg"));
        }
        else{
            lockBtn->setIcon(QIcon(":/icons/icons/lock-grey.svg"));
        }
        m_lockAspect = checked;
        m_graphRegress->replot();
    });


    QToolButton* regBtn = new QToolButton(m_graphRegress);
    regBtn->setCheckable(true);
    regBtn->move(80, 10);
    regBtn->setAutoRaise(true);
    regBtn->setText("Linear");
    regBtn->resize(60, 30);
    regBtn->setStyleSheet(R"(
        QToolButton {
            color: #737373;
            font-size: 14px;
            background: rgba(255, 255, 255, 160);
            border-radius: 8px;
            border: 2px solid #737373;
            padding: 0px;
        }
        QToolButton:hover {
            border: 2px solid #585858;
            background: rgba(228, 228, 228, 160);
        }
    )");

    QFont f = regBtn->font();
    f.setWeight(QFont::DemiBold);
    regBtn->setFont(f);

    connect(regBtn, &QToolButton::toggled, this, [=](bool checked){
        m_graphRegress->graph(1)->setVisible(false);
        if (checked){
            regBtn->setText("Quad");
            graph2FromTable();
            m_regPol = 2;
        }
        else{
            regBtn->setText("Linear");
            graph1FromTable();
            m_regPol = 1;
        }
    });

    connect(m_graphRegress, &QCustomPlot::mousePress, this, [=](QMouseEvent* event){
            drawRegress();
        });

    connect(m_graphRegress, &QCustomPlot::afterReplot, this, [=]() {
        if (!m_lockAspect)
            m_graphRegress->yAxis->setScaleRatio(m_graphRegress->xAxis, 1.5);
    });

    //m_graphRegress->addGraph();
    //m_graphRegress->addGraph();
    //connect(m_graphRegress, &QCustomPlot::mousePress, this, [=](QMouseEvent* event){
    //    createGraph();
    //});
    //createDots();
}

MainWindow::~MainWindow()
{
    delete m_graphRegress;
    delete ui;

}

void MainWindow::createGraph()
{
    QVector<double> x, y;
    for (double i = -10; i <= 10; i += 0.1)
    {
        x.append(i);
        y.append(sin(i));
    }
    m_graphRegress->xAxis->setRange(-10, 10);
    m_graphRegress->yAxis->setRange(-10, 10);
    m_graphRegress->graph(0)->setData(x, y);
    m_graphRegress->replot();
}

void MainWindow::createDots()
{
    QVector<double> x, y;
    for (int i = 0; i != 10; ++i){
        x << QRandomGenerator::global()->bounded(-9, 10);
        y << QRandomGenerator::global()->bounded(-9, 10);
    }
    QCPScatterStyle style;
    m_graphRegress->graph(1)->setLineStyle(QCPGraph::lsNone);
    style.setShape(QCPScatterStyle::ssPlusCircle);
    style.setPen(QPen(Qt::red));
    style.setSize(6);
    m_graphRegress->graph(1)->setScatterStyle(style);
    m_graphRegress->graph(1)->setData(x, y);
    m_graphRegress->xAxis->setRange(-10, 10);
    m_graphRegress->yAxis->setRange(-10, 10);
    m_graphRegress->replot();

}

void MainWindow::graph1FromTable(){
    QVector<double> x, y;
    QFile file("data.csv");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList values = line.split(";");

            if (values.size() >= 2) {
                x.append(values[0].toDouble());
                y.append(values[1].toDouble());
            }
        }
        m_graphRegress->graph(0)->setData(x, y);
        QCPScatterStyle style;
        m_graphRegress->graph(0)->setLineStyle(QCPGraph::lsNone);
        style.setShape(QCPScatterStyle::ssPlusCircle);
        style.setPen(QPen(Qt::red));
        style.setSize(6);
        m_graphRegress->graph(0)->setScatterStyle(style);
        m_graphRegress->xAxis->setRange(-10, 11);
        m_graphRegress->yAxis->setRange(-10, 11);
        m_graphRegress->replot();
    }
    else{
        qDebug() << "file opening failed";
    }
}

void MainWindow::graph2FromTable()
{
    QVector<double> x, y;
    QFile file("data2.csv");
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList values = line.split(";");

            if (values.size() >= 2) {
                x.append(values[0].toDouble());
                y.append(values[1].toDouble());
            }
        }
        m_graphRegress->graph(0)->setData(x, y);
        QCPScatterStyle style;
        m_graphRegress->graph(0)->setLineStyle(QCPGraph::lsNone);
        style.setShape(QCPScatterStyle::ssPlusCircle);
        style.setPen(QPen(Qt::red));
        style.setSize(6);
        m_graphRegress->graph(0)->setScatterStyle(style);
        m_graphRegress->xAxis->setRange(-10, 11);
        m_graphRegress->yAxis->setRange(-10, 11);
        m_graphRegress->replot();
    }
    else{
        qDebug() << "file opening failed";
    }
}

void MainWindow::drawRegress(){
    QVector<double> x, y;
    QCPGraph *graph = m_graphRegress->graph(0);
    QCPDataContainer<QCPGraphData>::const_iterator it = graph->data()->constBegin();
    QCPDataContainer<QCPGraphData>::const_iterator end = graph->data()->constEnd();

    for (; it != end; ++it) {
        x.append(it->key);
        y.append(it->value);
        }

    if (m_regPol == 1){
        drawRegress1(x, y);
    }
    else if (m_regPol == 2){
        drawRegress2(x, y);
    }
}

void MainWindow::drawRegress1(QVector<double> x, QVector<double> y){
    double ap_x = 0;;
    double ap_y = 0;
    double ap_xy = 0;
    double ap_x2 = 0;
    for (int i = 0; i < x.length(); ++i){
        ap_xy += x[i]*y[i];
        ap_x2 += x[i]*x[i];
        ap_x += x[i];
        ap_y += y[i];
    }
    ap_x /= x.length();
    ap_y /= y.length();
    ap_xy /=y.length();
    ap_x2 /=x.length();

    double a1;
    a1 = (ap_xy-ap_x*ap_y)/(ap_x2-ap_x*ap_x);
    double a0 = ap_y-a1*ap_x;

    QVector<double> x_reg, y_reg;

    for (int i = -20; i != 21; ++i){
        x_reg.append(i);
        y_reg.append(a0 + a1*i);
    }

    m_graphRegress->graph(1)->setData(x_reg, y_reg);
    m_graphRegress->graph(1)->setVisible(true);
    m_graphRegress->replot();
}

void MainWindow::drawRegress2(QVector<double> x, QVector<double> y){
    double s_xy = 0, s_x = 0, s_y = 0, s_x2 = 0, s_x3 = 0, s_x4 = 0, s_x2y = 0, d, d0, d1, d2, a0, a1, a2;

    for (int i = 0; i != x.length(); ++i){
        s_x += x[i];
        s_y += y[i];
        s_xy += x[i] * y[i];
        s_x2 += x[i] * x[i];
        s_x2y += x[i] * x[i] * y[i];
        s_x3 += x[i] * x[i] * x[i];
        s_x4 += x[i] * x[i] * x[i] * x[i];
    }

    d = x.length() * (s_x2 * s_x4 - s_x3 * s_x3) - s_x * (s_x * s_x4 - s_x3 * s_x2) + s_x2 * (s_x * s_x3 - s_x2 * s_x2);
    d0 = s_y * (s_x2 * s_x4 - s_x3 * s_x3) - s_x * (s_xy * s_x4 - s_x3 * s_x2y) + s_x2 * (s_xy * s_x3 - s_x2 * s_x2y);
    d1 = x.length() * (s_xy * s_x4 - s_x3 * s_x2y) - s_y * (s_x * s_x4 - s_x3 * s_x2) + s_x2 * (s_x * s_x2y - s_x2 * s_xy);
    d2 = x.length() * (s_x2 * s_x2y - s_xy * s_x3) - s_x * (s_x * s_x2y - s_xy * s_x2) + s_y * (s_x * s_x3 - s_x2 * s_x2);

    a0 = d0/d;
    a1 = d1/d;
    a2 = d2/d;
    QVector<double> x_reg, y_reg;

    for (int i = -20; i != 21; ++i){
        x_reg.append(i);
        y_reg.append(a0 + a1 * i + a2 * i * i);
    }

    m_graphRegress->graph(1)->setData(x_reg, y_reg);
    m_graphRegress->graph(1)->setVisible(true);
    m_graphRegress->replot();
}




