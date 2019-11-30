//
// Created by 朱原昊 on 2019/11/25.
//

#include "Channel_Count.h"

void Channel_Count::ShowSettingWindow() {
    this -> setting_widget = new QWidget;
    setting_widget -> setWindowTitle(this -> label);
    auto layout = new QHBoxLayout;
    layout -> addWidget(new QLabel("输入新的数值"));
    auto textline = new QLineEdit;
    auto comfirm_btn = new QPushButton("确定");
    QObject::connect(comfirm_btn, &QPushButton::clicked, this, &Channel_Count::SetComfirm);
    layout -> addWidget(textline);
    layout -> addWidget(comfirm_btn);
    this -> setting_widget -> setLayout(layout);
    this -> setting_widget -> show();
}

void Channel_Count::SetComfirm() {
    auto textline = this -> setting_widget -> findChild<QLineEdit*>();

    int new_channel_count = textline->text().toInt();
    if(new_channel_count < 1 || new_channel_count > MAX_CHANNEL_COUNT){
        QMessageBox::critical(setting_widget,"Warning","Invalid input");
        return;
    }

    this -> M_Channels_Count = new_channel_count;
    DBGprint("new channel count is %d\n",this -> M_Channels_Count);
    QMessageBox::information(setting_widget,"info","Setting successfully done");
    emit(ValueChanged(this));
    this -> setting_widget -> close();

}
