#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QToolButton>

class PageButton : public QToolButton
{
public:
    PageButton();
private:
    bool selected;
public Q_SLOT:
    void change_selected();
};

#endif // PAGEBUTTON_H
