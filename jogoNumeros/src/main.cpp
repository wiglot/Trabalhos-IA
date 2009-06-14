#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#include "tree.h"
#include <cstdlib>
//#include "tabuleiro.h"

queue <Tree*> leafs;

stack <Tabuleiro*> stackSolution;

vector<vector <Tabuleiro*> > history;

void buildSolution(Tree* child);
void aprofundamentoInterativo(Tabuleiro *t);

bool find(Tabuleiro* tab){
	int i = 0, j;
	if (tab == 0)
		return false;
	while (tab->pecas[i]!= '9' && i < 9)
		i++;
	if (i > 8)
		return true;
	if (history[i].size() == 0){
		history[i].push_back(tab);
		return false;
	}
	for (j = 0; j < history[i].size(); j++)
		if (tab->compara(history[i][j])){
			//tab->imprime();
			return true;
		}
	history[i].push_back(tab);
	return false;
}

	bool equal(Tree* node, Tree* parent){
		if (parent == 0)
			return false;
		if (node->getNode()->compara(parent->getNode()))
			return true;
		else
			return equal(node, parent->getParent());
	}

int dfsi(Tree* node, int deep){
	Tabuleiro* tmp;
	if (node == 0)
		return 0;
	if (node->getNode()->isSolution()){
		cout << "YEAH!!!\n";
		buildSolution(node);
		return 1;
	}
	if (node->getHeigth() >= deep){
		// if (!find(node->getNode()))
		leafs.push(node);
		return 0;
	}
	Tabuleiro *t = node->getNode();
	//cout << node->getHeigth() << endl;
	//t->imprime();
	if (!equal(node, node->getParent())){

		tmp = t->move(UP);
		if (!find(tmp)){
			node->setChild(tmp, UP);
			if (dfsi(node->getChild(UP), deep) == 1)
				return 1;
		}

		tmp = t->move(DW);
		if(!find(tmp)){
			node->setChild(tmp, DW);
			if (dfsi(node->getChild(DW), deep) == 1)
				return 1;
		}

		tmp = t->move(LE);
		if(!find(tmp)){
			node->setChild(tmp, LE);
			if (dfsi(node->getChild(LE), deep) == 1)
				return 1;
		}

		tmp = t->move(RI);
		if(!find(tmp)){
			node->setChild(tmp, RI);
			if (dfsi(node->getChild(RI), deep) == 1)
				return 1;
		}
		return 0;
	}
	//cout << "Found Equal on path\n";

	return 0;
}

int main(int argc, char **argv){

	Tabuleiro *tmp, *t = new Tabuleiro();

	unsigned int i, scramble;
	string input("123456789");
	vector <Tabuleiro*> t1, t2, t3, t4, t5, t6, t7, t8, t9;

	history.push_back(t1);
	history.push_back(t2);
	history.push_back(t3);
	history.push_back(t4);
	history.push_back(t5);
	history.push_back(t6);
	history.push_back(t7);
	history.push_back(t8);
	history.push_back(t9);

	cout << "Enter number of moves to scramble or 0 to enter by hand: ";
	cin >> scramble;

	if (scramble == 0){     
		cout << "Entre number in one line WITHOUT spaces and a '9' at blanck space: ";
		cin >> input;
	}

	t->pecas[0] = input[0];
	t->pecas[1] = input[1];
	t->pecas[2] = input[2];
	t->pecas[3] = input[3];
	t->pecas[4] = input[4];
	t->pecas[5] = input[5];
	t->pecas[6] = input[6];
	t->pecas[7] = input[7];
	t->pecas[8] = input[8];

	for (i =0; i< scramble; i++){
		tmp = t->move(rand()%4);
		while (tmp == 0){
			tmp = t->move(rand()%4);
		}
		delete t;
		t = tmp;
	}

	cout << "Initial positions:\n";             
	t->imprime();

	aprofundamentoInterativo(t);   

}

void buildSolution(Tree* child){
	Tree* father;
	stackSolution.push(child->getNode());
	father = child->getParent();
	while (father != 0){
		stackSolution.push(father->getNode());
		father = father->getParent();
	}
}

void funcao1(Tabuleiro *t){
	unsigned short move;

	
	cout << t->funcao1() << endl;


}

void aprofundamentoInterativo(Tabuleiro *t){ 
	Tree* arvore;
	unsigned int i;
	int deep = 2, inc = 2, MAX;

	cout << "Enter Initial Deep: ";
	cin >> deep;
	cout << "Inc: ";
	cin >> inc;
	cout << "Enter MAX Deep: ";
	cin >> MAX;


	leafs.push(new Tree(t));
	leafs.push(0); //Indicador de final de um nível;
	while (!leafs.empty()){
		arvore = leafs.front();
		leafs.pop();
		while (arvore != 0){
			if (dfsi(arvore, deep) == 1){
				cout << "Initial positions:\n";               
				stackSolution.top()->imprime();
				stackSolution.pop();
				i = 1;
				while (!stackSolution.empty()){
					cout << "Move #" << i << ", Moves ";
					stackSolution.top()->imprimeMove();
					stackSolution.top()->imprime();
					//cout << stackSolution.top()->funcao1() << endl;
					stackSolution.pop();
					i++;

				}
				cout <<"Solution found!!\n";
				return;
			}
			arvore = leafs.front();
			leafs.pop();
		}

		leafs.push(0); // Final de um nivel
		if (leafs.size() == 1){
			cout << "No more moves!, no solution found!\n";
			return;
		}
		if (deep >= MAX){
			cout <<"Not Fond solution in MAX deep: "<< MAX <<endl;
			return;
		}
		cout << "not found in deep: " << deep <<endl; 
		deep += inc;
	}
}
