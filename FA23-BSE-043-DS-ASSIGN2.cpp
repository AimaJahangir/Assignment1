#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Patient {
public:
    string name;
    int emergencyLevel;
    int id;
    static int count;

    Patient(string patientName, int level) {
        name = patientName;
        emergencyLevel = level;
        id = ++count;
    }

    bool operator>(const Patient& other) const {
        if (emergencyLevel == other.emergencyLevel)
            return id > other.id;
        return emergencyLevel > other.emergencyLevel;
    }
};

int Patient::count = 0;

void displayMainMenu() {
    cout << "\n--- Hospital Patient Priority Queue System ---\n";
    cout << "1. Add Patient\n";
    cout << "2. Treat Next Patient\n";
    cout << "3. Show Treatment Order\n";
    cout << "4. Show Disease Priority List\n";
    cout << "5. Exit\n";
    cout << "Select an option: ";
}

void displayDiseaseList() {
    cout << "\n--- Disease Priority List ---\n";
    cout << "1. Heart Attack (Priority: 1)\n";
    cout << "2. Stroke (Priority: 1)\n";
    cout << "3. Severe Burn (Priority: 2)\n";
    cout << "4. Broken Leg (Priority: 2)\n";
    cout << "5. Fractured Arm (Priority: 2)\n";
    cout << "6. Fever (Priority: 3)\n";
    cout << "7. Food Poisoning (Priority: 3)\n";
    cout << "8. Migraine (Priority: 3)\n";
    cout << "9. Mild Cold (Priority: 4)\n";
    cout << "10. Small Cut (Priority: 4)\n";
}

int main() {
    priority_queue<Patient, vector<Patient>, greater<Patient>> patientQueue;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string patientName;
            int level;

            cout << "Enter patient's name: ";
            getline(cin, patientName);

            displayDiseaseList();

            do {
                cout << "Enter emergency level (1-4): ";
                cin >> level;
                if (level < 1 || level > 4)
                    cout << "Invalid input. Please enter a value between 1 and 4.\n";
            } while (level < 1 || level > 4);

            patientQueue.push(Patient(patientName, level));
            cout << "Patient \"" << patientName << "\" added successfully.\n";
        }
        else if (choice == 2) {
            if (!patientQueue.empty()) {
                Patient nextPatient = patientQueue.top();
                patientQueue.pop();
                cout << "Treating: " << nextPatient.name << " (Emergency Level: " << nextPatient.emergencyLevel << ")\n";
            } else {
                cout << "No patients to treat.\n";
            }
        }
        else if (choice == 3) {
            if (patientQueue.empty()) {
                cout << "No patients in the queue.\n";
            } else {
                priority_queue<Patient, vector<Patient>, greater<Patient>> tempQueue = patientQueue;
                cout << "\n--- Current Treatment Order ---\n";
                while (!tempQueue.empty()) {
                    Patient p = tempQueue.top();
                    tempQueue.pop();
                    cout << "- " << p.name << " (Emergency Level: " << p.emergencyLevel << ")\n";
                }
            }
        }
        else if (choice == 4) {
            displayDiseaseList();
        }
        else if (choice == 5) {
            cout << "Exiting the system. Stay healthy!\n";
        }
        else {
            cout << "Invalid option! Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
