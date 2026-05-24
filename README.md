#  Muscle Memory — Gym Management System

OOP course project in C++ | Bahria University Islamabad

# Project Contents
| File | Description |
|------|-------------|
| Code/ | C++ source files (gym.h, gym.cpp, main.cpp) |
| Report/ | Project report (.docx) |
| PPT/ | Presentation slides |
| Demo/ | Screen-recorded demo video |

# How to Compile & Run

# Requirements
- C++ compiler (g++ / MinGW / MSVC)
- Windows or Linux
-Qt Creator for GUI

# Compile (g++)
```bash
g++ -o GymSystem main.cpp gym.cpp
```
# Run
```bash
./GymSystem        # Linux/Mac
GymSystem.exe      # Windows
```

# First Time Use
1. Run the program
2. Select **2. Register** to create your account
3. Enter username, password, confirm password
4. Select role (Admin / Member)
5. Login with your new credentials

# Data Files (auto-created on first run)
- `members.txt` — member records
- `trainers.txt` — trainer records  
- `payments.txt` — payment records
- `users.txt` — user accounts

# OOP Concepts Used
- Inheritance (Member, Trainer → Person)
- Polymorphism (virtual display())
- Encapsulation (private members + getters)
- Abstraction (GymManagementSystem class)
