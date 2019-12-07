//
// Created by 朱原昊 on 2019/11/23.
//

#ifndef CHART_SYSTEM_MAINWINDOW_H
#define CHART_SYSTEM_MAINWINDOW_H

#include "ui_header.h"
#include "Property.h"
#include "ChartContainer.h"
#define WELCOME_LABEL_MARGIN 200
#define WELCOME_LABEL_FONT_SIZE 40
class MainController;


class MainWindow  : public QMainWindow
{
    Q_OBJECT

private:
    QTabWidget *tab;//用于存放每一个打开的文件的tab窗口,加入新的ChartContainer就直接调用tabwidget的方法就可以

public:
    void AddPropertySettings(QList<Property*> prop);//将属性设置对象加入到菜单当中去
    void AddTab(ChartContainer *CC,const QString& filename);//将新打开的文件加入到一个Tab
    void closeEvent(QCloseEvent *event) override;//重写QMainWindow的函数，在关闭窗口时发出Windowclosing信号，让主控制器将设置属性写入配置文件再结束程序
     MainWindow()  ;//
    ~MainWindow() override {};
signals:
    void WindowClosing();

};


#endif //CHART_SYSTEM_MAINWINDOW_H
