#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "point.h"
#include "instancevrp.h"

// Constructors/Destructors
//  

InstanceVRP::InstanceVRP ( ):deposit(0) {

}

InstanceVRP::~InstanceVRP ( ) { 
	for (unsigned short i = 0; i < this->points.size(); i++){
		delete this->points.at(i);
	}
	delete this->deposit;
}


