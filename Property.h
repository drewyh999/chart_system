//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_PROPERTY_H
#define CHART_SYSTEM_PROPERTY_H
#include "ui_header.h"


class Property : public QObject{
   // Q_OBJECT
signals:
    void ValueChanged(Property *prop){};//用于传输属性值改变的信号
public slots:
    virtual void ShowSettingWindow(){};//用于接收调出设置窗口的信号的槽函数
private slots:
    virtual void SetComfirm(){};//用于接收在设置窗口中点击确认键之后的槽函数，会反馈一个对话框并且发出信号
public:
    QWidget *setting_widget;
    const char * label;//这个label是为了在加入到菜单时方便菜单项的字符串添加
    Property(){};
    ~Property(){delete(this);};
};


#endif //CHART_SYSTEM_PROPERTY_H
