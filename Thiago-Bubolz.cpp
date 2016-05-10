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
    nodoArvore *filhoesquerda;
    nodoArvore *filhodireita;
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
        }else{
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
    	}//testa se removeu o nodo da arvore, se sim decrementa de tamanho e retorna verdadeiro, do contrario retorna falso
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

    void buscaSugestoes(string palavra){
		buscarSugestoes(palavra, raiz);
	}

	int calculaDistancia(string palavra1, string palavra2){
		int tamanho1 = palavra1.length();
		int tamanho2 = palavra2.length();
	    int matriz[tamanho1+1][tamanho2+1];

	    for (int i=0; i<=tamanho1; i++){
	        for (int j=0; j<=tamanho2; j++){
	            if (i==0) {
	            	matriz[i][j] = j; 
	            	}else if (j==0){
	            			matriz[i][j] = i;
	            	}else if (palavra1[i-1] == palavra2[j-1]){
	            				matriz[i][j] = matriz[i-1][j-1];
	            		}else{
			                matriz[i][j] = 1 + min(min(matriz[i][j-1],
			                                   matriz[i-1][j]),
			                                   matriz[i-1][j-1]);
	        			}
	     }
	    }
	    return matriz[tamanho1][tamanho2];
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
            novo->filhoesquerda = novo->filhodireita = NULL;
            novo->pai = pai;
            return novo;
        }
        //Testa se a palavra é maior ou menor para decidir qual lado da arvore vai inserir
        if (palavra < nodo->palavra) {
            nodo->filhoesquerda = inserirArvore(nodo->filhoesquerda, palavra, nodo);
        } else {
            if (palavra > nodo->palavra) {
                nodo->filhodireita = inserirArvore(nodo->filhodireita, palavra, nodo);
            }
        }
        return nodo;
    }

    nodoArvore* buscarSugestoes(string palavra, nodoArvore* raiz){
		/*if(raiz->filhodireita ==NULL && raiz->filhoesquerda == NULL){
			return raiz;
		}else if(raiz->filhodireita == NULL){
				buscarSugestoes(palavra, raiz->filhoesquerda);
			} else if(raiz->filhoesquerda == NULL){
					 buscarSugestoes(palavra, raiz->filhodireita);
					}else if(calculaDistancia(palavra, raiz->filhoesquerda->palavra) < calculaDistancia(palavra, raiz->filhodireita->palavra)){
							buscarSugestoes(palavra, raiz->filhoesquerda);
						}else if(calculaDistancia(palavra, raiz->filhodireita->palavra) < calculaDistancia(palavra, raiz->filhoesquerda->palavra)){
								buscarSugestoes(palavra, raiz->filhodireita);
						}
		int distancia = calculaDistancia(palavra, raiz->palavra);
		cout << distancia << endl;
		if(distancia <= 2){
			cout << raiz->palavra << endl;
		}*/
		int distancia;
		if (raiz != NULL) {
            buscarSugestoes(palavra, raiz->filhoesquerda);
            distancia = calculaDistancia(palavra, raiz->palavra);
            if(distancia <= 2){
				cout << raiz->palavra << endl;
			}
            buscarSugestoes(palavra, raiz->filhodireita);
        }
	}

    nodoArvore* maiorDireita(nodoArvore *raiz){
    	nodoArvore* aux = raiz;
    	if(raiz->filhodireita != NULL){
    		return maiorDireita(raiz->filhodireita);
    	}else{
    		if(raiz->filhoesquerda != NULL){
    			raiz = raiz->filhoesquerda;
    		}else {
    			raiz = NULL;
    		}
    		return aux;
    	}
    }

    //Metodo privado que remove um nodo na lista
    nodoArvore* removerNodoArvore(string palavra, nodoArvore *raiz){
    	nodoArvore* aux = raiz;
    	nodoArvore* auxe;
    	nodoArvore* auxd;
    	//teste caso a busca tenha terminado e o nodo não foi encontrado
    	if(raiz == NULL){
    		cout << "Numero não existe na arvore" << endl;
    		return raiz;
    	}
		if(palavra < aux->palavra){
			raiz->filhoesquerda = removerNodoArvore(palavra, raiz->filhoesquerda);
		}else if(palavra > aux->palavra){
				raiz->filhodireita = removerNodoArvore(palavra, raiz->filhodireita);
		//Se a palavra não for maior nem menor ela é igual
		//então ajeita a arvore para o nodo ser removido
		//entra a partir do nodo ser removido a filhoesquerda, e pega o nodo amis a filhodireita
		//para trocar com o nodo a ser removido, e ajeita os ponteiros
		}else{
			//O nodo é uma folha
			if(aux->filhoesquerda == NULL && aux->filhodireita == NULL){
				delete(aux);
				raiz = NULL;
				return raiz;
			}else{
					if(raiz->filhoesquerda == NULL){//Nodo só tem filho da direita
		    			raiz = raiz->filhodireita;
		    			aux->filhodireita = NULL;
		    			delete(aux);
		    			aux = NULL;
		    			return raiz;
					}else if(raiz->filhodireita == NULL){//Nodo só tem o filho da esquerda
							raiz = raiz->filhoesquerda;
							aux->filhoesquerda = NULL;
							delete(aux);
							aux = NULL;
							return raiz;
					}else{
						aux = maiorDireita(raiz->filhoesquerda);
						aux->filhoesquerda = raiz->filhoesquerda;
						aux->filhodireita = raiz->filhodireita;
						aux->pai = raiz->pai;
						aux->filhoesquerda->pai = aux->filhodireita->pai = aux;
						aux->filhoesquerda->filhodireita = NULL;
						raiz->filhodireita = raiz->filhoesquerda = NULL;
						delete(raiz); 
						raiz = aux; 
						//aux = NULL;
						return raiz;
					}
				}
		}
		return raiz;
    }

    //Recebe a raiz da arvore, e imprime em ordem alfabetica os nodos da arvore
    void imprimeAlfabetica(nodoArvore *raiz){
        if (raiz != NULL) {
            imprimeAlfabetica(raiz->filhoesquerda);
            cout << raiz->palavra << endl; 
            imprimeAlfabetica(raiz->filhodireita);
        }
    }

    //Destroi a arvore inteira da filhoesquerda para a filhodireita, deletando nodo a nodo
    void destroiArvore(nodoArvore* raiz){
        if(raiz != NULL){
            destroiArvore(raiz->filhoesquerda); //entra na filhoesquerda até o nodo mais a filhoesquerda
            destroiArvore(raiz->filhodireita); //depois entra no nodo mais a filhodireita da sub arvore da filhoesquerda, 
            delete(raiz); //quando encontrar o nodo mais abaixo na filhoesquerda começa a deletar e voltar na recursão
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
		return false;
	}

	//Metodo que busca uma palavra dentro da lista
	//Passa a palavra como parametro
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

//Estrutura do Corretor ortografico, com os numeros de fator de carga atual, e fator de carga maximo
//tamanh da hash, e o seu numro de entradas total
//uma arvore binaria para auxiliar na busca por palavras proximas
//e um lista para cada posição do vetor da hash
struct corretorOrtografico{
	float FC, FCM;
	unsigned int tamanhoHash, numentradas;
	Arvore *arvorebin;
	nodoLista **lista;

	//Construtor que seta todos os atributos, e ja adiciona uma lista para cada posição do vetor da hash
	corretorOrtografico(int tamanhoHash, float FCM){
		this->tamanhoHash = tamanhoHash;
		this->FCM = FCM;
		this->FC = 0;
		this->numentradas = 0;
		this->arvorebin = new Arvore();
		this->lista = (nodoLista**) malloc(tamanhoHash * sizeof(nodoLista*));
		for(int i=0; i<tamanhoHash; i++){
			lista[i] = new nodoLista();
		}
	}
	
	//Metodo que insere umaa palavra no Dicionario, 
	//Recebe uma palavra como aparametro, calcula sua posição na Hash, e depois insere a palavra caso a mesma
	//ainda não exista na hash, insere tanto na Hash(lista), como na arvore que é uma estrutura auxiliar para 
	//a busca de sugestões.
	string inserePalavra(string palavra){
		unsigned int posicao = hashcode(palavra)%tamanhoHash;
		nodoLista* aux = lista[posicao];
		if(aux->palavra == palavra){ 
            return "fail";
        }else if(aux->palavra == ""){
			aux->palavra = palavra;
			arvorebin->insereArvore(palavra);
			numentradas++;
			if(calculaFatordeCarga() > FCM){
				//reHash();
			}
			return "ok";
		}
		//Faz uma busca na lista pela palavra, se não encontra adiciona na lista
        if(aux->buscaNodoLista(palavra) == NULL){ 
            aux->insereNodoLista(palavra);
            arvorebin->insereArvore(palavra);
            numentradas++;
            calculaFatordeCarga();
            if(FC > FCM){
                //reHash();
            }
            return "ok";
        }else return "fail"; //Se a busca não for NULL é porque ja existe a palavra e retorna fail ao inserir
	}

	void reHash(){
		unsigned int posicao;
	    nodoLista *atual,*anterior;
	   
	    int novoTamanho = tamanhoHash*2;
	    nodoLista **novaLista = (nodoLista**) malloc(novoTamanho*sizeof(nodoLista*));
	    
	    for(int i = 0; i < novoTamanho; i++){
	        novaLista[i] = new nodoLista();
	    }
	    
	    for(int i = 0; i < tamanhoHash; i++){
	        atual = lista[i];
	        while(atual != NULL){
	            if(atual->palavra != ""){// para nao tentar inserir palavras vazias
	                posicao = hashcode(atual->palavra) % novoTamanho;
	                if(novaLista[posicao]->palavra == ""){
	                    novaLista[posicao]->palavra = atual->palavra;
	                }
	                else{
	                    novaLista[posicao]->insereNodoLista(atual->palavra);
	                }
	                anterior = atual;
	                atual = atual->prox;
	                delete(anterior);
	            }
	            else{//caso em que o nodo é o primeiro da lista e não houve inserção nele, ele ainda contém ""
	                 atual = atual->prox;
	            }
	        }
	    }
	    delete(lista);
	    lista = novaLista;
	    tamanhoHash = novoTamanho; 
	    calculaFatordeCarga();
	}

	string removePalavra(string palavra){
	    if(palavra != ""){
	        unsigned int posicao = hashcode(palavra)%tamanhoHash;
	        nodoLista* aux = lista[posicao];
	        
	        if(aux->palavra == palavra){
	            aux->palavra = "";
	            arvorebin->removeNodoArvore(palavra);
	            numentradas--;
	            calculaFatordeCarga();
	            return "ok";
	        }
	        if(aux->removeNodoLista(palavra)){
	        	arvorebin->removeNodoArvore(palavra);
	            numentradas--;
	            calculaFatordeCarga();
	            return "ok";
	        }else return "fail";
	    }else return "fail";
	}

	string buscaPalavra(string palavra){
	    unsigned int posicao = hashcode(palavra)%tamanhoHash;
	    nodoLista* aux = lista[posicao];
	    
	    if(aux->palavra == palavra)
	        return "ok";
	    else if(aux->buscaNodoLista(palavra) == NULL){
	            return "fail";
	        }else return "ok";
	}

	//Função hash que calcula a posição da palavra na hash,
	//foi o calculo amis rapido e de melhor espalhamento achado
	unsigned int hashcode(string palavra){
	    string aux = palavra;
	    unsigned int h = 181421; //Numero primo grande
	    int i;
	    for (i = 0; i < aux.length(); i++){
	        h ^= (h << 5) + (h >> 2) + aux[i];
	    }
	    return h;
	}

	float calculaFatordeCarga(){
		float FC = (float) (numentradas/tamanhoHash);
		return FC;
	}

	void printHash(){
		nodoLista* nodo;
		for(int i=0; i < tamanhoHash; i++){
			nodo = lista[i];
			cout << "Indice:" << i << endl;
			while(nodo!=NULL){
				cout << nodo->palavra << endl;
				nodo = nodo->prox;
			}
		}
	}

};


int main(){
	corretorOrtografico dicionario(50,5);
    string entrada, palavra;

    cin >> entrada;
    transform(entrada.begin(),entrada.end(),entrada.begin(),::tolower); //Para deixar todas as letras minúsculas
    palavra = "";
    
    while(entrada != "*"){
        if(entrada == "+"){
                cout << dicionario.inserePalavra(palavra) << endl;
        }
        else{             
            if(entrada == "-"){
                    cout << dicionario.removePalavra(palavra) << endl;
            }
            else{
                palavra = entrada;
                if(dicionario.buscaPalavra(palavra) == "ok"){
                    cout << "ok" << endl;
                }
                else{
                	cout << "not found" <<endl;
                    dicionario.arvorebin->buscaSugestoes(palavra);
                }
            }
        }
        cin >> entrada;
        transform(entrada.begin(),entrada.end(),entrada.begin(),::tolower);
    }
    dicionario.printHash();


    /*corretorOrtografico dicionario = new corretorOrtografico()

    string palavra;
    int escolha;

    cout << "Escolha 0 para sair 1 insere 2 printa 3 remove" << endl;
    cin >> escolha;
    do{
        if(escolha == 1){
            cout << "Palavra : ";
            cin >> palavra;
            arvore.insereArvore(palavra);
        }else if(escolha == 2){
            arvore.imprimeAlfabeticaArvore();
        }else if(escolha == 3){
                cout << "Palavra : ";
                cin >> palavra;
                arvore.removeNodoArvore(palavra);
                }else if(escolha == 5){
                    cout << "Palavra:";
                    cin >> palavra;
                    arvore.buscaSugestoes(palavra);
                }
        cout << "Escolha 0 para sair 1 insere 2 printa 3 remove" << endl; 
        cin >> escolha;
    }while(escolha != 0);*/
}
