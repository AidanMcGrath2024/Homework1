#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
//Creating the vectors destinations and miles
vector<string> destinations;
vector<int> miles;

//Pushing the data into each vector
destinations.push_back("PHL");
destinations.push_back("ORL");
destinations.push_back("EWR");
miles.push_back(160);
miles.push_back(220);
miles.push_back(640);

cout << "The destinations vector looks like: " << destinations[0] << " " << destinations[1] << " " << destinations[2] << endl <<  "And the miles vector looks like: " << miles[0] << " " << miles[1] << " " << miles[2] << endl;
}
