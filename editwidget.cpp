#include "editwidget.h"

EditWidget::EditWidget(QWidget *parent) : QWidget(parent)
{
    main_layout = new QHBoxLayout(this);
    left_layout = new QVBoxLayout();
    right_layout = new QGridLayout();
    between_layout = new QVBoxLayout();
    main_layout->addLayout(left_layout);
    main_layout->addLayout(between_layout);
    main_layout->addLayout(right_layout);

    major_class_list = new QStringList();
    major_class_list->append(tr("--"));
    major_class_list->append(tr("食物"));
    major_class_list->append(tr("飲料"));
    major_class_list->append(tr("交通"));
    major_class_list->append(tr("娛樂"));

    create_calander();
    create_listwidget();
    create_fold_button();
    create_edit_board();

    left_layout->addWidget(calander);
    left_layout->addWidget(listwidget);
    between_layout->addWidget(fold_btn);
    between_layout->addSpacing(400);
}

void EditWidget::create_edit_board(){
    date_label = new QLabel(calander->selectedDate().toString(Qt::ISODate));
    right_layout->addWidget(date_label, 0, 0, 1, 2);
    connect(calander, SIGNAL(selectionChanged()), this, SLOT(selected_date_changed()));

    major_class_label = new QLabel(tr("種類"));
    major_class_cb = new QComboBox();
    major_class_cb->addItems(*major_class_list);
    right_layout->addWidget(major_class_label,1,0);
    right_layout->addWidget(major_class_cb, 1, 1, 1, 2);

    name_label = new QLabel(tr("項目"));
    name_le = new QLineEdit();
    right_layout->addWidget(name_label, 2, 0);
    right_layout->addWidget(name_le, 2, 1, 1, 2);
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

void EditWidget::selected_date_changed(){
    QString date_text = calander->selectedDate().toString(Qt::ISODate);
    date_label->setText(date_text);
}
