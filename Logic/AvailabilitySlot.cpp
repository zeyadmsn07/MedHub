#include "AvailabilitySlot.h"

AvailabilitySlot::AvailabilitySlot(
    const std::string& docId,
    Qt::DayOfWeek day,
    const QTime& start,
    const QTime& end
    )
        : doctorId(docId), weekDay(day), startTime(start), endTime(end)
    {
    }

const std::string& AvailabilitySlot::getDoctorId() const
{
    return doctorId;
}

Qt::DayOfWeek AvailabilitySlot::getWeekDay() const
{
    return weekDay;
}

QTime AvailabilitySlot::getStartTime() const
{
    return startTime;
}

QTime AvailabilitySlot::getEndTime() const
{
    return endTime;
}
