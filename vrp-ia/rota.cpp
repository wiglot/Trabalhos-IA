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

Rota::Rota():custoTotal(0){

}

void Rota::setCusto(){
	int j;
	for(j = 0; j < (this->rota.size() - 1); j++){
		this->custoRota += this->i->getDistancia(rota[j], rota[j+1]);
	}
}

Rota::~Rota(){

}
