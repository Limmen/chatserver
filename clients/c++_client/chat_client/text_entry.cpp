#include "text_entry.h"
#include <QKeyEvent>

void text_entry::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        {
            qDebug("Enter pressed in textedit");
            //            QString msg = main_gui->txt->toPlainText();
            ///           main_gui->socket->write(msg.toUtf8());
            //            main_gui->txt->setText("");
        }
    else
        {
            QTextEdit::keyPressEvent(event);
        }
}
