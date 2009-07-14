#include <ostream>
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#include "point.h"
#include "instancevrp.h"

// Constructors/Destructors
//  

InstanceVRP::InstanceVRP ( ):deposit(0) {

}

void InstanceVRP::criaMatrizDistancias(){
	int i, j;
	double d;
	this->m = new double*[points.size()];

//	cout << "criando  distancias para pontos...\n" ;	
	for(i = 0; i < this->points.size(); i++){
		this->m[i] = new double[i];
		for(j = 0; j < i; j++){
			double dx = (points[i]->getX() - points[j]->getX())*(points[i]->getX() - points[j]->getX());
			double dy = (points[i]->getY() - points[j]->getY())*(points[i]->getY() - points[j]->getY());
			d = sqrt(dx + dy);
			this->m[i][j] = d;
		}	
	}
}

void InstanceVRP::imprimeMatrizDistancias(){
	int i, j;
	for(i = 0; i < this->points.size(); i++){
		for(j = 0; j < this->points.size(); j++){
			cout << getDistancia(i, j) << " ";		
		}
		cout << "\n";
	}
}

InstanceVRP::~InstanceVRP ( ) { 
	for (unsigned short i = 0; i < this->points.size(); i++){
		delete this->points.at(i);
	}
	delete this->deposit;
}


