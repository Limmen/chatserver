#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QPushButton>
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QTcpSocket>
#include <QGridLayout>
#include <QTextEdit> 
#include "text_entry.h"

class ConnectWindow : public QScrollArea
{
    Q_OBJECT


 public:
    text_entry *txt;
    QGridLayout *main_container;
    QTextEdit *host_edit;
    QTextEdit *port_edit;
    void startChat();

    
    ConnectWindow(QScrollArea *parent=0);

    private slots:
        void test_connection();

 private:
        QPushButton *connect_button;
 
};


#endif
