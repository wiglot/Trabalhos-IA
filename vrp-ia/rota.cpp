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
#include "rota.h"

Rota::Rota():custoRota(0){

}

void Rota::setCusto(){
	int j;
	this->custoRota = 0.0;
	for(j = 0; j < (this->rota.size() - 1); j++){
		this->custoRota += this->i->getDistancia(rota[j], rota[j+1]);
	}
}

Rota::~Rota(){

}

void Rota::corrigeRota(){
	unsigned short j;
	double capacidade, distancia;
	if (rota.at(0) != 0)
		rota.insert(rota.begin(), 0);
	capacidade = 0.0;
	for (j = 0; j < this->rota.size(); j++){
		if ((capacidade + i->getPoint(j)->getDemand()) <= i->getCapcity())
			capacidade += i->getPoint(j)->getDemand();
		else{
			rota.insert(rota.begin()+j, 0)
			capacidade = 0.0
		}
	}
	if (rota.at(rota.back()) != 0)
		rota.insert(rota.back(), 0);
}
