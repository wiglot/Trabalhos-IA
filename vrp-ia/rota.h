
#ifndef ROTA_H
#define ROTA_H

class InstanceVRP;

class Rota{

private:
	vector<int> rota;
	InstanceVRP *i;
	double custoRota;
	
public:
	Rota();
	~Rota();
	inline void setPonto(int p){ this->rota.push_back(p); }
	inline int getPonto(int ind){ return this->rota.at(ind); }
	
	inline void setRota(vector<int> r){ this->rota = r; }
	inline vector<int> getRota(){ return this->rota; }
	
	int getTamanho(){return rota.size();}
	
	inline void setInstance(InstanceVRP* i){ this->i = i; }
	
	void setCusto();
	inline double getCusto(){ return this->custoRota; }

	void corrigeRota();
	
	bool validaRota();
	
	void mutate(double prob = 1.0);
//	inline bool operator<(const Rota& rota){
//		return (this->custoRota < rota.getCusto());
//	}

};

#endif
