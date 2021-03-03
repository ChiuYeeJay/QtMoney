#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QToolButton>
#include <QIcon>
#include <QList>

class PageButton : public QToolButton
{
public:
    PageButton(bool def_sel = false, QIcon icon = QIcon());
private:
    static QList<PageButton*> btn_list;
    bool selected;
public Q_SLOT:
    void change_selected();
    void mouse_enter();
    void mouse_leave();
    static void someone_clicked(PageButton *caller);
private:
    void setSelected(bool sel);
};

#endif // PAGEBUTTON_H
