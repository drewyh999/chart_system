//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_CHARTCONTAINER_H
#define CHART_SYSTEM_CHARTCONTAINER_H
#include "ui_header.h"
#include "ChartRow.h"
#include "Channel_Count.h"

class ChartContainer :public QWidget{
private:
    QList<ChartRow &> *ChartRows;
    QVBoxLayout *vboxlayout;
public:
    explicit ChartContainer(ChartRow *cha);//保证每一个ChartContainer至少要有一个ChartRow才可以,从语法上保证
};


#endif //CHART_SYSTEM_CHARTCONTAINER_H
