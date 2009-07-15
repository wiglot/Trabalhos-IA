
#ifndef ROTA_H
#define ROTA_H
#include <iostream>

using namespace std;

class InstanceVRP;

class Rota{

private:
	vector<int> rota;
	InstanceVRP *inst;
	double custoRota;
	
public:
	Rota();
	~Rota();
	inline void setPonto(int p){ this->rota.push_back(p); }
	inline int getPonto(int ind){ return this->rota.at(ind); }
	
	inline void setRota(vector<int> r){ this->rota = r; }
	inline vector<int> getRota(){ return this->rota; }
	
	int getTamanho(){return rota.size();}
	
	inline void setInstance(InstanceVRP* i){ this->inst = i; }
	
	void setCusto();
	inline double getCusto(){ return this->custoRota; }

	void corrigeRota();
	
	bool validaRota();
	
	void mutate(double prob = 1.0);
//	inline bool operator<(const Rota& rota){
//		return (this->custoRota < rota.getCusto());
//	}

	bool operator==(Rota *rota){
	
	    if (this->rota.size() == rota->getTamanho()){
			for (unsigned short i = 0; i < this->rota.size(); i++ ){
				if (this->getPonto(i) != rota->getPonto(i)){
				//	cout << "pontos diferentes: " << i << ": " << this->getPonto(i) << " _ "<<  rota->getPonto(i) << endl;
					return false;
				}
			}
	    }else{
	    //	cout << "Tamanho diferente " << this->rota.size() << " - " << rota->getTamanho() << endl;
			return false;
				
		}
	    return true;
	
	}
};
#endif
