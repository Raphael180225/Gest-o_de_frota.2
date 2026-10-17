#include <stdio.h>

#define MAX_VEICULOS 10
#define NUM_CIDADES 5
#define PRECO_COMBUSTIVEL 5.80

struct Veiculo {
    int id;
    char placa[8];
    char modelo[30];
    float consumoKmL; //Consumo em quilometros por Litros
    float capacidadeCarga;
    int status;

};

struct Viagem {
    int idVeiculo;
    int cidadeOrigem;
    int cidadeDestino;
    float distanciaTotal;
    float consumoEstimadoLitros;
    float custoEstimado;
};

//uso basico do ponteiro
const char *NOME_CIDADES[NUM_CIDADES] = {
    "0: Central",
    "1: Norte",
    "2: Sul",
    "3: Leste",
    "4: Oeste",
};


int distancias[NUM_CIDADES][NUM_CIDADES] = {
    {  0,  45,  60,  30,  80 },
    { 45,   0,  -1,  25, 110 },
    { 60,  -1,   0,  70,  40 },
    { 30,  25,  70,   0,  -1 },
    { 80, 110,  40,  -1,   0 }
}; 

int main() {

    int opcao;
    struct Veiculo frota[MAX_VEICULOS];
    int totalVeiculos = 0;
    int i;
    int existe;
    int j;
    int sub, origem, destino, novaDist;
    int idBusca, pos, confirma;
    struct Viagem viagem;


    do 
    {
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
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
        printf("\n==Cadastrar veiculo==\n\n");

            if (totalVeiculos >= MAX_VEICULOS)
            {
                printf("Limite de %d cadastro de veiculos atingido.\n\n", MAX_VEICULOS);
                break;
            }

            do
            {

                printf("Id: ");
                scanf("%d", &frota[totalVeiculos].id);

                existe = 0;
                for (i = 0; i < totalVeiculos; i++)
                {
                    if (frota[i].id == frota[totalVeiculos].id)
                    {
                        existe = 1;
                    }
                }
                if (existe == 1)
                {
                    printf("Esse id ja existe! Digite novamente.\n");
                }
            } while (existe == 1);

            printf("Placa: ");
            scanf("%7s", frota[totalVeiculos].placa);

            printf("Modelo: ");
            scanf(" %29[^\n]", frota[totalVeiculos].modelo);

            do
            {

                printf("Consumo (Km/l): ");
                scanf("%f", &frota[totalVeiculos].consumoKmL);

                if (frota[totalVeiculos].consumoKmL <= 0)
                {
                    printf("Valor invalido,digite um numero maior que 0.\n");
                }
            } while (frota[totalVeiculos].consumoKmL <= 0);

            do
            {

                printf("Capacidade de carga (T): ");
                scanf("%f", &frota[totalVeiculos].capacidadeCarga);
                if (frota[totalVeiculos].capacidadeCarga <= 0)
                {
                    printf("Valor invalido,digite um numero maior que 0.\n");
                }
            } while (frota[totalVeiculos].capacidadeCarga <= 0);

            do
            {
                printf("Status (0 = Disponivel, 1 = em viagem, 2 = Em manutencao): ");
                scanf("%d", &frota[totalVeiculos].status);
                if (frota[totalVeiculos].status < 0 || frota[totalVeiculos].status > 2)
                {
                    printf("Digite apenas 0,1 ou 2.\n");
                }
            } while (frota[totalVeiculos].status < 0 || frota[totalVeiculos].status > 2);

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
       printf("\n==Lista de veiculos cadastrados==\n\n");

            if(totalVeiculos == 0){
                printf("Nenhum veiculo cadastrado.\n\n");
                break;
            }

            printf("%-6s %-9s %-12s %-8s %-10s %s\n", "Id","Placa","Modelo","Km/L","Carga(T)","Status");
    
            
            for(i = 0; i < totalVeiculos; i++){
                printf("%-6d %-9s %-12s %-8.1f %-10.1f",
                frota[i].id,
                frota[i].placa,
                frota[i].modelo,
                frota[i].consumoKmL,
                frota[i].capacidadeCarga);

                if(frota[i].status == 0){
                    printf("Disponivel.\n");
                } else if(frota[i].status == 1){
                    printf("Em viagem.\n");
                } else {
                    printf("Em manutencao\n");
                }
            }
            printf("\n");

        break;

        case 3:
        printf("\n==Consultar matriz de distancia==\n\n");

            printf("%-12s", "");
            for(j = 0; j < NUM_CIDADES; j++) {
                printf("%-12s",NOME_CIDADES[j]);
            }
            printf("\n");
             
            for(i = 0; i < NUM_CIDADES; i++){
                printf("%-12s", NOME_CIDADES[i]);
                for(j = 0; j < NUM_CIDADES; j++){
                    printf("%-12d",distancias[i][j]);
                }
                printf("\n");
            }
            printf("\n(0 = mesma cidade, -1 sem rota direta)\n");

            printf("\n 1 - Alterar uma distancia\n 0 - Voltar ao menu\n");
            printf("Qual desejas: ");
            scanf("%d", &sub);

            if (sub == 1){
                do {
                    printf("Cidade A (0 a %d): ",NUM_CIDADES - 1);
                    scanf("%d",&origem);

                    if (origem < 0 || origem >= NUM_CIDADES) {
                        printf("Numero invalido. Use numero de 0 a %d.\n",NUM_CIDADES - 1);
                    }
                } while (origem < 0 || origem >= NUM_CIDADES);

                do{
                    printf("Cidade B (0 a %d): ",NUM_CIDADES - 1);
                    scanf("%d",&destino);

                    if(destino < 0 || destino >= NUM_CIDADES || destino == origem){
                        printf("Numero invalido. Use 0 a %d e diferente da cidade A (ponto de partida).\n",NUM_CIDADES - 1);
                    }
                } while(destino < 0 || destino >= NUM_CIDADES || destino == origem);

                do{
                    printf("Nova distancia em KM (Maior que 0, ou -1 se nao houver rota).\n");
                    scanf("%d",&novaDist);

                    if(novaDist == 0 || novaDist < -1){
                        printf("Numero invalido. Digite um numero maior que 0 ou -1.\n");
                    }
                } while(novaDist == 0 || novaDist < -1);

                distancias[origem][destino] = novaDist;
                distancias[destino][origem] = novaDist;
                printf("\nDistancia atualizada nos dois sentidos!\n\n");
            }

        break;

        case 4:
        printf("\n==Simular viagem==\n");
        break;
        case 5:
        printf("\n==Relatorio de desempenho==\n\n");
        break;
        case 6:
        printf("\nAte logo!\n\n");
        break;
        default:
        printf("\nopcao invalida, digite um numero de 1 a 6\n");
        }
    } while (opcao != 6);

    
    return 0;

}