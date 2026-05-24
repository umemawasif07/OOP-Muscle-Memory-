#include "viewmemberdialog.h"
#include "ui_viewmemberdialog.h"
#include <QMessageBox>

ViewMemberDialog::ViewMemberDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::ViewMemberDialog)
{
    ui->setupUi(this);
    setWindowTitle("All Gym Members");

    ui->tableMembers->setColumnCount(7);
    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Phone"
            << "Membership" << "Join Date" << "Expiry Date";
    ui->tableMembers->setHorizontalHeaderLabels(headers);
    ui->tableMembers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMembers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMembers->horizontalHeader()->setStretchLastSection(true);
}

ViewMemberDialog::~ViewMemberDialog() { delete ui; }

void ViewMemberDialog::loadMembers(std::vector<MemberData> members)
{
    m_members = members;
    ui->tableMembers->setRowCount(0);

    for (int i = 0; i < (int)members.size(); i++) {
        ui->tableMembers->insertRow(i);
        ui->tableMembers->setItem(i, 0, new QTableWidgetItem(QString::number(members[i].id)));
        ui->tableMembers->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(members[i].name)));
        ui->tableMembers->setItem(i, 2, new QTableWidgetItem(QString::number(members[i].age)));
        ui->tableMembers->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(members[i].phone)));
        ui->tableMembers->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(members[i].membershipType)));
        ui->tableMembers->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(members[i].joinDate)));
        ui->tableMembers->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(members[i].expiryDate)));
    }
}

void ViewMemberDialog::on_btnSave_clicked()
{
    // Table read-only hai toh save ka kaam sirf close karna hai
    QMessageBox::information(this, "Saved", "Data is already saved!");
    close();
}

void ViewMemberDialog::on_btnClose_clicked()
{
    close();
}

void ViewMemberDialog::on_btnDelete_clicked()
{
    int row = ui->tableMembers->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a member to delete!");
        return;
    }

    int id       = ui->tableMembers->item(row, 0)->text().toInt();
    QString name = ui->tableMembers->item(row, 1)->text();

    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirm Delete",
                              "Delete member: " + name + " (ID: " + QString::number(id) + ")?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        ui->tableMembers->removeRow(row);
        emit deleteMemberRequested(id);
        QMessageBox::information(this, "Deleted", "Member deleted successfully!");
    }
}