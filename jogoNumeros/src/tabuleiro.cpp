#include <iostream>
#include <cstring>

using namespace std;

#include "tabuleiro.h"

Tabuleiro::Tabuleiro():m(NO){
}

Tabuleiro* Tabuleiro::move(unsigned short move){
	register int i = 0;
	register int lin, col;
	bool ok = false;
	Tabuleiro* t = new Tabuleiro();

	while (pecas[i]!='9' && i < 9)
		i++;
	if (i > 8){
       delete t;
       return 0;}
	   
	col = i%3;
	lin = (int) i/3;
	
	switch(move){
		case DW: 
			if (lin < 2){
				ok = true;
				memcpy(t->pecas, this->pecas, 9);
				t->pecas[i] = t->pecas[i+3];
				t->pecas[i+3] = '9';
			}
			break;
			
		case UP: if (lin > 0){
				memcpy(t->pecas, this->pecas, 9);
				t->pecas[i] = t->pecas[i-3];
				t->pecas[i-3] = '9';
				ok = true;
			}
			break;
		case LE: if (col > 0){
				memcpy(t->pecas, this->pecas, 9);
				t->pecas[i] = t->pecas[i-1];
				t->pecas[i-1] = '9';
				ok = true;
			 } 
			 break;
		case RI: if (col < 2){
				memcpy(t->pecas, this->pecas, 9);
				t->pecas[i] = t->pecas[i+1];
				t->pecas[i+1] = '9';
				ok = true;
			}
			break;
	}
	if (ok)
		return t;
	else{
		delete t;
		return 0;
	}
	
}



void Tabuleiro::imprime(){
	if (pecas[0] == '9')
		cout <<  "  ";
	else
		cout << pecas[0] << " ";

	if (pecas[1] == '9')
		cout <<  "  ";
	else
		cout << pecas[1] << " ";

	if (pecas[2] == '9')
		cout <<  " \n";
	else
		cout << pecas[2] << "\n";

	if (pecas[3] == '9')
		cout <<  "  ";
	else
		cout << pecas[3] << " ";

	if (pecas[4] == '9')
		cout <<  "  ";
	else
		cout << pecas[4] << " ";

	if (pecas[5] == '9')
		cout <<  " \n";
	else
		cout << pecas[5] << "\n";

	if (pecas[6] == '9')
		cout <<  "  ";
	else
		cout << pecas[6] << " ";

	if (pecas[7] == '9')
		cout <<  "  ";
	else
		cout << pecas[7] << " ";

	if (pecas[8] == '9')
		cout <<  " \n\n";
	else
		cout << pecas[8] << "\n\n";

}


void Tabuleiro::imprimeMove(){
     switch(this->getMove()){
        case UP: cout <<"UP\n"; break;
        case DW: cout <<"DOWN\n"; break;
        case LE: cout <<"LEFT\n"; break;
        case RI: cout <<"RIGHT\n"; break;
     }
}


unsigned int Tabuleiro::funcao1(){
	unsigned char sol[9]= {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	unsigned int cont, num;
	for (cont = 0, num = 0; cont < 9; cont++)
		if (this->pecas[cont] != sol[cont])
			num++;
	return num;
}


