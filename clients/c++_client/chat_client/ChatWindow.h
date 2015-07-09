#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QString>
#include <QWidget>
#include <QScrollArea>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QAbstractSocket>
#include "text_entry.h"
#include <iostream>
#include <QString>
class ChatWindow : public QScrollArea
{
    Q_OBJECT


 public:
    text_entry *txt;
    QTcpSocket *socket;
    QVBoxLayout *upper_container;
    int socket_status;
    void test_connection(QString host, int port);
    void disconnectFrame();
    
    ChatWindow(QScrollArea *parent=0);

    private slots:
        void connected();
        void readyRead();
        void disconnected();
        void HandleStateChange(QAbstractSocket::SocketState socketState);

    
    
};


#endif
