#include "recordpaymentdialog.h"
#include "ui_recordpaymentdialog.h"
#include <QMessageBox>

RecordPaymentDialog::RecordPaymentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordPaymentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Record Payment");
}

RecordPaymentDialog::~RecordPaymentDialog()
{
    delete ui;
}

int RecordPaymentDialog::getMemberID() {
    return ui->spinBoxMemberID->value();
}

double RecordPaymentDialog::getAmount() {
    return ui->lineEditAmount->text().toDouble();
}

void RecordPaymentDialog::on_btnSave_clicked()
{
    QString amountText = ui->lineEditAmount->text().trimmed();

    // Amount khali nahi hona chahiye
    if (amountText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter payment amount!");
        ui->lineEditAmount->setFocus();
        return;
    }

    // Amount sirf numbers honi chahiye
    bool ok;
    double amount = amountText.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Amount must be a valid number!");
        ui->lineEditAmount->setFocus();
        return;
    }

    // Amount positive honi chahiye
    if (amount <= 0) {
        QMessageBox::warning(this, "Error", "Amount must be greater than 0!");
        ui->lineEditAmount->setFocus();
        return;
    }

    // Amount bohat zyada nahi honi chahiye
    if (amount > 1000000) {
        QMessageBox::warning(this, "Error", "Amount seems too large. Please check!");
        ui->lineEditAmount->setFocus();
        return;
    }

    accept();
}

void RecordPaymentDialog::on_btnCancel_clicked()
{
    reject();
}