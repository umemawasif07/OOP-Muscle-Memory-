#include "gym.h"

//  User Definitions

User::User()
{
    username = "";
    password = "";
    role = "member";
}

User::User(string u, string p, string r)
{
    username = u;
    password = p;
    role = r;
}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getRole()     const { return role; }

//  Person Definitions

Person::Person()
{
    name = "";
    age = 0;
    phone = "";
}

Person::Person(string n, int a, string p)
{
    name = n;
    age = a;
    phone = p;
}

Person::~Person() {}

string Person::getName() { return name; }
int    Person::getAge() { return age; }
string Person::getPhone() { return phone; }

void Person::display()
{
    cout << "Name  : " << name << "\n";
    cout << "Age   : " << age << "\n";
    cout << "Phone : " << phone << "\n";
}

//  Member Definitions

Member::Member() : Person()
{
    memberID = 0;
    membershipType = "";
    joinDate = "";
    expiryDate = "";
}

Member::Member(int id, string n, int a, string p,
    string type, string jDate, string eDate)
    : Person(n, a, p)
{
    memberID = id;
    membershipType = type;
    joinDate = jDate;
    expiryDate = eDate;
}

Member::~Member() {}

int    Member::getID() { return memberID; }
string Member::getMembershipType() { return membershipType; }
string Member::getJoinDate() { return joinDate; }
string Member::getExpiryDate() { return expiryDate; }

void Member::display()
{
    cout << "------------------------------\n";
    cout << "Member ID    : " << memberID << "\n";
    Person::display();
    cout << "Membership   : " << membershipType << "\n";
    cout << "Join Date    : " << joinDate << "\n";
    cout << "Expiry Date  : " << expiryDate << "\n";
}

//  Trainer Definitions

Trainer::Trainer() : Person()
{
    trainerID = 0;
    specialization = "";
}

Trainer::Trainer(int id, string n, int a, string p, string spec)
    : Person(n, a, p)
{
    trainerID = id;
    specialization = spec;
}

Trainer::~Trainer() {}

int    Trainer::getID() { return trainerID; }
string Trainer::getSpecialization() { return specialization; }

void Trainer::display()
{
    cout << "------------------------------\n";
    cout << "Trainer ID      : " << trainerID << "\n";
    Person::display();
    cout << "Specialization  : " << specialization << "\n";
}

//  Payment Definitions

Payment::Payment()
{
    paymentID = 0;
    memberID = 0;
    amount = 0.0;
}

Payment::Payment(int pid, int mid, double amt)
{
    paymentID = pid;
    memberID = mid;
    amount = amt;
}

Payment::~Payment() {}

int    Payment::getPaymentID() { return paymentID; }
int    Payment::getMemberID() { return memberID; }
double Payment::getAmount() { return amount; }

void Payment::display()
{
    cout << "------------------------------\n";
    cout << "Payment ID : " << paymentID << "\n";
    cout << "Member ID  : " << memberID << "\n";
    cout << "Amount     : " << amount << "\n";
}

//  GymManagementSystem Definitions

GymManagementSystem::GymManagementSystem()
{
    loggedInUsername = "";
    loggedInRole = "";
    loadUsers();
    loadMembers();
    loadTrainers();
    loadPayments();
}

GymManagementSystem::~GymManagementSystem()
{
    saveUsers();
    saveMembers();
    saveTrainers();
    savePayments();
}
//  Auth  –  main entry point called from main
bool GymManagementSystem::login()
{
    int choice;

    cout << "\n========================================\n";
    cout << "           MUSCLE MEMORY GYM            \n";
    cout << "========================================\n";
    cout << "  1. Login                              \n";
    cout << "  2. Register New Account               \n";
    cout << "  0. Exit                               \n";
    cout << "----------------------------------------\n";
    cout << "  Enter choice : ";
    cin >> choice;

    if (choice == 1)
        return loginUser();
    else if (choice == 2)
        return registerUser();
    else
    {
        cout << "Exiting...\n";
        return false;
    }
}

bool GymManagementSystem::registerUser()
{
    string uname, pwd, pwd2, role;

    cout << "\n--- Create New Account ---\n";

    // username (must be unique)
    cout << "Enter Username : ";
    cin.ignore();
    getline(cin, uname);

    if (uname.empty())
    {
        cout << "Username cannot be empty!\n";
        return false;
    }

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i].getUsername() == uname)
        {
            cout << "Username already exists! Please choose a different one.\n";
            return false;
        }
    }

    // password 
    cout << "Enter Password : ";
    getline(cin, pwd);

    if (pwd.empty())
    {
        cout << "Password cannot be empty!\n";
        return false;
    }

    cout << "Confirm Password : ";
    getline(cin, pwd2);

    if (pwd != pwd2)
    {
        cout << "Passwords do not match! Registration failed.\n";
        return false;
    }

    // role
    int r;
    cout << "Select Role:\n";
    cout << "  1. Admin\n";
    cout << "  2. Member\n";
    cout << "  Enter choice : ";
    cin >> r;
    cin.ignore(1000, '\n');          // clear leftover \n from cin >> r
    role = (r == 1) ? "admin" : "member";

    // save 
    users.push_back(User(uname, pwd, role));
    saveUsers();

    cout << "\nAccount created successfully!\n";
    cout << "Username : " << uname << "\n";
    cout << "Role     : " << role << "\n";
    cout << "\nPlease login with your new credentials.\n";

    // After registration, go straight to login
    return loginUser();
}
bool GymManagementSystem::loginUser()
{
    string uname, pwd;
    int attempts = 3;

    cout << "\n--- Login ---\n";

    while (attempts > 0)
    {
        cout << "Enter Username : ";
        cin >> ws;
        getline(cin, uname);

        cout << "Enter Password : ";
        cin >> ws;
        getline(cin, pwd);

        for (size_t i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == uname &&
                users[i].getPassword() == pwd)
            {
                loggedInUsername = uname;
                loggedInRole = users[i].getRole();

                cout << "\nLogin successful! Welcome, "
                    << uname << " (" << loggedInRole << ").\n";
                return true;
            }
        }

        attempts--;
        if (attempts > 0)
            cout << "Incorrect Username or Password! "
            << attempts << " attempt(s) remaining.\n\n";
        else
            cout << "Too many failed attempts. Exiting...\n";
    }

    return false;
}
void GymManagementSystem::saveUsers()
{
    ofstream file("users.txt");
    for (size_t i = 0; i < users.size(); i++)
    {
        file << users[i].getUsername() << "\n"
            << users[i].getPassword() << "\n"
            << users[i].getRole() << "\n";
    }
    file.close();
}

