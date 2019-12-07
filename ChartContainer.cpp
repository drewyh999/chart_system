//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartContainer.h"

void ChartContainer::SetChannelCount(Property * cha) {
    auto chartRows = this -> findChildren<ChartRow*>();
//    auto oldchildren = this -> findChildren<ChartRow*>();
    int current_count = chartRows.length();

    int required_count = dynamic_cast<Channel_Count*>(cha) -> M_Channels_Count;//获取我们需要设置的通道数

//    如果我们要设置的值就是当前的值或者说当前还没有chartrow存在与container中，那么我们直接返回
    if(chartRows.length() == required_count || current_count == 0)
        return;


    //如果要设置的通道数比当前大，那么我们增加
    if(current_count < required_count){
        //这里我们通过向maincontroller发送一个需要的通道数的信号,然后由MainController来进行新的charrow初始化（进行属性链接）再交给container加入
        emit(ReQuestForChartRows(required_count - current_count));
        return;
    }

    //如果要设置的通道数比当前值小，那么我们减少布局中的通道显示
    else if(current_count > required_count){
        auto vboxlayout = this -> layout();
            for (int i = current_count ; i > required_count; i--) {//这里从current_count开始是因为布局中第0个widget是一个strech，他来保证我们的表格是从上往下摆列的，所以我们的chartrow是从第1个元素开始的
                QLayoutItem *it = vboxlayout -> layout() -> takeAt(i);
                auto row = qobject_cast<ChartRow*>(it -> widget());
                delete row;
                DBGprint("channel setting value %d\n", i);
            }
           // this -> resize(this -> width(), (CHARTROW_HEIGHT + 2 * CHART_ROW_PADDING) * required_count);
    }
}


ChartContainer::ChartContainer(ChartRow *cha,DataProcessor *dataProcessor) {
    //链接dataprocessor到chartrow
    connect(cha,&ChartRow::RequestForChange,dataProcessor,&DataProcessor::Process);
    connect( dataProcessor,&DataProcessor::DataChanged,cha,&ChartRow::RePlot);

    //初始化布局
    auto vboxlayout = new QVBoxLayout;
    vboxlayout -> addStretch();
    vboxlayout -> addWidget(cha);//在布局中加入ChartRow
    vboxlayout -> setDirection(QBoxLayout::BottomToTop);
   // vboxlayout -> addSpacing(CHART_ROW_PADDING);

    //让dataprocessor来发出一次处理信号，通知Chartrow绘制曲线
    dataProcessor -> Process("原始");

    //将这个处理器初始化为他
    this -> dataProcessor = dataProcessor;

    //设置布局
    this -> setLayout(vboxlayout);
}

void ChartContainer::AddChartRow(QList<ChartRow *> Rows) {
    auto vboxlayout  = this -> layout();
    auto chartRows = this -> findChildren<ChartRow*>();

    DBGprint("Current layout items count is %d\n",chartRows . length());
    for(auto row : Rows){
            vboxlayout -> addWidget(row);
            //将chartrow链接到处理器对象
            auto dp = new DataProcessor(dataProcessor->GetData());
            connect(row,&ChartRow::RequestForChange,dp,&DataProcessor::Process);
            connect(dp,&DataProcessor::DataChanged,row,&ChartRow::RePlot);
            dp -> Process("原始");
    }
}


