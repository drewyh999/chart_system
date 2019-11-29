//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartRow.h"

ChartRow::ChartRow() {
    //初始化一个scrollSpeed
    this -> scrollSpeed = 20;

    //初始化isScrollling
    this -> isScrolling = false;

    //初始化曲线
    series = new QLineSeries();
    series -> setVisible(true);

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
    XScrollBar = new QScrollBar(Qt::Horizontal,chartView);
    XScrollBar -> setMaximum(0);
    YScrollBar = new QScrollBar(Qt::Vertical,chartView);
    YScrollBar -> setMaximum(0);

    //链接滚动轴值变化信号到函数
    connect(YScrollBar,&QAbstractSlider::valueChanged,this,&ChartRow::OnYScrollValueChange);
    connect(XScrollBar,&QAbstractSlider::valueChanged,this,&ChartRow::OnXScrollValueChange);


    //链接xy轴范围变化信号到函数
    connect(XAxis,&QValueAxis::rangeChanged,this,&ChartRow::OnXAxisRangeChange);
    connect(YAxis,&QValueAxis::rangeChanged,this,&ChartRow::OnYAxisRangeChange);


    //初始化combobox
    comboBox = new QComboBox;
    comboBox -> addItem("微分");
    comboBox -> addItem("积分");
    comboBox -> addItem("原始");
    comboBox -> setFixedSize(100,100);

    //链接combobox选项变化信号到请求更改数据函数
    connect(comboBox,&QComboBox::currentTextChanged,this,&ChartRow::OnComboBoxChange);


    //将组建组合在一起
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout -> addWidget(YScrollBar);
    horizontal_layout -> addWidget(chartView);
    horizontal_layout -> addWidget(comboBox);
    auto vertical_layout = new QVBoxLayout;
    vertical_layout -> addLayout(horizontal_layout);
    vertical_layout -> addWidget(XScrollBar);

    //将组合好的组件放置到行中去
    this -> setLayout(vertical_layout);
    this -> setFixedSize(900,400);

}

void ChartRow::RePlot(const QList<short>& chartData){
    Cchart -> removeAllSeries();
    series = new QLineSeries();
    series -> setVisible(true);
    for(int i = 0;i < chartData.length();i ++){
        series -> append(i, chartData.at(i));
    }
    Cchart -> addSeries(series);
    series -> attachAxis(XAxis);
    series -> attachAxis(YAxis);
}

void ChartRow::OnYAxisRangeChange(qreal min, qreal max) {
    //如果用户还在拖动滚动条，就先不重画
    if (isScrolling) return;

    //如果轴的变化范围超过我们的最大范围，那么把它重制到最大范围
    if(min < (double)SHRT_MIN || max > (double)SHRT_MAX){
        YAxis -> setRange(SHRT_MIN,SHRT_MAX);
        //让滚动条恢复原状
        YScrollBar -> setMaximum(0);
        return;
    }

    qreal visible_width = max - min;//现在可以见的轴的范围是

    qreal all_width = SHRT_MAX - SHRT_MIN;//总共的轴的范围是

    isScrolling = true;
    YScrollBar -> setMaximum(100 * (int)(all_width -  visible_width));//滚动条的最大值是全长减去可见长度(由于范围是个浮点数，而滚动条value只能是整数，所以我们扩大100倍尽量获得精确的值)
    YScrollValue = 0.5 * (100 * (int)(all_width -  visible_width));//把新的滚动条值放在中间，因为这里是纵向滚动
    YScrollBar->setValue(YScrollValue);
    isScrolling = false;
}

void ChartRow::OnXAxisRangeChange(qreal min, qreal max) {
    //如果用户还在拖动滚动条，就先不重画
    if (isScrolling) return;

    //如果轴的变化范围超过我们的最大范围，那么把它重制到最大范围
    if(min < 0 || max > series -> at(series -> count() - 1).x()){
        XAxis -> setRange(0,series -> at(series -> count() - 1).x());
        //让滚动条恢复原状
        XScrollBar -> setMaximum(0);
        return;
    }

    qreal visible_width = max - min;//现在可以见的轴的范围是

    qreal all_width = SHRT_MAX - SHRT_MIN;//总共的轴的范围是

    isScrolling = true;
    XScrollBar -> setMaximum( (int)(all_width -  visible_width));//滚动条的最大值是全长减去可见长度(由于范围是个浮点数，而滚动条value只能是整数，所以我们扩大100倍尽量获得精确的值)
    XScrollValue = 100 * (((min)/all_width) * (all_width - visible_width));//设置新的滚动条值，并且也扩大100倍，以获得相同比例
    XScrollBar->setValue(XScrollValue);
    isScrolling = false;
}

void ChartRow::OnXScrollValueChange(int value) {
    //同样，我们只在滚动条停下的时候进行渲染
    if (!isScrolling) {
        isScrolling = true;
        double scroll_distance = scrollSpeed * ((double)value - XScrollValue);//获得需要移动的距离
        Cchart -> scroll(scroll_distance, 0);//移动chart
        XScrollValue = value;//将ScrollValue设置为现在的值
        isScrolling = false;
    }
}

void ChartRow::OnYScrollValueChange(int value) {
    if (!isScrolling) {
        isScrolling = true;
        double scroll_distance = scrollSpeed * ((double)value - YScrollValue);//获得需要移动的距离
        Cchart -> scroll(0, scroll_distance);//移动chart
        YScrollValue = value;//将ScrollValue设置为现在的值
        isScrolling = false;
    }

}

void ChartRow::OnComboBoxChange(const QString &text) {
    emit(RequestForChange(text));
}

void ChartRow::SetScrollSpeed(Scroll_Speed *scrollSpeed) {
    this -> scrollSpeed = (scrollSpeed -> M_Scroll_Speed);
}

void ChartRow::SetCurveColor(Curve_Color *curveColor) {

}



