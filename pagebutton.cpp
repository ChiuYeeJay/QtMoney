#include "pagebutton.h"

PageButton::PageButton(bool def_sel, QIcon n_icon, QIcon s_icon, QWidget *parent)
    :QToolButton(parent)
{
    selected = def_sel;
    normal_icon = n_icon;
    selected_icon = s_icon;
    setIcon(n_icon);
}

void PageButton::setSelected(bool sel){
    if(selected && !sel){
        setIcon(normal_icon);
    }
    else if(!selected && sel){
        setIcon(selected_icon);
    }
    selected = sel;
}
