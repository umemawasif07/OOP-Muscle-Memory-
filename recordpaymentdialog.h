#ifndef RECORDPAYMENTDIALOG_H
#define RECORDPAYMENTDIALOG_H

#include <QDialog>

namespace Ui {
class RecordPaymentDialog;
}

class RecordPaymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordPaymentDialog(QWidget *parent = nullptr);
    ~RecordPaymentDialog();

    int    getMemberID();
    double getAmount();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::RecordPaymentDialog *ui;
};

#endif // RECORDPAYMENTDIALOG_H