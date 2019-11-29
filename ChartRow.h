//
// Created by 朱原昊 on 2019/11/25.
//

#ifndef CHART_SYSTEM_CHARTROW_H
#define CHART_SYSTEM_CHARTROW_H


#include "ui_header.h"
#include "Curve_Color.h"
#include "Scroll_Speed.h"
#include "DataProcessor.h"


class ChartRow : public QWidget{
    Q_OBJECT
signals:
    void RequestForChange (const QString &text);
private:
    QChart *Cchart;//用于显示一个通道的数据
    QLineSeries *series;//曲线
    QScrollBar *XScrollBar;//x轴滚动条
    QScrollBar *YScrollBar;//y轴滚动条
    QComboBox *comboBox;//用于选取变换的多选框
    int YScrollValue;//用于保存当前y轴滚动条的值
    int XScrollValue;//用于保存当前x轴滚动条的值
    int scrollSpeed;//用于保存滚动速度
    QValueAxis *XAxis;//图表的X轴
    QValueAxis *YAxis;//图表的Y轴
    bool isScrolling;//是否在滚动当中
    //信号槽
public slots:
    //通过滚动条值的改变，发出信号让chart显示数据的不同部分，来实现滚动显示数据的效果
    //同时x y 轴在压缩和放大数据的时候轴的范围改变，也通过信号的方式通知对应的滚动轴改变位置和值
    void RePlot(const QList<short>&);//根据chartdata重新绘制曲线
    void SetCurveColor(Curve_Color *curveColor);//用于接收曲线颜色改变信号
    void SetScrollSpeed(Scroll_Speed *scrollSpeed);//用于接收滚轮区域大小改变信号
    void OnYScrollValueChange(int value);//用于接收y轴滚动条值改变信号的函数
    void OnXScrollValueChange(int value);//用于接收x轴滚动条值改变的信号的函数
    void OnXAxisRangeChange(qreal min, qreal max);//用于接收X轴范围改变的信号的函数
    void OnYAxisRangeChange(qreal min, qreal max);//用于接收Y轴范围改变的信号的函数
    void OnComboBoxChange(const QString &text);//用于接收combobox改变信号
public :
    ChartRow();
    ~ChartRow(){ }
};

//#include "moc_ChartRow.cpp"
#endif //CHART_SYSTEM_CHARTROW_H
