#pragma once
#include "Doctor.h"

class DataManager
{
private:
    Qt::DayOfWeek parseDayOfWeek(QString dayText);

public:
    void loadStaticData(std::vector<Doctor>&);
    void saveLocalData();
    void loadLocalData();
};
