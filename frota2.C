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
    int melhor;
    int qtdDisp, qtdViagem, qtdManut;
    float somaCarga, mediaCarga;



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
            printf("\nTotal de veiculos cadastrados: %d \n\n",totalVeiculos);
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
                    printf("Nova distancia em KM (Maior que 0, ou -1 se nao houver rota): ");
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

        if(totalVeiculos == 0){
            printf("Cadastre um veiculo antes de simular uma viagem.\n\n");
            break;
        }

        printf("ID do veiculo: ");
        scanf("%d",&idBusca);

        pos = -1;
        for(i = 0;i < totalVeiculos; i++){
            if (frota[i].id == idBusca){
                pos = i;
            }
        }
        
        if (pos == -1){
            printf("Veiculo nao encontrado.\n\n");
            break;
        }

        if(frota[pos].status != 0){
            printf("Esse veiculo nao esta disponivel.\n\n");
            break;
        }
        
        do{
            printf("Cidade de origem (0 a %d): ", NUM_CIDADES - 1);
            scanf("%d",&origem);

            if(origem < 0 || origem >= NUM_CIDADES){
                printf("Invalido,use um numero de 0 a %d.\n",NUM_CIDADES - 1);
            }
        } while(origem < 0 || origem >= NUM_CIDADES);

        do{
            printf("Cidade de destino (0 a %d): ",NUM_CIDADES - 1);
            scanf("%d",&destino);

            if(destino < 0 || destino >= NUM_CIDADES){
                printf("Invalido,use um numero de 0 a %d.\n",NUM_CIDADES - 1);
            }
        } while(destino < 0 || destino >= NUM_CIDADES);

        if (distancias[origem][destino] <= 0) {
            printf("Nao ha rota valida.\n\n");
            break;
        }

        viagem.idVeiculo = idBusca;
        viagem.cidadeOrigem = origem;
        viagem.cidadeDestino = destino;
        viagem.distanciaTotal = distancias[origem][destino];
        viagem.consumoEstimadoLitros = viagem.distanciaTotal / frota[pos].consumoKmL;
        viagem.custoEstimado = viagem.consumoEstimadoLitros * PRECO_COMBUSTIVEL;

        printf("\n----Resumo viagem----\n");
        printf("Rota: %s -> %s\n",NOME_CIDADES[origem], NOME_CIDADES[destino]);
        printf("Distancia: %.1f Km\n",viagem.distanciaTotal);
        printf("Consumo estimado: %.2f litros\n", viagem.consumoEstimadoLitros);
        printf("Custo estimado: R$ %.2f\n",viagem.custoEstimado);

        printf("Confirmar viagem? (1 = sim, 0 = nao): ");
        scanf("%d",&confirma);

        if(confirma == 1){
            frota[pos].status = 1;
            printf("\nViagem confirmada.O Veiculo agora esta em viagem. =)\n\n");
        } else {
            printf("Viagem cancelada. =(\n\n");
        }

        break;

        case 5:
        printf("\n==Relatorio de desempenho==\n\n");

        if(totalVeiculos == 0){
            printf("Nao ha nenhum veiculo cadastrado ate o momento");
            break;
        }

        melhor = 0;
        qtdDisp = 0;
        qtdManut = 0;
        qtdViagem = 0;
        somaCarga = 0;

        for(i = 0; i < totalVeiculos; i++){
            if(frota[i].consumoKmL > frota[melhor].consumoKmL){
                melhor = i;
            }

            if(frota[i].status == 0){
                qtdDisp++;
            } else if(frota[i].status == 1){
                qtdViagem++;
            } else {
                qtdManut++;
            }

            somaCarga = somaCarga + frota[i].capacidadeCarga;
            
        }

            mediaCarga = somaCarga / totalVeiculos;

            printf("Veiculo mais eficiente: %s - %s (%.1f km/l)\n",
                frota[melhor].placa,
                frota[melhor].modelo,
                frota[melhor].consumoKmL);

            printf("\n---Veiculos por Status---\n\n");
            printf("Disponiveis ----> %d (%.1f%%)\n",qtdDisp,qtdDisp * 100.0 / totalVeiculos);
            printf("Em viagem ------> %d (%.1f%%)\n",qtdViagem,qtdViagem * 100.0 / totalVeiculos);
            printf("Em manutencao --> %d (%.1f%%)\n",qtdManut,qtdManut * 100.0 / totalVeiculos);

            printf("\nMedia de capacidade de carga: %.1f T(toneladas).\n\n",mediaCarga);
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