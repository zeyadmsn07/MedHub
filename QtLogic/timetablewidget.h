#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "../Logic/HospitalSystem.h"

namespace Ui { class TimeTableWidget; }

class TimeTableWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimeTableWidget(QWidget *parent = nullptr);
    ~TimeTableWidget();

    void populateDoctorList(HospitalSystem& backend, QString deptFilter = "");

public slots:
    void on_doctorView_clicked(const QModelIndex &index);
signals:
    void appointmentChanged();
private slots:
    void on_btnCancelAppointment_clicked();

private:
    Ui::TimeTableWidget *ui;
    HospitalSystem* backendPtr;
    QStandardItemModel* docModel;
    QStandardItemModel* slotModel;
    QSortFilterProxyModel* proxyModel;
};
