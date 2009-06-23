

#include "solucao.h"


Solucao::Solucao(InstanceVRP* instance, int numSolucoes)
	:instance(instance)
	,numSolucoes(numSolucoes)
{
	geraTodasRotas();
	rankeia();
}

void Solucao::geraTodasRotas(){
	unsigned short i;
	for (i = 0 ; i < this->getNumSolucoes(); i++){
		rotas.push_back(geraRota());
	}
}

Rota* Solucao::geraRota(){

/*
	Seleciona aleatoriamente um indice para um ponto consumidor (!= 0), marca ele como visitado.
	Se a inserção estoura a capacidade do veiculo, insere o ponto depósito e insere a o ponto.(zera capacidade) 
*/
int capacidade, cont = instance->getCapacity();

	while (cont >0 ){
	
		cont--;
	}
	

}

void Solucao::rankeia(){
	int i, j;
	
	for ( i = 0; i < this->rotas.size(); i++){
		for (j = i+1; j < this->rotas.size(); j++){
			if (*(rota.at(j)) < *(rota(i))){
				Rota* tmp = rota[i];
				rota[i] = rota[j];
				rota[j] = tmp;
			}
		}
	}
		
	if (rotas.size() > this->getNumSolucoes()){
		for (i = 30; i < rotas.size(); i++)
			delete rotas.at(i);
		erase (rotas.begin()+30, rotas.end());
	}
}

static Rota* crossover(Rota* rota1, Rota* rota2){
	short probabilidade = (short) (rota1->getCusto() / (double)(rota1->getCusto() + rota2->getCusto())) * 100;
	int posRota1 = 0, posRota2 = 0;
	
	Rota* novaRota = new Rota();
	
	
	while ((posRota1 < rota1->getTamanhoRota()) && (posRota2 < rota2->getTamanhoRota())){
		if ((rand() % 100 ) > probabilidade){
			//Add rota2
			int novoPonto = rota2->getPonto(posRota2++);
			
		}else{
			//Add rota1;
			int novoPonto = rota1->getPonto(posRota1++);
		}
			
	}
}
