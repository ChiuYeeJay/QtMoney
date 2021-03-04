#include "mainwindow.h"
#include <QIcon>
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    create_tool_bar();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create_tool_bar(){
    //edit button
    edit_icon_n = new QIcon(":/images/edit_n.png");
    edit_icon_s = new QIcon(":/images/edit_s.png");
    edit_tlbtn = new QToolButton(this);
    edit_tlbtn->setIcon(*edit_icon_n);
    connect(edit_tlbtn, SIGNAL(clicked()), this, SLOT(edit_tool_button_clicked()));
    //analysis button
    analysis_icon_n = new QIcon(":/images/analysis_n.png");
    analysis_icon_s = new QIcon(":/images/analysis_s.png");
    analysis_tlbtn = new QToolButton(this);
    analysis_tlbtn->setIcon(*analysis_icon_n);
    connect(analysis_tlbtn, SIGNAL(clicked()), this, SLOT(analysis_tool_button_clicked()));
    //settings button
    settings_icon_n = new QIcon(":/images/settings_n.png");
    settings_icon_s = new QIcon(":/images/settings_s.png");
    settings_tlbtn = new QToolButton(this);
    settings_tlbtn->setIcon(*settings_icon_n);
    connect(settings_tlbtn, SIGNAL(clicked()), this, SLOT(settings_tool_button_clicked()));
    //toolbar
    toolbar = new QToolBar();
    toolbar->addWidget(edit_tlbtn);
    toolbar->addWidget(analysis_tlbtn);
    toolbar->addWidget(settings_tlbtn);
    toolbar->setIconSize(QSize(60, 60));
    toolbar->setMovable(false);
    toolbar->setAllowedAreas(Qt::LeftToolBarArea);
    toolbar->layout()->setSpacing(20);
    edit_tlbtn->click();
    this->addToolBar(Qt::LeftToolBarArea, toolbar);
}

void MainWindow::edit_tool_button_clicked(){
    qDebug() << "click edit";
    edit_tlbtn->setIcon(*edit_icon_s);
    analysis_tlbtn->setIcon(*analysis_icon_n);
    settings_tlbtn->setIcon(*settings_icon_n);
}

void MainWindow::analysis_tool_button_clicked(){
    qDebug() << "click anal";
    edit_tlbtn->setIcon(*edit_icon_n);
    analysis_tlbtn->setIcon(*analysis_icon_s);
    settings_tlbtn->setIcon(*settings_icon_n);
}

void MainWindow::settings_tool_button_clicked(){
    qDebug() << "click sett";
    edit_tlbtn->setIcon(*edit_icon_n);
    analysis_tlbtn->setIcon(*analysis_icon_n);
    settings_tlbtn->setIcon(*settings_icon_s);
}
