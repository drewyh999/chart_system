//
// Created by 朱原昊 on 2019/11/23.
//

#ifndef CHART_SYSTEM_CONST_VARS_H
#define CHART_SYSTEM_CONST_VARS_H



#include <QMainWindow>
#include <QApplication>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include <QValueAxis>
#include <QObject>
#include <QScrollBar>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <stdio.h>
#include <QChart>
#include <QChartView>
using namespace QtCharts;

#define DEBUG

#ifdef DEBUG
#define DBGprint(...) printf(__VA_ARGS__)
#else
#define DBGprint(...)
#endif
//最大可以拥有的通道数目
#define MAX_CHANNEL_COUNT 5
//定义最多可以打开的文件数目
#define MAX_FILE_OPENED 3



#endif //CHART_SYSTEM_CONST_VARS_H