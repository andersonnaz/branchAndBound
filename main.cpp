#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <list>

using namespace std;

struct No{
	int *variaveisNo; //itens escolhidos para colocar na mochila, 1 - item na mochila, 0 - n�o est� na mochila
	float maiorLimite;
	float menorLimite;
	float funcaoObjetivo;
};

struct itens{
    int chave;
    float valor; // custo beneficio
};

void algGuloso(int *valorItens, int *pesoItens, itens *&custoBeneficio, int qtdItens){ //decide qual item tem prioridade na mochila
	int j, k, max;
	float aux, aux_chave;
	for(int i = 0; i < qtdItens; i++){
		custoBeneficio[i].valor = (float)valorItens[i]/pesoItens[i];
	}

	for(j = 0; j < qtdItens; j++){
    	max = j;
    	for(k = j+1; k < qtdItens; k++) {
      		if(custoBeneficio[k].valor > custoBeneficio[max].valor){
   				max = k;
      		}
    	}
    	if(j != max){
      		aux = custoBeneficio[j].valor;
      		aux_chave = custoBeneficio[j].chave;

      		custoBeneficio[j].valor = custoBeneficio[max].valor;
      		custoBeneficio[j].chave = custoBeneficio[max].chave;

      		custoBeneficio[max].valor = aux;
      		custoBeneficio[max].chave = aux_chave;
    	}

  	}

}

int main()
{
	int qtdItens, capacidadeMochila;
	No no;
	no.variaveisNo = new int[qtdItens];

	ifstream arqEntrada;
	arqEntrada.open("entrada2.txt");
	arqEntrada >> qtdItens;
	arqEntrada >> capacidadeMochila;

	int *valorItens; //valor financeiro de cada item
	int *pesoItens; //peso de cada item

    valorItens = new int[qtdItens];
    pesoItens = new int[qtdItens];

    itens *custoBeneficio = new itens[qtdItens]; //custo benef�cio, raz�o entre o valor do produto e o peso

	for (int i = 0; i < qtdItens; i++){
		arqEntrada >> valorItens[i];
	}

	for (int i = 0; i < qtdItens; i++){
		arqEntrada >> pesoItens[i];
	}

	arqEntrada.close();


	cout << qtdItens << endl;
	cout << capacidadeMochila << endl << endl;

    for(int i = 0; i < qtdItens; i++){
		custoBeneficio[i].valor = 0;
		custoBeneficio[i].chave = i;
	}

	for (int x = 0; x < qtdItens; x++){
        cout << "["<< custoBeneficio[x].chave << "]";
		cout << custoBeneficio[x].valor << " ";
	}

	algGuloso(valorItens, pesoItens, custoBeneficio, qtdItens);
    cout << "\n\n";
    for (int x = 0; x < qtdItens; x++){
        cout << "["<< custoBeneficio[x].chave << "]";
		cout <<  custoBeneficio[x].valor << " ";
	}

	delete[]valorItens;
	delete[]pesoItens;
	delete[]custoBeneficio;
	cout << "\n\n";
	system("pause");
	return 0;
}
