#include "pagebutton.h"

PageButton::PageButton(bool def_sel, QIcon icon)
    :QToolButton()
{
    selected = def_sel;
    setIcon(icon);
    btn_list.append(this);
    connect(this, &PageButton::clicked, &PageButton::someone_clicked);
}

void PageButton::someone_clicked(PageButton *caller){
    for(PageButton *pb : btn_list){
        if(pb == caller) pb->setSelected(true);
        else pb->setSelected(false);
    }
}

void PageButton::change_selected(){

}

void PageButton::setSelected(bool sel){
    if(selected && !sel){

    }
    else if(!selected && sel){

    }
    selected = sel;
}
