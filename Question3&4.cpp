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

    //To keep track of destinations and miles vectors initialization
    static bool initialized;

public:
    // Constructor
    Plane(string from, string to) {
        //Makes sure that the destinations and miles vectors are filled out once
        if (!initialized) {
            initialize();
            initialized = true;
        }
        origin = from;
        destination = to;

        auto startiteration = find(destinations.begin(), destinations.end(), origin);
        auto enditeration = find(destinations.begin(), destinations.end(), destination);
        int startindex = startiteration - destinations.begin(); 
        int endindex = enditeration - destinations.begin();  

        distance = miles[startindex] + miles[endindex];  
        pos = 0;
        vel = 0;
        at_SCE = false;
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
            at_SCE = false;
            return;
        } else {
            if (destination == "SCE") {
                at_SCE = true;
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
        //Loading data into destinations and miles
        destinations.push_back("PHL");
        destinations.push_back("ORL");
        destinations.push_back("EWR");
        miles.push_back(160);
        miles.push_back(220);
        miles.push_back(640);
    }
};
