#ifndef TEXT_ENTRY_H
#define TEXT_ENTRY_H

#include <QKeyEvent>
#include <QTextEdit>
#include <QWidget>


class text_entry : public QTextEdit
{
    Q_OBJECT
 public:
    explicit text_entry(QWidget *parent = 0) : QTextEdit(parent) { }
    void keyPressEvent(QKeyEvent *event);
};

#endif // TEXT_ENTRY_H
