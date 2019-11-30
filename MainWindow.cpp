
#include "MainWindow.h"
#include <string>

//将属性设置加入到菜单当中去

void MainWindow::AddPropertySettings(QList<Property *> props) {
    auto menubar = this -> menuBar();
    auto setting_menu = new QMenu("Settings");
    for(auto prop : props){
        const char *type_name = prop -> label;
        auto temp_action = new QAction(type_name);
        connect(temp_action,&QAction::triggered,prop,&Property::ShowSettingWindow);
        setting_menu -> addAction(temp_action);
    }
    menubar -> addMenu(setting_menu);
}

void MainWindow::closeEvent(QCloseEvent *event)  {
    emit(WindowClosing());
}

MainWindow::MainWindow() {
    //初始化tab
    tab = new QTabWidget;

    //设置tab的最小大小可以足够容纳所有通道
    tab -> setMinimumHeight(MAX_CHANNEL_COUNT * (CHARTROW_HEIGHT));

    //设置欢迎标签
    auto welcomelabel = new QLabel("请选择文件");
    welcomelabel -> setMargin(200);
    auto font = welcomelabel -> font();
    font.setPointSize(40);
    welcomelabel -> setFont(font);

    //将欢迎设置为当前的中央widget
    this -> setCentralWidget(dynamic_cast<QWidget*>(welcomelabel));
}

void MainWindow::AddTab(ChartContainer *CC,const QString& filename) {
    this -> tab -> addTab(CC,filename);
    //设置为可以滚动
    QScrollArea *s = new QScrollArea(this);
    s -> setWidget(tab);
    this -> setCentralWidget(s);
}









