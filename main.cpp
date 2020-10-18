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
    if(no.capacidade_mochila < 0){
        no.capacidade_mochila = -1;
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

int verificarVariavelFracionaria(){

    return 0;
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

    

    //esboço de como ficará a descida.
    float melhorSolucaoInteira = 0; //melhor solução inteira - MSI do vídeo
    float melhorLimite = 0; //melhor limite - ML do vídeo
    float gap = 0;//formula do gap -> (melhorLimite - MSI)/MSI 
    bool stop = true;
    int cont = 0;
    No noTemp;
    No noAux;
    bool variaveisFixadas[qtd_itens]; // true fixada em 1, false fixada em 0
    marcar_indice = -1; //se o indice passar do for com valor = -1 não existe variável fracionária
    list<No>aux;

    while(stop){   
        cout << "cont: " << cont << endl;
        noTemp = arvore.front(); //variável no segura o primeiro item da pilha
        arvore.pop_front(); //remove o primeiro item da pilha
        for (int i = 0; i < qtd_itens; i++){//for verifica qual variável é fracionária e salva seu índice
            if((noTemp.solucao[i] > 0)&&(noTemp.solucao[i] < 1)){
                marcar_indice = i;
            }   
        }
        if(marcar_indice != -1){ //verifica se existe variável fracionária
            variaveisFixadas[marcar_indice] = true; //fixa a varivel em true, se for para o lado esquerdo na descida muda-se para false
            
            marcar_indice = 1; //fixando a variável para passar pra relaxação
            relaxacao_linear(no, item, qtd_itens, capacidade_mochila, peso_item, valor_item, marcar_indice);//usar o marcar_indice para fixar a variável na relaxação
            No filhoDireita = no; //a variável no quarda o local da memória na função (gambiarra)
            
            no.capacidade_mochila = 0;//zerando a variável no pra mandar os dados do outro filho(gambiarra)
            no.funcao_objetivo = 0;
            marcar_indice = 0; //fixando a variável para passar pra relaxação 
            relaxacao_linear(no, item, qtd_itens, capacidade_mochila, peso_item, valor_item, marcar_indice);//usar o marcar_indice para fixar a variável na relaxação
            No filhoEsquerda = no;//a variável no quarda o local da memória na função (gambiarra)
            
            if((filhoDireita.capacidade_mochila == -1)&&(filhoEsquerda.capacidade_mochila == -1)){

                cout << "soluções invalidas para os filhos, iteração" << cont << endl;
            }else if(filhoEsquerda.capacidade_mochila == -1){
                arvore.push_front(filhoDireita);
                cout << "filho da esquerda poda por inviabilidade" << endl;
            }else if(filhoDireita.capacidade_mochila == -1){
                arvore.push_front(filhoEsquerda);
                variaveisFixadas[marcar_indice] = false;
                cout << "filho da direita poda por inviabilidade" << endl;
            }else{
                if(filhoDireita.funcao_objetivo > filhoEsquerda.funcao_objetivo){ //verificação de qual é o melhor filho baseado no valor da função objetivo
                    arvore.push_front(filhoEsquerda); //desce pra direita
                    arvore.push_front(filhoDireita);
                }else{
                    arvore.push_front(filhoDireita); //desce pra esquerda
                    arvore.push_front(filhoEsquerda);
                    variaveisFixadas[marcar_indice] = false;
                }
            }         
            
        }else{ //guardar a melhor solução inteira.
            if(melhorSolucaoInteira < noTemp.funcao_objetivo){
                melhorSolucaoInteira = noTemp.funcao_objetivo;
            }
            int size = arvore.size();
            for(int i = 0; i < size; i++){ //este for tira todos os itens da pilha para verificar qual o melhor limite
                noAux = arvore.front(); //variável no segura o primeiro item da pilha
                arvore.pop_front(); //remove o primeiro item da pilha
                if(melhorLimite < noAux.funcao_objetivo){ 
                    melhorLimite = noAux.funcao_objetivo; //guardando o maior limite
                }
                aux.push_front(noAux);
            }
            for(int i = 0; i < size; i++){//este for volta todos os itens para a pilha
                noAux = aux.front();
                arvore.push_front(noAux);
                aux.pop_front();//voltando os nós pra pilha original
            }

            gap = ((melhorLimite - melhorSolucaoInteira)/melhorSolucaoInteira); //cálculo do gap 

            cout << "ML: " << melhorLimite << endl;
            cout << "MSI: " << melhorSolucaoInteira << endl;
            cout << "GAP: " << gap << endl;
        }


        if(cont == 10){stop = false;};
        cont++;
        marcar_indice = -1;
        if(arvore.size() == 0){stop = false;};
    }
    

    cout << endl;
    delete[]valor_item;
    delete[]peso_item;
    delete[]item;
    delete[]no.solucao;
    system("pause");
    return 0;
}