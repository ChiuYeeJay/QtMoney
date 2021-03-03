#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QToolButton>
#include <QIcon>

class PageButton : public QToolButton
{
public:
    PageButton(bool def_sel = false, QIcon icon = QIcon());
private:
    bool selected;
public Q_SLOT:
    void change_selected();
    void mouse_enter();
    void mouse_leave();
};

#endif // PAGEBUTTON_H
