#include "pagebutton.h"

PageButton::PageButton(bool def_sel, QIcon n_icon, QIcon s_icon)
    :QToolButton()
{
    selected = def_sel;
    normal_icon = n_icon;
    selected_icon = s_icon;
    setIcon(n_icon);
    btn_list.append(this);
    selected_id = 0;
    connect(this, &PageButton::clicked, &PageButton::someone_clicked);
}

void PageButton::someone_clicked(PageButton *caller){
    for(PageButton *pb : btn_list){
        if(pb == caller) pb->setSelected(true);
        else pb->setSelected(false);
    }
    selected_id = btn_list.indexOf(caller);
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
