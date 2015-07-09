#include "ConnectWindow.h"

ConnectWindow *connect_window;

ConnectWindow::ConnectWindow(QScrollArea *parent) : QScrollArea(parent)
{


    connect_window = this;
    
    QWidget *main_widget = new QWidget;
    
    main_container = new QGridLayout(main_widget);
    main_container->setVerticalSpacing(10);
    main_container->setHorizontalSpacing(0);
        
    this->setWidget(main_widget);
    this->setWidgetResizable(true);

    QLabel *title = new QLabel();
    title->setText("<font size= '4' color='black'> <b>Connect to a running chatserver </b></font>");
     title->setMaximumHeight(30);
    QLabel *host_label = new QLabel("Hostname:");
    host_label->setMaximumHeight(50);
    host_edit = new QTextEdit("");
    host_edit->setMaximumHeight(50);
    QLabel *port_label = new QLabel("Port:");
    port_label->setMaximumHeight(50);
    port_edit = new QTextEdit("");
    port_edit->setMaximumHeight(50);
    connect_button = new QPushButton("Connect");
    connect_button->setMaximumHeight(50);
    
    main_container->addWidget(title, 0, 0, 1, 2);        
    main_container->addWidget(host_label, 1, 0, 1, 1);
    main_container->addWidget(host_edit, 1, 1, 1, 1);
    main_container->addWidget(port_label, 2, 0, 1, 1);
    main_container->addWidget(port_edit, 2, 1, 1, 1);
    main_container->addWidget(connect_button, 3, 0, 1, 2);

    connect(connect_button, SIGNAL (released()), this, SLOT (test_connection()));
}

 
void ConnectWindow::test_connection()
{
    this->startChat();
}
