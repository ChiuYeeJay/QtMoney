#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QToolButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QToolBar *toolbar;
    //edit tool button
    QToolButton *edit_tlbtn;
    QIcon *edit_icon_n;
    QIcon *edit_icon_s;
    //analysis tool button
    QToolButton *analysis_tlbtn;
    QIcon *analysis_icon_n;
    QIcon *analysis_icon_s;
    //settings tool button
    QToolButton *settings_tlbtn;
    QIcon *settings_icon_n;
    QIcon *settings_icon_s;

private:
    void create_tool_bar();
    void create_menu();

private slots:
    void edit_tool_button_clicked();
    void analysis_tool_button_clicked();
    void settings_tool_button_clicked();

};
#endif // MAINWINDOW_H
