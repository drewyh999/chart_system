//
// Created by 朱原昊 on 2019/11/28.
//

#include "DataProcessor.h"

void DataProcessor::Process(QString mode) {
    emit(DataChanged(data));
}

