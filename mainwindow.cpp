#include "mainwindow.h"
#include <QIcon>
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    btn_list = QList<PageButton*>();
    selected_id = 0;
    create_tool_bar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create_tool_bar(){
    //edit button
    QIcon edit_icon_n(":/images/edit_n.png");
    QIcon edit_icon_s(":/images/edit_s.png");
    edit_btn = new PageButton(true, edit_icon_n, edit_icon_s, this);
    btn_list.append(edit_btn);
    connect(edit_btn, SIGNAL(pressed()), this, SLOT(rcv()));
    //analysis button
    QIcon analysis_icon_n(":/images/analysis_n.png");
    QIcon analysis_icon_s(":/images/analysis_s.png");
    analysis_btn = new PageButton(false, analysis_icon_n, analysis_icon_s, this);
    btn_list.append(analysis_btn);
    //settings button
    QIcon settings_icon_n(":/images/settings_n.png");
    QIcon settings_icon_s(":/images/settings_s.png");
    settings_btn = new PageButton(false, settings_icon_n, settings_icon_s, this);
    btn_list.append(settings_btn);
    toolbar = new QToolBar();
    toolbar->addWidget(edit_btn);
    toolbar->addWidget(analysis_btn);
    toolbar->addWidget(settings_btn);
    toolbar->setIconSize(QSize(150, 150));
    toolbar->setMovable(false);
    toolbar->setContentsMargins(10, 10, 10, 10);
    toolbar->setAllowedAreas(Qt::LeftToolBarArea);
    this->addToolBar(Qt::LeftToolBarArea, toolbar);
}

void MainWindow::page_buttons_clicked(PageButton *caller){
    for(PageButton* pb : btn_list){
        if(pb == caller){
            pb->setSelected(true);
        }
        else{
            pb->setSelected(false);
        }
    }
    selected_id = btn_list.indexOf(caller);
}
