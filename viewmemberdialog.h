#ifndef VIEWMEMBERDIALOG_H
#define VIEWMEMBERDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui { class ViewMemberDialog; }

struct MemberData {
    int id;
    std::string name;
    int age;
    std::string phone;
    std::string membershipType;
    std::string joinDate;
    std::string expiryDate;
};

class ViewMemberDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ViewMemberDialog(QWidget *parent = nullptr);
    ~ViewMemberDialog();
    void loadMembers(std::vector<MemberData> members);

signals:
    void deleteMemberRequested(int id);

private slots:
    void on_btnSave_clicked();    // Save button
    void on_btnClose_clicked();   // Close button
    void on_btnDelete_clicked();  // Delete Member button

private:
    Ui::ViewMemberDialog *ui;
    std::vector<MemberData> m_members;
};

#endif // VIEWMEMBERDIALOG_H