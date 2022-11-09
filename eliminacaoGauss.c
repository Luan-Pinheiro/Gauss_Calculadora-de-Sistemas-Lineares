#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

double **cadastraSL(int,int);
void verSL(double**, int, int);
void instrucoes();
double **resolverSL(double**, int, int);
void retroSubstituicao(double**, int, int);
void sair(double**, int);

int main(){
    setlocale(LC_ALL,"Portuguese");
    setlocale(LC_ALL,"pt_BR.UTF-8");
    int selecao;
    printf("O que deseja fazer? \n______________________________\n");
    printf("1) Cadastrar Sistema Linear \n2) Ver Sistema Linear inserido\n");
    printf("3) Exibir instruoces de erros \n4) Ver o Sitema Linear Escalonado\n5)Resolver Sistema Linear atraves do metodo de Gauss\n0) Sair\n______________________________\n");
    scanf("%d", &selecao);
    while(selecao!=0){//ciclo
        switch (selecao){
            case 1:
                printf("Qual a dimensao do sistema linear? \n(Incluindo a coluna de solucoes! Se o sistema eh 5x5 entao devera ser inserido como 5x6, ja que ha a coluna de solucoes) :\nOBS:Dimensao minima [5x6]  ");
                int linhas, colunas;
                scanf("%d%d", &linhas, &colunas);//escaneia e armazena os valores nos enderecos de linhas e colunas
                if(linhas < 5 || colunas <6){//limite mínimo estipulado
                    printf("ERRO#001 - Valores nao aceitos!");
                    break;
                }
                if(linhas > 1000 || colunas >1001){//limite máximo estipulado
                    printf("ERRO#002 - Valores nao aceitos!");
                    break;
                }
                double **matrizOriginal = cadastraSL(linhas, colunas); 
            break;

            case 2:
                if (*matrizOriginal == NULL){
                printf("Matriz deve ser cadastrada primeiro!\n");
                break;
                }
                printf("\n------------------------------------------\n");
                verSL(matrizOriginal, linhas, colunas);//imprime a matriz
                printf("------------------------------------------\n\n");
            break;

            case 3:
                instrucoes();
            break;

            case 4:
                if (*matrizOriginal == NULL){
                printf("Matriz deve ser cadastrada primeiro!\n");
                break;
                }
                printf("\n****************\nMatriz original: \n------------------------------------------\n\n");
                verSL(matrizOriginal,linhas,colunas);//imprime a matriz
                printf("\nMatriz ao aplicar o metodo de Gauss: \n------------------------------------------\n\n");
                verSL(resolverSL(matrizOriginal,linhas,colunas),linhas,colunas);//imprime a matriz escalonada
                printf("\n");
            break;

            case 5:
                if (*matrizOriginal == NULL){
                printf("Matriz deve ser cadastrada primeiro!\n");
                break;
                }
                printf("\n****************\nResultados: \n------------------------------------------\n\n");
                retroSubstituicao(matrizOriginal,linhas,colunas);//imprime os resultados
                printf("\n");
                sair(matrizOriginal, colunas);
            break;

            default:
                printf("ERRO#03! \n");
            }
            
            

        printf("\nO que deseja fazer? \n______________________________\n");
        printf("1) Cadastrar Sistema Linear \n2) Ver Sistema Linear inserido\n");
        printf("3) Exibir instruoces de ajuda \n4) Ver o Sitema Linear Escalonado\n5)Resolver Sistema Linear atraves do metodo de Gauss\n0) Sair\n______________________________\n");
        scanf("%d", &selecao);
    }
    
    return 0;
}

double **cadastraSL(int linha, int coluna){

    double **ponteiroMatriz;
    ponteiroMatriz = (double**) malloc(linha * sizeof(double *));//alocando linhas

    for(int i = 0; i<linha; i++){
        ponteiroMatriz[i] = (double*) malloc(coluna * sizeof(double));//alocando colunas
        for(int j=0; j<coluna; j++){
            if((coluna == j+1)){
                printf("Insira o valor do resultado da linha %d do Sistema Linear: ",i+1);
                scanf("%lf", &ponteiroMatriz[i][j]);//escaneira os termos independentes
            }else{
                printf("Insira o valor do coeficiente na posicao [%d][%d]: ",i+1, j+1);
                scanf("%lf", &ponteiroMatriz[i][j]);//escaneia as respotas das equações
            }
        }      
    }  
    return ponteiroMatriz;//retorna a matriz
}

void verSL(double **matriz,int m,int n){
    for(int i = 0; i<m; i++){
        for(int j = 0; j < n; j++){
            printf("%0.2lf\t", matriz[i][j]);//imprime cada elemento da matriz
        }
        printf("\n");
    }
}

void instrucoes(){
    //impressão de possíveis erros
    printf("ERRO#001 -> Valores incorretos inseridos na acao!\n");
    printf("ERRO#002 -> Valores nao suportados!\n");
    printf("ERRO#003 -> Entrada nao esperada!\n");
}

double **resolverSL(double **matriz,int m,int n){
    double **matrizAuxiliar = matriz;

    //percorre colunas
    for(int j = 0; j < n - 2; j++){
        // (n-2) se dá devido reduzir um do vetor e um da coluna de soluções
        //percorre linhas
        for(int i = j; i < m; i++){
            if(matrizAuxiliar[i][j] != 0){
                if(i != j){
                    // trocando Linha(i) e Linha(j)
                    double aux;
                    for(int l = 0; l < n; l++){
                        aux =  matrizAuxiliar[i][l];
                        matrizAuxiliar[i][l] = matrizAuxiliar[j][l];
                        matrizAuxiliar[j][l] = aux;
                    }
                }
                //pivô não nulo, entao vamos executar as operacoes nas linhas;
                for(int k = j+1; k < m; k++){//percorre as linhas
                    // Lk <-_contante * Lj + Lk 
                    double cnst = -matrizAuxiliar[k][j]/matrizAuxiliar[j][j];//definindo constante
                    for( int x = j; x < n; x++){
                        matrizAuxiliar[k][x] += cnst * matrizAuxiliar[j][x]; //substituindo na linha o novo valor
                    }
                }
            break;

            }else{
                if(i == m-1){
                    printf("Este sistema nao possui so uma solucao! \n");
                    printf("FIM DA EXECUCAO! \n\n");
                    return 0;//encerra o programa
                }
            }
        }
    }
    return matrizAuxiliar;
}

void retroSubstituicao(double **matriz, int m, int n){
    double **matrizAxiliar = matriz;
    double *resI = (double*) malloc(m * sizeof(double)); //respostas das incognitas
    double **matrizAuxiliarDois = resolverSL(matrizAxiliar, m, n);//

    for(int i = 0; i < m; i++){
        int indice = m -1 -i; // detectar indice
        double b = matrizAuxiliarDois[indice][n-1]; //termo independente da linha indice
        //"levando" pro outro lado da igualdade com sinal trocado
        for(int j = indice+1; j < n -1; j++){
            b -= matrizAuxiliarDois[indice][j] * resI[j];//zerando os termos independentes para chegar na triangular superior
        }
        double xIndice = b / matrizAuxiliarDois[indice][indice]; //encontrando valor das variáveis x's, ao dividir pelo seu coeficiente;
        resI[indice] = xIndice;
        printf("x%d = %0.2lf\n",m-i, xIndice);
    }
    
}

void sair(double **matriz,int n){
    for(int i = 0; i<n; i++)
        free(matriz[i]);//liberando as colunas alocadas  
    free(matriz);//liberando as linhas alocadas
}