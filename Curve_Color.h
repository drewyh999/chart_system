//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_CURVE_COLOR_H
#define CHART_SYSTEM_CURVE_COLOR_H


#include "Property.h"

class Curve_Color : public Property{
//Q_OBJECT
public:
    //定义通道颜色枚举
    enum C_COLOR{ RED = 0,BLUE,AQUA,GREEN,PURPLE };
    C_COLOR M_Curve_Color;
    Curve_Color(C_COLOR M_Curve_Color){this -> label = "Curve_Color"; this -> M_Curve_Color = M_Curve_Color;};
public slots:
     void ShowSettingWindow() override ;
private slots:
     void SetComfirm() override ;
};


#endif //CHART_SYSTEM_CURVE_COLOR_H
