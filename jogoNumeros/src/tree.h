#ifndef TREE_H
#define TREE_H
#include "tabuleiro.h" 

class Tree{
private:
	Tree* parent;
	Tree* child[4];
	Tabuleiro *node;
//	unsigned short numChild;
	unsigned long h; //Altura
public:
	Tree(Tabuleiro* node){
		parent = 0;
		this->node=node;
		this->h = 0;
	}
	~Tree(){
		int i;
		for (i = 0; i<4 ; i++)
			if(this->child[i] != 0)
				delete child[i];

		delete node;
	 }

	//Index indica o movimento feito (UP,DW,LE e RI)
	//Set tabuleiro como filho(cria novo nó)
	void setChild(Tabuleiro* t, unsigned short index){
		if(t != 0){		
			child[index] = new Tree(t);
			child[index]->setParent(this);
			t->setMove(index);
			child[index]->setHeigth(this->getHeigth()+1);
		}else
			child[index] = 0;
	}
	
	inline void setParent(Tree* p){parent = p;}
	inline Tree* getParent(){return parent;}
	inline Tree* getChild(unsigned short index)
		{return child[index];}

	inline void setHeigth(unsigned long h){this->h = h;}
	inline unsigned long getHeigth(){return h;}

	inline Tabuleiro* getNode(){return node;}
	inline Tabuleiro* getNode(unsigned short index){return getChild(index)->getNode();}
};

#endif
