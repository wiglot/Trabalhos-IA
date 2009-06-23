#ifndef SOLUCAO_H
#define SOLUCAO_H

class InstanceVRP;
class Rota;

class Solucao{
public:
	Solucao(InstanceVRP* instance, int numSolucoes);
	~Solucao();
	
	const int NUM_SOLUCOES;
	
	Rota* getRota(unsigned short indice){ return rotas.at(indice);}
	void setRota(Rota* rota, unsigned short indice);
	
	inline int getNumSolucoes(){return numSolucoes;}
	
private:
	vector<Rota*> rotas;
	int numSolucoes;
	InstanceVRP* instance;
	
	void rankeia();
	void geraTodasRotas();
	Rota* geraRota();
	
	static Rota* crossover(Rota* rota1, Rota* rota2);
};

#endif
