#ifndef TEXT_ENTRY_H
#define TEXT_ENTRY_H

#include <QKeyEvent>
#include <QTextEdit>
#include <QWidget>
//#include "MainWindow"
class text_entry : public QTextEdit
{
    Q_OBJECT
    //    MainWindow outer;
 public:
    explicit text_entry(QWidget *parent = 0) : QTextEdit(parent) { }
    void keyPressEvent(QKeyEvent *event);
    //  void setOuter(MainWindow outer);
};

#endif // TEXT_ENTRY_H
