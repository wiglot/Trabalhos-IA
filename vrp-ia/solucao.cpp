

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

}