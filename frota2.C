#include <stdio.h>

int main() {

    int opcao;

    do {

    printf("================================================= \n");
    printf("           Sistema de Gestao de Frota           \n");
    printf("================================================= \n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Listar veiculos\n");
    printf("3 - Consultar matriz de distancia\n");
    printf("4 - Simular viagem\n");
    printf("5 - Relatorio de desempenho da frota\n");
    printf("6 - Sair\n");
    printf(" \n");
    printf("Escolha uma opcao: ");
    scanf("%d",&opcao);
   
     switch (opcao) {
        case 1:
        printf("\nCadastro do veiculo\n");
        break;
        case 2: 
        printf("\nListar veiculo\n");
        break;
        case 3:
        printf("\nConsultar matriz de distancia\n");
        break;
        case 4:
        printf("\nSimular viagem\n");
        break;
        case 5:
        printf("\nRelatorio de desempenho\n");
        break;
        case 6:
        printf("\nAte logo\n");
        break;
        default:
        printf("\nopcao invalida, digite um numero de 1 a 6\n");
        }
    } while (opcao != 6);

    
    return 0;

}