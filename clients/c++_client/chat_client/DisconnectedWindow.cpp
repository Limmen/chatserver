#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include "DisconnectedWindow.h"


DisconnectedWindow::DisconnectedWindow(QScrollArea *parent) : QScrollArea(parent)
{
    
    QWidget *main_widget = new QWidget;
    
    main_container = new QGridLayout(main_widget);
    main_container->setVerticalSpacing(10);
    main_container->setHorizontalSpacing(0);
        
    this->setWidget(main_widget);
    this->setWidgetResizable(true);

    QLabel *title = new QLabel();
    title->setText("<font size= '4' color='red'> <b>Your connection was lost</b></font>");
     title->setMaximumHeight(30);
    connect_button = new QPushButton("Connect again");
    connect_button->setMaximumHeight(50);
    
    main_container->addWidget(title, 0, 0, 1, 2);        
    main_container->addWidget(connect_button, 1, 0, 1, 2);
    
    connect(connect_button, SIGNAL (released()), this, SLOT (test_connection()));
}
void DisconnectedWindow::test_connection()
{
    this->new_connection();
}
