//
// Created by 朱原昊 on 2019/11/29.
//

#include "MainController.h"

void MainController::NewFile() {
    //首先用filedialog获取文件的地址
    QString filepath = QFileDialog::getOpenFileName(mainWindow, tr("Open file"), ".", tr("All files(*)"));
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
    auto processor = new DataProcessor(data);
    auto cr = InitNewChartRow();
    auto NewContainer = new ChartContainer(cr,processor);

    //链接新的container到SetChannel属性以及主控制器
    connect(channelCount,&Property::ValueChanged,NewContainer,&ChartContainer::SetChannelCount);
    connect(NewContainer,&ChartContainer::ReQuestForChartRows,this,&MainController::HandleNewChartRowReQuest);
    connect(this,&MainController::NewChartRowGenerated,NewContainer,&ChartContainer::AddChartRow);

    //根据设置,通知组件进行相应调整
    emit(curveColor -> ValueChanged(curveColor));
    emit(scrollSpeed -> ValueChanged(scrollSpeed));
    emit(channelCount -> ValueChanged(channelCount));

    //将Container添加到主窗口的Tab中去
    mainWindow -> AddTab(NewContainer,filepath);

    //设置主窗口的初始大小为当前设置通道数的大小
    mainWindow -> resize(CHARTROW_WIDTH,channelCount -> M_Channels_Count * (CHARTROW_HEIGHT + 40));
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
    auto file = new QFile("./chart_config.config");
    file -> open(QIODevice::ReadWrite);
    QString channelcount_text("Channel_Count:" + QString::number(channelCount -> M_Channels_Count));
    QString curvecolor_text("Curve_Color:" + QString::number(curveColor -> M_Curve_Color));
    QString scrollspeed_text("Scroll_Speed:" + QString::number(scrollSpeed -> M_Scroll_Speed));
    file -> write(channelcount_text.toUtf8());
    file -> write("\n");
    file -> write(curvecolor_text.toUtf8());
    file -> write("\n");
    file -> write(scrollspeed_text.toUtf8());
    file -> write("\n");
    file -> close();
}

void MainController::ReadConfig() {
    auto file = new QFile("./chart_config.config");

    //如果配置文件不存在，那么我们直接给出默认的配置
    if(!file -> exists()){
       scrollSpeed = new Scroll_Speed(10);
       curveColor = new Curve_Color(Curve_Color::RED);
       channelCount = new Channel_Count(1);
    }

    //如果有配置文件,那么我们对于配置文件进行读取
    else{
        file -> open(QIODevice::ReadOnly);
        while (!file -> atEnd())
        {
            QByteArray fileline = file -> readLine();
            QString str(fileline);
            DBGprint("Reading a line of %d\n",str.length());

            /* 配置文件的格式为 [PropertyName]:[Value]*/

            auto line = str.split(":");
            if(line.length() != 2){
                //如果配置文件损坏那么我们给初始化一个默认的属性
                QMessageBox::warning(mainWindow,"Warning","配置文件损坏");
                scrollSpeed = new Scroll_Speed(10);
                curveColor = new Curve_Color(Curve_Color::RED);
                channelCount = new Channel_Count(1);
                return;
            }
            //读取通道数信息
            if(line.at(0) == "Channel_Count"){
                channelCount = new Channel_Count(line.at(1).toInt());
            }

            //读取曲线颜色信息
            else if(line.at(0) == "Curve_Color"){
                curveColor = new Curve_Color((Curve_Color::C_COLOR)(line.at(1).toInt()));
            }

            //读取滚动速度信息
            if(line.at(0) == "Scroll_Speed"){
                scrollSpeed = new Scroll_Speed(line.at(1).toInt());
            }
        }
        file -> close();
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
        mainWindow -> show();
}


//按照请求初始化一些chartrow然后发送给container
void MainController::HandleNewChartRowReQuest(int count) {
    QList<ChartRow*> list;
    for(int i = 0;i < count;i ++){
        list.append(InitNewChartRow());
    }
    emit(NewChartRowGenerated(list));
}

