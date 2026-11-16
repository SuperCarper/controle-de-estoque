#include <stdio.h>
#include <string.h>

int main() {
    int lista = 0;

    while (lista == 0) {

        FILE *ponteirinho;
        ponteirinho = fopen("inventory.txt", "a");
        
        if (ponteirinho == NULL) {
            printf("Erro ao abrir o arquivo.");
            return 1;
        }
        fclose(ponteirinho);

        char nomes[100][50];
        int quantidades[100];
        int i, total = 0;

        // Carregar os dados do arquivo
        ponteirinho = fopen("inventory.txt", "r");

        char linha[1000];

        while (total < 100 && fgets(linha, 1000, ponteirinho) != NULL) {

            if (sscanf(linha, "Nome: %49[^\n]", nomes[total]) == 1) {

                if (fgets(linha, 1000, ponteirinho) != NULL) {

                    if (sscanf(linha, "Quantidade: %d", &quantidades[total]) == 1) {
                        total++;
                    }
                }
            }
        }

        fclose(ponteirinho);

        printf("================================\nControle de Estoque\n================================\nSelecione uma opção:\n1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\nOpção: ");

        int option, quantidade;
        scanf("%d", &option);

        char digito[50];

        if (option == 1) {

            printf("Digite o nome do item: ");
            scanf(" %49[^\n]", digito);

            printf("\nDigite a quantidade: ");
            scanf("%d", &quantidade);

            if (quantidade <= 0) {
                printf("Quantidade inválida.\n");
            }
            else {
                int encontrado = 0;

                for (i = 0; i < total; i++) {
                    if (strcmp(nomes[i], digito) == 0) {
                        quantidades[i] += quantidade;
                        encontrado = 1;
                        break;
                    }
                }

                if (encontrado == 0 && total < 100) {
                    strcpy(nomes[total], digito);
                    quantidades[total] = quantidade;
                    total++;
                }

                else if (encontrado == 0) {
                    printf("Limite de itens atingido.\n");
                }

                if (encontrado == 1 || total <= 100) {
                    ponteirinho = fopen("inventory.txt", "w");

                    for (i = 0; i < total; i++) {
                        fprintf(ponteirinho, "Nome: %s\n", nomes[i]);
                        fprintf(ponteirinho, "Quantidade: %d\n\n", quantidades[i]);
                    }

                    fclose(ponteirinho);

                    if (encontrado == 1) {
                        printf("Quantidade atualizada com sucesso!\n");
                    }
                    else {
                        printf("Item adicionado com sucesso!\n");
                    }
                }
            }
        }

        else if (option == 2) {

            printf("Digite o nome do item: ");
            scanf(" %49[^\n]", digito);

            printf("\nDigite a quantidade a ser removida: ");
            scanf("%d", &quantidade);

            int encontrado = 0;

            for (i = 0; i < total; i++) {

                if (strcmp(nomes[i], digito) == 0) {

                    encontrado = 1;

                    if (quantidade <= 0) {
                        printf("Quantidade inválida.\n");
                    }

                    else if (quantidades[i] < quantidade) {
                        printf("Estoque insuficiente. Quantidade disponível: %d\n", quantidades[i]);
                    }

                    else {
                        quantidades[i] -= quantidade;

                        if (quantidades[i] == 0) {

                            for (int j = i; j < total - 1; j++) {
                                strcpy(nomes[j], nomes[j + 1]);
                                quantidades[j] = quantidades[j + 1];
                            }

                            total--;

                            printf("Item removido do estoque!\n");
                        }

                        else {
                            printf("Quantidade atualizada com sucesso!\n");
                        }

                        // Atualizar o arquivo
                        ponteirinho = fopen("inventory.txt", "w");

                        for (int j = 0; j < total; j++) {
                            fprintf(ponteirinho, "Nome: %s\n", nomes[j]);
                            fprintf(ponteirinho, "Quantidade: %d\n\n", quantidades[j]);
                        }

                        fclose(ponteirinho);
                    }

                    break;
                }
            }

            if (encontrado == 0) {
                printf("Item não encontrado.\n");
            }
        }

        else if (option == 3) {

            if (total == 0) {
                printf("O estoque está vazio.\n");
            }

            else {
                printf("=============================\nEstoque Atual\n=============================\n");

                for (i = 0; i < total; i++) {
                    printf("Nome: %s\n", nomes[i]);
                    printf("Quantidade: %d\n\n", quantidades[i]);
                }
            }
        }

        else if (option == 4) {
            printf("Obrigado por usar o Controle de Estoques! Até a próxima.");
            lista = 1;
            continue;
        }

        else {
            printf("Opção inválida.\n");
        }

        printf("\nDeseja realizar outra operação? (s/n): ");

        char loop;
        scanf(" %c", &loop);

        if (loop == 's' || loop == 'S') {
            lista = 0;
        }
        else {
            lista = 1;
            printf("Obrigado por usar o Controle de Estoques! Até a próxima.");
        }
    }

    return 0;
}