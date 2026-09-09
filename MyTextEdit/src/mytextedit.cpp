#include "mytextedit.h"

#include <QScrollBar>
#include <QPainter>

const QString MyTextEdit::vowels = QStringLiteral("aeiouyаеёиоуыэюя");
const QList<int> MyTextEdit::navigationKeys = {Qt::Key_Left, Qt::Key_Right, Qt::Key_Up, Qt::Key_Down};

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent) {}

void MyTextEdit::keyPressEvent(QKeyEvent *event)
{    
    if ((event->modifiers() & Qt::ControlModifier) || navigationKeys.contains(event->key())) {
        QTextEdit::keyPressEvent(event);
        return;
     }

    if (event->text().isEmpty() || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        return;

    QString text = event->text();
    QChar ch = text.at(0).toLower();
    QTextCharFormat currentFormat = this->currentCharFormat();

    if (vowels.contains(ch)) {
        QTextCharFormat vowelFormat = currentFormat;
        vowelFormat.setForeground(Qt::red);

        QTextCursor cursor = this->textCursor();
        cursor.insertText(text.toUpper(), vowelFormat);

        currentFormat.clearForeground();
        this->setCurrentCharFormat(currentFormat);
        this->ensureCursorVisible();

    } else {
        if (currentFormat.foreground().color() == Qt::red) {
            currentFormat.clearForeground();
            this->setCurrentCharFormat(currentFormat);
        }
        QTextEdit::keyPressEvent(event);
    }
}

void MyTextEdit::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);

    if (this->toPlainText().isEmpty()){
        QPainter painter(viewport());
        painter.setPen(Qt::gray);

        QPoint pos = cursorRect().topLeft();
        pos.setY(pos.y() + fontMetrics().ascent());

        QFont font = painter.font();
        font.setItalic(true);
        font.setPointSize(10);

        painter.setFont(font);
        painter.drawText(pos, "Начните вводить текст — гласные выводятся красными и заглавными");
    }
}

