#include "MainWindow.h"
#include "PatientRegistrationDialog.h"
#include "AppointmentBookingDialog.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    backend.loadDocs();

    ui->timeTable->populateDoctorList(backend);

    updateDashboardStats();
    connect(ui->timeTable, &TimeTableWidget::appointmentChanged, this, &MainWindow::updateDashboardStats);
}

MainWindow::~MainWindow() {
    backend.saveData();
    delete ui;
}

void MainWindow::updateDashboardStats() {
    QString statsText = QString("Docs: %1 | Patients: %2 | Appts: %3")
    .arg(backend.getDoctorCount())
        .arg(backend.getPatientCount())
        .arg(backend.getAppointmentCount());

    ui->lblStats->setText(statsText);
}

void MainWindow::on_btnRegisterPatient_clicked() {
    PatientRegistrationDialog dialog(backend, this);
    dialog.exec();
    updateDashboardStats();
}

void MainWindow::on_btnBookAppointment_clicked() {
    AppointmentBookingDialog dialog(backend, this);

    if (dialog.exec() == QDialog::Accepted) {
        QModelIndex index = ui->timeTable->findChild<QTableView*>("doctorView")->currentIndex();
        if (index.isValid()) {
            ui->timeTable->on_doctorView_clicked(index);
        }
        updateDashboardStats();
    }
}
