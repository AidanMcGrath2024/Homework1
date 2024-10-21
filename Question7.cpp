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
            swap(origin, destination);
            pos = 0.0;
            return;
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
    //Using raw pointers (old C/CPP-style)
    Pilot* pilot1 = new Pilot("Alpha");
    Pilot* pilot2 = new Pilot("Unknown");
    
    //Starting with myPlane designated to pilot1
    pilot1->myPlane = new Plane("SCE", "PHL");

    pilot1->myPlane->setvel(450); // [450 miles per hour]
    double timestep = 15; // [seconds]
    double timemax = 9000; // [seconds]

    //Before starting the iterations:
    cout << "Pilot " << pilot1->getname() << " is now in control of plane " << pilot1->myPlane << endl;
    //Printing information for copilot
    cout << "Pilot " << pilot2->getname() << " is not in control of the plane." << endl;

    for (int time = 0; time < (timemax / timestep); time++) {

        pilot1->myPlane->operate(timestep);
        double position = pilot1->myPlane->getpos();
        
        /* Muting the Question 5 Outputs
        cout << "Time: " << timestep * (time + 1) << " seconds, Position: " << position << " miles." << endl;
        */

        //When the plane lands at SCE:
        if (pilot1->myPlane->getatsce() == 1) {
            cout << "The Plane " << pilot1->myPlane << " is at SCE." << endl;

            // Switching control for pilots: if myPlane points to a plane object (isn't a null pointer)
            if (pilot1->myPlane != nullptr) {
                //Switching command by designating myPlane to pilot2
                pilot2->myPlane = pilot1->myPlane;
                //Clearing pilot1's reference
                pilot1->myPlane = nullptr;; 
            }

            //Printing information for pilot in command
            cout << "Pilot " << pilot2->getname() << " is now in control of plane " << pilot2->myPlane << endl;
            //Printing information for copilot
            cout << "Pilot " << pilot1->getname() << " is not in control of the plane." << endl;

            //Swapping pilots
            Pilot* temp = pilot1;
            pilot1 = pilot2;
            pilot2 = temp;
        }
    }

    delete pilot1->myPlane;
    delete pilot2->myPlane; //Covers all my bases
    delete pilot1;
    delete pilot2;

    return 0;
}
