#include "viewpaymentsdialog.h"
#include "ui_viewpaymentsdialog.h"

ViewPaymentsDialog::ViewPaymentsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewPaymentsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Payment History");

    ui->tablePayments->setColumnCount(3);
    QStringList headers;
    headers << "Payment ID" << "Member ID" << "Amount (Rs)";
    ui->tablePayments->setHorizontalHeaderLabels(headers);
    ui->tablePayments->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablePayments->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePayments->horizontalHeader()->setStretchLastSection(true);
}

ViewPaymentsDialog::~ViewPaymentsDialog()
{
    delete ui;
}

void ViewPaymentsDialog::loadPayments(std::vector<PaymentData> payments)
{
    ui->tablePayments->setRowCount(0);

    for (int i = 0; i < (int)payments.size(); i++) {
        ui->tablePayments->insertRow(i);
        ui->tablePayments->setItem(i, 0, new QTableWidgetItem(
                                             QString::number(payments[i].paymentID)));
        ui->tablePayments->setItem(i, 1, new QTableWidgetItem(
                                             QString::number(payments[i].memberID)));
        ui->tablePayments->setItem(i, 2, new QTableWidgetItem(
                                             QString::number(payments[i].amount)));
    }
}

void ViewPaymentsDialog::on_btnClose_clicked()
{
    close();
}