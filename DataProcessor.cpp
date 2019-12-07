//
// Created by 朱原昊 on 2019/11/28.
//

#include "DataProcessor.h"
#include <stdlib.h>

void DataProcessor::Process(const QString& mode) {
    QVector<short> result(data.size());
    DBGprint("Data received\n");
    if(mode == "原始") {
        result = data;
        emit(DataChanged(result));
    }
    else if(mode == "绝对值"){
        for(long long i = 0;i < data.size();i ++){
            result[i] = abs(data[i]);
        }
        emit(DataChanged(result));
    }
}

