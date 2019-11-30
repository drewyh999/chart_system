//
// Created by 朱原昊 on 2019/11/28.
//

#include "DataProcessor.h"
#include <stdlib.h>

void DataProcessor::Process(const QString& mode) {
    QList<short> result;
    DBGprint("Data received\n");
    if(mode == "原始") {
        result = data;
        emit(DataChanged(result));
    }
    else if(mode == "绝对值"){
        for(auto i : data){
            result.append(abs(i));
        }
        emit(DataChanged(result));
    }
}

