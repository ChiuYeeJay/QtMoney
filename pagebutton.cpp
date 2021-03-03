#include "pagebutton.h"

PageButton::PageButton(bool def_sel, QIcon icon)
    :QToolButton()
{
    selected = def_sel;
    setIcon(icon);
}

void PageButton::change_selected(){

}
