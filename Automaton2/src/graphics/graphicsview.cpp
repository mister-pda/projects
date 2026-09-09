#include "graphicsview.h"

#include <QWheelEvent>
#include <QPainter>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(
                QGraphicsView::AnchorUnderMouse);
}

void GraphicsView::wheelEvent(QWheelEvent* event)
{
    constexpr double scaleFactor = 1.15;

    if (event->angleDelta().y() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(1.0 / scaleFactor,
              1.0 / scaleFactor);
    }
}
