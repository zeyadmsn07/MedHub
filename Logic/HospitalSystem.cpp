#include "HospitalSystem.h"
#include <algorithm>

int HospitalSystem::getDoctorCount() const { return doctors.size(); }
int HospitalSystem::getPatientCount() const { return patients.size(); }
int HospitalSystem::getAppointmentCount() const { return appointments.size(); }

bool HospitalSystem::registerPatient(const Patient& p)
{
    for(int i = 0; i < patients.size(); i++) //check whether the patient is already registered
    {
        if(patients.at(i) == p)
            return false;
    }

    patients.push_back(p);
    return true;
}

bool HospitalSystem::bookAppointment(const Appointment& appt)
{
    //Check if all conditions are met
    if( checkDailyLimit(appt.getPatient()->getNationalID(), appt.getDate()) ||
        hasConflict(appt.getDoctor()->getId(), appt.getPatient()->getNationalID(), appt.getDate(), appt.getStartTime()) ||
        !isWithinBusinessHours(appt.getDate(), appt.getStartTime()) ||
        !isWithinBookableRange(appt.getDate()) )
        return false;

    appointments.push_back(appt);
    return true;
}

bool HospitalSystem::cancelAppointment(const string& patID, QDate d, QTime t)
{
    for(Appointment apt : appointments)
    {
        if(apt.getDate() == d && apt.getStartTime() == t && apt.getPatient()->getNationalID() == patID)
        {
            vector<Appointment>::iterator i = find(appointments.begin(), appointments.end(), apt);
            appointments.erase(i);
            return true;
        }
    }

    return false;
}

bool HospitalSystem::checkDailyLimit(const string& patID, QDate d) const
{
    int count = 0;
    for(Appointment appt : appointments)
    {
        if(appt.getPatient()->getNationalID() == patID && appt.getDate() == d)
            count++;
    }

    if (count == 2)
        return true;
    else
        return false;
}

bool HospitalSystem::hasConflict(const string& docID, const string& patID,QDate d, QTime t) const
{
    for(Appointment appt : appointments)
    {
        if( (appt.getPatient()->getNationalID() == patID || appt.getDoctor()->getId() == docID)
            && appt.getDate() == d
            && appt.getStartTime() == t )
            return true;
    }

    return false;
}

bool HospitalSystem::isWithinBusinessHours(const QDate& d, const QTime& t) const
{
    if(d == QDate::currentDate())
    {
        if(QTime::currentTime().addSecs(3600) > t)
            return false;
    }
    else if(d < QDate::currentDate())
        return false;

    return true;
}

bool HospitalSystem::isWithinBookableRange(const QDate& d) const
{
    if(d > QDate::currentDate().addMonths(2))
        return false;
    else
        return true;
}

vector<QTime> HospitalSystem::generate20MinSlots (const string& docID, const QDate& d)
{
    vector <QTime> timeSlots(0);
    QTime start, end;
    Doctor* doc = findDoctorByID(docID);

    if(!doc) return timeSlots;
    for(int i = 0; i < doc->getAvailable().size(); i++)
    {
        if(doc->getAvailable().at(i).getWeekDay() != d.dayOfWeek()) continue;

        start = doc->getAvailable().at(i).getStartTime();
        end = doc->getAvailable().at(i).getEndTime();
        while (start.addSecs(1200) <= end)
        {
            timeSlots.push_back(start);
            start = start.addSecs(1200);
        }
    }

    return timeSlots;
}

Patient* HospitalSystem::findPatientByName(const string& n)
{
    for(int i = 0; i < patients.size(); i++)
    {
        if(patients.at(i).getName() == n)
            return &patients.at(i);
    }
    return nullptr;
}

Doctor* HospitalSystem::findDoctorByID(const string& id)
{
    for(int i = 0; i < doctors.size(); i++)
    {
        if(doctors.at(i).getId() == id)
            return &doctors.at(i);
    }
    return nullptr;
}
vector<Doctor> HospitalSystem::getDoctorsByDepartment(const string& dept) const
{
    vector<Doctor> deptDocs;
    for(int i = 0; i < doctors.size(); i++)
    {
        if(doctors.at(i).getDept() == dept)
            deptDocs.push_back(doctors.at(i));
    }
    return deptDocs;
}

void HospitalSystem::loadDocs()
{
    DM.loadStaticData(doctors);
    DM.loadLocalData(patients, appointments, doctors);
}

void HospitalSystem::saveData()
{
    DM.saveLocalData(patients, appointments);
}
