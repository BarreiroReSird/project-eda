#include <stdio.h>
#include <stdlib.h>
#include "archive.h"
#include <string.h>
#include <math.h>

int main()
{
    printf("\nBem vindo!\n");
    // menuArea();
    // Codigo temporario para a fase 1:
    CustomerV2 *head1 = NULL;
    Mobility *head2 = NULL;
    printf("\nA carregar dados para o programa...\n"); // Carrega dados predefenidos para a lista ligada
    CustomerV2 *customer1 = createCustomer(1, "John Doe", 'a', 123456789, 1000.0, "123 Main St");
    CustomerV2 *customer2 = createCustomer(2, "Jane Smith", 'b', 987654321, 500.0, "456 High St");
    CustomerV2 *customer3 = createCustomer(3, "Bob Johnson", 'c', 111111111, 2000.0, "789 Park Ave");
    CustomerV2 *customer4 = createCustomer(4, "Mary Brown", 'd', 222222222, 1500.0, "456 Elm St");
    CustomerV2 *customer5 = createCustomer(5, "Tom Davis", 'e', 333333333, 3000.0, "789 Maple St");
    CustomerV2 *customer6 = createCustomer(1, "John Smith", 'a', 123456789, 1000.0, "123 Main St");
    CustomerV2 *customer7 = createCustomer(2, "Jane Johnson", 'b', 987654321, 500.0, "456 High St");
    CustomerV2 *customer8 = createCustomer(3, "Bob Brown", 'c', 111111111, 2000.0, "789 Park Ave");
    CustomerV2 *customer9 = createCustomer(4, "Mary Davis", 'd', 222222222, 1500.0, "456 Elm St");
    CustomerV2 *customer10 = createCustomer(5, "Tom Doe", 'e', 333333333, 3000.0, "789 Maple St");
    insertCustomer(&head1, customer1);
    insertCustomer(&head1, customer2);
    insertCustomer(&head1, customer3);
    insertCustomer(&head1, customer4);
    insertCustomer(&head1, customer5);
    insertCustomer(&head1, customer6);
    insertCustomer(&head1, customer7);
    insertCustomer(&head1, customer8);
    insertCustomer(&head1, customer9);
    insertCustomer(&head1, customer10);
    printf("\nDados carregados!\n");
    // Verifica se os clientes tem os dados necessarios (nome, password, NIF, saldo, e morada)
    checkData(head1);
    while (1)
    {
        // Chama o menu
        int choice = menuFase1();
        switch (choice)
        {
        case 0: // Sair do programa
            exit(0);
        case 1: // Inserir todas as informacoes sobre um meio de mobilidade eletrica
            insertMobility(&head2);
            Mobility *newMobility = (Mobility *)malloc(sizeof(Mobility));
            if (newMobility == NULL)
            {
                printf("Erro ao alocar memória!\n");
            }
            else
            {
                printf("Meio de mobilidade inserido com sucesso!\n");
            }
            continue;
        case 2: // Listar todas as informacoes sobre um meio de mobilidade eletrica
            listMobility(head2);
            break;
        case 3: // Carregar saldo de um cliente escolhido
            addBalance(head1);
            break;
        case 4: // Alugar meio de mobilidade eletrica

            break;
        default:
            break;
        }
    }
    // Codigo temporario para a fase 1:

    return 0;
}