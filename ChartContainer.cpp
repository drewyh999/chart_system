//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartContainer.h"

void ChartContainer::SetChannelCount(Property * cha) {
    int current_count = ChartRows -> size();
    int required_count = dynamic_cast<Channel_Count*>(cha) -> M_Channels_Count;

    if(ChartRows->length() == required_count)
        return;

    //如果要设置的通道数比当前小，那么我们减少ChartRows中的项目数，反之我们增加
    if(current_count < required_count){
        //这里我们通过向maincontroller发送一个需要的通道数的信号,然后由MainController来进行新的charrow初始化（进行属性链接）再交给container加入
        emit(ReQuestForChartRows(required_count - current_count));
        return;
    }
    else if(current_count > required_count){
        for(auto i = 0;i < current_count - required_count;i ++){
            ChartRows -> removeFirst();
        }
    }
    //重新给布局分配一次内存空间
    vboxlayout = new QVBoxLayout;
    //将现在的ChartRow加入到布局当中去
    for(auto row : *ChartRows){
        vboxlayout -> addWidget(row);
    }
    this -> setLayout(vboxlayout);
}


ChartContainer::ChartContainer(ChartRow *cha,DataProcessor *dataProcessor) {
    //链接dataprocessor到chartrow
    this -> dataProcessor = dataProcessor;
    connect(cha,&ChartRow::RequestForChange,this -> dataProcessor,&DataProcessor::Process);
    connect(this -> dataProcessor,&DataProcessor::DataChanged,cha,&ChartRow::RePlot);
    vboxlayout = new QVBoxLayout;
    vboxlayout -> addWidget(cha);
    ChartRows -> append(cha);
    this -> setLayout(vboxlayout);
}

void ChartContainer::AddChartRow(QList<ChartRow *> Rows) {
    for(auto row : Rows){
            ChartRows -> append(row);//首先将其加入ChartRow的list
            //将chartrow链接到处理器对象
            connect(row,&ChartRow::RequestForChange,this -> dataProcessor,&DataProcessor::Process);
            connect(this -> dataProcessor,&DataProcessor::DataChanged,row,&ChartRow::RePlot);
    }
}


