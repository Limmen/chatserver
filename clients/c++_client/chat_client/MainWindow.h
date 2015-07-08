// We need to include a couple Qt classes that we'll use:
#include <QMainWindow>
#include <QTcpSocket>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTextEdit>
#include "text_entry.h"
// This is the include file that Qt generates for us from the
// GUI we built in Designer  

/*
 * This is the MainWindow class that we have told to inherit from
 * our Designer MainWindow (ui::MainWindow)
 */
class MainWindow : public QMainWindow
{
     Q_OBJECT
    public:
     text_entry *txt;
     QTcpSocket *socket;
     QVBoxLayout *upper_container;
        // Every QWidget needs a constructor, and they should allow
        // the user to pass a parent QWidget (or not).
        MainWindow(QWidget *parent=0);

    private slots:
        void readyRead();
        
        void connected();
        void keyPressEvent(QKeyEvent *e);

    private:

        // This is the socket that will let us communitate with the server.
};
