#pragma once

#include <QDialog>
#include "../Logic/HospitalSystem.h"

namespace Ui {
class AppointmentBookingDialog;
}

class AppointmentBookingDialog : public QDialog {
    Q_OBJECT

public:
    explicit AppointmentBookingDialog(HospitalSystem& sys, QWidget *parent = nullptr);
    void prefill(const QString& docID, const QDate& date, const QTime& time);
    ~AppointmentBookingDialog();

private slots:
    void accept() override;

private:
    Ui::AppointmentBookingDialog *ui;
    HospitalSystem& backend;
};
