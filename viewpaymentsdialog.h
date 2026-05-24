#ifndef VIEWPAYMENTSDIALOG_H
#define VIEWPAYMENTSDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class ViewPaymentsDialog;
}

struct PaymentData {
    int paymentID;
    int memberID;
    double amount;
};

class ViewPaymentsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPaymentsDialog(QWidget *parent = nullptr);
    ~ViewPaymentsDialog();
    void loadPayments(std::vector<PaymentData> payments);

private slots:
    void on_btnClose_clicked();

private:
    Ui::ViewPaymentsDialog *ui;
};

#endif // VIEWPAYMENTSDIALOG_H