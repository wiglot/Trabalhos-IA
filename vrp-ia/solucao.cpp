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

#include "solucao.h"

Solucao::Solucao(InstanceVRP* instance, int numSolucoes)
:instance(instance)
,numSolucoes(numSolucoes)
{

	srand(time(NULL));
//	cout << "Vai gerar as rotas.." << endl;
	geraTodasRotas();
//	cout << "Gerou rotas..." << endl;
//	cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << endl;
	rankeia();
	for (unsigned short j = 0; j < this->numSolucoes; j++){
		cout << rotas[j]->getCusto() << ";" ;
	}
	cout << endl;
	//cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << " Custo Rota 3: "<< rotas[2]->getCusto() << " Custo Rota 4: "<< rotas[3]->getCusto()<< endl;
	
}

void Solucao::geraTodasRotas(){
	unsigned short i;
	Rota* tmp;

/*	for (i = 0 ; i < (this->getNumSolucoes()/2); i++){
		tmp = geraRotaHeuristica();
		if (tmp->validaRota())
			rotas.push_back(tmp);
		else{
			i--;
			cout << "gerada rota invalida!\n";
		}
	}
*/
	
	for (i = 0 ; i < (this->getNumSolucoes()); i++){
		tmp = geraRotaAleatoria();
		if (tmp->validaRota())
			rotas.push_back(tmp);
		else{
			i--;
			//cout << "gerada rota invalida!\n";
		}
	}
}


Rota* Solucao::geraRotaAleatoria(){
	//	Seleciona aleatoriamente um indice para um ponto consumidor (!= 0), marca ele como visitado.
	//	Se a inser��o estoura a capacidade do veiculo, insere o ponto dep�sito e insere a o ponto.(zera capacidade)
	Rota *rota = new Rota();
	vector<int> visitados;
	int capacidade = 0, i, pos;
	int cont = instance->getCapacity();
	rota->setInstance(this->instance);
	rota->setPonto(0);
	vector<Point*> points = instance->getPoints();
	for(i = 0; i < points.size()-1; i++){
		do {
			pos = rand() % points.size();
		} while (!getVisitado(visitados, pos) && pos!=0);

	
		if((capacidade + points[pos]->getDemand()) <= cont){
			capacidade += points[pos]->getDemand();
			rota->setPonto(pos);
			visitados.push_back(pos);
		}
		else{
			rota->setPonto(0);
			rota->setPonto(pos);
			capacidade = points[pos]->getDemand();
			visitados.push_back(pos);								
		}
		

	}

	
	for(i = 0; i < points.size()-1; i++){
		if (getVisitado(visitados, i)){
			if((capacidade + points[i]->getDemand()) <= instance->getCapacity()){
				capacidade += points[i]->getDemand();
				rota->setPonto(i);
				visitados.push_back(i);
			}
			else{
				rota->setPonto(0);
				rota->setPonto(i);
				capacidade = points[i]->getDemand();
				visitados.push_back(i);								
			}
		}
	}
	rota->setPonto(0);
	
	vector<int> tmp = rota->getRota();
//	for(i = 0; i < tmp.size(); i++)
//		if(tmp[i] == 0)
//			cout << tmp[i] << endl;
//		else
//			cout << tmp[i] << " ";
	rota->setCusto();
//	cout << "\n";
//	cout << rota->getCusto() << endl;

	return rota;
}
Rota* Solucao::geraRotaHeuristica(){
	Rota *rota = new Rota();
	vector<int> visitados;
	int capacidade = 0, i = 0, j, pos, menor;
	int cont = instance->getCapacity();
	rota->setInstance(this->instance);
	rota->setPonto(0);
	vector<Point*> points = instance->getPoints();
	while(i < (instance->getNumPoints()-1)){
		pos = rand() % instance->getNumPoints();
		if((pos != 0) && getVisitado(visitados, pos)){
			rota->setPonto(pos);
			capacidade += points[pos]->getDemand();
			visitados.push_back(pos);
			i++;
		}
		while((capacidade != 0)){
			double dist = 1000000.0;
			menor = -1;
			for(j = 1; j < instance->getNumPoints(); j++){
				if (getVisitado(visitados, j) && j != pos && menor != pos){
//					cout << instance->getDistancia(pos, j) << " " << instance->getDistancia(pos, menor) << endl;
					if((instance->getDistancia(pos, j) < dist)){
						dist = instance->getDistancia(pos, j);
						menor = j;
					}
				}
			}
			if (-1 == menor){
				capacidade = 0;
				rota->setPonto(0);
			}else{
				if(capacidade + points[menor]->getDemand() <= cont){
					pos = menor;
					rota->setPonto(pos);
					capacidade += points[pos]->getDemand();
					visitados.push_back(pos);
					i++;
				}else{
					capacidade = 0;
					rota->setPonto(0);
				}
			}
			if (i == instance->getNumPoints()){
				capacidade = 0;
			}
		}
	}
	rota->setPonto(0);
	cout << "Gerou uma rota" << endl;
	vector<int> tmp = rota->getRota();
	for(i = 0; i < tmp.size(); i++)
		if(tmp[i] == 0)
			cout << tmp[i] << endl;
		else
			cout << tmp[i] << " ";
	rota->setCusto();
	cout << "\n";
	cout << rota->getCusto() << endl;

	return rota;
}



bool Solucao::getVisitado(vector<int> visitados, int pos){
	int i;
	for(i = 0; i < visitados.size(); i++){
		if(visitados[i] == pos)
			return false;

	}
	return true;
}

