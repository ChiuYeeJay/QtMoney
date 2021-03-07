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

struct AccountData{
    QDate date;
    QDateTime edit_time;
    QDateTime create_time;
    QString name;
    QString major_class;
    QStringList minor_class;
    int money;
    bool money_posneg;
    QString note;
};

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(QWidget *parent = nullptr);

public:
    QStringList *major_class_list;
    QList<QStringList> *minor_class_list;
    typedef QMap<int, QMap<int, QMap<int, QVector<AccountData>>>> AccountDataDateTree;
    AccountDataDateTree account_data_tree;

private:
    //main layout
    QHBoxLayout *main_layout;
    QVBoxLayout *left_layout;
    QGridLayout *right_layout;
    QHBoxLayout *between_layout;
    QFrame *edit_board_frame;

    QPushButton *back_today_btn;
    QPushButton *remove_account_btn;

    //edit board
    QWidget *edit_board_widget;
    QLabel *date_label;
    QDateTime create_time;
    AccountData *origin_data;

    QLabel *major_class_label;
    QComboBox *major_class_cb;

    QLabel *name_label;
    QLineEdit *name_le;

    QLabel *minor_class_label;
    QComboBox *minor_class_cb;
    QPushButton *minor_class_add_btn;
    QPushButton *minor_class_remove_btn;
    QListWidget *minor_class_listwid;

    QLabel *money_label;
    QPushButton *money_posneg_btn;
    bool money_pos_neg;
    QLineEdit *money_le;

    QLabel *note_label;
    QTextEdit *note_te;

    QPushButton *commit_btn;
    QPushButton *reset_btn;

    //calandar
    QCalendarWidget *calander;

    //list
    QListWidget *account_list;
    QList<AccountData> *origin_account_list;

    //button
    QPushButton *fold_btn;

private:
    void create_edit_board();
    void create_calander();
    void create_account_list();
    void create_fold_button();
    void create_between_buttons();

    void setup_class_lists();
    void append_account_data_to_tree(AccountData data);
    void import_account_data(AccountData *org_data);

private slots:
    void selected_date_changed();
    void major_class_changed();
    void money_posneg_reverse();
    void minor_class_addbtn_clicked();
    void minor_class_removebtn_clicked();
    void minor_class_listwid_selection_changed();
    void commit_account_board();
    void reset_account_board();
    void account_list_update();
    void account_list_double_clicked();
    void backtoday_btn_clicked();
    void account_list_sel_row_changed(int index);
};

#endif // EDITWIDGET_H
