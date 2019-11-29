//
// Created by 朱原昊 on 2019/11/28.
//

#ifndef CHART_SYSTEM_DATAPROCESSOR_H
#define CHART_SYSTEM_DATAPROCESSOR_H

#include "ui_header.h"
#include <QObject>

class DataProcessor : public QObject{
    Q_OBJECT
signals:
    void DataChanged(const QList<short>& data);//用于通知其他组件数据发生更改的信号
private :
    QList<short> data;
public slots:
    void Process(const QString &mode);//根据mode字符串来处理数据，处理完成之后通过信号DataChanged通知组件修改过后的数据
public :
    DataProcessor(QList<short> data){  this -> data = data; }
    ~DataProcessor(){};
};

//#include "moc_DataProcessor.cpp"

#endif //CHART_SYSTEM_DATAPROCESSOR_H
