//
// Created by 朱原昊 on 2019/11/25.
//

#include "Scroll_Speed.h"

void Scroll_Speed::ShowSettingWindow() {
    this -> setting_widget = new QWidget;
    setting_widget -> setWindowTitle(this -> label);
    auto layout = new QHBoxLayout;
    layout -> addWidget(new QLabel("输入新的数值"));
    auto textline = new QLineEdit;
    auto comfirm_btn = new QPushButton("确定");
    QObject::connect(comfirm_btn, &QPushButton::clicked, this, &Scroll_Speed::SetComfirm);
    layout -> addWidget(textline);
    layout -> addWidget(comfirm_btn);
    this -> setting_widget -> setLayout(layout);
    this -> setting_widget -> show();
}

void Scroll_Speed::SetComfirm() {
    auto textline = this -> setting_widget -> findChild<QLineEdit*>();

    int new_Scroll_Area_Size = textline->text().toInt();
    if(new_Scroll_Area_Size  < 0 || new_Scroll_Area_Size  > 2000){
        QMessageBox::critical(setting_widget,"Warning","Invalid input");
        return;
    }

    this -> M_Scroll_Speed = new_Scroll_Area_Size ;
    DBGprint("new channel count is %d",this -> M_Scroll_Speed);
    emit(ValueChanged(this));
    QMessageBox::information(setting_widget,"info","Setting successfully done");
    this -> setting_widget -> close();
}
