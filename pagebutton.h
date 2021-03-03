#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QToolButton>
#include <QIcon>
#include <QList>

class PageButton : public QToolButton
{

public:
    PageButton(bool def_sel = false, QIcon n_icon = QIcon(), QIcon h_icon = QIcon(), QWidget *parent=nullptr);

private:
    bool selected;
    QIcon normal_icon;
    QIcon selected_icon;

signals:
    void selected_id_changed();
    void pressed();

public:
    void setSelected(bool sel);
};

#endif // PAGEBUTTON_H
