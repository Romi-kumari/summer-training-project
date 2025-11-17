#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;
int complaintCounter = 1; 
map<string, int> typeWeights = {
    {"Fire Hazard", 5},
    {"Water Leakage", 4},
    {"Garbage Overflow", 3},
    {"Pothole", 2},
    {"Streetlight Issue", 1}
};

// Complaint structure
struct Complaint {
    int id;
    string name;
    string type;
    string zone;
    int urgency;
    string description;
    time_t timestamp;
    int priority;

    // Operator overloading for priority queue (max-heap)
    bool operator<(const Complaint& other) const {
        return priority < other.priority; // Higher priority first
    }
};

// Priority queue to hold all complaints
priority_queue<Complaint> complaintsQueue;

// Function to calculate final priority
int calculatePriority(string type, int urgency) {
    return urgency + typeWeights[type];
}

// Register a new complaint
void registerComplaint() {
    Complaint c;
    cin.ignore(); // flush input
    cout << "\nEnter your name: ";
    getline(cin, c.name);
    cout << "Enter complaint type (Fire Hazard / Water Leakage / Garbage Overflow / Pothole / Streetlight Issue): ";
    getline(cin, c.type);
    cout << "Enter your zone/area: ";
    getline(cin, c.zone);
    cout << "Enter urgency level (1 to 10): ";
    cin >> c.urgency;
    cin.ignore();
    cout << "Enter complaint description: ";
    getline(cin, c.description);

    c.id = complaintCounter++;
    c.timestamp = time(0);
    c.priority = calculatePriority(c.type, c.urgency);

    complaintsQueue.push(c);

    cout << "\n✅ Complaint Registered with ID: " << c.id << "\n";
}

// Display all complaints in priority order
void displayComplaints(priority_queue<Complaint> tempQueue) {
    if (tempQueue.empty()) {
        cout << "\n⚠️  No complaints to display.\n";
        return;
    }

    cout << "\n===== Pending Complaints (High Priority First) =====\n";
    while (!tempQueue.empty()) {
        Complaint c = tempQueue.top();
        tempQueue.pop();
        cout << "\nComplaint ID: " << c.id
             << "\nName: " << c.name
             << "\nType: " << c.type
             << "\nZone: " << c.zone
             << "\nUrgency: " << c.urgency
             << "\nPriority Score: " << c.priority
             << "\nDescription: " << c.description
             << "\nTimestamp: " << ctime(&c.timestamp)
             << "-------------------------------------------\n";
    }
}

// Resolve the top complaint
void resolveTopComplaint() {
    if (complaintsQueue.empty()) {
        cout << "\n⚠️  No complaints to resolve.\n";
        return;
    }

    Complaint top = complaintsQueue.top();
    complaintsQueue.pop();

    ofstream file("resolved_complaints.txt", ios::app);
    if (file.is_open()) {
        file << "Complaint ID: " << top.id << "\n"
             << "Name: " << top.name << "\n"
             << "Type: " << top.type << "\n"
             << "Zone: " << top.zone << "\n"
             << "Urgency: " << top.urgency << "\n"
             << "Priority: " << top.priority << "\n"
             << "Description: " << top.description << "\n"
             << "Resolved At: " << ctime(&top.timestamp)
             << "---------------------------------------\n";
        file.close();
        cout << "\n✅ Complaint ID " << top.id << " resolved and logged.\n";
    } else {
        cout << "\n❌ Error writing to file.\n";
    }
}

// View resolved complaints from file
void viewResolvedComplaints() {
    ifstream file("resolved_complaints.txt");
    if (file.is_open()) {
        cout << "\n===== Resolved Complaints =====\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "\n⚠️  No resolved complaints file found.\n";
    }
}

// Main menu
void menu() {
    int choice;
    do {
        cout << "\n===== Smart City Complaint Portal =====\n";
        cout << "1. Register New Complaint\n";
        cout << "2. View All Complaints (Prioritized)\n";
        cout << "3. Resolve Top Priority Complaint\n";
        cout << "4. View Resolved Complaints\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerComplaint(); break;
            case 2: displayComplaints(complaintsQueue); break;
            case 3: resolveTopComplaint(); break;
            case 4: viewResolvedComplaints(); break;
            case 5: cout << "\n👋 Exiting... Thank you!\n"; break;
            default: cout << "\n❌ Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}