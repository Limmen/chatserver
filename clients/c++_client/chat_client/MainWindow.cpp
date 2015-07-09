#include "MainWindow.h"
#include "text_entry.h"
#include <QSizePolicy>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeyEvent>
#include <QTime>
#include <QEventLoop>
#include <QString>
#include <QCoreApplication>
#include <QMessageBox>
MainWindow *main_gui;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    main_gui = this;

    connectFrame();
    
    help = new QAction("&Help", this);
    QAction *about = new QAction("&About", this);
    QMenu *main_menu;
    main_menu = menuBar()->addMenu("&Options");
    main_menu->addAction(help);
    main_menu->addAction(about);


    connect(help, SIGNAL(triggered()), this, SLOT (helpBox()));
    connect(about, SIGNAL(triggered()), this, SLOT (aboutBox()));
		

}

 void ConnectWindow::startChat(){
            main_gui->chat = new ChatWindow;
            QString host = host_edit->toPlainText();
            QString port_string = port_edit->toPlainText();
            int port = port_string.toInt();
            main_gui->chat->test_connection(host, port);
            host_edit->setText("Connecting..");
            port_edit->setText("Connecting..");
            main_gui->delay();
            if(main_gui->chat->socket_status == 3){
                main_gui->chatFrame();
            }
            else{
                host_edit->setText("<font color='red'> Could'nt connect </font> <font color='black'> </font>");
                port_edit->setText("<font color='red'> Could'nt connect </font> <font color='black'> </font>");
            }
 }            


void MainWindow::connectFrame(){
    connect_window = new ConnectWindow;
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    QVBoxLayout *container = new QVBoxLayout(centralWidget);
    container->setSpacing(1);
    container->addWidget(connect_window);    
}

void MainWindow::chatFrame(){
    QWidget *centralWidget = new QWidget(main_gui);
    main_gui->setCentralWidget(centralWidget);
    QVBoxLayout *container = new QVBoxLayout(centralWidget);
    container->setSpacing(1);
    container->addWidget(main_gui->chat);
}
void MainWindow::disconnectFrame(){
    disconnect = new DisconnectedWindow;
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);
    QVBoxLayout *container = new QVBoxLayout(centralWidget);
    container->setSpacing(1);
    container->addWidget(disconnect);    
}
void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);    
}            

void ChatWindow::disconnectFrame(){
    main_gui->disconnectFrame();
}

void DisconnectedWindow::new_connection(){
    main_gui->connectFrame();
}


 
void MainWindow::helpBox(){
    QMessageBox *msgBox  = new QMessageBox();
    msgBox->setWindowTitle("Help");
    msgBox->setText("<html> <body> email: kimham@kth.se </body> </html>");
    msgBox->show();
}
void MainWindow::aboutBox(){
    QMessageBox *msgBox  = new QMessageBox();
    msgBox->setWindowTitle("About");
    msgBox->setText("<html> <body> Chat-client. <br> Connect with IP/hostname + port number to a running chat-server. <br> Use command --active too se a list of active users in the chat. Write 'EXIT' to leave</body> </html>");
    msgBox->show();
}

