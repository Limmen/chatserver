#include "MainWindow.h"
#include <iostream>
// We'll need some regular expression magic in this code:
#include <QRegExp>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include "text_entry.h"

MainWindow *main_gui;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    main_gui = this;    
QWidget *centralWidget = new QWidget(this);
this->setCentralWidget(centralWidget);

QVBoxLayout *container = new QVBoxLayout(centralWidget);
container->setSpacing(1);


QWidget *upper_widget = new QWidget;
QWidget *lower_widget = new QWidget;
QScrollArea *scroll = new QScrollArea;  
upper_container = new QVBoxLayout(upper_widget);
upper_container->setSpacing(1);

QVBoxLayout *lower_container = new QVBoxLayout(lower_widget);
lower_container->setSpacing(1);
lower_container->addWidget(upper_widget);

scroll->setWidget(lower_widget);
scroll->setWidgetResizable(true);

container->addWidget(scroll);

// MyTextEdit tt;  
txt = new text_entry;


//upper_container->addWidget(lbl);
lower_container->addWidget(txt);


 QAction *help = new QAction("&Help", this);
 QAction *about = new QAction("&About", this);

 QMenu *file;
 file = menuBar()->addMenu("&Options");
 file->addAction(help);
 file->addAction(about);
    
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));

    socket->connectToHost("localhost", 2000);
    qDebug("Socket connected");
}

void MainWindow::readyRead()
{
    std::cout << "Ready read" << std::endl;
    // We'll loop over every (complete) line of text that the server has sent us:
    while(socket->canReadLine())
    {
        // Here's the line the of text the server sent us (we use UTF-8 so
        // that non-English speakers can chat in their native language)
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        qDebug() << "Debug Message";
        qDebug() << line;
        
        QLabel *entry = new QLabel();
        entry->setText(line);
        upper_container->addWidget(entry);
    }
}
void text_entry::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        {
            qDebug("Enter pressed in textedit");
            //main_gui->connected();
            QString msg = main_gui->txt->toPlainText();
            main_gui->socket->write(msg.toUtf8());
            main_gui->txt->setText("");
        }
    else
        {
            QTextEdit::keyPressEvent(event);
        }
}


void MainWindow::connected()
{
    // Flip over to the chat page:
    //    stackedWidget->setCurrentWidget(chatPage);
    qDebug("socket connected");
    // And send our username to the chat server.
    //    socket->write(QString("hi").toUtf8());
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {  
        std::cout << "KEy pressed ! " << std::endl;
        //        QString msg = txt->toPlainText();
        //        socket->write(msg.toUtf8());
        //        txt->setText("");
    } 
}

