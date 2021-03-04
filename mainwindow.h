#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QToolButton>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    //tool bar
    QToolBar *toolbar;
    QToolButton *edit_tlbtn;
    QIcon *edit_icon_n;
    QIcon *edit_icon_s;
    QToolButton *analysis_tlbtn;
    QIcon *analysis_icon_n;
    QIcon *analysis_icon_s;
    QToolButton *settings_tlbtn;
    QIcon *settings_icon_n;
    QIcon *settings_icon_s;

    //stacked widget
    QStackedWidget *stacked_wid;
    QLabel *fake1;
    QLabel *fake2;
    QLabel *fake3;
private:
    void create_central_widget();
    void create_tool_bar();
    void create_menu();

private slots:
    void edit_tool_button_clicked();
    void analysis_tool_button_clicked();
    void settings_tool_button_clicked();

};
#endif // MAINWINDOW_H
