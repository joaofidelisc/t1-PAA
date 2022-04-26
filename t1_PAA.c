/*Nome: João Vitor Fidelis Cardozo - RA: 769719
Segundo Trabalho Prático (Primeira Versão) - PAA*/

#include <stdio.h>
#include <stdlib.h>

/*Intercala os valores do vetor em ordem decrescente*/
void intercala1(int v[], int p, int q, int r){
    int i, j, k, tam;
    i=p; j=q; k=0; tam =r-p;
    int *w = (int*) malloc(tam * sizeof(int));
    while(i<q && j<r){
        if (v[i] >= v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while(i<q) w[k++] = v[i++];
    while(j<r) w[k++] = v[j++];
    for(k=0; k<tam; k++) v[p+k] = w[k];
    free(w);
}

/*Merge sort*/
void mergeSortR(int v[], int p, int r){
    int m;
    if (r-p>1){
        m = (p+r)/2;
        mergeSortR(v, p, m);
        mergeSortR(v, m, r);
        intercala1(v, p, m, r);
    }
}

/*A função abaixo, recebe como parâmetros um vetor e o seu respectivo tamanho. Feito isso, considerando que o vetor está ordenado em ordem decrescente, 
ela pega o resto da divisão do tamanho do vetor por 3, e esse resto significa exatamente os valores que vão ser descartados, pois a cada 2 produtos, o 3 comprado
é de graca e é justamente onde está o maior desconto (vetor em ordem decrescente), entao, nao interessa se o cliente comprou 4 ou 5 produtos, pois o maior desconto, 
sempre estará a cada 3 posições, por isso soma-se 3 no contador a cada iteração do while.*/
long long int exibeMaiorDesconto(int v[], int tamanho_vetor){
    int contador = 2;
    long long int total = 0;
    int valores_descartados = tamanho_vetor%3;
    while(tamanho_vetor-valores_descartados>contador){
        total = v[contador]+total;
        contador+=3; //Pega os valores a cada 3 posições, pois o vetor está ordenado em ordem decrescente
    }
    return total;
}

int main(){
    FILE *arquivo;
    int n_itens = 0, i=0;
    int *vetor_valores = NULL;
    char nome_arquivo[15];
    long long int total_desconto = 0;

    scanf("%s", nome_arquivo); //Lê nome do arquivo
    arquivo = fopen(nome_arquivo, "r");
    
    fscanf(arquivo, "%d", &n_itens); //Lê tamanho do vetor (número de itens)
    if (n_itens>=3){
        vetor_valores = (int*) malloc(n_itens*sizeof(int)); //Reserva na memória um vetor de tamanho n_itens

        for (i=0; i<n_itens; i++){
            fscanf(arquivo, "%d", &vetor_valores[i]); //Lê cada elemento do vetor
        }
        mergeSortR(vetor_valores, 0, n_itens); //Ordena em ordem decrescente

        total_desconto = exibeMaiorDesconto(vetor_valores, n_itens);
        printf("%lld\n", total_desconto);
        free(vetor_valores); //Libera memória alocada
    }
    else{
        printf("0\n");
    }

    fclose(arquivo); //Fecha arquivo
    return 0;
}