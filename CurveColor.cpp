//
// Created by 朱原昊 on 2019/11/25.
//

#include "CurveColor.h"

void Curve_Color::ShowSettingWindow() {
    this -> setting_widget = new QWidget;
    setting_widget -> setWindowTitle(this -> label);
    auto layout = new QHBoxLayout;
    //加入combobox
    auto combobox = new QComboBox;
    combobox -> addItem("Red");
    combobox -> addItem("Blue");
    combobox -> addItem("Aqua");
    combobox -> addItem("Green");
    combobox -> addItem("Purple");
    layout -> addWidget(combobox);
    auto btn = new QPushButton("确认");
    layout -> addWidget(btn);
    QObject::connect(btn, &QPushButton::clicked, this, &Curve_Color::SetComfirm);
    setting_widget -> setLayout(layout);
    setting_widget -> show();
}

void Curve_Color::SetComfirm() {
    auto combobox = setting_widget -> findChild<QComboBox*>();
    if(combobox -> currentText() == "Red"){
        M_Curve_Color = RED;
    }
    else if(combobox -> currentText() == "Green"){
        M_Curve_Color = GREEN;
    }
    else if(combobox -> currentText() == "Blue"){
        M_Curve_Color = BLUE;
    }
    else if(combobox -> currentText() == "Aqua"){
        M_Curve_Color = AQUA;
    }
    else if(combobox -> currentText() == "Purple"){
        M_Curve_Color = PURPLE;
    }
    DBGprint("new curve color is %d",this -> M_Curve_Color);
    emit (ValueChanged(this));
    QMessageBox::information(setting_widget,"info","Setting successfully done");
    this -> setting_widget -> close();

}
