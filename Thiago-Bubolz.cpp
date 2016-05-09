#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


//Estrutura para um nodo da arvore, tem uma palavra, um ponteiro pro pai, e para os dois filhos 
struct nodoArvore{
    string palavra;
    nodoArvore *pai;
    nodoArvore *esquerda;
    nodoArvore *direita;
};

//Estrutura para a arvore, e os metodos publicos e privados
struct Arvore{
    int tamanho;
    nodoArvore *raiz;

    //Contrutor vazio, que seta tamanho para 0 e raiz nula
    Arvore(){
        this->tamanho = 0;
        this->raiz = NULL;
    }

    //Metodo publico que testa se a arvore ta vazia e então chama o metodo privado e cria a raiz
    //ou então ele chama o metodo privado para inserir um novo nodo
    bool insereArvore(string palavra){
        if (tamanho == 0){
            raiz = inserirArvore(raiz, palavra, NULL);
            if (raiz){
                tamanho++; 
                return true;
            } else{
                return false;
            }
        } else{
            if (inserirArvore(raiz, palavra, raiz->pai)){
                tamanho++;
                return true;
            }else{
                return false;
            }
        }
    }

    //Metodo publico que chama o metodo privado para remover o nodo d arvore
    bool removeNodoArvore(string palavra){
    	//Testa se a arvore esta vazia, se estiver não tem nodo a ser removido, e retorna falso;
    	if(tamanho == 0){
    		cout << "Arvore Vazia, não há nodo a ser removido" << endl;
    		return false;
    	}
    	//testa se removeu o nodo da arvore, se sim decrementa de tamanho e retorna verdadeiro, do contrario retorna falso
    	if(removerNodoArvore(palavra, raiz)){
    		tamanho--;
    		return true;
    	}else return false;
    }

    //Metodo publico que chama o metodo privado passando a raiz como parametro
    void imprimeAlfabeticaArvore(){
        imprimeAlfabetica(raiz);
    }
    
    //Metodo destruidor da arvore que chama o metodo privado, manda a raiz como parametro, 
    //depois seta a raiz como NULL
    ~Arvore(){
        destroiArvore(raiz);
        raiz = NULL;
    }
  
//Conjunto de metodos privados chamados pelos metodos publicos da arvore
private:

	//Metodo da arvore que insere um novo nodo
	//Recebe dois ponteiros de nodoArvore um deles sendo o pai para se guiar na inserção
	//Recebe a palavra a ser inserida
    nodoArvore* inserirArvore(nodoArvore *nodo, string palavra, nodoArvore *pai){
        //Testa se a arvore esta vazia, e retorna o primeiro Nodo
        if (nodo == NULL) {
            nodoArvore* novo = new nodoArvore(); 
            novo->palavra = palavra;
            novo->esquerda = novo->direita = NULL;
            novo->pai = pai;
            return novo;
        }
        //Testa se a palavra é maior ou menor para decidir qual lado da arvore vai inserir
        if (palavra < nodo->palavra) {
            nodo->esquerda = inserirArvore(nodo->esquerda, palavra, nodo);
        } else {
            if (palavra > nodo->palavra) {
                nodo->direita = inserirArvore(nodo->direita, palavra, nodo);
            }
        }
        return nodo;
    }


    //Metodo privado que remove um nodo na lista
    bool removerNodoArvore(string palavra, nodoArvore *raiz){
    	nodoArvore *aux = raiz;
    	nodoArvore *maisdireita, *aux2;

    	//Se a palavra é igual e o proximo aqui for NULL ele é o unico da lista, portanto só deleta ele
    	if(palavra == aux->palavra && aux->esquerda == NULL && aux->direita == NULL){
    		delete(aux);
    		return true;
    	}
    	//Testa se a palavra é menor entra na recursao a esquerda, senão entra na recursão a direita
    	while(aux != NULL){
    		cout << aux->palavra << endl;
    		if(palavra < aux->palavra){
    			aux = aux->esquerda;
    		}else if(palavra > aux->palavra){
    				aux = aux->direita;
			//Se a palavra não for maior nem menor ela é igual
			//então ajeita a arvore para o nodo ser removido
			//entra a partir do nodo ser removido a esquerda, e pega o nodo amis a direita
			//para trocar com o nodo a ser removido, e ajeita os ponteiros
    		}else{
    			if(palavra == aux->palavra && aux->esquerda == NULL && aux->direita == NULL){
    				delete(aux);
    				return true;
    			}else{
	    			cout << "Palavra igual : " << aux->palavra << endl;
					maisdireita = aux->esquerda;
					while(maisdireita->direita != NULL){
						maisdireita = maisdireita->direita;
					}
					cout << "Palavra mais a direita: " << maisdireita->palavra << endl;
					aux2 = maisdireita->pai;
					aux2->direita = NULL;
					maisdireita->esquerda = aux->esquerda;
					maisdireita->direita = aux->direita;
					maisdireita->pai = aux->pai;
					delete(aux);
					return true;
				}
    		}
    	}
		
    	return false;
    }

