#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QString>
#include "ChatWindow.h"
#include "text_entry.h"

ChatWindow *chat_window;

ChatWindow::ChatWindow(QScrollArea *parent) : QScrollArea(parent)
{


    chat_window = this;
    
    QWidget *upper_widget = new QWidget;
    QWidget *lower_widget = new QWidget;
    
    upper_container = new QVBoxLayout(upper_widget);
    upper_container->setSpacing(1);
    QVBoxLayout *lower_container = new QVBoxLayout(lower_widget);
    txt = new text_entry;
    
    lower_container->setSpacing(1);
    lower_container->addWidget(upper_widget);
    this->setWidget(lower_widget);
    this->setWidgetResizable(true);
    lower_container->addWidget(txt);

}

void ChatWindow::test_connection(QString host, int port){
    socket_status = 0;
    qDebug("Connecting to:");
    qDebug() << host;
    qDebug() << port;

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), 
            this, SLOT(HandleStateChange(QAbstractSocket::SocketState)));
    
    socket->connectToHost(host, port);

}


void ChatWindow::readyRead()
{
   
    while(socket->canReadLine())
        {
            QString line = QString::fromUtf8(socket->readLine()).trimmed();
            qDebug() << "Debug Message";
            qDebug() << line;
        
            QLabel *entry = new QLabel();
            entry->setText(line);
            upper_container->addWidget(entry);
        }
}


void ChatWindow::HandleStateChange(QAbstractSocket::SocketState socketState){
    qDebug("State changed");
    if(socketState == 3){
        socket_status = 3;
    }
    std::cout << socketState << std::endl;
}

void ChatWindow::connected()
{

}

void ChatWindow::disconnected()
{
    this->disconnectFrame();
}

void text_entry::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        {
            qDebug("Enter pressed in textedit");
            QString msg = chat_window->txt->toPlainText();
            chat_window->socket->write(msg.toUtf8());
            chat_window->txt->setText("");
        }
    else
        {
            QTextEdit::keyPressEvent(event);
        }
}
