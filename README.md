# DicionarioAED2
Trabalho de Estrtura de dados 2 usando Hash e arvore para fazer um corretor ortográfico

######################################################################################################################################################
Nome: Thiago Luiz Alves Bubolz

Trabalho implementado em C++ onde sua principal função era implementar um corretor ortografico, que deveria ser possível inserir e remover palavras,
assim como buscar sugestões de palavras proximas aquelas que não estavam inseridas no dicionario.

Foi usada uma extrutura auxiliar de arvore binaria, junto com um hash, onde qualquer palavra inserida ou removida era inserida e removida nas duas estruturas, foi escolhida a arvore binaria pois ja era uma estrutura na qual estou familiarizado e que ja possuia parte de sua implementação feita do semestre passado na cadeira de AED1, a estrutura permitiu que as palavras sugeridas fossem listadas em ordem alfabetica, e a sua inserção tende a não ser tão custosa. A estrutura de lista também ja havia implementado na cadeira de AED1 portando foi de facil adaptação para o problema. Nota-se que a mesma não é circular, e insere sempre no inicio da lista, para se ter uma inserção na hash constante.

A função Hash foi pesquisada entre outras que seriam voltadas para armazenamento de strings e dentro de testes feitos foi a que se mostrou mais eficiente em tempo e espalhamento, tornando assim as listas que seguiam de cada indice do vetor da Hash não muito longas minimizando a busca na hash.

Foram usadas 3 structs no trabalho, uma para cada estrutura implementada, assim como foram criados metodos proprios ara cada struct dando uma ideia como se cada uma fosse uma classe.

Foi usado o Algoritmo edit distance para calcular a distancia entre das strings para imprimir as sugestões ao usuário.

######################################################################################################################################################

Aprendizados

* Primeira hash que implemento, gostei bastante do proposito do trabalho, foi desafiador, e me fez quebrar a cabeça com o uso de ponteiros e strucs novamente.

* Aprendi uma maneira de usar as structs com uma ideia de classes implementando metodos dentro delas, facilitou bastante principalmente na hierarquia de variaveis e estruturas dentro do problema.

* Com certeza aprimorei minhas habilidades com a linguagem C++, aprendi coisas novas, e lembrei de coisas que ja ahvia implementado anteriormente, também pude trabalhar com a ideia de usar estruturas com strings onde na cadeira de AED1 só se trabalhava com valores inteiros, e com strings se tem um trabalho a mais para manipular as ideias

######################################################################################################################################################
