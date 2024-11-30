#include <DMem.h>

DataMemory::DataMemory() {
    data.resize(UINT16_MAX);
    we_dm = false;
}

DataMemory::DataMemory(const char* filename) {
    DataFile.open(filename);
    if(!DataFile.is_open()) {

    }
    data.resize(UINT16_MAX);
    we_dm = false;
}

uint16_t DataMemory::getData(const uint16_t &address) {
    uint16_t returnData;
    if(address < UINT16_MAX) {
        returnData = data[address];
    }
    return returnData;
}

void DataMemory::writeDataToMemory(const uint16_t &address, const uint16_t &writeData) {
    if(we_dm) {
        data[address] = writeData;
    }
    else return;
}