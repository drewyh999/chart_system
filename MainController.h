//
// Created by 朱原昊 on 2019/11/29.
//

#ifndef CHART_SYSTEM_MAINCONTROLLER_H
#define CHART_SYSTEM_MAINCONTROLLER_H


#include <QObject>
#include "Property.h"
#include "MainWindow.h"
#define DEFAULT_SCROLLING_SPEED 10
#define DEFAULT_CURVE_COLOR 1
#define DEFAULT_CHANNEL_COUNT 3
#define CONFIG_ITEM_LENTH 2
#define CONFIG_ITEM_INDEX 0
#define CONFIG_VALUE_INDEX 1

class MainController : public QObject{
Q_OBJECT
public://c++的静态变量必须
     Scroll_Speed *scrollSpeed;
     Channel_Count *channelCount;
     Curve_Color *curveColor;
private:
    MainWindow *mainWindow;
public:
    MainController();//构造函数需要做的事情是初始化主窗口并且读入配置文件
    void ShowMainWindow();//显示主窗口
    signals:
        void NewChartRowGenerated(QList<ChartRow*>);
public slots:
    void NewFile();//打开一个新的二进制文件,并且按照short读入
    void OnClosing();//用于接收窗口关闭信号的函数，在关闭窗口时，主控制器需要进行配置文件的写入
    ChartRow* InitNewChartRow();//初始化一个新的chartRow(并且链接好property)
    void HandleNewChartRowReQuest(int);//处理chartcontainer发来的新建chartrow信号
private:
    //从配置文件中读取配置信息，如果配置文件不存在那么我们创建一个默认的属性
    void WriteConfig();//根据属性，写配置文件
    void ReadConfig();//读取配置文件
};


#endif //CHART_SYSTEM_MAINCONTROLLER_H
