#include "editwidget.h"

EditWidget::EditWidget(QWidget *parent) : QWidget(parent)
{
    //set up basic layout
    main_layout = new QHBoxLayout(this);
    left_layout = new QVBoxLayout();
    right_layout = new QGridLayout();
    between_layout = new QVBoxLayout();
    main_layout->addLayout(left_layout);
    main_layout->addLayout(between_layout);
    edit_board_frame = new QFrame();
    edit_board_frame->setLayout(right_layout);
    edit_board_frame->setFrameShadow(QFrame::Sunken);
    edit_board_frame->setFrameShape(QFrame::Box);
    main_layout->addWidget(edit_board_frame);

    create_calander();
    create_listwidget();
    create_edit_board();

    left_layout->addWidget(calander);
    left_layout->addWidget(listwidget);
    between_layout->addSpacing(400);
}

void EditWidget::create_edit_board(){
    //time label
    date_label = new QLabel(calander->selectedDate().toString(Qt::ISODate));
    right_layout->addWidget(date_label, 0, 0, 1, 2);
    connect(calander, SIGNAL(selectionChanged()), this, SLOT(selected_date_changed()));

    //major class
    major_class_label = new QLabel(tr("種類"));
    major_class_cb = new QComboBox();
    setup_class_lists();
    connect(major_class_cb, SIGNAL(activated(int)), this, SLOT(major_class_changed()));
    major_class_cb->addItems(*major_class_list);
    right_layout->addWidget(major_class_label,1,0);
    right_layout->addWidget(major_class_cb, 1, 1, 1, 2);

    //name
    name_label = new QLabel(tr("項目"));
    name_le = new QLineEdit();
    right_layout->addWidget(name_label, 2, 0);
    right_layout->addWidget(name_le, 2, 1, 1, 2);

    //minor class tag
    minor_class_label = new QLabel(tr("標籤"));
    minor_class_cb = new QComboBox();
    minor_class_cb->addItems(minor_class_list->at(major_class_cb->currentIndex()));
    add_minor_class_btn = new QPushButton(tr("加入"));
    minor_class_frame_layout = new QVBoxLayout();
    minor_calss_frame = new QFrame();
    minor_calss_frame->setLayout(minor_class_frame_layout);
    minor_calss_frame->setFrameShadow(QFrame::Sunken);
    minor_calss_frame->setFrameShape(QFrame::Box);
    right_layout->addWidget(minor_class_label, 3, 0);
    right_layout->addWidget(minor_class_cb, 3, 1, 1, 1);
    right_layout->addWidget(add_minor_class_btn, 3, 2);
    right_layout->addWidget(minor_calss_frame, 4, 1, 2, 3);

    //money
    money_label = new QLabel(tr("錢錢"));
    money_le = new QLineEdit();
    right_layout->addWidget(money_label, 6, 0);
    right_layout->addWidget(money_le, 6, 1, 1, 2);

    //note
    note_label = new QLabel(tr("備註"));
    note_te = new QTextEdit();
    right_layout->addWidget(note_label, 7, 0);
    right_layout->addWidget(note_te, 7, 1, 2, 2);

    //commit, reset buttons
    commit_btn = new QPushButton(tr("提交"));
    reset_btn = new QPushButton(tr("重設"));
    right_layout->addWidget(commit_btn, 9,1);
    right_layout->addWidget(reset_btn, 9, 2);
}

void EditWidget::create_calander(){
    calander = new QCalendarWidget();
}

void EditWidget::create_listwidget(){
    listwidget = new QListWidget();
    listwidget->addItem(tr("item1"));
    listwidget->addItem(tr("item2"));
    listwidget->addItem(tr("item3"));
}

void EditWidget::create_fold_button(){
    fold_btn = new QPushButton(tr("fold"));
}

void EditWidget::setup_class_lists(){
    major_class_list = new QStringList();
    major_class_list->insert(0, tr("--"));
    major_class_list->insert(1, tr("食物"));
    major_class_list->insert(2, tr("飲料"));
    major_class_list->insert(3, tr("交通"));
    major_class_list->insert(4, tr("娛樂"));

    minor_class_list = new QList<QStringList>();
    QStringList food_ctgr = {tr("--"), tr("外食"), tr("食材"), tr("零食")};
    QStringList drink_ctgr = {tr("--"), tr("手搖杯"), tr("便利超商"), tr("茶包")};
    QStringList commute_ctgr = {tr("--"), tr("公車"), tr("計程車"), tr("加油")};
    QStringList entertain_ctgr = {tr("--"), tr("書籍"), tr("電影"), tr("遊戲")};
    minor_class_list->insert(0, QStringList(tr("--")));
    minor_class_list->insert(1, food_ctgr);
    minor_class_list->insert(2, drink_ctgr);
    minor_class_list->insert(3, commute_ctgr);
    minor_class_list->insert(4, entertain_ctgr);
}

void EditWidget::selected_date_changed(){
    QString date_text = calander->selectedDate().toString(Qt::ISODate);
    date_label->setText(date_text);
}

void EditWidget::major_class_changed(){
    while(minor_class_cb->count() > 0) minor_class_cb->removeItem(0);
    minor_class_cb->addItems(minor_class_list->at(major_class_cb->currentIndex()));
}
