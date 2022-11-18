#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

double **cadastraSL(int,int);
void verSistemaLinear(double **,int ,int);
void verMatriz(double**, int, int);
void instrucoes();
double **resolverSL(double**, int, int);
void retroSubstituicao(double**, int, int);
void sair(double**, int);

int main(){

    setlocale(LC_ALL,"Portuguese");
    setlocale(LC_ALL,"pt_BR.UTF-8");

    int selecao;

    printf("\n|********************************************************|\n|\t\t\tMENU\t\t\t\t |");
    printf("\n|********************************************************|\n");
    printf("|1) Cadastrar Sistema Linear\t\t\t\t |");
    printf("\n|2) Ver Sistema Linear inserido\t\t\t\t |");
    printf("\n|3) Exibir instruoces de erros\t\t\t\t |");
    printf("\n|4) Ver o Matriz Escalonada\t\t\t\t |");
    printf("\n|5) Resolver Sistema Linear atraves do metodo de Gauss\t |");
    printf("\n|6) Resolver o Sistema Linear pelo metodo de Gauss-Jordan|");
    printf("\n|0) Sair\t\t\t\t\t\t |\n|________________________________________________________|\n");
    scanf("%d", &selecao);

    while(selecao!=0){//ciclo
        switch (selecao){
            case 1:
                printf("Qual a dimensao do sistema linear? \n(Sem incluir a coluna de solucoes!)\n");
                int linhas;
                int colunas;
                scanf("%d", &linhas);//escaneia e armazena os valores nos enderecos de linhas e colunas

                colunas = linhas + 1;

                if(linhas != colunas && linhas< 5){//limite mínimo estipulado
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
                printf("------------------------------------------\nSistema Linear:\n");
                verSistemaLinear(matrizOriginal, linhas, colunas);
                printf("------------------------------------------\n\n");
                printf("\n------------------------------------------\nMatriz:\n");
                verMatriz(matrizOriginal, linhas, colunas);//imprime a matriz
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
                verMatriz(matrizOriginal,linhas,colunas);//imprime a matriz
                printf("\nMatriz ao aplicar o metodo de Gauss: \n------------------------------------------\n\n");
                verMatriz(resolverSL(matrizOriginal,linhas,colunas),linhas,colunas);//imprime a matriz escalonada
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
            printf("\n|********************************************************|\n|\t\t\tMENU\t\t\t\t |");
            printf("\n|********************************************************|\n");
            printf("|1) Cadastrar Sistema Linear\t\t\t\t |");
            printf("\n|2) Ver Sistema Linear inserido\t\t\t\t |");
            printf("\n|3) Exibir instruoces de erros\t\t\t\t |");
            printf("\n|4) Ver o Matriz Escalonada\t\t\t\t |");
            printf("\n|5) Resolver Sistema Linear atraves do metodo de Gauss\t |");
            printf("\n|6) Resolver o Sistema Linear pelo metodo de Gauss-Jordan|");
            printf("\n|0) Sair\t\t\t\t\t\t |\n|________________________________________________________|\n");
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

void verSistemaLinear(double **matriz,int m,int n){
    for(int i = 0; i<m; i++){
        for(int j = 0; j < n; j++){;// imprime elementos do sistema linear e seus operadores
            if(j == 0){
                if(matriz[i][j] >= 0)
                    printf("%0.1lfx%d  ", matriz[i][j], j+1);
                else
                    printf("%0.1lfx%d  ", matriz[i][j], j+1);       
            }
            else{
                if(matriz[i][j] >= 0)
                    (j==n-1) ? printf("= %0.1lf", matriz[i][j]) : printf("+ %0.1lfx%d  ", matriz[i][j], j+1);
                else
                    (j==n-1) ? printf("= %0.1lf", matriz[i][j]) : printf("%0.1lfx%d  ", matriz[i][j], j+1);
            }
        }
        printf("\n");
    }
}
void verMatriz(double **matriz,int m,int n){
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