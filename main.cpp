#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <list>

using namespace std;

struct No {
	list<int> variaveisNo; //itens escolhidos para colocar na mochila, 1 - item na mochila, 0 - não está na mochila
	float maiorLimite;
	float menorLimite;
	float funcaoObjetivo;
};

float algGuloso(*valorItens, *pesoItens){
	float aux;
	float *custoBeneficioOrdenado[valorItens.size()];
	for (int i = 0; i < valorItens.size(); i++){
		custoBeneficioOrdenado = valorItens[i]/pesoItens[i];
	}
	aux = custoBeneficioOrdenado[0];
	aux2 = custoBeneficioOrdenado[0]; 
	for(int i = 0; i < valorItens.size(); i++){
		for(int j = 0; j < valorItens.size(); j++){
			if(aux < custoBeneficioOrdenado[j]){
				aux = custoBeneficioOrdenado[j];
				custoBeneficioOrdenado[j] = aux2;
				custoBeneficioOrdenado[i] = aux;
				aux2 = aux;
			}						
		}
	}
	//retorna o valor ordenado mas não guarda o índice que corresponde a variável,
	//pensar em uma forma de retornar o índice junto com a razão em um vetor ordenado.
	return custoBeneficioOrdenado;
}

int main(int argc, char const *argv[])
{
	int qtdItens, capacidadeMochila;
	list<int> variaveis;
	list<int>::iterator it;
	No no;

	ifstream arqEntrada;
	arqEntrada.open("entrada.txt");
	arqEntrada >> qtdItens;
	arqEntrada >> capacidadeMochila;
	
	for(int i = 0; i < qtdItens; i++){
		variaveis.push_front(0); //variáveis setadas em 0
	};

	no.variaveisNo = variaveis;
	
	int *valorItens[qtdItens]; //valor financeiro de cada item
	int *pesoItens[qtdItens]; //peso de cada item
	float *custoBeneficio[qtdItens] //custo benefício, razão entre o valor do produto e o peso
	
	for (int i = 0; i < qtdItens; i++){
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

	for (it = variaveis.begin(); it != variaveis.end(); it++){
		cout << *it << " ";
	} 
	cout << endl;
	arqEntrada.close();

	custoBeneficio = algGuloso(valorItens, pesoItens);
	
	return 0;
}

