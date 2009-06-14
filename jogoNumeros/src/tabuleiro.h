#ifndef TABULEIRO_H
#define TABULEIRO_H
#include <cstring>

#define UP 0
#define DW 1
#define RI 2
#define LE 3
#define ROOT 4
#define NO 5

class Tabuleiro{
public:
	//Tabuleiro
	unsigned char pecas[9];

	//Compara e devolve se sao iguais
	inline bool compara(Tabuleiro* t){
		unsigned short cont;
		if (t == 0)
			return false;
		for (cont = 0; this->pecas[cont] == t->pecas[cont] && cont < 9; cont++);

		if (cont == 9)
			return true;
		else
			return false;

/*		if (this->pecas[0] == t->pecas[0] && this->pecas[1] == t->pecas[1] && this->pecas[2] == t->pecas[2]
		   && this->pecas[3] == t->pecas[3] && this->pecas[4] == t->pecas[4] &&this->pecas[5] == t->pecas[5]
		   && this->pecas[6] == t->pecas[6] &&this->pecas[7] == t->pecas[7] &&this->pecas[8] == t->pecas[8])
			return true;
		else
			return false;*/
	}

	inline bool isSolution(){
		unsigned char sol[9]={'1','2','3','4','5','6','7','8','9'};
		if (memcmp(pecas, sol, 9) == 0)
			return true;
		else
			return false;
//		if (this->pecas[0] == '1' && this->pecas[1] == '2' && this->pecas[2] == '3'
//				   && this->pecas[3] == '4' && this->pecas[4] == '5' && this->pecas[5] == '6'
//				   && this->pecas[6] == '7' &&this->pecas[7] == '8' &&this->pecas[8] == '9')
//					return true;
//				else
//					return false;
	}

	//Faz o movimento e devolve um novo tabuleiro (com o movimento)
	//ou 0 se movimento eh ilegal
	Tabuleiro* move(unsigned short move);

	inline void setMove(unsigned short newMove){m = newMove;}
	inline unsigned short getMove(){return m;}

	void imprimeMove();
	void imprime();

	unsigned int funcao1();
	unsigned int funcao2();

	Tabuleiro();
	~Tabuleiro(){ }


private:
	unsigned short m;

};

#endif //TABULEIRO_H
