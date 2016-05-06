#include <iostream>
#include <string>
using namespace std;



struct TreeNode {
              string palavra;   // chave da arvore
              TreeNode *left;   // ponteiro pro filho da esquerda
              TreeNode *right;  // ponteiro pro filho da direita
           };



//Função que acha o minimo entre 3 valores, isando a função min dentro de outra
int min3(int x, int y, int z) 
{
    return min(min(x, y), z);
}


//Algoritmo que verifica a diferença entre dias strings
int editDistance(string str1, string str2, int m, int n)
{
    // Cria uma matriz para preencher os valores do calculo
    int dp[m+1][n+1];
 
    // 2 for para completar a matriz com os valores
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        { 
            // Se o ultimo caractere for igual, ignora e chama a recursão para verificar o anterior
            if (str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }else{		//se os dois ultimos não forem iguais acha o minimo entre os valores da matriz
                dp[i][j] = 1 + min(dp[i][j-1],  // Insert
                                   dp[i-1][j],  // Remove
                                   dp[i-1][j-1]); // Replace
            }
        }
    }
 
    return dp[m][n];
}