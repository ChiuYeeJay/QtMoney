#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QToolButton>
#include <QIcon>
#include <QList>

class PageButton : public QToolButton
{
public:
    PageButton(bool def_sel = false, QIcon n_icon = QIcon(), QIcon h_icon = QIcon());

public:
    static int selected_id;

private:
    static QList<PageButton*> btn_list;
    bool selected;
    QIcon normal_icon;
    QIcon selected_icon;

public Q_SLOT:
    static void someone_clicked(PageButton *caller);

public Q_SIGNAL:
    void selected_id_changed();

private:
    void setSelected(bool sel);
};

#endif // PAGEBUTTON_H
