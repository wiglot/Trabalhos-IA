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
	cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << " Custo Rota 3: "<< rotas[2]->getCusto() << " Custo Rota 4: "<< rotas[3]->getCusto()<< endl;
	
}

void Solucao::geraTodasRotas(){
	unsigned short i;
	Rota* tmp;
//	for (i = 0 ; i < (this->getNumSolucoes()/2); i++){
//		rotas.push_back(geraRotaHeuristica());
//	}
	for (i = 0 ; i < (this->getNumSolucoes()); i++){
		tmp = geraRotaAleatoria();
		if (tmp->validaRota())
			rotas.push_back(tmp);
		else{
			i--;
			cout << "gerada rota invalida!\n";
			}
	}
}


Rota* Solucao::geraRotaAleatoria(){
	//	Seleciona aleatoriamente um indice para um ponto consumidor (!= 0), marca ele como visitado.
	//	Se a inserção estoura a capacidade do veiculo, insere o ponto depósito e insere a o ponto.(zera capacidade)
	Rota *rota = new Rota();
	vector<int> visitados;
	int capacidade = 0, i, pos;
	int cont = instance->getCapacity();
	rota->setInstance(this->instance);
	rota->setPonto(0);
	vector<Point*> points = instance->getPoints();
//	cout << "Capacidade " << cont << endl;
	for(i = 0; i < points.size()-1; i++){
		do {
			pos = rand() % points.size();
		} while (!getVisitado(visitados, pos) && pos!=0);
//		if((getVisitado(visitados, pos))){
	
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
		
/*		}else{
			if(i < instance->getPoints().size())
				i--;
			else{
				rota->setPonto(0);
				break;
			}
		}
*/
	}
//	cout << "Gerou uma rota" << endl;
	rota->setPonto(0);
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
	int i, j;
	
	//vector <Rota*> novosIndividuos;
	Rota* tmp;
	elite = ceil(numSolucoes/100.0 * elite);
	
	for (i = 0 ; i< numGeracoes; i++){
	
		for (j = 0; j < this->numSolucoes; j++){
			int rota1 = rand()%elite;
			int rota2 = (rand()%(this->numSolucoes-elite))+elite;
			//cout << "Crossover entre rota " << rota1  << " e " << rota2 << endl;
			tmp = crossover(rotas[rota1], rotas[rota2]);
			if (tmp != 0)
				rotas.push_back(tmp);
			else{
				j--;
			}
			//cout << "Terminou crossover \n";
		}
		//Tinha que ter round, não apenas ranking...
		
		rankeia();
		cout << "1;" << rotas[0]->getCusto() << ";2;"<< rotas[1]->getCusto() << ";3;"<< rotas[2]->getCusto() << ";4;"<< rotas[3]->getCusto()<< endl;
		
	}
	
	cout << "Custo rota 1:" << rotas[0]->getCusto() << " Custo Rota 2: "<< rotas[1]->getCusto() << " Custo Rota 3: "<< rotas[2]->getCusto() << " Custo Rota 4: "<< rotas[3]->getCusto()<< endl;

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
		for (i = this->getNumSolucoes(); i < rotas.size(); i++)
			delete rotas.at(i);
		rotas.erase (rotas.begin()+this->getNumSolucoes(), rotas.end());
	}
	
}

