# 💼 Payroll Management System

## 📌 Overview

The Payroll Management System is a console-based application developed in C++ that helps manage employee payroll records efficiently. The system allows administrators to add, remove, and view employee information, while employees can calculate their salary based on the number of days worked.

The project demonstrates the use of Object-Oriented Programming (OOP), file handling, STL vectors, and payroll calculations in C++.

---

## 🚀 Features

### Administrator Module

* Add new employees
* Remove existing employees
* View employee records
* Store employee data in files

### Employee Module

* Employee login using name
* Salary calculation based on days worked
* PF (Provident Fund) deduction calculation
* ESI (Employee State Insurance) deduction calculation
* Display detailed salary breakdown

---

## 🛠️ Technologies Used

* C++
* Object-Oriented Programming (OOP)
* File Handling
* STL Vector
* Windows Console API
* Data Structures

---

## 🎯 Key Functionalities

### Employee Management

* Unique Employee ID generation
* Employee details storage
* Employee record deletion
* Employee list display

### Payroll Processing

Salary is calculated using:

```text
Initial Salary = Daily Wage × Days Worked

Basic Pay = 60% of Initial Salary

PF = 12% of Basic Pay

ESI = 4% of Initial Salary

Final Salary = Initial Salary - PF - ESI
```

---

## 📂 Data Storage

Employee records are stored in:

```text
Employees.txt
```

The system automatically:

* Loads employee data at startup
* Updates records when employees are added or removed
* Maintains persistent employee information

---

## ⚙️ Installation

### Clone the Repository

```bash
git clone https://github.com/yourusername/payroll-management-system.git
cd payroll-management-system
```

### Compile the Program

Using g++:

```bash
g++ Payroll_Management_System.cpp -o payroll
```

### Run the Program

```bash
./payroll
```

For Windows:

```bash
payroll.exe
```

---

## ▶️ How to Use

### Administrator

1. Select **Administrator** from the main menu.
2. Add new employees with:

   * Name
   * Designation
   * Daily Wage
3. View all employee records.
4. Remove employees using Employee ID.

### Employee

1. Select **Employee** from the main menu.
2. Enter employee name.
3. Enter number of days worked.
4. View salary details including:

   * Initial Salary
   * Basic Pay
   * PF Deduction
   * ESI Deduction
   * Final Salary

---

## 📊 Sample Output

```text
Employee Details

ID          : 101
Name        : John
Position    : Manager
Daily Wage  : Rs.1000

Salary Details

Initial Salary : Rs.30000
Basic Pay      : Rs.18000
PF             : Rs.2160
ESI            : Rs.1200
Final Salary   : Rs.26640
```

---

## 🧠 Concepts Demonstrated

* Classes and Objects
* Encapsulation
* Constructors
* File Handling
* Vectors (STL)
* Searching and Deletion
* Payroll Computation Logic
* Console-based User Interface

---

