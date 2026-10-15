#include <stdio.h>

int main() {

    int opcao;

    printf("================================================= \n");
    printf("           Sistema de Gestao de Frota           \n");
    printf("================================================= \n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Listar veiculos;\n");
    printf("3 - Consultar matriz de distancia;\n");
    printf("4 - Simular viagem\n");
    printf("5 - Relatorio de desempenho da frota\n");
    printf("6 - Sair\n");
    printf(" \n");
    printf("Escolha uma opcao: ");
    scanf("%d",&opcao);
    printf("Voce escolheu a opcao %d\n",opcao);
    
    return 0;

}