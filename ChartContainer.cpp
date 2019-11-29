//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartContainer.h"

//void ChartContainer::SetChannelCount(Channel_Count * cha) {
//    int current_count = ChartRows -> size();
//    int required_count = cha -> M_Channels_Count;
//
//    //如果要设置的通道数比当前小，那么我们减少ChartRows中的项目数，反之我们增加
//    if(current_count < cha -> M_Channels_Count){
//        for(auto i = 0;i < required_count - current_count;i ++){
//            ChartRows -> append(new ChartRow);
//        }
//    }
//    else if(current_count > cha -> M_Channels_Count){
//        for(auto i = 0;i < current_count - required_count;i ++){
//            ChartRows -> removeFirst();
//        }
//    }
//    //重新给布局分配一次内存空间
//    vboxlayout = new QVBoxLayout;
//    //将现在的ChartRow加入到布局当中去
//    for(auto row : *ChartRows){
//        vboxlayout -> addWidget(row);
//    }
//    this -> setLayout(vboxlayout);
//}

//}
ChartContainer::ChartContainer(ChartRow *cha) {

}
