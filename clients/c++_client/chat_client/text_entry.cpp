#include "text_entry.h"

void text_entry::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        {
            qDebug("Enter pressed in textedit");
        }
    else
        {
            QTextEdit::keyPressEvent(event);
        }
}
