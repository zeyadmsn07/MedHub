#include "DataManager.h"
#include "AvailabilitySlot.h"
#include "Doctor.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QStringList>

Qt::DayOfWeek DataManager::parseDayOfWeek(QString dayText)
{
    QString cleanDay = dayText.trimmed().toLower();

    if (cleanDay == "monday")    return Qt::Monday;
    if (cleanDay == "tuesday")   return Qt::Tuesday;
    if (cleanDay == "wednesday") return Qt::Wednesday;
    if (cleanDay == "thursday")  return Qt::Thursday;
    if (cleanDay == "friday")    return Qt::Friday;
    if (cleanDay == "saturday")  return Qt::Saturday;
    if (cleanDay == "sunday")    return Qt::Sunday;

    return Qt::Monday;
}

using namespace std;
void DataManager::loadStaticData(vector<Doctor>& allDocs)
{
    vector<AvailabilitySlot> allSlots;

    QFile fileDoc(":/doctors-1.csv");
    if(!fileDoc.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream inDoc(&fileDoc);
    if(!inDoc.atEnd()) inDoc.readLine();

    while(!inDoc.atEnd())
    {
        QString s = inDoc.readLine();
        if(s.isEmpty()) continue;

        QStringList data = s.split(",");
        Doctor doc(data[1].toStdString(), data[2].toStdString(), data[0].toStdString());
        allDocs.push_back(doc);
    }
    fileDoc.close();

    QFile file(":/availability-1.csv");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    if(!in.atEnd()) in.readLine();

    while(!in.atEnd())
    {
        QString s = in.readLine();
        if(s.isEmpty()) continue;

        QStringList data = s.split(",");
        Qt::DayOfWeek day = parseDayOfWeek(data[1]);

        QTime startT = QTime::fromString(data[2].trimmed(), "h:mm");
        QTime endT = QTime::fromString(data[3].trimmed(), "h:mm");

        AvailabilitySlot a(data[0].toStdString(), day, startT, endT);
        allSlots.push_back(a);
    }
    file.close();

    for(const AvailabilitySlot& slot : allSlots)
    {
        for(Doctor& doct : allDocs)
        {
            if(slot.getDoctorId() == doct.getId())
                doct.addAvailabilitySlot(slot);
        }
    }
}

void DataManager::saveLocalData()
{

}

void DataManager::loadLocalData()
{

}
