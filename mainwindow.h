#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <pagebutton.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QList<PageButton*> btn_list;
    int selected_id;
    QToolBar *toolbar;
    PageButton *edit_btn;
    PageButton *analysis_btn;
    PageButton *settings_btn;

private:
    void create_tool_bar();
    void create_menu();

public slots:
    void page_buttons_clicked(PageButton *caller);
    void rcv(){}
};
#endif // MAINWINDOW_H