void Solucao::start(int numGeracoes, int elite){
	int i, j, k = 0;
	int rota1, rota2;
	//vector <Rota*> novosIndividuos;
	Rota* tmp;
	elite = ceil(numSolucoes/100.0 * elite);
	
	for (i = 0 ; i< numGeracoes; i++){
	
		for (j = 0; j < this->numSolucoes; j++){
		
			//k conta o número de rotas geradas mas que são repitidas.
			if (k > 20){
				k = 0;
				do{
					rota1 = rand()%elite;
					rota2 = (rand()%(this->numSolucoes-elite))+elite;
					tmp = crossover(rotas[rota1], rotas[rota2]);
				}while (tmp == 0);
				//cout << "20 rotas geradas e nenhuma é inedita... removendo rota e inserindo no final...\n";
				for (unsigned short count = 0; count < (this->numSolucoes/2); count++){
					if((*tmp) == (rotas[count])){
						delete rotas[count];
						rotas.erase(rotas.begin()+count);
						rotas[count] = tmp;
						j++;
						break; //Sai do laço interno...
					}
				}
			}
			//cout << "Crossover entre rota " << rota1  << " e " << rota2 << endl;
			do{
				rota1 = rand()%elite;
				rota2 = (rand()%(this->numSolucoes-elite))+elite;
				tmp = crossover(rotas[rota1], rotas[rota2]);
			}while(tmp == 0);
			// Tentativa de uma busca Tabu, mas tah trancando...
			for (unsigned short count = 0; count < (this->numSolucoes/2); count++){
				if((*tmp) == (rotas[count])){
					delete tmp;
					tmp = 0;
					break; //Sai do laço interno...
				}
			}
			if (tmp != 0){
				rotas.push_back(tmp);
				k = 0;
			}
			else{
				j--;
				k++;
			}
		
		}
		round();	
		for (j = 0; j < this->numSolucoes; j++){
			cout << rotas[j]->getCusto() << ";" ;
		}
		cout << endl;
		
	}
	
	//cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << " Custo Rota 3: "<< rotas[2]->getCusto() << " Custo Rota 4: "<< rotas[3]->getCusto()<< endl;

}

void Solucao::rankeia(){
	int i, j;
	for ( i = 0; i < this->rotas.size(); i++){
		for (j = i+1; j < this->rotas.size(); j++){
			if ((rotas.at(j)->getCusto()) < (rotas.at(i))->getCusto()){
				Rota* tmp = rotas[i];
				rotas[i] = rotas[j];
				rotas[j] = tmp;
			}
		}
	}
	
}

void Solucao::round(){
	int extremes = (int)ceil((5.0/this->getNumSolucoes()) * 100);
	int i, j;
	Rota *r;
	
	//Existe a probabilidade de 5% de um elemento da nova geração passar a ser da 
	if (rotas.size() > this->getNumSolucoes()){
		for (i = this->getNumSolucoes(); i < rotas.size(); i++){
			if (rotas.at(i)->getCusto() < rotas[0]->getCusto()){
				r = rotas[0];
				rotas[0] = rotas[i];
				rotas[i] = r;	
			}
			if (i-this->getNumSolucoes() > extremes && i-this->getNumSolucoes() < this->getNumSolucoes())
				if ((rand()%100) < 5){
					r = rotas.at(i);
					rotas[i] = rotas[i-this->getNumSolucoes()];
					rotas[i-this->getNumSolucoes()] = r;
				}
			
			delete rotas.at(i);
		}
		rotas.erase (rotas.begin()+this->getNumSolucoes(), rotas.end());
	}
	
	for (i = this->getNumSolucoes()-(2*extremes); i < this->getNumSolucoes(); i++){
		do{
			r = geraRotaAleatoria();
		}while(!r->validaRota());
		delete rotas.at(i);
		rotas.at(i) = r;
	}
	
	rankeia();

}

Rota* Solucao::crossover(Rota* rota1, Rota* rota2){
	short probabilidade = 50;
	int posRota1 = 1, posRota2 = 1;
	int novoPonto;
	int i;
	bool *usado;
	double custoAcumulado = 0.0;	
	int ant = 0;
	
	Rota* novaRota = new Rota;

	novaRota->setInstance(instance);

	usado = new bool[instance->getNumPoints()];
	for (i = 0; i < instance->getNumPoints(); i++)
		usado[i] = false;
		 
	while ((posRota1 < rota1->getTamanho()) && (posRota2 < rota2->getTamanho())){
		if ((rand() % 100 ) < probabilidade){
			//Add rota2
			do{
				novoPonto = rota2->getPonto(posRota2++);
			}while ((posRota2 < rota2->getTamanho()) && novoPonto != 0);

			if (novoPonto != 0 && !usado[novoPonto]){
				posRota1++;
				novaRota->setPonto(novoPonto);
			}

		}else{
			//Add rota1;
			do{
				novoPonto = rota1->getPonto(posRota1++);
			}while(posRota1 < rota1->getTamanho() && novoPonto != 0);

			if (novoPonto != 0 && !usado[novoPonto]){
				posRota2++;
				novaRota->setPonto(novoPonto);
			}
			
		}	
	}

	for (i = 1; i < instance->getNumPoints(); i++)
		if (!usado[i])
			novaRota->setPonto(i);
	
	//Aplica Muta��o...
	novaRota->mutate();
	//...e faz as divis�es das rotas...
	novaRota->corrigeRota();
	if (!novaRota->validaRota()){
		delete novaRota;
		return 0;
	}
//	novaRota->setPonto(0);
	novaRota->setCusto();
	
	return novaRota;
//	rotas.push_back(novaRota);
				
//	for (posRota1 = 0 ; posRota1 < novaRota->getTamanho(); posRota1++){
//		cout << novaRota->getPonto(posRota1) << " - ";
//	}	
}
