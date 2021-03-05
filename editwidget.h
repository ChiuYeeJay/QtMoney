#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QLineEdit>

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(QWidget *parent = nullptr);

public:
    QStringList *major_class_list;

private:
    //main layout
    QHBoxLayout *main_layout;
    QVBoxLayout *left_layout;
    QGridLayout *right_layout;
    QVBoxLayout *between_layout;

    //edit board
    QWidget *edit_board_widget;
    QLabel *date_label;
    QLabel *major_class_label;
    QComboBox *major_class_cb;
    QLabel *name_label;
    QLineEdit *name_le;
    QLabel *minor_class_label;
    QComboBox *minor_class_cb;
    QPushButton *add_minor_class_btn;
    QFrame *minor_calss_frame;
    QVBoxLayout *minor_class_frame_layout;
    QLabel *money_label;
    QPushButton *pos_neg_btn;
    QLineEdit *money_le;
    QLabel *note_label;
    QTextEdit *note_te;

    //calandar
    QCalendarWidget *calander;

    //list
    QListWidget *listwidget;

    //button
    QPushButton *fold_btn;

private:
    void create_edit_board();
    void create_calander();
    void create_listwidget();
    void create_fold_button();

private slots:
    void selected_date_changed();
};

#endif // EDITWIDGET_H