void GymManagementSystem::loadUsers()
{
    ifstream file("users.txt");
    if (!file) return;

    string u, p, r;
    while (getline(file, u))
    {
        if (getline(file, p) && getline(file, r))
            users.push_back(User(u, p, r));
    }
    file.close();
}

void GymManagementSystem::addMember(string name, int age, string phone,
    string type, string joinDate,
    string expiryDate)
{
    int id = 1001 + (int)members.size();
    members.push_back(Member(id, name, age, phone, type, joinDate, expiryDate));
    saveMembers();
}

void GymManagementSystem::viewAllMembers()
{
    cout << "\n===== ALL MEMBERS =====\n";
    if (members.empty())
    {
        cout << "No members found.\n";
        return;
    }
    for (size_t i = 0; i < members.size(); i++)
        members[i].display();
}

void GymManagementSystem::deleteMember(int id)
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].getID() == id)
        {
            members.erase(members.begin() + i);
            saveMembers();
            cout << "Member deleted successfully!\n";
            return;
        }
    }
    cout << "Member ID not found!\n";
}

void GymManagementSystem::addTrainer(string name, int age,
    string phone, string spec)
{
    int id = 2001 + (int)trainers.size();
    trainers.push_back(Trainer(id, name, age, phone, spec));
    saveTrainers();
}

void GymManagementSystem::viewAllTrainers()
{
    cout << "\n===== ALL TRAINERS =====\n";
    if (trainers.empty())
    {
        cout << "No trainers found.\n";
        return;
    }
    for (size_t i = 0; i < trainers.size(); i++)
        trainers[i].display();
}

void GymManagementSystem::deleteTrainer(int id)
{
    for (size_t i = 0; i < trainers.size(); i++)
    {
        if (trainers[i].getID() == id)
        {
            trainers.erase(trainers.begin() + i);
            saveTrainers();
            cout << "Trainer deleted successfully!\n";
            return;
        }
    }
    cout << "Trainer ID not found!\n";
}

void GymManagementSystem::recordPayment(int memberID, double amount)
{
    int pid = 5001 + (int)payments.size();
    payments.push_back(Payment(pid, memberID, amount));
    savePayments();
}

void GymManagementSystem::viewAllPayments()
{
    cout << "\n===== PAYMENT HISTORY =====\n";
    if (payments.empty())
    {
        cout << "No payments recorded.\n";
        return;
    }
    for (size_t i = 0; i < payments.size(); i++)
        payments[i].display();
}

void GymManagementSystem::saveMembers()
{
    ofstream file("members.txt");
    for (size_t i = 0; i < members.size(); i++)
    {
        file << members[i].getID() << "\n"
            << members[i].getName() << "\n"
            << members[i].getAge() << "\n"
            << members[i].getPhone() << "\n"
            << members[i].getMembershipType() << "\n"
            << members[i].getJoinDate() << "\n"
            << members[i].getExpiryDate() << "\n";
    }
    file.close();
}

void GymManagementSystem::loadMembers()
{
    ifstream file("members.txt");
    if (!file) return;

    int    id, age;
    string name, phone, type, joinDate, expiryDate;

    while (file >> id)
    {
        file.ignore();
        getline(file, name);
        file >> age;
        file.ignore();
        getline(file, phone);
        getline(file, type);
        getline(file, joinDate);
        getline(file, expiryDate);
        members.push_back(Member(id, name, age, phone, type, joinDate, expiryDate));
    }
    file.close();
}

void GymManagementSystem::saveTrainers()
{
    ofstream file("trainers.txt");
    for (size_t i = 0; i < trainers.size(); i++)
    {
        file << trainers[i].getID() << "\n"
            << trainers[i].getName() << "\n"
            << trainers[i].getAge() << "\n"
            << trainers[i].getPhone() << "\n"
            << trainers[i].getSpecialization() << "\n";
    }
    file.close();
}

void GymManagementSystem::loadTrainers()
{
    ifstream file("trainers.txt");
    if (!file) return;

    int    id, age;
    string name, phone, spec;

    while (file >> id)
    {
        file.ignore();
        getline(file, name);
        file >> age;
        file.ignore();
        getline(file, phone);
        getline(file, spec);
        trainers.push_back(Trainer(id, name, age, phone, spec));
    }
    file.close();
}

void GymManagementSystem::savePayments()
{
    ofstream file("payments.txt");
    for (size_t i = 0; i < payments.size(); i++)
    {
        file << payments[i].getPaymentID() << "\n"
            << payments[i].getMemberID() << "\n"
            << payments[i].getAmount() << "\n";
    }
    file.close();
}

void GymManagementSystem::loadPayments()
{
    ifstream file("payments.txt");
    if (!file) return;

    int    pid, mid;
    double amt;

    while (file >> pid >> mid >> amt)
        payments.push_back(Payment(pid, mid, amt));

    file.close();
}