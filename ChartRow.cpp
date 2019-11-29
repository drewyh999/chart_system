//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartRow.h"

ChartRow::ChartRow() {

    //设置Chart组件
    Cchart = new QChart;
    Cchart -> setVisible(true);
    Cchart -> setAnimationOptions(QChart::AllAnimations);
    Cchart -> legend() -> setVisible(false);


    //根据Qt需要用ChartView容纳Chart
    auto chartView = new QChartView(Cchart);
    //设置rubberBand使得chart具有缩放功能
    chartView -> setRubberBand(QChartView::RectangleRubberBand);
    chartView -> setRenderHint(QPainter::Antialiasing);


    //初始化xy轴
    XAxis = new QValueAxis;
    XAxis -> setVisible(true);
    YAxis = new QValueAxis;
    YAxis -> setVisible(true);
    YAxis -> setRange(SHRT_MIN,SHRT_MAX);


    //将xy轴加入到chart当中去
    Cchart -> addAxis(YAxis, Qt::AlignLeft);
    Cchart -> addAxis(XAxis, Qt::AlignBottom);


    //初始化滚动轴
    HScrollBar = new QScrollBar(Qt::Horizontal,chartView);
    HScrollBar -> setMaximum(0);
    VScrollBar = new QScrollBar(Qt::Vertical,chartView);
    VScrollBar -> setMaximum(0);

    //链接滚动轴值变化信号到函数
    connect(VScrollBar,&QAbstractSlider::valueChanged,this,&ChartRow::OnXScrollValueChange);
    connect(HScrollBar,&QAbstractSlider::valueChanged,this,&ChartRow::OnYScrollValueChange);


    //链接xy轴范围变化信号到函数
    connect(XAxis,&QValueAxis::rangeChanged,this,&ChartRow::OnYAxisRangeChange);
    connect(YAxis,&QValueAxis::rangeChanged,this,&ChartRow::OnXAxisRangeChange);


    //初始化combobox
    comboBox = new QComboBox;
    comboBox -> addItem("微分");
    comboBox -> addItem("积分");
    comboBox -> addItem("原始");
    comboBox -> setFixedSize(100,100);


    //将组建组合在一起
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout -> addWidget(VScrollBar);
    horizontal_layout -> addWidget(chartView);
    horizontal_layout -> addWidget(comboBox);
    auto vertical_layout = new QVBoxLayout;
    vertical_layout -> addLayout(horizontal_layout);
    vertical_layout -> addWidget(HScrollBar);

    //将组合好的组件放置到行中去
    this -> setLayout(vertical_layout);
    this -> setFixedSize(900,400);

}

void ChartRow::RePlot(const QList<short>& chartData){
    Cchart -> removeAllSeries();
    auto series = new QLineSeries();
    series -> setVisible(true);
    for(int i = 0;i < chartData.length();i ++){
        series -> append(i, chartData.at(i));
    }
    Cchart -> addSeries(series);
    series -> attachAxis(XAxis);
    series -> attachAxis(YAxis);
}

void ChartRow::OnYAxisRangeChange(qreal min, qreal max) {

}

void ChartRow::OnXAxisRangeChange(qreal min, qreal max) {

}

void ChartRow::OnXScrollValueChange(int value) {

}

void ChartRow::OnYScrollValueChange(int value) {

}

void ChartRow::OnComboBoxChange() {
    emit(RequestForChange(comboBox -> currentText()));
}

void ChartRow::SetScrollSpeed(Scroll_Speed *scrollSpeed) {

}

void ChartRow::SetCurveColor(Curve_Color *curveColor) {
}