    //Recebe a raiz da arvore, e imprime em ordem alfabetica os nodos da arvore
    void imprimeAlfabetica(nodoArvore *raiz){
        if (raiz != NULL) {
            imprimeAlfabetica(raiz->esquerda);
            cout << raiz->palavra << endl; 
            imprimeAlfabetica(raiz->direita);
        }
    }

    //Destroi a arvore inteira da esquerda para a direita, deletando nodo a nodo
    void destroiArvore(nodoArvore* raiz){
        if(raiz != NULL){
            destroiArvore(raiz->esquerda); //entra na esquerda até o nodo mais a esquerda
            destroiArvore(raiz->direita); //depois entra no nodo mais a direita da sub arvore da esquerda, 
            delete(raiz); //quando encontrar o nodo mais abaixo na esquerda começa a deletar e voltar na recursão
        }
    }
};

//Implementação de uma lista para tratar a colisão na Hash
struct nodoLista{
	string palavra;
	nodoLista* prox;

	//Construtor sem parametros
	nodoLista(){
		this->palavra = "";
		this->prox = NULL;
	}

	//Construtor de um novo nodo, que recebe uma palavra como parametro,e insere a palavra no Nodo
	nodoLista(string palavra){
		this->palavra = palavra;
		this->prox = NULL;
	}

	//Metodo que insere um novo Nodo na lista, chama o construtor de Nodo lista
	//Insere sempre no inicio da lista pois é muito menos custoso dependendo do tamanho da lista
	//a raiz aponta para o nodo a ser inserido
	//O novo nodo aponta para o nodo que a cabeça apontava
	void insereNodoLista(string palavra){
		nodoLista* novo = new nodoLista(palavra);
		if(novo == NULL){
			cout << "Memoria insuficiente para alocar Nodo da Lista" << endl;
			exit(1);
		}
		novo->prox = this->prox;
		this->prox = novo;
	}

	//Metodo que remove um nodo da lista
	//Passa por parametro uma palavra para procurar
	//Mantem a lista, e nunca apaga a cabeça
	bool removeNodoLista(string palavra){
		nodoLista* novo = this->prox;
		nodoLista* ant = this;

		while(novo != NULL){
			if(novo->palavra == palavra){
				ant->prox = novo->prox;
				delete(novo);
				return true;
			}else{
				ant = novo;
				novo = novo->prox;
			}
		}
		cout << "Nodo não removido da lista" << endl;
		return false;
	}

	//Metodo que busca uma palavra dentro da lista
	//Passa a palavra e a cabeça da lista como parametro
	nodoLista* buscaNodoLista(string palavra){
		nodoLista* aux;
		aux = this->prox;
		while(aux != NULL){
			if(aux->palavra == palavra){
				return aux;
			}else{
				aux = aux->prox;
			}
		}
		cout << "Palavra não esta na lista" << endl;
		return NULL;
	}

	//Passa por todos os nodos e os imprime, usada para testar se codigo esta funcionando
	void imprimeLista(){
		nodoLista* aux = this->prox;
		while(aux != NULL){
			cout << aux->palavra << endl;
			aux = aux->prox;
		}
	}

};



int main(){
    Arvore arvore;

    string palavra;
    int escolha;

    cout << "Escolha 0 para sair 1 insere 2 printa 3 remove" << endl;
    cin >> escolha;
    do{
        if(escolha == 1){
            cout << "Palavra : ";
            cin >> palavra;
            cout << "passou";
            arvore.insereArvore(palavra);
        }else if(escolha == 2){
            arvore.imprimeAlfabeticaArvore();
        }else if(escolha == 3){
        		cout << "Palavra : ";
            	cin >> palavra;
        		arvore.removeNodoArvore(palavra);
       			}
        cout << "Escolha 0 para sair 1 insere 2 printa 3 remove" << endl; 
        cin >> escolha;
    }while(escolha != 0);
}
