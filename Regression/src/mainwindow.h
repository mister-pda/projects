#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/CUSTOM_PLOT/qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createGraph();
    void createDots();
    void graph1FromTable();
    void graph2FromTable();
    void drawRegress();

private:
    Ui::MainWindow *ui;
    QCustomPlot* m_graphRegress;
    bool m_lockAspect;
    int m_regPol;

    void drawRegress1(QVector<double>, QVector<double>);
    void drawRegress2(QVector<double>, QVector<double>);

};
#endif // MAINWINDOW_H
