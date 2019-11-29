//
// Created by 朱原昊 on 2019/11/29.
//

#include "MainController.h"

void MainController::NewFile() {
    //首先用filedialog获取文件的地址
    QString filepath = QFileDialog::getOpenFileName(mainWindow, tr("Open file"), ".", tr("All files"));
    auto file = new QFile(filepath);

    //如果文件没有读权限，那么报错
    if(!file -> open(QIODevice::ReadOnly)) {
        QMessageBox::warning(mainWindow,"Warning","无法打开文件");
        return;
    }
    QList<short> data;

    //使用数据流读入数据
    QDataStream input(file);
    while(!file -> atEnd()) {
        short temp;
        input >> temp;
        data.append(temp);
    }

    //创建一个新的container，用于装新的表格数据，由于每一个container里面至少有一个chart，所以我们先传入一个
    auto NewContainer = new ChartContainer(new ChartRow,new DataProcessor(data));

    //链接新的container到SetChannel属性以及主控制器
    connect(channelCount,&Property::ValueChanged,NewContainer,&ChartContainer::SetChannelCount);
    connect(NewContainer,&ChartContainer::ReQuestForChartRows,this,&MainController::HandleNewChartRowReQuest);
    connect(this,&MainController::NewChartRowGenerated,NewContainer,&ChartContainer::AddChartRow);

    //让Container自行调整通道数量
    NewContainer -> SetChannelCount(channelCount);

    //将Container添加到主窗口的Tab中去
    mainWindow -> AddTab(NewContainer,filepath);
}

ChartRow *MainController::InitNewChartRow() {
    auto chartrow = new ChartRow;
    //将滚动速度以及曲线颜色与chartrow链接
    connect(scrollSpeed,&Property::ValueChanged,chartrow,&ChartRow::SetScrollSpeed);
    connect(curveColor,&Property::ValueChanged,chartrow,&ChartRow::SetCurveColor);

    return chartrow;
}

void MainController::OnClosing() {
    WriteConfig();
}

void MainController::WriteConfig() {
    //TODO Writeconfig
}

void MainController::ReadConfig() {
    auto file = new QFile("./chart_config");
    if(!file -> exists()){
       scrollSpeed = new Scroll_Speed(10);
       curveColor = new Curve_Color(Curve_Color::RED);
       channelCount = new Channel_Count(3);
    }
}

MainController::MainController() {
    mainWindow = new MainWindow;
    //菜单栏添加File -> open 按钮
    auto menubar = mainWindow -> menuBar();
    auto menu = new QMenu("File");
    auto open_action = new QAction("Open");
    connect(open_action,&QAction::triggered,this,(&MainController::NewFile));
    menu -> addAction(open_action);
    menubar -> addMenu(menu);
    connect(mainWindow,&MainWindow::WindowClosing,this,&MainController::OnClosing);

    //从配置文件读入属性设置
    ReadConfig();

    //将需要设置的属性加入一个list，然后加入设置菜单
    auto list = new QList<Property*>;
    list -> append(channelCount);
    list -> append(scrollSpeed);
    list -> append(curveColor);
    mainWindow -> AddPropertySettings(*list);


}

void MainController::ShowMainWindow() {
    mainWindow -> resize(960,960);
    mainWindow -> show();
}

void MainController::HandleNewChartRowReQuest(int count) {
    QList<ChartRow*> list;
    for(int i = 0;i < count;i ++){
        list.append(InitNewChartRow());
    }
    emit(NewChartRowGenerated(list));
}

