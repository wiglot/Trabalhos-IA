#include <ostream>
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

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
		this->custoRota += this->inst->getDistancia(rota[j], rota[j+1]);
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
		if ((capacidade + inst->getPoint(this->rota[j])->getDemand()) <= inst->getCapacity())
			capacidade += inst->getPoint(this->rota[j])->getDemand();
		else{
			rota.insert(rota.begin()+j, 0);
			capacidade = 0.0;
		}
	}
	if (rota.at(rota.back()) != 0)
		rota.push_back(0);
}

void Rota::mutate(double prob){
	unsigned short count, pos;
	int tmp;
	for (count = 0;  count < this->rota.size(); count++){
		if (((rand()%100)) < prob){
			pos = rand()%(this->rota.size()-1);
			if (pos >= count)
				pos++;
			tmp = this->rota[count];
			this->rota[count] = this->rota[pos];
			this->rota[pos] = tmp;
		}
	}	
}

bool Rota::validaRota(){
	int i;
	bool *visitado;
	double capacidade = 0;

//	if ( ( (this->inst->getNumPoints()*2 ) +1 ) < this->getTamanho() || this->getTamanho() < this->inst->getNumPoints() )
//		return false;
	
	visitado = new bool[this->inst->getNumPoints()];


	for (i = 0; i < this->inst->getNumPoints(); i++)
		visitado[i] = false;
		

	for(i = 0; i < this->getTamanho(); i++){
		if (!visitado[this->getPonto(i)]){
			if (this->getPonto(i) == 0)
				capacidade = 0;
			if (capacidade + inst->getPoint(this->rota[i])->getDemand() > inst->getCapacity())
				return false;
			capacidade += this->inst->getPoint(this->rota[i])->getDemand();
			if (this->getPonto(i) != 0)
				visitado[this->getPonto(i)] = true;
			
		}else{
			//cout << "Dois pontos Visitados" << i << endl;
			return false;
		}

	}
	for(i = 1; i < this->inst->getNumPoints(); i++)
		if (!visitado[i])
			return false;
	delete []visitado;			
	return true;
}
