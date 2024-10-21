#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
using namespace std;

// Question 3
class Plane {
private: 
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    string origin, destination;
    static vector<string> destinations;
    static vector<int> miles;

    //To keep track of destinations and miles vectors
    static bool initialized;

public:
    // Constructor
    Plane(string from, string to) {
        //Makes sure that the destinations and miles vectors are filled out once
        if (!initialized) {
            initialize();
            initialized = 1;
        }
        origin = from;
        destination = to;

        auto enditeration = find(destinations.begin(), destinations.end(), destination);
        int endindex = enditeration - destinations.begin();  

        //distance is set to be the distance to the destination
        distance = miles[endindex];  
        pos = 0;
        vel = 0;
        at_SCE = 0;
        cout << "Plane Created at " << this << endl;
    }

    // Destructor
    ~Plane() {
        cout << "Plane Destroyed" << endl;
    }

    // Operate function
    void operate(double dt) {
        if (pos < distance) {
            pos += (vel / 3600) * dt; // Converting mph to miles per second
            at_SCE = 0;
            return;
        } else {
            if (destination == "SCE") {
                at_SCE = 1;
                swap(origin, destination);
                pos = 0.0;
                return;
            } 
            else {
            swap(origin, destination);
            pos = 0.0;
            return;
            }
        }
    }

    // Getters
    double getpos() const {
        return pos;
    }

    string getorigin() const {
        return origin;
    }

    string getdestination() const {
        return destination;
    }

    bool getatsce() const {
        return at_SCE;
    }

    double getvel() const {
        return vel;
    }

    // Setter for velocity
    void setvel(double newvel) {
        vel = newvel;
    }

private:
    static void initialize() {
        //Using .push_back instead of directly assigning to each element - I got errors using direct assignment
        destinations.push_back("PHL");
        destinations.push_back("ORL");
        destinations.push_back("EWR");
        miles.push_back(160);
        miles.push_back(220);
        miles.push_back(640);
    }
};

// Question 6
class Pilot {
private:
    string name;

public:
    // Constructor
    Pilot(string name) : name(name) {
        cout << "Pilot " << this->name << " with certificate number " << this << " is at the gate, ready to board the plane." << endl;
    }

    ~Pilot() {
        cout << "Pilot " << name << " is out of the plane." << endl;
    }

    string getname() const {
        return name;
    }

    Plane* myPlane; // Changed to shared_ptr
};


// Question 2: Modified for Question 3
vector<string> Plane::destinations(3);
vector<int> Plane::miles(3);
bool Plane::initialized = 0;

// Question 5
int main() {
    Plane plane1("SCE", "PHL");
    plane1.setvel(450); // [450 miles per hour]
    double timestep = 15; // [seconds]
    double timemax = 9000; // [seconds]
    for (int time = 0; time < (timemax / timestep); time++) {
        //Using the operate function in Plane class
        plane1.operate(timestep);
        //Getting position
        double position = plane1.getpos();
        cout << "Time: " << timestep * (time + 1) << " seconds, Position: " << position << " miles." << endl;
    }
    return 0;
}
