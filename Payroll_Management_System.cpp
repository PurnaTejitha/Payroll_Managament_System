#include<iostream>
#include<iomanip>
#include<algorithm>
#include<fstream>
#include<iterator>
#include<conio.h>
#include<vector>
#include<windows.h>

using namespace std;

class Color{ 
    public: 
         Color(int desiredColor){ 
             consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
             color = desiredColor; 
            } 
         friend ostream& operator<<(ostream& ss, Color obj){ 
             SetConsoleTextAttribute(obj.consoleHandle, obj.color); 
             return ss; 
            } 
    private: 
         int color; 
         HANDLE consoleHandle; 
}; 

class Employee {
private:
    int employeeID;
    string name;
    string position;
    double DailyWage;

public:
    Employee(int id, const string& n, const string& pos, double wage): employeeID(id),name(n),position(pos),DailyWage(wage){}
    int getEmployeeID() const {
        return employeeID;
    }
    string getName() const {
        return name;
    }
    string getPosition() const {
        return position;
    }
    double getDailyWage() const {
        return DailyWage;
    }
};

class Payroll {
private:
    vector<Employee> employees;
public:
    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    double calculateSalary(int employeeID, int daysWorked) const {
    	for (const Employee& emp : employees) {
        	if (emp.getEmployeeID() == employeeID) {
            	return emp.getDailyWage() * daysWorked;
        	}
    	}
    	return 0.0;  // Employee not found, return a default value
	}


    void displayEmployeeList() const {
    	cout << Color(12) << "\nEmployee List:\n" << endl;        
        cout << setfill('-') << setw(55) << "-" << endl;
        cout << Color(8) << setfill(' ') << left  << setw(10) << "ID" << setw(15) <<"Name" << setw(15) << "Position" << "Daily Wage(Rs)\n";
        cout << setfill('-') << setw(55) << "-" << endl;
    	for (const Employee& emp : employees) {
        	cout << Color(9) <<setfill(' ') << left << setw(10) << emp.getEmployeeID() << setw(15) << emp.getName() << setw(15) << emp.getPosition() << emp.getDailyWage() << endl;
    	}
        cout << setfill('-') << setw(55) << "-" << endl;
	}
    void loadEmployeesFromFile(const string& filename) {
        ifstream file(filename.c_str()); // Convert filename to C-style string
        if (file.is_open()) {
            int id;
            string name, position;
            double wage;

            while (file >> id >> name >> position >> wage) {
                Employee emp(id, name, position, wage);
                employees.push_back(emp); // Add the loaded employee to the vector
            }

            file.close();
            cout << "Employee data loaded successfully.\n";
        } else {
            cerr << "Unable to open file " << filename << " for reading.\n";
            perror("Error"); // Print system error message
        }
    }
    void storeEmployeesToFile(const string& filename) {
        ofstream file(filename.c_str(),ios::app);
        if (file.is_open()) {
            const Employee& emp = employees.back();
                file << emp.getEmployeeID() << " "
                    << emp.getName() << " "
                    << emp.getPosition() << " "
                    << emp.getDailyWage() << "\n";
            file.close();
            cout << "Employee data stored successfully.\n";
        } else {
            cerr << "Unable to open file " << filename << " for writing.\n";
            perror("Error");
        }
    }
    vector<Employee>& getEmployees() {
        return employees;
    }
    
};

