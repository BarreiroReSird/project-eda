#include <stdio.h>   // Funções de input/output padrão
#include <stdlib.h>  // Funções da biblioteca padrão
#include "archive.h" // Biblioteca personalizada
#include <string.h>  // Funções de manipulação de strings
#include <math.h>    // Funções matemáticas
#include <stdbool.h> // Tipo de dado booleano

int main()
{
    int clientId = 1;         // Variavel do ID de cliente
    float maxDistance = 10.0; // Variavel de distancia maxima

    printf("\nBem vindo!\n");

    CustomerV2 *head1 = NULL; // Lista ligada dos cliente inicia como NULL
    Mobility *head2 = NULL;   // Lista ligada dos meios de mobilidade inicia como NULL
    Admin *head3 = NULL;      // Lista ligada dos gestores inicia como NULL
    GraphNode *graph = NULL;  // Nó de grafo inicia como NULL

    printf("\nA carregar dados para o programa...\n"); // Carrega dados predefenidos para a lista ligada
    // Dados dos clientes
    CustomerV2 *customer1 = createCustomer(1, "John Doe", 'a', 123456789, 1000.0, "133 Main St", "ponte.azul.pedra");
    CustomerV2 *customer2 = createCustomer(2, "Jane Smith", 'b', 987654321, 500.0, "458 High St", "votam.grampo.teste");
    CustomerV2 *customer3 = createCustomer(3, "Bob Johnson", 'c', 111111111, 2000.0, "459 Park Ave", "caneta.estudar.teste");
    CustomerV2 *customer4 = createCustomer(4, "Mary Brown", 'd', 222222222, 1500.0, "478 Elm St", "votam.caneta.estudo");
    CustomerV2 *customer5 = createCustomer(5, "Tom Davis", 'e', 333333333, 3000.0, "719 Maple St", "votam.grampo.caneta");
    CustomerV2 *customer6 = createCustomer(6, "John Smith", 'a', 123476789, 1000.0, "123 Main St", "navegar.grampo.teste");
    CustomerV2 *customer7 = createCustomer(7, "Jane Johnson", 'b', 987684321, 500.0, "456 High St", "votam.grampo.pedra");
    CustomerV2 *customer8 = createCustomer(8, "Bob Brown", 'c', 111191111, 2000.0, "789 Park Ave", "carro.grampo.teste");
    CustomerV2 *customer9 = createCustomer(9, "Mary Davis", 'd', 222922222, 1500.0, "456 Elm St", "votam.rato.teste");
    CustomerV2 *customer10 = createCustomer(10, "Tom Doe", 'e', 333339933, 3000.0, "789 Maple St", "torre.grampo.teste");
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
    // Dados dos gestores
    Admin *admin1 = createAdmin(1, "Robert James", "admin1", 1);
    Admin *admin2 = createAdmin(2, "Jackson Diaz", "admin2", 0);
    Admin *admin3 = createAdmin(3, "Thiago Miles", "admin3", 0);
    Admin *admin4 = createAdmin(4, "Bill Clinton", "admin4", 1);
    Admin *admin5 = createAdmin(5, "Pedro Rodriguez", "admin5", 0);
    Admin *admin6 = createAdmin(6, "Albert Kenyon", "admin6", 0);
    Admin *admin7 = createAdmin(7, "Rick Peletier", "admin7", 1);
    Admin *admin8 = createAdmin(8, "Norman Grimes", "admin8", 0);
    Admin *admin9 = createAdmin(9, "Norman Ghee", "admin9", 0);
    Admin *admin10 = createAdmin(10, "Carol Dixon", "admin10", 1);
    insertAdmin(&head3, admin1);
    insertAdmin(&head3, admin2);
    insertAdmin(&head3, admin3);
    insertAdmin(&head3, admin4);
    insertAdmin(&head3, admin5);
    insertAdmin(&head3, admin6);
    insertAdmin(&head3, admin7);
    insertAdmin(&head3, admin8);
    insertAdmin(&head3, admin9);
    insertAdmin(&head3, admin10);
    // Dados dos meios de mobilidade
    insertDefaultMobility(&head2);
    printf("\nDados carregados!\n");

    checkData(head1); // Verifica se os clientes tem os dados necessarios (nome, password, NIF, saldo, e morada)
    while (1)
    {
        // Chama o menu
        int choice = menuFase();
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
            rentMobility(head1, head2);
            break;
        case 5: // Alterar meio de mobilidade eletrica
            updateMobility(head2);
            break;
        case 6: // Remover meio de mobilidade eletrica
            deleteMobility(&head2);
            break;
        case 7: // Localizar meio de mobilidade eletrica
            listMobility4geocode(head2);
            break;
        case 8: // Remover cliente
            removeCustomer(&head1);
            break;
        case 9: // Remover gestor
            removeAdmin(&head3);
            break;
        case 10: // Alterar cliente
            updateCustomer(head1);
            break;
        case 11: // Alterar gestor
            updateAdmin(&head3);
            break;
        case 12: // Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia
            listMobilityByAutonomy(head2);
            break;
        case 13: // Listagem da localizacao dos meios de mobilidade elétrica e dos clientes
            listData(head1, head2);
            break;
        case 14: // Lista os clientes
            listCustomer(head1);
            break;
        case 15: // Guardar dado num ficheiro txt
            saveDataToFile(head2, head1);
            break;
        case 16: // Guardar dado num ficheiro bin
            saveDataToFileBinary(head2, head1);
            break;
        case 17: // Localizar meios mais proximos de certo cliente
            listDataV2(head1, head2);
            break;
        case 18: // Lista todos os meios abaixo de 50% de bateria
            listMobilityBelow50(head2);
            break;
        default:
            break;
        }
    }

    return 0;
}