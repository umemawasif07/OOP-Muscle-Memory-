#include "viewtrainerdialog.h"
#include "ui_viewtrainerdialog.h"
#include <QMessageBox>

ViewTrainerDialog::ViewTrainerDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::ViewTrainerDialog)
{
    ui->setupUi(this);
    setWindowTitle("All Gym Trainers");

    ui->tableTrainers->setColumnCount(5);
    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Phone" << "Specialization";
    ui->tableTrainers->setHorizontalHeaderLabels(headers);
    ui->tableTrainers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableTrainers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTrainers->horizontalHeader()->setStretchLastSection(true);
}

ViewTrainerDialog::~ViewTrainerDialog() { delete ui; }

void ViewTrainerDialog::loadTrainers(std::vector<TrainerData> trainers)
{
    m_trainers = trainers;
    ui->tableTrainers->setRowCount(0);

    for (int i = 0; i < (int)trainers.size(); i++) {
        ui->tableTrainers->insertRow(i);
        ui->tableTrainers->setItem(i, 0, new QTableWidgetItem(QString::number(trainers[i].id)));
        ui->tableTrainers->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(trainers[i].name)));
        ui->tableTrainers->setItem(i, 2, new QTableWidgetItem(QString::number(trainers[i].age)));
        ui->tableTrainers->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(trainers[i].phone)));
        ui->tableTrainers->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(trainers[i].specialization)));
    }
}

void ViewTrainerDialog::on_btnSave_clicked()
{
    QMessageBox::information(this, "Saved", "Data is already saved!");
    close();
}

void ViewTrainerDialog::on_btnClose_clicked()
{
    close();
}

void ViewTrainerDialog::on_btnDelete_clicked()
{
    int row = ui->tableTrainers->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a trainer to delete!");
        return;
    }

    int id       = ui->tableTrainers->item(row, 0)->text().toInt();
    QString name = ui->tableTrainers->item(row, 1)->text();

    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirm Delete",
                              "Delete trainer: " + name + " (ID: " + QString::number(id) + ")?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        ui->tableTrainers->removeRow(row);
        emit deleteTrainerRequested(id);
        QMessageBox::information(this, "Deleted", "Trainer deleted successfully!");
    }
}