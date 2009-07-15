
#ifndef SOLUCAO_H
#define SOLUCAO_H

class InstanceVRP;
class Rota;

class Solucao{
public:
	Solucao(InstanceVRP* instance, int numSolucoes);
	~Solucao();
	
	
	Rota* getRota(unsigned short indice){ return rotas.at(indice);}
	void setRota(Rota* rota, unsigned short indice);
	
	inline int getNumSolucoes(){return numSolucoes;}
	
	void start(int numGeracoes, int elite = 20);
	
private:
	vector<Rota*> rotas;
	int numSolucoes;
	InstanceVRP* instance;
	void round();
	void rankeia();
	void geraTodasRotas();
	Rota* geraRotaHeuristica();
	Rota* geraRotaAleatoria();
	bool getVisitado(vector<int> visitados, int pos);
	
	
	
	Rota* crossover2(Rota* rota1, Rota* rota2);
	Rota* crossover1(Rota* rota1, Rota* rota2);
	Rota* crossover(Rota* rota1, Rota* rota2);
	
};

#endif
