//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_CHANNEL_COUNT_H
#define CHART_SYSTEM_CHANNEL_COUNT_H


#include "Property.h"

class Channel_Count : public Property{
    Q_OBJECT
public :
    int M_Channels_Count;
    Channel_Count(int M_Channels_Count){ this -> label = "Channel_Count"; this -> M_Channels_Count = M_Channels_Count;};
public slots:
    void ShowSettingWindow() override ;
private slots:
    void SetComfirm() override ;
};


#endif //CHART_SYSTEM_CHANNEL_COUNT_H
