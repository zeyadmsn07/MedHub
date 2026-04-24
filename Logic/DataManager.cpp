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

void DataManager::saveLocalData(const std::vector<Patient>& patients, const std::vector<Appointment>& appointments)
{
    QFile pFile("patients_saved.csv");
    if(pFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&pFile);
        for(const Patient& p : patients) {
            out << QString::fromStdString(p.getName()) << ","
                << p.getBirthdate().toString("yyyy-MM-dd") << ","
                << QString(p.getGender()) << ","
                << QString::fromStdString(p.getMobileNumber()) << ","
                << QString::fromStdString(p.getNationalID()) << "\n";
        }
        pFile.close();
    }

    QFile aFile("appointments_saved.csv");
    if(aFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&aFile);
        for(const Appointment& appt : appointments) {
            out << QString::fromStdString(appt.getPatient()->getNationalID()) << ","
                << QString::fromStdString(appt.getDoctor()->getId()) << ","
                << appt.getDate().toString("yyyy-MM-dd") << ","
                << appt.getStartTime().toString("hh:mm AP") << "\n";
        }
        aFile.close();
    }
}

void DataManager::loadLocalData(std::vector<Patient>& patients, std::vector<Appointment>& appointments, std::vector<Doctor>& doctors)
{
    QFile pFile("patients_saved.csv");
    if(pFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&pFile);
        while(!in.atEnd()) {
            QString line = in.readLine();
            if(line.isEmpty()) continue;
            QStringList data = line.split(",");
            if(data.size() >= 5) {
                Patient p(data[0].toStdString(),
                          QDate::fromString(data[1], "yyyy-MM-dd"),
                          data[2].at(0).toLatin1(),
                          data[3].toStdString(),
                          data[4].toStdString());
                patients.push_back(p);
            }
        }
        QFile aFile("appointments_saved.csv");
        if(aFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&aFile);
            while(!in.atEnd()) {
                QString line = in.readLine();
                if(line.isEmpty() || line.startsWith("PatientID")) continue; // Skip header or empty lines

                QStringList data = line.split(",");
                if(data.size() >= 4) {
                    string patID = data[0].toStdString();
                    string docID = data[1].toStdString();
                    QDate d = QDate::fromString(data[2], "yyyy-MM-dd");
                    QTime t = QTime::fromString(data[3], "hh:mm AP");

                    Patient* pPtr = nullptr;
                    for(int i = 0; i < patients.size(); i++) {
                        if(patients[i].getNationalID() == patID) {
                            pPtr = &patients[i];
                            break;
                        }
                    }

                    Doctor* dPtr = nullptr;
                    for(int i = 0; i < doctors.size(); i++) {
                        if(doctors[i].getId() == docID) {
                            dPtr = &doctors[i];
                            break;
                        }
                    }

                    if(pPtr != nullptr && dPtr != nullptr) {
                        Appointment appt(pPtr, dPtr, d, t);
                        appointments.push_back(appt);
                    }
                }
            }
            aFile.close();
        }
    }

}
