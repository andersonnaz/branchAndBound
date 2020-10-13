#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <list>
using namespace std;

struct No{
    int chave;
    float *solucao;
    float funcao_objetivo;
    int capacidade_mochila;
    list<No>arvore;
};

struct CUSTO_BENEFICIO{
    float custo_beneficio;
    int chave;
};

void guloso(CUSTO_BENEFICIO *&item, int qtd_itens){
    int valor_max, indice_1, indice_2;
    CUSTO_BENEFICIO armazenar;

    for(indice_1=0; indice_1 < qtd_itens; indice_1++){
        valor_max = indice_1;
        for(indice_2 = indice_1+1; indice_2 < qtd_itens; indice_2++){
            if(item[indice_2].custo_beneficio > item[valor_max].custo_beneficio){
                valor_max = indice_2;
            }
        }
        if(indice_1 != valor_max){
            armazenar.custo_beneficio = item[indice_1].custo_beneficio;
            armazenar.chave = item[indice_1].chave;

            item[indice_1].custo_beneficio = item[valor_max].custo_beneficio;
            item[indice_1].chave = item[valor_max].chave;

            item[valor_max].custo_beneficio = armazenar.custo_beneficio;
            item[valor_max].chave = armazenar.chave;
        }
    }
}

void relaxacao_linear(No &no, CUSTO_BENEFICIO *item, int qtd_itens, int capacidade_mochila, int *peso_itens, int *valor_itens, int marcar_indice){
    no.funcao_objetivo = 0;
    no.capacidade_mochila = capacidade_mochila;

    if(marcar_indice > 0){
        no.funcao_objetivo = valor_itens[marcar_indice-1];
        no.capacidade_mochila -= peso_itens[marcar_indice-1];

        for(int i=0;i<qtd_itens;i++){
            if(i!= marcar_indice-1){
                no.solucao[i] = 0;
            }
            else{
                no.solucao[i] = 1;
            }
        }
    }
    else if(marcar_indice < 0){
        marcar_indice = -(marcar_indice);
        no.funcao_objetivo = 0;
        no.capacidade_mochila = capacidade_mochila;

        for(int i=0;i<qtd_itens;i++){
            no.solucao[i] = 0;
        }
    }

    cout << "---------------------------------------\nChave No: " << no.chave << endl;
    cout << "[capacidade mochila]: " << no.capacidade_mochila << endl;
    cout << "[funcao objetivo]: " << no.funcao_objetivo << endl;

    for(int i=0;i<qtd_itens;i++){
        if((peso_itens[item[i].chave] <= no.capacidade_mochila)&&(i != item[marcar_indice-1].chave)){
            no.solucao[item[i].chave] = 1;
            no.funcao_objetivo += valor_itens[item[i].chave];
            no.capacidade_mochila -= peso_itens[item[i].chave];

            cout << "\n[capacidade mochila]: " << no.capacidade_mochila << endl;
            cout << "[funcao objetivo]: " << no.funcao_objetivo << endl;
        }
        else if((no.capacidade_mochila > 0)&&(i != item[marcar_indice-1].chave)){
            no.chave = item[i].chave + 1;
            marcar_indice = no.chave;
            no.solucao[item[i].chave] = (float)no.capacidade_mochila/peso_itens[item[i].chave];

            no.funcao_objetivo += ((float)no.capacidade_mochila/peso_itens[item[i].chave])*valor_itens[item[i].chave];
            no.capacidade_mochila -= ((float)no.capacidade_mochila/peso_itens[item[i].chave])*peso_itens[item[i].chave];

            cout << "\n[capacidade mochila]: " << no.capacidade_mochila << endl;
            cout << "[funcao objetivo]: " << no.funcao_objetivo << endl;

            break;
        }

    }
    cout << "<<" << marcar_indice << ">>\n";
    if(no.arvore.size()==0){
        no.arvore.push_back(no);
    }
    cout << "solucao parcial -> [ ";
    for(int i=0;i<qtd_itens;i++){
        cout << no.solucao[i] << " ";
    }
    cout << "]" << endl << endl;
}

int main()
{
    int qtd_itens;
    int capacidade_mochila;
    int *valor_item;
    int *peso_item;
    list<No>arvore;
    No no;

    ifstream arqEntrada;
	arqEntrada.open("entrada2.txt");

	arqEntrada >> qtd_itens;
	arqEntrada >> capacidade_mochila;

	valor_item = new int[qtd_itens];
	peso_item = new int[qtd_itens];
    no.chave = 0;
    no.funcao_objetivo = 0;
    no.capacidade_mochila = capacidade_mochila;
    no.solucao = new float[qtd_itens];

    for(int i=0;i<qtd_itens;i++){
        arqEntrada >> valor_item[i];
        no.solucao[i] = 0;
    }
    for(int i=0;i<qtd_itens;i++){
        arqEntrada >> peso_item[i];
    }
    arqEntrada.close();

    cout << "# quantidade de itens: " << qtd_itens << "\n# capacidade da mochila: " << capacidade_mochila << endl;
    cout << "# valor dos itens: [ ";
    for(int i=0;i<qtd_itens;i++){
        cout << valor_item[i] << " ";
    }
    cout << "]\n# peso dos itens: [";
    for(int i=0;i<qtd_itens;i++){
        cout << peso_item[i] << " ";
    }
    cout << "]\n" << endl;

    CUSTO_BENEFICIO *item = new CUSTO_BENEFICIO[qtd_itens];
    for(int i=0;i<qtd_itens;i++){
        item[i].custo_beneficio = (float)valor_item[i]/peso_item[i];
        item[i].chave = i;
    }

    cout << "# Relacao custo/beneficio: ";
    for(int i=0;i<qtd_itens;i++){
        cout << "[" << item[i].chave << "]" << item[i].custo_beneficio << " ";
    }
    cout << "\n" << endl;


    guloso(item,qtd_itens);

    cout << "# Relacao custo/beneficio apos GULOSO: ";
    for(int i=0;i<qtd_itens;i++){
        cout << "[" << item[i].chave << "]" << item[i].custo_beneficio << " ";
    }
    cout << "\n" << endl;

    int marcar_indice = 0;
    relaxacao_linear(no,item,qtd_itens,capacidade_mochila,peso_item,valor_item,marcar_indice);
    arvore.push_front(no);
    cout << "\n[indice No] -> " << no.chave << "\n[Funcao objetivo] -> " << no.funcao_objetivo << "\n[capacidade mochila] -> " << no.capacidade_mochila << endl;

    marcar_indice = 1;
    relaxacao_linear(no,item,qtd_itens,capacidade_mochila,peso_item,valor_item,marcar_indice);
    arvore.push_front(no);
    cout << "\n[indice No] -> " << no.chave << "\n[Funcao objetivo] -> " << no.funcao_objetivo << "\n[capacidade mochila] -> " << no.capacidade_mochila << endl;


    marcar_indice = -1;
    relaxacao_linear(no,item,qtd_itens,capacidade_mochila,peso_item,valor_item,marcar_indice);
    arvore.push_front(no);
    cout << "\n[indice No] -> " << no.chave << "\n[Funcao objetivo] -> " << no.funcao_objetivo << "\n[capacidade mochila] -> " << no.capacidade_mochila << endl;


    cout << endl;
    delete[]valor_item;
    delete[]peso_item;
    delete[]item;
    delete[]no.solucao;
    system("pause");
    return 0;
}
