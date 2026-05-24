#ifndef GYM_H
#define GYM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User
{
private:
    string username;
    string password;
    string role;       // "admin" or "member"

public:
    User();
    User(string u, string p, string r);

    string getUsername() const;
    string getPassword() const;
    string getRole()     const;
};

class Person
{
protected:
    string name;
    int    age;
    string phone;

public:
    Person();
    Person(string n, int a, string p);
    virtual ~Person();

    string getName();
    int    getAge();
    string getPhone();

    virtual void display();
};

class Member : public Person
{
private:
    int    memberID;
    string membershipType;
    string joinDate;
    string expiryDate;

public:
    Member();
    Member(int id, string n, int a, string p,
        string type, string jDate, string eDate);
    ~Member();

    int    getID();
    string getMembershipType();
    string getJoinDate();
    string getExpiryDate();

    void display() override;
};

class Trainer : public Person
{
private:
    int    trainerID;
    string specialization;

public:
    Trainer();
    Trainer(int id, string n, int a, string p, string spec);
    ~Trainer();

    int    getID();
    string getSpecialization();

    void display() override;
};

class Payment
{
private:
    int    paymentID;
    int    memberID;
    double amount;

public:
    Payment();
    Payment(int pid, int mid, double amt);
    ~Payment();

    int    getPaymentID();
    int    getMemberID();
    double getAmount();

    void display();
};

class GymManagementSystem
{
private:
    vector<Member>  members;
    vector<Trainer> trainers;
    vector<Payment> payments;
    vector<User>    users;          //  new

    string loggedInUsername;        // tracks who is logged in
    string loggedInRole;            // "admin" or "member"

public:
    GymManagementSystem();
    ~GymManagementSystem();

    bool login();
    bool registerUser();                    // create new account
    bool loginUser();                       // verify existing credentials
    void saveUsers();
    void loadUsers();

    void addMember(string name, int age, string phone,
        string type, string joinDate, string expiryDate);
    void viewAllMembers();
    void deleteMember(int id);

    void addTrainer(string name, int age, string phone, string spec);
    void viewAllTrainers();
    void deleteTrainer(int id);

    void recordPayment(int memberID, double amount);
    void viewAllPayments();

    void saveMembers();
    void loadMembers();
    void saveTrainers();
    void loadTrainers();
    void savePayments();
    void loadPayments();
};
#endif#pragma once