int main() {
    Payroll restaurantPayroll;
    int maxID=0;
    restaurantPayroll.loadEmployeesFromFile("Employees.txt");
    for (const Employee& emp : restaurantPayroll.getEmployees()) {
        if (emp.getEmployeeID() > maxID) {
            maxID = emp.getEmployeeID();
        }
    }
    static int id = maxID+1;

    while (true) {
    	system("cls");
        int choice;
        cout << Color(1) << "\n------------ Restaurant Payroll Management System ------------\n";
        cout << Color(2) << "\nLOGIN:\n";
        cout << "\t1. Administrator\n";
        cout << "\t2. Employee\n";
        cout << "\t3. Exit\n";
        cout << "->Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
            	system("cls");
                // Administrator menu
                int ch;
                while (1) {
                    cout<<Color(12);
                    cout << "\n------------------ Administrator Menu -----------------\n\n";
                    cout<<Color(0);
                    cout << "\t1. Add employee\n";
                    cout << "\t2. Remove employee\n";
                    cout << "\t3. Display\n";
                    cout << "\t4. Exit to the main menu\n";
                    cout << "\tEnter your choice: ";
                    cin >> ch;

                    switch (ch) {
                        case 1: {
                            // Add employee
                            int newEmployeeID;
                            string newName, newPosition;
                            double newDailyWage;

                            newEmployeeID=id++;

                            cout <<Color(3)<<"\nEnter new employee details:";
                            cout << "\nName\t\t: ";
                            cin.ignore();
                            cout<<Color(7);
                            getline(cin, newName);

                            cout <<Color(3)<< "Designation\t: ";
                            cout<<Color(7);
                            getline(cin, newPosition);

                            cout <<Color(3)<< "Daily wage\t: ";
                            cout<<Color(7);
                            cin >> newDailyWage;

                            Employee newEmployee(newEmployeeID, newName, newPosition, newDailyWage);
                            restaurantPayroll.addEmployee(newEmployee);

                            restaurantPayroll.storeEmployeesToFile("Employees.txt");
                            cout << "Employee added successfully!\n";
                            break;
                        }

                        case 2: {
                            // Remove employee
                            int removeEmployeeID;
                            cout << "\nEnter the ID of the employee to remove: ";
                            cin >> removeEmployeeID;

                            auto& employees = restaurantPayroll.getEmployees();
                            auto it = find_if(employees.begin(), employees.end(),
                                [removeEmployeeID](const Employee& emp) {
                                    return emp.getEmployeeID() == removeEmployeeID;
                                });

                            if (it != employees.end()) {
                                // Element found, erase it
                                employees.erase(it);
                                cout << "Employee removed successfully!\n";

                                // Rewrite the employee data to the file without the removed employee
                                ofstream file("Employees.txt");
                                if (file.is_open()) {
                                    for (const Employee& emp : employees) {
                                        file << emp.getEmployeeID() << " "
                                            << emp.getName() << " "
                                            << emp.getPosition() << " "
                                            << emp.getDailyWage() << "\n";
                                    }
                                    file.close();
                                    cout << "Employee data updated in file.\n";
                                } else {
                                    cerr << "Unable to open file for writing.\n";
                                }
                            } else {
                                cout << "Employee not found.\n";
                            }

                            break;
                        }


                        case 3: {
                            // Display
                            restaurantPayroll.displayEmployeeList();
                            break;
                        }

                        case 4: {
                            break;
                        }

                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }

                    if (ch == 4) {
                        break; // Exit the loop if the user chooses to go back to the main menu
                    }
                }
                break;
            }

            case 2: {
            	system("cls");
                // Employee menu
                string empName;
                cout <<Color(3)<< "Enter your name: ";
                cin.ignore();
                getline(cin, empName);

                bool employeeFound = false; // Added a flag to track if the employee is found

                // Assume the name is unique for simplicity
                for (Employee& emp : restaurantPayroll.getEmployees()) {
                    if (emp.getName() == empName) {
                        employeeFound = true; // Set the flag to true if the employee is found

                        int daysWorked;
                        cout << "Enter days worked: ";
                        cin >> daysWorked;

                        double initialSalary = restaurantPayroll.calculateSalary(emp.getEmployeeID(), daysWorked);
                        double basicPay = 0.6 * initialSalary; // 60% of total salary
                        double pf = 0.12 * basicPay; // 12% of basic pay
                        double esi = 0.04 * initialSalary; // Assume ESI is 4% of the total salary
                        double finalSalary = initialSalary - pf - esi;

                        cout << Color(13) << "\nEmployee Details:\n" << endl;
                        cout << Color(7) <<"ID\t\t: " << emp.getEmployeeID() << "\nName\t\t: " << emp.getName()
                            << "\nPosition\t: " << emp.getPosition() << "\nDaily Wage\t: Rs." << emp.getDailyWage() << endl;

                        cout << Color(13) << "\nSalary Details:\n" << endl;
                        cout << Color(7) << "Initial Salary  : Rs." << initialSalary << endl;
                        cout << "Basic Pay\t: Rs." << basicPay << endl;
                        cout << "PF\t\t: Rs." << pf << endl;
                        cout << "ESI\t\t: Rs." << esi << endl;
                        cout << "Final Salary\t: Rs." << finalSalary << endl;

                        break;
                    }
                }

                if (!employeeFound) {
                    cout << "Employee not found!!" << endl;
                }
                cout<<"\nPress any key to continue....";
                getch();
                break;
            }

            case 3:
                cout << Color(0) << "\nExiting the program.\n";
                for(int i=0;i<32;i++)
                cout<<char(1)<<" ";
                cout<<"\n\n\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}