#include "TimeTableWidget.h"
#include "ui_timetablewidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include <vector>

using namespace std;

TimeTableWidget::~TimeTableWidget() {
    delete ui;
}

TimeTableWidget::TimeTableWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TimeTableWidget), backendPtr(nullptr)
{
    ui->setupUi(this);

    docModel = new QStandardItemModel(this);
    docModel->setHorizontalHeaderLabels({"ID", "Doctor Name", "Department"});

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(docModel);
    ui->doctorView->setModel(proxyModel);
    ui->doctorView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    slotModel = new QStandardItemModel(this);
    slotModel->setHorizontalHeaderLabels({"Date", "Time", "Status", "Patient ID"});
    ui->slotView->setModel(slotModel);
    ui->slotView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->txtSearch, &QLineEdit::textChanged, this, [this](const QString &text){
        proxyModel->setFilterKeyColumn(1);
        proxyModel->setFilterFixedString(text);
    });
}

void TimeTableWidget::populateDoctorList(HospitalSystem& backend, QString deptFilter) {
    backendPtr = &backend;
    docModel->removeRows(0, docModel->rowCount());

    vector<Doctor> list = deptFilter.isEmpty() ? backend.getDoctors() : backend.getDoctorsByDepartment(deptFilter.toStdString());

    for (int i = 0; i < list.size(); ++i) {
        docModel->setItem(i, 0, new QStandardItem(QString::fromStdString(list[i].getId())));
        docModel->setItem(i, 1, new QStandardItem(QString::fromStdString(list[i].getName())));
        docModel->setItem(i, 2, new QStandardItem(QString::fromStdString(list[i].getDept())));
    }
}

void TimeTableWidget::on_doctorView_clicked(const QModelIndex &index) {
    if (!backendPtr) return;

    slotModel->removeRows(0, slotModel->rowCount());

    QString docID = proxyModel->data(proxyModel->index(index.row(), 0)).toString();
    QDate startDate = QDate::currentDate();

    for (int i = 0; i < 7; ++i) {
        QDate d = startDate.addDays(i);
        std::vector<QTime> dailySlots = backendPtr->generate20MinSlots(docID.toStdString(), d);

        for (QTime t : dailySlots) {
            int row = slotModel->rowCount();
            slotModel->insertRow(row);
            slotModel->setItem(row, 0, new QStandardItem(d.toString("yyyy-MM-dd")));
            slotModel->setItem(row, 1, new QStandardItem(t.toString("hh:mm AP")));

            string patientID = "";
            bool booked = false;
            for(auto& appt : backendPtr->getAppointments()) {
                if(appt.getDoctor()->getId() == docID.toStdString() &&
                    appt.getDate() == d && appt.getStartTime() == t) {
                    booked = true;
                    patientID = appt.getPatient()->getNationalID();
                    break;
                }
            }

            slotModel->setItem(row, 2, new QStandardItem(booked ? "Booked" : "Available"));
            slotModel->setItem(row, 3, new QStandardItem(QString::fromStdString(patientID)));
        }
    }
}
void TimeTableWidget::on_btnCancelAppointment_clicked() {
    QModelIndex index = ui->slotView->currentIndex();
    if (!index.isValid() || !backendPtr) return;

    QDate d = QDate::fromString(slotModel->item(index.row(), 0)->text(), "yyyy-MM-dd");
    QTime t = QTime::fromString(slotModel->item(index.row(), 1)->text(), "hh:mm AP");
    string patID = slotModel->item(index.row(), 3)->text().toStdString();

    if (patID.empty()) {
        QMessageBox::warning(this, "Error", "Cannot cancel an empty slot.");
        return;
    }

    if (backendPtr->cancelAppointment(patID, d, t)) {
        QMessageBox::information(this, "Success", "Appointment cancelled.");
        on_doctorView_clicked(ui->doctorView->currentIndex());
        emit appointmentChanged();
    }
}

