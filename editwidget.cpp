#include "editwidget.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QMapIterator>
#include <QFile>

EditWidget::EditWidget(QWidget *parent) : QWidget(parent)
{
    //set up basic layout
    main_layout = new QHBoxLayout(this);
    left_layout = new QVBoxLayout();
    right_layout = new QGridLayout();
    between_layout = new QHBoxLayout();
    main_layout->addLayout(left_layout);
    edit_board_frame = new QFrame();
    edit_board_frame->setLayout(right_layout);
    edit_board_frame->setFrameShadow(QFrame::Sunken);
    edit_board_frame->setFrameShape(QFrame::Box);
    main_layout->addWidget(edit_board_frame);

    create_calander();
    create_account_list();
    create_between_buttons();
    create_edit_board();

    left_layout->addWidget(calander);
    left_layout->addLayout(between_layout);
    left_layout->addWidget(account_list);

    load_account_data_file();
}

void EditWidget::create_edit_board(){
    //time label
    date_label = new QLabel(calander->selectedDate().toString(Qt::ISODate));
    right_layout->addWidget(date_label, 0, 0, 1, 2);
    create_time = QDateTime::currentDateTime();
    origin_data = NULL;
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
    minor_class_cb->setHidden(true);

    minor_class_add_btn = new QPushButton(tr("新增"));
    minor_class_remove_btn = new QPushButton(tr("刪除"));
    minor_class_remove_btn->setDisabled(true);
    connect(minor_class_add_btn, SIGNAL(clicked()), this, SLOT(minor_class_addbtn_clicked()));
    connect(minor_class_remove_btn, SIGNAL(clicked()), this, SLOT(minor_class_removebtn_clicked()));

    minor_class_listwid = new QListWidget();
    minor_class_listwid->setFrameShadow(QFrame::Sunken);
    minor_class_listwid->setFrameShape(QFrame::Box);
    minor_class_listwid->setHidden(true);
    connect(minor_class_listwid, SIGNAL(itemSelectionChanged()), this, SLOT(minor_class_listwid_selection_changed()));

    right_layout->addWidget(minor_class_label, 3, 0);
    right_layout->addWidget(minor_class_add_btn, 3, 1);
    right_layout->addWidget(minor_class_remove_btn, 3, 2);
    right_layout->addWidget(minor_class_cb, 4, 1, 1, 3);
    right_layout->addWidget(minor_class_listwid, 5, 1, 2, 3);

    //money
    money_label = new QLabel(tr("錢錢"));
    money_le = new QLineEdit();
    money_posneg_btn = new QPushButton();
    money_pos_neg = false;
    money_posneg_btn->setText(tr("支出"));
    connect(money_posneg_btn, SIGNAL(clicked()), this, SLOT(money_posneg_reverse()));

    right_layout->addWidget(money_label, 7, 0);
    right_layout->addWidget(money_le, 7, 1);
    right_layout->addWidget(money_posneg_btn, 7, 2);

    //note
    note_label = new QLabel(tr("備註"));
    note_te = new QTextEdit();
    right_layout->addWidget(note_label, 8, 0);
    right_layout->addWidget(note_te, 8, 1, 2, 2);

    //commit, reset buttons
    commit_btn = new QPushButton(tr("提交"));
    reset_btn = new QPushButton(tr("重設"));
    connect(commit_btn, SIGNAL(clicked()), this, SLOT(account_board_commit()));
    connect(reset_btn, SIGNAL(clicked()), this, SLOT(account_board_reset()));
    right_layout->addWidget(commit_btn, 10,1);
    right_layout->addWidget(reset_btn, 10, 2);
}

void EditWidget::create_calander(){
    calander = new QCalendarWidget();
}

void EditWidget::create_account_list(){
    account_list = new QListWidget();
    account_list_update();
    connect(calander, SIGNAL(selectionChanged()), this, SLOT(account_list_update()));
    connect(account_list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(account_list_double_clicked()));
}

