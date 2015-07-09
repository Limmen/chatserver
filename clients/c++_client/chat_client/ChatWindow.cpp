#include "ChatWindow.h"

ChatWindow *chat_window;

ChatWindow::ChatWindow(QScrollArea *parent) : QScrollArea(parent)
{


    chat_window = this;
    
    QWidget *upper_widget = new QWidget;
    upper_widget->setMinimumHeight(0);
    QWidget *lower_widget = new QWidget;
    lower_widget->setMinimumHeight(0);
    upper_widget->setContentsMargins(-1, -1, -1, 0);
    lower_widget->setContentsMargins(-1, 0, -1, -1);

    upper_container = new QVBoxLayout(upper_widget);
    upper_container->setSpacing(0);
    upper_container->setMargin(0);
    upper_container->setContentsMargins(0,0,0,0);

    QVBoxLayout *lower_container = new QVBoxLayout(lower_widget);
    lower_container->setSpacing(0);
    lower_container->setMargin(0);
    lower_container->setContentsMargins(0,0,0,0);
    
    txt = new text_entry;
    txt->setMaximumHeight(60);
    QLabel *placeholder = new QLabel();
    placeholder->setText("");

    lower_container->addWidget(upper_widget, 0, Qt::AlignTop);
    this->setWidget(lower_widget);
    this->setWidgetResizable(true);
    this->setContentsMargins(0,0,0,0);

    lower_container->addWidget(txt, 0, Qt::AlignTop);
    lower_container->addWidget(placeholder, 0, Qt::AlignTop);

}

void ChatWindow::test_connection(QString host, int port){
    socket_status = 0;
    
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
        
            QLabel *entry = new QLabel();
            entry->setText(line);
            upper_container->addWidget(entry,  0, Qt::AlignTop);
        }
}


void ChatWindow::HandleStateChange(QAbstractSocket::SocketState socketState){
    if(socketState == 3){
        socket_status = 3;
    }
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
            QString msg = chat_window->txt->toPlainText();
            chat_window->socket->write(msg.toUtf8());
            chat_window->txt->setText("");
        }
    else
        {
            QTextEdit::keyPressEvent(event);
        }
}
