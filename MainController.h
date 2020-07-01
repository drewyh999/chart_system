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
public:
     Scroll_Speed *scrollSpeed;
     Channel_Count *channelCount;
     Curve_Color *curveColor;
private:
    MainWindow *mainWindow;
public:
    MainController();//构造函数需要做的事情是初始化主窗口并且读入配置文件，并且初始化一个主窗口，在主窗口的菜单中添加好属性设置对象
    void ShowMainWindow();//显示主窗口
    signals:
        void NewChartRowGenerated(QList<ChartRow*>);
public slots:
    void NewFile();//handle打开新文件时需要做的事情,首先是调用私有函数读入文件中的数据，然后再掉InitNewChartContainer用来初始化chartcintainer来显示数据
    void OnClosing();//用于接收窗口关闭信号的函数，在关闭窗口时，主控制器需要进行配置文件的写入
    ChartRow* InitNewChartRow();//初始化一个新的chartRow(并且链接好property)
    void HandleNewChartRowReQuest(int);//处理chartcontainer发来的新建chartrow信号
private:
    //从配置文件中读取配置信息，如果配置文件不存在那么我们创建一个默认的属性
    QVector<short> ReadDataFromFile();//从文件读入数据
    ChartContainer* InitNewChartContainer(DataProcessor* processor);//初始化一个新的ChartContainer,为他链接好各种属性，由于ChartContainer构造时是需要一个dataprocessor的所以
    void WriteConfig();//根据属性，写配置文件
    void ReadConfig();//读取配置文件
    QString filepath;//用于保存读取到的文件的路径
    QString displaypath;//用于保存显示在tab上的路径名称
};


#endif //CHART_SYSTEM_MAINCONTROLLER_H
