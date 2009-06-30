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
	cout << "Vai gerar as rotas.." << endl;
	geraTodasRotas();
	cout << "Gerou rotas..." << endl;
	cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << endl;
	rankeia();
	cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << endl;
	for (unsigned short i = 0 ; i< 20000; i++){
		rotas.push_back(crossover(rotas[(i+1)%2], rotas[i%2]));
		cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << " Custo Rota 3: "<< rotas[2]->getCusto() << endl;
		rankeia();	
		
	}
}

void Solucao::geraTodasRotas(){
	unsigned short i;
	for (i = 0 ; i < this->getNumSolucoes(); i++){
		rotas.push_back(geraRota());
		cout << "Gerou rota " << i << endl;
	}
}

Rota* Solucao::geraRota(){
/*
	Seleciona aleatoriamente um indice para um ponto consumidor (!= 0), marca ele como visitado.
	Se a inserção estoura a capacidade do veiculo, insere o ponto depósito e insere a o ponto.(zera capacidade) 
*/      Rota *rota = new Rota();
        vector<int> visitados;
        int capacidade = 0, i, pos;
	int cont = instance->getCapacity();
	rota->setInstance(this->instance);
        rota->setPonto(0);
        vector<Point*> points = instance->getPoints();
	cout << "Capacidade " << cont << endl;
        for(i = 0; i < points.size(); i++){
                pos = rand() % points.size();
//		cout << "POS escolhida em " << i << "=" << pos << endl;
                if((pos != 0) && (getVisitado(visitados, pos))){
//			cout << "Posicao naum foi visitada e eh diferente de zero" << endl;
			//cout << "Demanda do ponto " << pos << "=" << points[pos]->getDemand() << endl; 

	                if((capacidade + points[pos]->getDemand()) <= cont){
//			    cout << "capacidade naum foi excedida...pos incluida na rota " << endl;
	                    capacidade += points[pos]->getDemand();
	                    rota->setPonto(pos);
	                    visitados.push_back(pos);
	                }
	                else{
//			     cout << "Posicao excede a capacidade..." << endl;
	                     rota->setPonto(0);
	                     capacidade = 0;
	                }
                }else{
	//		     cout << "Posicao jah foi visitada" << endl;
			     if(i < instance->getPoints().size())
			   	     i--;
			    else{
				    rota->setPonto(0);
				      break;
		            }
                }
	}
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
		
	if (rotas.size() > this->getNumSolucoes()){
		for (i = 2; i < rotas.size(); i++)
			delete rotas.at(i);
		rotas.erase (rotas.begin()+2, rotas.end());
	}
	
}

Rota* Solucao::crossover(Rota* rota1, Rota* rota2){
	short probabilidade = (short) (rota1->getCusto() / (double)(rota1->getCusto() + rota2->getCusto()))* 100;
	int posRota1 = 0, posRota2 = 0;
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
		 
	while ((posRota1 < rota1->getTamanho()) || (posRota2 < rota2->getTamanho())){
		if ((rand() % 100 ) > probabilidade){
			//Add rota2
			do{
				novoPonto = rota2->getPonto(posRota2++);
		//		cout << novoPonto << "Ponto2 - ";
			}while (usado[novoPonto] &&  (posRota2 < rota2->getTamanho()));
//			cout << "Selecionado Ponto 2\n";
			
			if (novoPonto != 0)
				usado[novoPonto] = true;
			custoAcumulado += instance->getDistancia(ant, novoPonto);
			if (custoAcumulado > instance->getCapacity()){
				if (novoPonto != 0)
					novaRota->setPonto(0);
				custoAcumulado = instance->getDistancia(0, novoPonto);
				ant = novoPonto;
			}
			novaRota->setPonto(novoPonto);
			if (posRota2 == rota2->getTamanho())
				probabilidade = 100;
				// Testar se é valida (quanto a demanda)???
		}else{
			//Add rota1;
			do{
				novoPonto = rota1->getPonto(posRota1++);
		//		cout << novoPonto << "Ponto1 - ";
			}while(usado[novoPonto] &&  (posRota1 < rota1->getTamanho()));
//			cout << "Selecionado Ponto 1\n";
			
			if (novoPonto != 0)
				usado[novoPonto] = true;
				
			custoAcumulado += instance->getDistancia(ant, novoPonto);
			if (custoAcumulado > instance->getCapacity()){
				if (novoPonto != 0)
					novaRota->setPonto(0);
				custoAcumulado = instance->getDistancia(0, novoPonto);
				ant = novoPonto;
			}

			novaRota->setPonto(novoPonto);
			
			if (posRota1 == rota1->getTamanho())
				probabilidade = -1;
		}	
	}


	
	novaRota->setPonto(0);
	novaRota->setCusto();
	
	return novaRota;
//	rotas.push_back(novaRota);
				
//	for (posRota1 = 0 ; posRota1 < novaRota->getTamanho(); posRota1++){
//		cout << novaRota->getPonto(posRota1) << " - ";
//	}	
}
