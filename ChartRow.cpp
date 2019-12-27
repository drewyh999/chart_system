//
// Created by 朱原昊 on 2019/11/25.
//

#include "ChartRow.h"

ChartRow::ChartRow() {

    //初始化isScrollling
    this -> isScrolling = false;

    //初始化曲线
    series = new QLineSeries();
    series -> setVisible(true);

    //设置Chart组件
    Cchart = new QChart;
    Cchart -> setVisible(true);
    Cchart -> setAnimationOptions(QChart::NoAnimation);
    Cchart -> legend() -> setVisible(false);


    //根据Qt需要用ChartView容纳Chart
    auto chartView = new QChartView(Cchart);
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
    comboBox -> addItem("原始");
    comboBox -> addItem("导数");
    comboBox -> addItem("积分");
    comboBox -> addItem("绝对值");
    comboBox -> setFixedSize(COMBOBOX_WIDTH,COMBOBOX_HEIGHT);

    //链接combobox选项变化信号到请求更改数据函数
    connect(comboBox,&QComboBox::currentTextChanged,this,&ChartRow::OnComboBoxChange);

    //缩放XY轴的slider
    XSlider = new QSlider;
    XSlider -> setRange(SLIDER_MIN_PERCENT,SLIDER_MAX_PERCENT);
    XSlider -> setValue(SLIDER_MAX_PERCENT);
    YSlider = new QSlider;
    YSlider -> setRange(SLIDER_MIN_PERCENT,SLIDER_MAX_PERCENT);
    YSlider -> setValue(SLIDER_MAX_PERCENT);

    //链接Slider
    connect(XSlider,&QSlider::valueChanged,this,&ChartRow::SetXScale);
    connect(YSlider,&QSlider::valueChanged,this,&ChartRow::SetYScale);


    //将组建组合在一起
    auto horizontal_layout = new QHBoxLayout;
    horizontal_layout -> addWidget(YScrollBar);
    horizontal_layout -> addWidget(chartView);

    auto manu_panel = new QVBoxLayout;//右侧的操作拦
    manu_panel -> addWidget(comboBox);

    auto sliders = new QHBoxLayout;//两个slider
    sliders -> addWidget(XSlider);
    sliders -> addWidget(YSlider);

    manu_panel -> addLayout(sliders);
    horizontal_layout -> addLayout(manu_panel);

    auto vertical_layout = new QVBoxLayout;
    vertical_layout -> addLayout(horizontal_layout);
    vertical_layout -> addWidget(XScrollBar);

    //将组合好的组件放置到行中去
    this -> setLayout(vertical_layout);
    this -> setFixedSize(CHARTROW_WIDTH,CHARTROW_HEIGHT);
    //this -> setContentsMargins(CHART_ROW_PADDING,CHART_ROW_PADDING,CHART_ROW_PADDING,CHART_ROW_PADDING);

}

void ChartRow::RePlot(const QVector<short>& chartData){
    Cchart -> removeAllSeries();//首先去除现在图上的所有曲线
    series = new QLineSeries();//新建一个曲线对象
    series -> setVisible(true);
    series -> setUseOpenGL(true);
    int length = chartData.length();
    for(int i = 0;i < length;i ++){//将新的数据点加入到曲线当中
        short temp = chartData.at(i);
        series -> append(i, temp);
    }
    Cchart -> addSeries(series);//将曲线加入到chart当中
    series -> attachAxis(XAxis);//将轴附着到曲线
    series -> attachAxis(YAxis);
    DBGprint("Plot completed\n");
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
    if(min < 0 || max >= series -> count() - 1){
        XAxis -> setRange(0,series -> at(series -> count() - 1).x());
        //让滚动条恢复原状
        XScrollBar -> setMaximum(0);
        return;
    }

    qreal visible_width = max - min;//现在可以见的轴的范围是
    qreal all_width = series -> count();//总共的轴的范围是

    isScrolling = true;
    int ori_max = XScrollBar -> maximum();
    XScrollBar -> setMaximum(  (int)(all_width -  visible_width));//滚动条的最大值是全长减去可见长度
    XScrollValue =  (int)(((min)/ori_max)  *(all_width - visible_width));//设置新的滚动条值，获得相同比例
    XScrollBar -> setValue(XScrollValue);
    isScrolling = false;
}

void ChartRow::OnXScrollValueChange(int value) {
    //同样，我们只在滚动条停下的时候进行渲染
    if (!isScrolling) {
        isScrolling = true;
        DBGprint("received Scroll value change original scroll value is %d new one is %d \n",XScrollValue,scrollSpeed * ((double)value - XScrollValue));
        DBGprint("the Scroll Speed is %d\n",scrollSpeed);
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

void ChartRow::SetScrollSpeed(Property *speed) {
    this -> scrollSpeed = (dynamic_cast<Scroll_Speed*>(speed) -> M_Scroll_Speed);
}

void ChartRow::SetCurveColor(Property *curveColor) {
    Curve_Color::C_COLOR color = dynamic_cast<Curve_Color*>(curveColor) -> M_Curve_Color;
    QColor set_color;
    switch(color){
        case Curve_Color::RED:
            set_color = QColor("red");
            break;
        case Curve_Color::AQUA:
            set_color = QColor("aqua");
            break;
        case Curve_Color::PURPLE:
            set_color = QColor("purple");
            break;
        case Curve_Color::BLUE:
            set_color = QColor("blue");
            break;
        case Curve_Color::GREEN:
            set_color = QColor("green");
            break;
    }
    series -> setColor(set_color);
}

void ChartRow::SetXScale(int value) {
    if(value != 0) {
        auto min = this->XAxis->min();
        this->XAxis->setRange(min,((qreal)value / SLIDER_MAX_PERCENT) * ((this -> series -> count() - 1)) + min);
    }
}

void ChartRow::SetYScale(int value) {
    if(value != 0) {
        this->YAxis->setRange(SHRT_MIN * ((qreal)value / SLIDER_MAX_PERCENT),SHRT_MAX * ((qreal)value / SLIDER_MAX_PERCENT));
    }
}