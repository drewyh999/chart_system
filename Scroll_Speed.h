//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_SCROLL_SPEED_H
#define CHART_SYSTEM_SCROLL_SPEED_H


#include "Property.h"

class Scroll_Speed : public Property{
Q_OBJECT
public :
    int M_Scroll_Speed;
    explicit Scroll_Speed(int M_Scroll_Speed){ this -> label = "Scroll_Speed"; this -> M_Scroll_Speed = M_Scroll_Speed;};
public slots:
    void ShowSettingWindow() override ;
private slots:
    void SetComfirm() override ;
};


#endif //CHART_SYSTEM_SCROLL_SPEED_H