void EditWidget::create_between_buttons(){
    back_today_btn = new QPushButton(tr("回到今天"));
    remove_account_btn = new QPushButton(tr("刪除"));
    remove_account_btn->setDisabled(true);
    connect(account_list, SIGNAL(currentRowChanged(int)), this, SLOT(account_list_sel_row_changed(int)));
    connect(back_today_btn, SIGNAL(clicked()), this, SLOT(backtoday_btn_clicked()));
    connect(remove_account_btn, SIGNAL(clicked()), this, SLOT(account_list_remove_selected_row()));
    between_layout->addWidget(back_today_btn);
    between_layout->addWidget(remove_account_btn);
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

void EditWidget::import_account_data(AccountData *org_data){
    origin_data = NULL;
    account_board_reset();

    create_time = org_data->create_time;
    major_class_cb->setCurrentText(org_data->major_class);
    name_le->setText(org_data->name);

    if(!org_data->minor_class.isEmpty()){
        minor_class_listwid->setHidden(false);
        minor_class_listwid->addItems(org_data->minor_class);
    }

    QString money_str;
    money_str.setNum(org_data->money);
    money_le->setText(money_str);
    money_pos_neg = org_data->money_posneg;
    money_posneg_btn->setText(tr(money_pos_neg? "收入" : "支出"));

    note_te->setPlainText(org_data->note);

    origin_data = org_data;
}

void EditWidget::save_account_data_file(){
    //account data to Json
    QJsonObject json;
    QJsonObject year_obj, month_obj, jo;
    QJsonArray day_arr;

    QMapIterator<int, QMap<int, QMap<int, QList<AccountData>>>> it_year(account_data_tree);
    while(it_year.hasNext()){
        it_year.next();
        QMap<int, QMap<int, QList<AccountData>>> map_month = account_data_tree.operator[](it_year.key());
        QMapIterator<int, QMap<int, QList<AccountData>>> it_month(map_month);
        year_obj = QJsonObject();
        while(it_month.hasNext()){
            it_month.next();
            QMapIterator<int, QList<AccountData>> it_day(account_data_tree[it_year.key()][it_month.key()]);
            month_obj = QJsonObject();
            while(it_day.hasNext()){
                it_day.next();
                day_arr = QJsonArray();
                for(int i=0; i<it_day.value().count();i++){
                    AccountData a = it_day.value().value(i);
                    jo = QJsonObject();
                    jo.insert("date", a.date.toString(Qt::ISODate));
                    jo.insert("edit_time", a.edit_time.toString());
                    jo.insert("create_time", a.create_time.toString());
                    jo.insert("name", a.name);
                    jo.insert("major_class", a.major_class);
                    QJsonArray minor_arr = QJsonArray();
                    for(int j=0;j<a.minor_class.count();j++) minor_arr.append(a.minor_class.value(j));
                    jo.insert("minor_class", minor_arr);
                    jo.insert("money", a.money);
                    jo.insert("money_posneg", a.money_posneg);
                    jo.insert("note", a.note);
                    day_arr.append(jo);
                }
                QString key_day_str;
                month_obj.insert(key_day_str.setNum(it_day.key()), day_arr);
            }
            QString key_month_str;
            year_obj.insert(key_month_str.setNum(it_month.key()), month_obj);
        }
        QString key_year_str;
        json.insert(key_year_str.setNum(it_year.key()), year_obj);
    }
    //save json to file
    QFile file("account_data.json");
    file.open(QFileDevice::WriteOnly);
    QJsonDocument jd(json);
    QByteArray out = jd.toJson();
    file.write(out, qstrlen(out));
    file.close();
}

void EditWidget::load_account_data_file(){
    //read file
    QFile fl("account_data.json");
    QJsonDocument js_data;
    QJsonObject js_obj;
    QJsonParseError err;
    QByteArray in;
    fl.open(QFile::ReadOnly);
    in = fl.readAll();
    js_data = QJsonDocument::fromJson(in, &err);
    js_obj = js_data.object();
    fl.close();

    //json to map
    account_data_tree = AccountDataDateTree();
    QStringList year_keys, month_keys, day_keys;
    QJsonObject year_obj, month_obj, day_obj;
    year_keys = js_obj.keys();
    for(const QString &year_key : year_keys){
        QMap<int, QMap<int, QList<AccountData>>> this_year = QMap<int, QMap<int, QList<AccountData>>>();
        month_keys = js_obj.value(year_key).toObject().keys();
        for(const QString &month_key : month_keys){
            QMap<int, QList<AccountData>> this_month = QMap<int, QList<AccountData>>();
            day_keys = js_obj.value(year_key).toObject().value(month_key).toObject().keys();
            for(const QString &day_key : day_keys){
                QList<AccountData> this_day = QList<AccountData>();
                QJsonArray day_arr = js_obj.value(year_key).toObject().value(month_key).toObject().value(day_key).toArray();
                for(int i=0;i<day_arr.count();i++){
                    AccountData ad = AccountData();
                    QJsonObject ev = day_arr[i].toObject();
                    ad.date = QDate::fromString(ev["date"].toString(), Qt::ISODate);
                    ad.create_time = QDateTime::fromString(ev["create_time"].toString());
                    ad.edit_time = QDateTime::fromString(ev["edit_time"].toString());
                    ad.major_class = ev["major_class"].toString();
                    for(int j=0;j<ev["minor_class"].toArray().count();j++){
                        ad.minor_class.append(ev["minor_class"].toArray()[j].toString());
                    }
                    ad.money = ev["money"].toInt();
                    ad.money_posneg = ev["money_posneg"].toBool();
                    ad.name = ev["name"].toString();
                    ad.note = ev["note"].toString();
                    this_day.append(ad);
                }
                this_month.insert(day_key.toInt(), this_day);
            }
            this_year.insert(month_key.toInt(), this_month);
        }
        account_data_tree.insert(year_key.toInt(), this_year);
    }

    account_list_update();
}

void EditWidget::selected_date_changed(){
    QString date_text = calander->selectedDate().toString(Qt::ISODate);
    if(origin_data == NULL) date_label->setText(date_text);
}

void EditWidget::major_class_changed(){
    while(minor_class_cb->count() > 0) minor_class_cb->removeItem(0);
    minor_class_cb->addItems(minor_class_list->at(major_class_cb->currentIndex()));
    while(minor_class_listwid->count() > 0) minor_class_listwid->takeItem(0);
    minor_class_listwid->setHidden(true);
}

void EditWidget::money_posneg_reverse(){
    money_pos_neg = !money_pos_neg;
    money_posneg_btn->setText(tr(money_pos_neg? "收入" : "支出"));
}

void EditWidget::minor_class_addbtn_clicked(){
    if(minor_class_cb->isHidden()){
        minor_class_cb->setHidden(false);
    }
    else{
        int maj_index = major_class_cb->currentIndex();
        int min_index = minor_class_cb->currentIndex();
        if(min_index == 0){
            minor_class_cb->setHidden(true);
        }
        else{
            if(minor_class_listwid->isHidden()) minor_class_listwid->setHidden(false);
            QString item = minor_class_list->at(maj_index).at(min_index);
            if(minor_class_listwid->findItems(item, Qt::MatchFixedString).isEmpty()) minor_class_listwid->addItem(item);
            minor_class_cb->setCurrentIndex(0);
        }
    }
}

void EditWidget::minor_class_removebtn_clicked(){
    int index = minor_class_listwid->currentIndex().row();
    if(0 <= index && index < minor_class_listwid->count()){
        minor_class_listwid->takeItem(index);
        if(minor_class_listwid->count() == 0){
            minor_class_listwid->setHidden(true);
            minor_class_remove_btn->setDisabled(true);
        }
    }
}

void EditWidget::minor_class_listwid_selection_changed(){
    minor_class_remove_btn->setDisabled(false);
}

void EditWidget::append_account_data_to_tree(AccountData data){
    if(account_data_tree.constFind(data.date.year()) == account_data_tree.constEnd())
        account_data_tree.insert(data.date.year(), QMap<int, QMap<int, QList<AccountData>>>());
    QMap<int, QMap<int, QList<AccountData>>> &year_tree = account_data_tree[data.date.year()];
    if(year_tree.constFind(data.date.month()) == year_tree.constEnd())
        year_tree.insert(data.date.month(), QMap<int, QList<AccountData>>());
    QMap<int, QList<AccountData>> &month_tree = year_tree[data.date.month()];
    if(month_tree.constFind(data.date.day()) == month_tree.constEnd())
        month_tree.insert(data.date.day(), QList<AccountData>());
    QList<AccountData> &day_list = month_tree[data.date.day()];
    day_list.append(data);
}

void EditWidget::account_board_commit(){
    AccountData data;

    bool money_ok;
    int money = (money_le->text()).toInt(&money_ok);
    if(!money_ok){
        qDebug() << "Money Mistake";
        return;
    }

    if(origin_data == NULL) data.date = calander->selectedDate();
    else data.date = origin_data->date;
    data.edit_time = QDateTime::currentDateTime();
    data.create_time = this->create_time;
    data.name = name_le->text();
    data.major_class = major_class_cb->currentText();
    while(minor_class_listwid->count() > 0) data.minor_class.append(minor_class_listwid->takeItem(0)->text());
    data.money = money;
    data.money_posneg = money_pos_neg;
    data.note = note_te->toPlainText();

    if(origin_data == NULL) append_account_data_to_tree(data);
    else *origin_data = data;

    origin_data = NULL;
    account_board_reset();
    account_list_update();
    save_account_data_file();
    calander->setSelectedDate(data.date);
}

void EditWidget::account_board_reset(){
    if(origin_data == NULL){
        create_time = QDateTime::currentDateTime();
        major_class_cb->setCurrentIndex(0);
        name_le->setText("");
        minor_class_cb->setCurrentIndex(0);
        minor_class_cb->setHidden(true);
        while(minor_class_listwid->count()) minor_class_listwid->takeItem(0);
        minor_class_listwid->setHidden(true);
        money_le->setText("");
        money_pos_neg = false;
        money_posneg_btn->setText(tr("支出"));
        note_te->setText("");
    }
    else{
        import_account_data(origin_data);
    }
}

void EditWidget::account_list_update(){
    account_list->clear();
    QDate sel_date = calander->selectedDate();
    QList<AccountData> a;
    if(account_data_tree.contains(sel_date.year()) &&
       account_data_tree[sel_date.year()].contains(sel_date.month()) &&
       account_data_tree[sel_date.year()][sel_date.month()].contains(sel_date.day())){
        a = account_data_tree.value(sel_date.year()).value(sel_date.month()).value(sel_date.day());
    }
    else return;
    origin_account_list = &account_data_tree[sel_date.year()][sel_date.month()][sel_date.day()];

    for(int i=0;i<a.count();i++){
        AccountData item = a[i];
        QString money_str;
        money_str.setNum(item.money);
        account_list->insertItem(i,item.major_class + " " + item.name + " " +  money_str);
    }
}

void EditWidget::account_list_double_clicked(){
    import_account_data(&(origin_account_list->operator[](account_list->currentRow())));
}

void EditWidget::backtoday_btn_clicked(){
    calander->setSelectedDate(QDate::currentDate());
}

void EditWidget::account_list_sel_row_changed(int index){
    if(index == -1) remove_account_btn->setDisabled(true);
    else remove_account_btn->setDisabled(false);
}

void EditWidget::account_list_remove_selected_row(){
    origin_account_list->remove(account_list->currentRow());
    account_list_update();
    save_account_data_file();
}
