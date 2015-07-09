#ifndef DISCONNECTEDWINDOW_H
#define DISCONNECTEDWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QTcpSocket>
#include <QGridLayout>
#include <QTextEdit> 
#include "text_entry.h"

class DisconnectedWindow : public QScrollArea
{
    Q_OBJECT


 public:
    QGridLayout *main_container;
    QTextEdit *host_edit;
    QTextEdit *port_edit;
    void new_connection();
    
    DisconnectedWindow(QScrollArea *parent=0);

    private slots:
        void test_connection();

 private:
        QPushButton *connect_button;
 
};


#endif
