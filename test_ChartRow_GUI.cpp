#include "ChartRow.h"
#include <stdio.h>
#include "ui_header.h"



int main(int argc, char *argv[]) {
        QApplication a(argc, argv);
        QMainWindow w;
        QList<short> data;
        for (short i = 0; i < 1000; i++) {
            data.append(i * i);
        }
        auto chartrow = new ChartRow();
        auto dataprocessor = new DataProcessor(data);
        QObject::connect(chartrow, &ChartRow::RequestForChange, dataprocessor, &DataProcessor::Process);
        QObject::connect(dataprocessor, &DataProcessor::DataChanged, chartrow, &ChartRow::RePlot);
        dataprocessor->Process("原始");
        w.setCentralWidget(chartrow);
        w.resize(960, 720);
        w.show();
        return a.exec();
    }


