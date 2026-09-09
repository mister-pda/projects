#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    QGraphicsScene* m_scene;
};

#endif // MAINWINDOW_H
