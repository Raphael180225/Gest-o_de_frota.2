#include <stdio.h>

#define MAX_VEICULOS 10

struct Veiculo{
    int id;
    char placa[8];
    char modelo[30];
    float consumoKmL; //Consumo em quilometros por Litros
    float capacidadeCarga;
    int status;

};


int main() {

    int opcao;
    struct Veiculo frota[MAX_VEICULOS];
    int totalVeiculos = 0; //contador

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
       printf("\n==Cadastrar do veiculo==\n\n");

        printf("Id: ");
        scanf("%d",&frota[totalVeiculos].id);

        printf("Placa: ");
        scanf("%7s",frota[totalVeiculos].placa);
        
        printf("Modelo: ");
        scanf(" %29[^\n]",frota[totalVeiculos].modelo);

        printf("Consumo de Km/l: ");
        scanf("%f",&frota[totalVeiculos].consumoKmL);           
        
        printf("Capacidade de carga (T): ");
        scanf("%f",&frota[totalVeiculos].capacidadeCarga);

        printf("Status (0 = Disponivel, 1 = em viagem, 2 = Em manutencao): ");
        scanf("%d",&frota[totalVeiculos].status);

        printf("\nCadastro: %d | %s | %s | %.1f | %.1f T(toneladas) | status %d\n",
                frota[totalVeiculos].id,
                frota[totalVeiculos].placa,
                frota[totalVeiculos].modelo,
                frota[totalVeiculos].consumoKmL,
                frota[totalVeiculos].capacidadeCarga,
                frota[totalVeiculos].status);

            totalVeiculos++;
            printf("\nTotal de veiculos cadastrados:%d \n\n",totalVeiculos);
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