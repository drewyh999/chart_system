//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_CHARTCONTAINER_H
#define CHART_SYSTEM_CHARTCONTAINER_H
#include "ui_header.h"
#include "ChartRow.h"
#include "Channel_Count.h"

class ChartContainer :public QWidget{
    Q_OBJECT
private:
    QList<ChartRow *> *ChartRows;//Container中所存在的显示通道
    QVBoxLayout *vboxlayout;//Container的布局
    DataProcessor *dataProcessor;//用一个list来保存我们的dataprocessor，避免被垃圾回收
    signals:
        void ReQuestForChartRows(int);
public:
    explicit ChartContainer(ChartRow *cha,DataProcessor *dataProcessor);//保证每一个ChartContainer至少要有一个ChartRow才可以,从语法上保证
public slots:
    void SetChannelCount(Property *cha);//用于接收通道数变化信号的函数
    void AddChartRow(QList<ChartRow*> Rows);//用于接收新的ChartRow的函数
};


#endif //CHART_SYSTEM_CHARTCONTAINER_H
