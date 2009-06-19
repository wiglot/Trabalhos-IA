
#ifndef ROTA_H
#define ROTA_H

class InstanceVRP;

class Rota{

private:
	vector<int> rota;
	InstanceVRP *i;
	int custoRota;
	
public:
	Rota();
	~Rota();
	inline void setPonto(int p){ this->rota.push_back(p); }
	inline int getPonto(int ind){ return this->rota.at(ind); }
	
	inline void setRota(vector<int> r){ this->rota = r; }
	inline vector<int> getRota(){ return this->rota; }
	
	inline void setInstance(InstanceVRP* i){ this->i = i; }
	
	void setCusto();
	inline void getCusto(){ return this->custoRota; }
	

};

#endif