//Probabilidade do próximo mais próximo
Rota* Solucao::crossover2(Rota* rota1, Rota* rota2){
	short probabilidade = (short) (rota1->getCusto() / (double)(rota1->getCusto() + rota2->getCusto()))* 100;
	int posRota1 = 1, posRota2 = 1;
	int novoPonto;
	int i;
	bool *usado;
	double custoAcumulado = 0.0;	
	int ant = 0;
	
	double distancia1, distancia2;
	
	Rota* novaRota = new Rota;

	novaRota->setInstance(instance);
	//Toda nova rota inicia no deposito
	novaRota->setPonto(0);
	
	
	usado = new bool[instance->getNumPoints()];
	for (i = 0; i < instance->getNumPoints(); i++)
		usado[i] = false;
		 
	while ((posRota1 < rota1->getTamanho()) || (posRota2 < rota2->getTamanho())){
	
		distancia1 = 100000;
		if (posRota1 < rota1->getTamanho())
			do{
				distancia1 =  instance->getDistancia(ant, rota1->getPonto(posRota1));
			}while  (usado[rota1->getPonto(posRota1++)] && (posRota1 < rota1->getTamanho()));
			
		distancia2 = 100000;
		if (posRota2 < rota2->getTamanho())
			do{
				distancia2 = instance->getDistancia(ant, rota2->getPonto(posRota2));
			}while  (usado[rota2->getPonto(posRota2++)] && (posRota2 < rota2->getTamanho()));
		// probabilidade do custo + probabilidade da próxima menor distancia
//		probabilidade = ((rota1->getCusto() / (rota1->getCusto() + rota2->getCusto())) +  (distancia1/(distancia1+distancia2)) *3) * 25;
		probabilidade = (distancia1/(distancia1+distancia2)) * 100;
		//Assim temos a maior probabilidade para o menor valor
		probabilidade = 100 - probabilidade;
		//	cout << probabilidade << endl;
		// testar as distâncias
		if ((rand() % 100 ) >= probabilidade){
			//Add rota2
			//do{
			if (posRota2 < rota2->getTamanho()){
				novoPonto = rota2->getPonto(posRota2);
			//		cout << novoPonto << "Ponto2 - ";
				//}while (usado[novoPonto] &&  (posRota2 < rota2->getTamanho()));
	//			cout << "Selecionado Ponto 2\n";
				if (!usado[novoPonto]){
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
					if (posRota2 >= rota2->getTamanho())
						probabilidade = 100;
				}
			}
				// Testar se é valida (quanto a demanda)???
		}else{
			//Add rota1;
			if (posRota1 < rota1->getTamanho()){
//			do{			
				novoPonto = rota1->getPonto(posRota1);
	//			cout << novoPonto << "Ponto1 - ";
	//		}while(usado[novoPonto] &&  (posRota1 < rota1->getTamanho()));
	//			cout << "Selecionado Ponto 1\n";
				if (!usado[novoPonto]){
					if (novoPonto != 0 )
						usado[novoPonto] = true;
				
					custoAcumulado += instance->getDistancia(ant, novoPonto);
					if (custoAcumulado > instance->getCapacity()){
						if (novoPonto != 0)
							novaRota->setPonto(0);
						custoAcumulado = instance->getDistancia(0, novoPonto);
						ant = novoPonto;
					}

					novaRota->setPonto(novoPonto);
			
					if (posRota1 >= rota1->getTamanho())
						probabilidade = -1;
				}
			}
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

// Crossover que leva em consideração a menor distância entre o ponto atual da rota e o próximo ponto  e os custos
Rota* Solucao::crossover1(Rota* rota1, Rota* rota2){
	short probabilidade = (short) (rota1->getCusto() / (double)(rota1->getCusto() + rota2->getCusto()))* 100;
	int posRota1 = 1, posRota2 = 1;
	int novoPonto;
	int i;
	bool *usado;
	double custoAcumulado = 0.0;	
	int ant = 0;
	
	double distancia1, distancia2;
	
	Rota* novaRota = new Rota;

	novaRota->setInstance(instance);
	//Toda nova rota inicia no deposito
	novaRota->setPonto(0);
	
	
	usado = new bool[instance->getNumPoints()];
	for (i = 0; i < instance->getNumPoints(); i++)
		usado[i] = false;
		 
	while ((posRota1 < rota1->getTamanho()) || (posRota2 < rota2->getTamanho())){
	
		distancia1 = 100000;
		if (posRota1 < rota1->getTamanho())
			if (!usado[rota1->getPonto(posRota1)])
				distancia1 =  instance->getDistancia(ant, rota1->getPonto(posRota1));
			
			
		distancia2 = 100000;
		if (posRota2 < rota2->getTamanho())
			if (!usado[rota2->getPonto(posRota2)])
				distancia2 = instance->getDistancia(ant, rota2->getPonto(posRota2));
		// probabilidade do custo + probabilidade da próxima menor distancia
		probabilidade = ((rota1->getCusto() / (rota1->getCusto() + rota2->getCusto())) +  (distancia1/(distancia1+distancia2)) *3) * 25;
		//Assim temos
		probabilidade = 100 - probabilidade;
		//	cout << probabilidade << endl;
		// testar as distâncias
		if ((rand() % 100 ) >= probabilidade){
			//Add rota2
			//do{
			if (posRota2 < rota2->getTamanho()){
				novoPonto = rota2->getPonto(posRota2++);
			//		cout << novoPonto << "Ponto2 - ";
				//}while (usado[novoPonto] &&  (posRota2 < rota2->getTamanho()));
	//			cout << "Selecionado Ponto 2\n";
				if (!usado[novoPonto]){
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
					if (posRota2 >= rota2->getTamanho())
						probabilidade = 100;
				}
			}
				// Testar se é valida (quanto a demanda)???
		}else{
			//Add rota1;
			if (posRota1 < rota1->getTamanho()){
//			do{			
				novoPonto = rota1->getPonto(posRota1++);
	//			cout << novoPonto << "Ponto1 - ";
	//		}while(usado[novoPonto] &&  (posRota1 < rota1->getTamanho()));
	//			cout << "Selecionado Ponto 1\n";
				if (!usado[novoPonto]){
					if (novoPonto != 0 )
						usado[novoPonto] = true;
				
					custoAcumulado += instance->getDistancia(ant, novoPonto);
					if (custoAcumulado > instance->getCapacity()){
						if (novoPonto != 0)
							novaRota->setPonto(0);
						custoAcumulado = instance->getDistancia(0, novoPonto);
						ant = novoPonto;
					}

					novaRota->setPonto(novoPonto);
			
					if (posRota1 >= rota1->getTamanho())
						probabilidade = -1;
				}
			}
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
	
	//Aplica Mutação...
	novaRota->mutate();
	//...e faz as divisões das rotas...
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
