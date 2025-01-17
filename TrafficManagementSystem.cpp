#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>   // Keep this for now, but we will not use it

#ifdef _WIN32
#include <windows.h>  // This will allow you to use Sleep on Windows
#endif

using namespace std;

// Greedy algorithm for traffic management
class TrafficManagementSystem {
public:
    struct Intersection {
        int id;
        int incomingVehicles;
        int outgoingVehicles;
    };

    void welcome() {
        int choice;
        do {
            clearScreen();
            cout << "======================================" << endl;
            cout << "  Real-Time Traffic Management System" << endl;
            cout << "======================================" << endl;
            cout << "1. Record new vehicles" << endl;
            cout << "2. Manage traffic at intersections" << endl;
            cout << "3. Search vehicle records" << endl;
            cout << "4. View challan records" << endl;
            cout << "5. Help & Helpline Info" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: recordVehicle(); break;
                case 2: manageTraffic(); break;
                case 3: searchVehicle(); break;
                case 4: viewChallanRecords(); break;
                case 5: displayHelp(); break;
                case 6: cout << "Exiting program. Thank you!" << endl; break;
                default: cout << "Invalid choice. Try again!" << endl;
            }
        } while (choice != 6);
    }

private:
    vector<pair<string, string>> vehicleRecords;
    vector<pair<string, string>> challanRecords;

    void clearScreen() {
        cout << "\033[2J\033[1;1H";
    }

    // Using Sleep for Windows instead of thread-based sleep
    void delay(int seconds) {
#ifdef _WIN32
        Sleep(seconds * 1000);  // Sleep takes milliseconds, so multiply by 1000
#else
        std::this_thread::sleep_for(std::chrono::seconds(seconds));  // For other platforms
#endif
    }


void recordVehicle() {
        clearScreen();
        cout << "Enter vehicle registration number: ";
        string regNo;
        cin >> regNo;
        cout << "Enter owner name: ";
        string ownerName;
        cin.ignore();
        getline(cin, ownerName);

        vehicleRecords.emplace_back(regNo, ownerName);
        cout << "Vehicle record added successfully!" << endl;
        delay(2);
    }

    void manageTraffic() {
        clearScreen();
        int numIntersections;
        const int MAX_INTERSECTIONS = 1000;  // Add a reasonable limit

        cout << "Enter the number of intersections (max " << MAX_INTERSECTIONS << "): ";
        cin >> numIntersections;

        if (numIntersections <= 0 || numIntersections > MAX_INTERSECTIONS) {
            cout << "Invalid number of intersections. Exiting..." << endl;
            return;
        }
  vector<Intersection> intersections(numIntersections);
        for (int i = 0; i < numIntersections; ++i) {
            cout << "Enter details for Intersection " << i + 1 << ":\n";
            intersections[i].id = i + 1;
            cout << "  Incoming vehicles: ";
            cin >> intersections[i].incomingVehicles;
            cout << "  Outgoing vehicles: ";
            cin >> intersections[i].outgoingVehicles;
        }

        // Apply greedy algorithm: prioritize intersections with max incoming vehicles
        sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) {
            return a.incomingVehicles > b.incomingVehicles;
        });

        cout << "\nTraffic flow prioritized as follows:\n";
        for (const auto &intersection : intersections) {
            cout << "Intersection " << intersection.id
                 << ": Incoming Vehicles = " << intersection.incomingVehicles
                 << ", Outgoing Vehicles = " << intersection.outgoingVehicles << endl;
        }
        delay(5);
    }
void searchVehicle() {
        clearScreen();
        cout << "Enter registration number to search: ";
        string regNo;
        cin >> regNo;

        auto it = find_if(vehicleRecords.begin(), vehicleRecords.end(),
                          [&regNo](const pair<string, string> &record) { return record.first == regNo; });

        if (it != vehicleRecords.end()) {
            cout << "Vehicle found! Owner: " << it->second << endl;
        } else {
            cout << "Vehicle not found!" << endl;
        }
        delay(2);
    }
