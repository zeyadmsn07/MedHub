#pragma once
#include <string>
#include <QTime>
#include <Qt>

class AvailabilitySlot
{
private:
    const std::string doctorId;
    const Qt::DayOfWeek weekDay;
    const QTime startTime, endTime;

public:
    AvailabilitySlot(const std::string& docId, Qt::DayOfWeek day, const QTime& start, const QTime& end);

    const std::string& getDoctorId() const;

    Qt::DayOfWeek getWeekDay() const;

    QTime getStartTime() const;

    QTime getEndTime() const;
};
