#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <list>

using namespace std;

struct No {
	int *variaveisNo; //itens escolhidos para colocar na mochila, 1 - item na mochila, 0 - não está na mochila
	float maiorLimite;
	float menorLimite;
	float funcaoObjetivo;
};

void algGuloso(int valorItens[], int pesoItens[], float *&custoBeneficio, int qtdItens){ //decide qual item tem prioridade na mochila
	int j, k, max; 
	float aux;
	for(int i = 0; i < qtdItens; i++){
		custoBeneficio[i] = valorItens[i]/pesoItens[i];
		cout << custoBeneficio[i] << " ";
	}
	cout << endl;
	
	for(j = 0; j < (qtdItens-1); j++){
    	max = j;
    	for(k = j+1; k < qtdItens; k++) {
      		/* Caso tenha algum numero menor ele faz a troca do minimo*/
      		if(custoBeneficio[k] > custoBeneficio[max]){
   				max = j;
      		}
    	}
    	/* Se o minimo for diferente do primeiro numero não ordenado ele faz a troca para ordena-los*/
    	if(j != max){
      		aux = custoBeneficio[j];
      		custoBeneficio[j] = custoBeneficio[max];
      		custoBeneficio[max] = aux;
    	}

		cout << custoBeneficio[j] << " ";
  	}
	//retorna o valor ordenado mas não guarda o índice que corresponde a variável,
	//pensar em uma forma de retornar o índice junto com a razão em um vetor ordenado.
}

int main(int argc, char const *argv[])
{
	int qtdItens, capacidadeMochila;
	No no;
	no.variaveisNo = new int[qtdItens];

	ifstream arqEntrada;
	arqEntrada.open("entrada.txt");
	arqEntrada >> qtdItens;
	arqEntrada >> capacidadeMochila;
	
	for(int i = 0; i < qtdItens; i++){
		no.variaveisNo[i] = 0; //variáveis setadas em 0
	};
	
	int valorItens[qtdItens]; //valor financeiro de cada item
	int pesoItens[qtdItens]; //peso de cada item
	float *custoBeneficio = new float[qtdItens]; //custo benefício, razão entre o valor do produto e o peso

	for(int i = 0; i < qtdItens; i++){
		arqEntrada >> valorItens[i];
	};

	for (int i = 0; i < qtdItens; i++){
		arqEntrada >> pesoItens[i];
	};

	cout << qtdItens << endl;
	cout << capacidadeMochila << endl;
	for (int i = 0; i < qtdItens; i++){
		cout << valorItens[i] << " ";
	};

	cout << endl;
	
	for (int i = 0; i < qtdItens; i++){
		cout << pesoItens[i] << " ";
	};

	cout << endl;

	for (int i = 0; i < qtdItens; i++){
		cout << no.variaveisNo[i] << " ";
	} 
	cout << endl;
	arqEntrada.close();

	algGuloso(valorItens, pesoItens, custoBeneficio, qtdItens);
	
	cout << custoBeneficio[0] << endl;
	
	delete[]custoBeneficio;
	return 0;
}

