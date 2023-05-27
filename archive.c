#include <stdio.h>   // Funções de input/output padrão
#include <stdlib.h>  // Funções da biblioteca padrão
#include "archive.h" // Biblioteca personalizada
#include <string.h>  // Funções de manipulação de strings
#include <math.h>    // Funções matemáticas
#include <stdbool.h> // Tipo de dado booleano

// Cria cliente e retorna para ser inserido
CustomerV2 *createCustomer(int id, char *name, char password, int NIF, float balance, char *address, char *geocode)
{
    CustomerV2 *newCustomer = (CustomerV2 *)malloc(sizeof(CustomerV2));
    newCustomer->id = id;
    strcpy(newCustomer->name, name);
    newCustomer->password = password;
    newCustomer->NIF = NIF;
    newCustomer->balance = balance;
    strcpy(newCustomer->address, address);
    strcpy(newCustomer->geocode, geocode);
    newCustomer->next = NULL;
    return newCustomer;
}

// Acede ao cliente guardado temporariamente e insere na lista ligada
void insertCustomer(CustomerV2 **head1, CustomerV2 *newCustomer)
{
    if (*head1 == NULL)
    {
        *head1 = newCustomer;
    }
    else
    {
        CustomerV2 *current = *head1;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

// Verifica se o cliente tem os dados minimos
int checkData(CustomerV2 *head1)
{
    printf("\nA verificar integridade dos dados...\n");
    CustomerV2 *current = head1;

    while (current != NULL)
    {
        if (current->name == NULL)
        {
            printf("Nome do cliente invalido %d\n", current->id);
            return 0;
        }

        if (current->password == '\0')
        {
            printf("Password do cliente invalida %d\n", current->id);
            return 0;
        }

        if (current->NIF < 100000000 || current->NIF > 999999999)
        {
            printf("NIF invalido para o cliente com ID %d\n", current->id);
            return 0;
        }

        if (isnan(current->balance))
        {
            printf("Saldo do cliente invalido %d\n", current->id);
            return 0;
        }

        if (current->address == NULL)
        {
            printf("Morada do cliente invalida %d\n", current->id);
            return 0;
        }

        current = current->next;
    }

    printf("\nTodos os dados necessarios foram inseridos corretamente!\n");
    return 1;
}

// Abre o menu
int menuFase()
{
    int choice;
    printf("\n--> MENU <--\n");
    printf("1 para inserir dados sobre os meios de mobilidade eletrica\n");
    printf("2 para listar todos os dados sobre os meios de mobilidade eletrica\n");
    printf("3 para carregar saldo de um cliente escolhido\n");
    printf("4 para alugar meio de mobilidade eletrica (Recomendado listar primeiro todos os meios para saber o id do meio pretendido)\n");
    printf("5 para alterar meio de mobilidade eletrica\n");
    printf("6 para remover meio de mobilidade eletrica\n");
    printf("7 para localizar meio de mobilidade eletrica\n");
    printf("8 para remover cliente por id\n");
    printf("9 para remover gestor por id\n");
    printf("10 para alterar dados do cliente por id\n");
    printf("11 para alterar dados do gestor por id\n");
    printf("12 para listar os meios de mobilidade eletrica por ordem decrescente de autonomia\n");
    printf("13 para listar a localizacao dos clientes e dos meios de mobilidade eletrica (atraves de grafos)\n");
    printf("14 para listar os clientes\n");
    printf("15 para guardar os dados num ficheiro .txt\n");
    printf("16 para guardar os dados num ficheiro .bin\n");
    printf("17 para localizar os meios mais proximos do cliente desejado\n");
    printf("18 para determinar a rota mais rapida para recolher os meios abaixo de 50 de bateria e quantas vezes o tem de fazer\n");
    printf("0 para encerrar o programa\n");
    printf("\nA sua escolha:");
    scanf("%d", &choice);
    return (choice);
}

// Insere meio na lista ligada
void insertMobility(Mobility **head2)
{
    Mobility *newMobility = (Mobility *)malloc(sizeof(Mobility));

    // Encontra o último ID existente
    Mobility *temp = *head2;
    int lastID = 0;
    while (temp != NULL)
    {
        if (temp->id > lastID)
        {
            lastID = temp->id;
        }
        temp = temp->next;
    }

    // Adiciona 1 ao último ID existente para gerar o novo ID
    newMobility->id = lastID + 1;

    printf("Insira o tipo do meio de mobilidade: ");
    scanf(" %s", &newMobility->type);

    printf("Insira a carga da bateria (em %%): ");
    scanf("%f", &newMobility->battery);

    printf("Insira a autonomia (em km): ");
    scanf("%f", &newMobility->autonomy);

    printf("Insira o custo (por hora): ");
    scanf("%f", &newMobility->price);

    printf("Insira o geocodigo do meio de mobilidade: ");
    scanf(" %s", &newMobility->geocode);

    newMobility->next = *head2;
    *head2 = newMobility;
}

// Lista a lista ligada
void listMobility(Mobility *head2)
{
    Mobility *current = head2;
    GraphNode *graph = NULL;
    GraphNode *current_node = NULL;

    while (current != NULL)
    {
        GraphNode *new_node = (GraphNode *)malloc(sizeof(GraphNode));
        new_node->id = current->id;
        strcpy(new_node->type, current->type);
        strcpy(new_node->geocode, current->geocode);
        new_node->next = NULL;

        if (graph == NULL)
        {
            graph = new_node;
            current_node = new_node;
        }
        else
        {
            current_node->next = new_node;
            current_node = new_node;
        }

        current = current->next;
    }

    // Imprime os dados do grafo
    printf("--> Lista de meios de mobilidade <--\n");
    printf("---------------------------------\n");
    printf("ID    | Tipo                | Localizacao\n");
    printf("---------------------------------\n");

    current_node = graph;
    while (current_node != NULL)
    {
        printf("%-5d | %-20s | %-20s\n",
               current_node->id,
               current_node->type,
               current_node->geocode);

        current_node = current_node->next;
    }

    // Liberta a memória alocada pelo grafo
    current_node = graph;
    while (current_node != NULL)
    {
        GraphNode *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
}

// Encontra o cliente pretendido
CustomerV2 *findCustomer(CustomerV2 *head, int id)
{
    CustomerV2 *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Adiciona saldo a um cliente pretendido
void addBalance(CustomerV2 *head)
{
    int id;
    float amount;
    printf("Insira o ID do cliente: ");
    scanf("%d", &id);
    CustomerV2 *customer = findCustomer(head, id);
    if (customer == NULL)
    {
        printf("Cliente não encontrado.\n");
        return;
    }
    printf("Insira a quantia a ser adicionada ao saldo (euro): ");
    scanf("%f", &amount);
    if (amount < 0)
    {
        printf("A quantia não pode ser negativa.\n");
        return;
    }
    customer->balance += amount;
    printf("O saldo do cliente %s foi atualizado para %.2f (euro).\n", customer->name, customer->balance);
}

// Encontra meio pretendido
Mobility *findMobility(Mobility *head, int id)
{
    Mobility *current_mobility = head;
    while (current_mobility != NULL)
    {
        if (current_mobility->id == id)
        {
            return current_mobility;
        }
        current_mobility = current_mobility->next;
    }
    return NULL;
}

// Aluga meio pretendido
void rentMobility(CustomerV2 *head1, Mobility *head2)
{
    int customer_id, mobility_id;
    printf("Insira o ID do cliente que ira alugar o meio de mobilidade eletrica: ");
    scanf("%d", &customer_id);
    printf("Insira o ID do meio de mobilidade eletrica: ");
    scanf("%d", &mobility_id);

    // Procura o cliente na lista ligada
    CustomerV2 *current_customer = findCustomer(head1, customer_id);
    if (current_customer == NULL)
    {
        printf("Cliente nao encontrado.\n");
        return;
    }

    // Procura o meio de mobilidade eletrica na lista ligada
    Mobility *current_mobility = findMobility(head2, mobility_id);
    if (current_mobility == NULL)
    {
        printf("Meio de mobilidade eletrica nao encontrado.\n");
        return;
    }

    // Verifica se o cliente tem saldo suficiente
    if (current_customer->balance < current_mobility->price)
    {
        printf("Saldo insuficiente.\n");
        return;
    }

    // Atualiza o saldo do cliente
    current_customer->balance -= current_mobility->price;

    printf("Meio de mobilidade eletrica alugado com sucesso!\n");
}

// Altera dados de um meio existente
void updateMobility(Mobility *head2)
{
    int id;
    printf("Insira o ID do meio de mobilidade eletrica que deseja atualizar: ");
    scanf("%d", &id);

    // Procura o meio de mobilidade eletrica na lista ligada
    Mobility *current_mobility = findMobility(head2, id);
    if (current_mobility == NULL)
    {
        printf("Meio de mobilidade eletrica nao encontrado.\n");
        return;
    }

    printf("Insira o novo tipo do meio de mobilidade: ");
    scanf(" %s", &current_mobility->type);

    printf("Insira a nova carga da bateria (em %%): ");
    scanf("%f", &current_mobility->battery);

    printf("Insira a nova autonomia (em km): ");
    scanf("%f", &current_mobility->autonomy);

    printf("Insira o novo custo (por hora): ");
    scanf("%f", &current_mobility->price);

    printf("Insira o novo geocodigo do meio de mobilidade: (What3Words sera aplicado brevemente)");
    scanf(" %s", &current_mobility->geocode);

    printf("Dados do meio de mobilidade eletrica atualizados com sucesso!\n");
}

// Apaga um meio existente
void deleteMobility(Mobility **head2)
{
    int id;
    printf("Insira o ID do meio de mobilidade eletrica que deseja remover: ");
    scanf("%d", &id);

    Mobility *current_mobility = *head2;
    Mobility *previous_mobility = NULL;

    while (current_mobility != NULL)
    {
        if (current_mobility->id == id)
        {
            // Remove o meio de mobilidade eletrica da lista ligada
            if (previous_mobility == NULL)
            {
                // Se o meio de mobilidade eletrica a ser removido for o primeiro da lista
                *head2 = current_mobility->next;
            }
            else
            {
                // Caso contrário, atualiza o ponteiro "next" do elemento anterior
                previous_mobility->next = current_mobility->next;
            }

            // Apaga a memória alocada do meio de mobilidade eletrica removido
            free(current_mobility);

            printf("Meio de mobilidade eletrica removido com sucesso.\n");
            return;
        }

        previous_mobility = current_mobility;
        current_mobility = current_mobility->next;
    }

    printf("Meio de mobilidade eletrica nao encontrado.\n");
}

// Cria um gestor e retorna para ser inserido
Admin *createAdmin(int id, char *name, char *password, int active)
{
    Admin *newAdmin = (Admin *)malloc(sizeof(Admin));
    newAdmin->id = id;
    strcpy(newAdmin->name, name);
    strcpy(newAdmin->password, password);
    newAdmin->active = active;
    newAdmin->next = NULL;
    return newAdmin;
}

// Insere o gestor na lista ligada
void insertAdmin(Admin **head, Admin *newAdmin)
{
    if (*head == NULL)
    {
        *head = newAdmin;
    }
    else
    {
        Admin *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newAdmin;
    }
}

// Remove cliente
void removeCustomer(CustomerV2 **head)
{
    int id;
    printf("Insira o ID do cliente que deseja remover: ");
    scanf("%d", &id);

    CustomerV2 *current_customer = *head;
    CustomerV2 *previous_customer = NULL;

    while (current_customer != NULL)
    {
        if (current_customer->id == id)
        {
            // o elemento a ser removido é o primeiro
            if (previous_customer == NULL)
            {
                *head = current_customer->next;
            }
            // Caso contrário, atualiza o ponteiro "next" do elemento anterior
            else
            {
                previous_customer->next = current_customer->next;
            }

            printf("Cliente removido com sucesso!\n");
            free(current_customer);
            return;
        }

        previous_customer = current_customer;
        current_customer = current_customer->next;
    }

    printf("Cliente com ID %d nao encontrado.\n", id);
}

// Remove gestor
void removeAdmin(Admin **head)
{
    int id;
    printf("\nInsira o ID do gestor que deseja remover: ");
    scanf("%d", &id);

    Admin *current_admin = *head;
    Admin *previous_admin = NULL;

    while (current_admin != NULL)
    {
        if (current_admin->id == id)
        {
            // o elemento a ser removido é o primeiro
            if (previous_admin == NULL)
            {
                *head = current_admin->next;
            }
            // Caso contrário, atualiza o ponteiro "next" do elemento anterior
            else
            {
                previous_admin->next = current_admin->next;
            }

            printf("Gestor removido com sucesso!\n");
            free(current_admin);
            return;
        }

        previous_admin = current_admin;
        current_admin = current_admin->next;
    }

    printf("Gestor com ID %d nao encontrado.\n", id);
}

// Altera dados do cliente
void updateCustomer(CustomerV2 *head)
{
    int id;
    printf("Insira o ID do cliente que deseja editar: ");
    scanf("%d", &id);

    CustomerV2 *current_customer = head;

    while (current_customer != NULL)
    {
        if (current_customer->id == id)
        {
            printf("Nome atual: %s\n", current_customer->name);
            printf("Insira o novo nome (ou deixe em branco para manter o atual): ");
            char new_name[50];
            scanf("%[^\n]%*c", new_name); // ler uma string com espaços em branco

            if (strlen(new_name) > 0)
            {
                strncpy(current_customer->name, new_name, 50);
            }

            printf("Senha atual: %c\n", current_customer->password);
            printf("Insira a nova senha (ou deixe em branco para manter a atual): ");
            char new_password;
            scanf(" %c", &new_password);

            if (new_password != '\n')
            {
                current_customer->password = new_password;
            }

            printf("NIF atual: %d\n", current_customer->NIF);
            printf("Insira o novo NIF (ou deixe em branco para manter o atual): ");
            int new_nif;
            scanf("%d", &new_nif);

            if (new_nif != '\n')
            {
                current_customer->NIF = new_nif;
            }

            printf("Saldo atual: %.2f\n", current_customer->balance);
            printf("Insira o novo saldo (ou deixe em branco para manter o atual): ");
            float new_balance;
            scanf("%f", &new_balance);

            if (new_balance != '\n')
            {
                current_customer->balance = new_balance;
            }

            printf("Endereco atual: %s\n", current_customer->address);
            printf("Insira o novo endereco (ou deixe em branco para manter o atual): ");
            char new_address[100];
            scanf("%[^\n]%*c", new_address);

            if (strlen(new_address) > 0)
            {
                strncpy(current_customer->address, new_address, 100);
            }

            printf("Local atual: %s\n", current_customer->geocode);
            printf("Insira a nova localizacao (ou deixe em branco para manter o atual): ");
            char new_geocode[25];
            scanf("%[^\n]%*c", new_geocode);

            if (strlen(new_geocode) > 0)
            {
                strncpy(current_customer->geocode, new_geocode, 25);
            }

            printf("Cliente editado com sucesso!\n");
            return;
        }

        current_customer = current_customer->next;
    }

    printf("Cliente com ID %d nao encontrado.\n", id);
}

// Altera dados do gestor
void updateAdmin(Admin **head)
{
    int id;
    printf("Insira o ID do gestor que deseja editar: ");
    scanf("%d", &id);

    Admin *current_admin = *head;
    while (current_admin != NULL)
    {
        if (current_admin->id == id)
        {
            printf("ID: %d\n", current_admin->id);
            printf("Nome: %s\n", current_admin->name);
            printf("Senha: %s\n", current_admin->password);
            printf("Estado: %d\n", current_admin->active);

            printf("Insira o novo nome do gestor: ");
            scanf("%s", current_admin->name);
            printf("Insira a nova senha do gestor: ");
            scanf("%s", current_admin->password);
            printf("Insira o novo estado do gestor (0 = inativo, 1 = ativo): ");
            scanf("%d", &current_admin->active);

            printf("Dados do gestor atualizados!\n");
            return;
        }
        current_admin = current_admin->next;
    }

    printf("Gestor com ID %d nao encontrado.\n", id);
}

// Esta função pergunta o id do meio que o utilizador deseja saber a localização, confere que existe e caso exista mostra a sua localização através do conceito what3words.
void listMobility4geocode(Mobility *head2)
{
    Mobility *current = head2;
    int targetId;
    int found = 0; // Se o ID foi encontrado;

    if (current == NULL)
    {
        printf("\nNenhum meio de mobilidade encontrado!\n");
    }
    else
    {
        printf("Insira o ID que deseja saber onde esta: ");
        scanf("%d", &targetId);

        while (current != NULL)
        {
            if (current->id == targetId)
            {
                printf("Esse meio esta localizado em: ");
                printf("%s\n", current->geocode);
                found = 1; // ID encontrado
                break;     // Encerra a lista
            }
            current = current->next;
        }

        if (!found)
        {
            printf("O ID %d não existe.\n", targetId);
        }
    }
}

void listMobilityByAutonomy(Mobility *head2)
{
    Mobility *current = head2;
    Mobility *temp = NULL;
    Mobility *sortedHead = NULL;

    if (current == NULL)
    {
        printf("\nNenhum meio de mobilidade encontrado!\n");
        return;
    }

    // Cria uma nova lista ligada ordenada por autonomia
    while (current != NULL)
    {
        Mobility *newNode = (Mobility *)malloc(sizeof(Mobility));
        newNode->id = current->id;
        strcpy(newNode->type, current->type);
        newNode->battery = current->battery;
        newNode->autonomy = current->autonomy;
        newNode->price = current->price;
        strcpy(newNode->geocode, current->geocode);

        // Insere o novo nó na lista ordenada
        if (sortedHead == NULL || newNode->autonomy > sortedHead->autonomy)
        {
            newNode->next = sortedHead;
            sortedHead = newNode;
        }
        else
        {
            Mobility *temp = sortedHead;
            while (temp->next != NULL && newNode->autonomy <= temp->next->autonomy)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        current = current->next;
    }

    // Mostra a lista ordenada por autonomia
    printf("\n--> Lista de meios de mobilidade ordenada por autonomia <--\n");
    printf("ID\tTipo\tBateria\tAutonomia\tPreco\tGeocode\n");

    Mobility *sortedCurrent = sortedHead;
    while (sortedCurrent != NULL)
    {
        printf("%d\t%s\t%.2f\t%.2f\t\t%.2f\t%s\n", sortedCurrent->id, sortedCurrent->type, sortedCurrent->battery, sortedCurrent->autonomy, sortedCurrent->price, sortedCurrent->geocode);
        sortedCurrent = sortedCurrent->next;
    }

    // Liberta a memória alocada pela lista ordenada
    while (sortedHead != NULL)
    {
        Mobility *temp = sortedHead;
        sortedHead = sortedHead->next;
        free(temp);
    }
}

// Lista os dados de todos os clientes
void listCustomer(CustomerV2 *head)
{
    CustomerV2 *current_customer = head;

    printf("ID    | Nome                | Senha | NIF      | Saldo   | Endereco             | Localizacao\n");
    printf("---------------------------------------------------------------------------------------------\n");

    while (current_customer != NULL)
    {
        printf("%-5d | %-20s | %-5c | %-8d | %-7.2f | %-20s | %-20s\n",
               current_customer->id,
               current_customer->name,
               current_customer->password,
               current_customer->NIF,
               current_customer->balance,
               current_customer->address,
               current_customer->geocode);

        current_customer = current_customer->next;
    }
}

// Lista a localizacao dos meios de mobilidade e dos cliente recorrendo a um grafo
void listData(CustomerV2 *head, Mobility *head2)
{
    GraphNode *graph = NULL;
    GraphNode *current_node = NULL;

    // Constrói o grafo a partir da primeira lista ligada (clientes)
    CustomerV2 *current_customer = head;
    while (current_customer != NULL)
    {
        GraphNode *new_node = (GraphNode *)malloc(sizeof(GraphNode));
        new_node->id = current_customer->id;
        strcpy(new_node->name, current_customer->name);
        strcpy(new_node->geocode, current_customer->geocode);
        new_node->next = NULL;

        if (graph == NULL)
        {
            graph = new_node;
            current_node = new_node;
        }
        else
        {
            current_node->next = new_node;
            current_node = new_node;
        }

        current_customer = current_customer->next;
    }

    // Adiciona os meios de mobilidade ao grafo
    Mobility *current_mobility = head2;
    while (current_mobility != NULL)
    {
        GraphNode *new_node = (GraphNode *)malloc(sizeof(GraphNode));
        new_node->id = current_mobility->id;
        strcpy(new_node->type, current_mobility->type);
        strcpy(new_node->geocode, current_mobility->geocode);
        strcpy(new_node->name, ""); // Define o campo 'Nome' como uma string vazia
        new_node->next = NULL;

        if (graph == NULL)
        {
            graph = new_node;
            current_node = new_node;
        }
        else
        {
            current_node->next = new_node;
            current_node = new_node;
        }

        current_mobility = current_mobility->next;
    }

    // Imprime os dados do grafo
    printf("--> Lista de dados de clientes e meios de mobilidade <--\n");
    printf("------------------------------------------------------\n");

    printf("Clientes e meios de mobilidade:\n");
    printf("ID    | Nome                | Tipo                | Localizacao\n");
    printf("-------------------------------------------------------------\n");

    current_node = graph;
    while (current_node != NULL)
    {
        printf("%-5d | %-20s | %-20s | %-20s\n",
               current_node->id,
               current_node->name,
               current_node->type,
               current_node->geocode);

        current_node = current_node->next;
    }

    // Liberta a memória alocada pelo grafo
    current_node = graph;
    while (current_node != NULL)
    {
        GraphNode *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
}

// Função para armazenar as informações em um arquivo de texto
void saveDataToFile(Mobility *head2, CustomerV2 *head)
{
    FILE *file = fopen("data.txt", "w"); // Abre o arquivo em modo de escrita

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve as informações da lista de mobilidade no arquivo
    Mobility *current_mobility = head2;
    while (current_mobility != NULL)
    {
        fprintf(file, "%s|%d|%.2f|%.2f|%.2f|%s\n", "Meio", current_mobility->id, current_mobility->battery, current_mobility->autonomy, current_mobility->price, current_mobility->geocode);
        current_mobility = current_mobility->next;
    }

    // Escreve as informações da lista de clientes no arquivo
    CustomerV2 *current_customer = head;
    while (current_customer != NULL)
    {
        fprintf(file, "%s|%d|%c|%d|%.2f|%s|%s\n",
                "Cliente",
                current_customer->id,
                current_customer->password,
                current_customer->NIF,
                current_customer->balance,
                current_customer->address,
                current_customer->geocode);

        current_customer = current_customer->next;
    }

    fclose(file); // Fecha o arquivo
    printf("Dados salvos com sucesso no arquivo 'data.txt'!\n");
}

// Função para armazenar as informações em um arquivo binário
void saveDataToFileBinary(Mobility *head2, CustomerV2 *head)
{
    FILE *file = fopen("data.bin", "wb"); // Abre o arquivo em modo de escrita binária

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve as informações da lista de mobilidade no arquivo
    Mobility *current_mobility = head2;
    while (current_mobility != NULL)
    {
        fwrite(current_mobility, sizeof(Mobility), 1, file);
        current_mobility = current_mobility->next;
    }

    // Escreve as informações da lista de clientes no arquivo
    CustomerV2 *current_customer = head;
    while (current_customer != NULL)
    {
        fwrite(current_customer, sizeof(CustomerV2), 1, file);
        current_customer = current_customer->next;
    }

    fclose(file); // Fecha o arquivo
    printf("Dados salvos com sucesso no arquivo 'data.bin'!\n");
}

// Insere dados automaticamente na lista ligada
void insertDefaultMobility(Mobility **head2)
{
    char types[10][20] = {"Bicicleta", "Bicicleta", "Bicicleta", "Trotinete", "Trotinete",
                          "Mota", "Trotinete", "Trotinete", "Mota", "Trotinete"};
    float batteries[10] = {90.5, 100, 80.3, 50.2, 70.9, 60.1, 75.6, 45.8, 85.2, 95.4};
    float autonomies[10] = {500, 30, 20, 300, 1000, 2000, 100, 250, 400, 50};
    float prices[10] = {10.5, 5.2, 2.8, 15.3, 25.6, 50.1, 30.7, 8.9, 12.4, 20.6};
    char geocodes[10][20] = {"coelho.estrela.azul", "ovos.macaco.sino", "ferro.zero.bem", "asno.loja.cubo", "banana.filme.espada",
                             "urso.pedra.nuvem", "comida.bola.panda", "cesta.joelho.cama", "jaguar.seta.cubo", "cozinha.dois.lua"};

    for (int i = 0; i < 10; i++)
    {
        Mobility *newMobility = (Mobility *)malloc(sizeof(Mobility));
        newMobility->id = i + 1;
        strcpy(newMobility->type, types[i]);
        newMobility->battery = batteries[i];
        newMobility->autonomy = autonomies[i];
        newMobility->price = prices[i];
        strcpy(newMobility->geocode, geocodes[i]);
        newMobility->next = *head2;
        *head2 = newMobility;
    }
}

// Recebe 2 vertices e cria uma aresta entre eles
void addEdge(Graph *graph, int src, int dest)
{
    graph->adjacencyMatrix[src][dest] = 1; // Define a aresta entre o vértice de origem (src) e o vértice de destino (dest) como 1.
    graph->adjacencyMatrix[dest][src] = 1; // Define a aresta entre o vértice de destino (dest) e o vértice de origem (src) como 1.
}

// Cria e constrói um grafo com base nas informações dos clientes e dos meios de mobilidade
Graph *buildGraph(CustomerV2 *customers, Mobility *mobility)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph)); // Aloca memória para uma estrutura de dados do tipo Graph e atribui o ponteiro a 'graph'.
    graph->V = 0;                                  // Inicia o número de vértices (V) no grafo como 0.

    // Conta o número de clientes na lista e adiciona ao número total de vértices (V) no grafo.
    for (CustomerV2 *currentCustomer = customers; currentCustomer != NULL; currentCustomer = currentCustomer->next)
    {
        graph->V++;
    }

    // Conta o número de mobilidades na lista e adiciona ao número total de vértices (V) no grafo.
    for (Mobility *currentMobility = mobility; currentMobility != NULL; currentMobility = currentMobility->next)
    {
        graph->V++;
    }

    // Inicia a matriz de adjacência do grafo com valores zero.
    for (int i = 0; i < graph->V; i++)
    {
        for (int j = 0; j < graph->V; j++)
        {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }

    int currentVertex = 0; // Variável para procurar o vértice atual no processo de construção do grafo.

    // Adiciona arestas entre os clientes no grafo, atualizando o vértice atual a cada iteração.
    for (CustomerV2 *currentCustomer = customers; currentCustomer != NULL; currentCustomer = currentCustomer->next)
    {
        addEdge(graph, currentVertex, currentVertex + 1);
        currentVertex += 2;
    }

    // Adiciona arestas entre as mobilidades no grafo, atualizando o vértice atual a cada iteração.
    for (Mobility *currentMobility = mobility; currentMobility != NULL; currentMobility = currentMobility->next)
    {
        addEdge(graph, currentVertex, currentVertex + 1);
        currentVertex += 2;
    }

    return graph; // Retorna o ponteiro para o grafo construído.
}

// Implementa uma busca em largura (BFS) para calcular as distâncias dos vértices em relação a um vértice de origem no grafo
int *calculateDistancesBFS(Graph *graph, int source)
{
    int *distances = (int *)malloc(graph->V * sizeof(int));  // Aloca memória para um array de distâncias com base no número de vértices no grafo.
    bool *visited = (bool *)malloc(graph->V * sizeof(bool)); // Aloca memória para um array de booleanos para rastrear os vértices visitados.

    // Inicia os arrays de distâncias e visitados.
    for (int i = 0; i < graph->V; i++)
    {
        distances[i] = -1;  // Define -1 para indicar que a distância é desconhecida.
        visited[i] = false; // Define false para indicar que o vértice não foi visitado.
    }

    distances[source] = 0;  // Define a distância do vértice de origem como 0.
    visited[source] = true; // Marca o vértice de origem como visitado.

    int queue[MAX_VERTICES]; // Cria uma fila para armazenar os vértices a serem visitados.
    int front = 0, rear = 0; // Variáveis para controlar o início e o fim da fila.
    queue[rear++] = source;  // Insere o vértice de origem na fila.

    // Executa a busca em largura (BFS) para calcular as distâncias.
    while (front != rear)
    {
        int currentVertex = queue[front++]; // Obtém o próximo vértice da fila.

        for (int i = 0; i < graph->V; i++)
        {
            // Verifica se há uma aresta entre o vértice atual e o vértice 'i' e se o vértice 'i' ainda não foi visitado.
            if (graph->adjacencyMatrix[currentVertex][i] && !visited[i])
            {
                visited[i] = true;                           // Marca o vértice 'i' como visitado.
                distances[i] = distances[currentVertex] + 1; // Atualiza a distância do vértice 'i'.
                queue[rear++] = i;                           // Insere o vértice 'i' na fila para visitar seus vizinhos posteriormente.
            }
        }
    }

    free(visited);    // Liberta a memória alocada para o array de visitados.
    return distances; // Retorna o array de distâncias calculadas.
}

// Lista os meios de mobilidade elétrica mais próximos a um cliente específico
void listDataV2(CustomerV2 *head, Mobility *head2)
{
    // Constrói o grafo a partir das listas ligadas (clientes e meios de mobilidade)
    Graph *graph = buildGraph(head, head2);

    // Solicitar o ID do cliente ao utilizador
    int customerID;
    printf("Insira o ID do cliente: ");
    scanf("%d", &customerID);

    // Verificar se o ID do cliente é válido
    int source = customerID * 2 - 1;
    if (source < 0 || source >= graph->V)
    {
        printf("Cliente não encontrado.\n");
        free(graph); // Libertar memória do grafo
        return;
    }

    // Calcular a distância mínima entre o cliente e os meios de mobilidade elétrica usando BFS
    int *distances = calculateDistancesBFS(graph, source);

    // Criar uma lista de meios de mobilidade elétrica ordenados pela distância ao cliente
    MobilityDistance *mobilityDistances = (MobilityDistance *)malloc((graph->V - 1) * sizeof(MobilityDistance));

    int index = 0;
    for (int i = 0; i < graph->V; i++)
    {
        if (i != source)
        {
            mobilityDistances[index].distance = distances[i];
            mobilityDistances[index].mobility = i % 2 == 1 ? &head2[i / 2] : &head2[i / 2 - 1];
            index++;
        }
    }

    // Ordenar a lista de meios de mobilidade elétrica por distância crescente
    for (int i = 0; i < graph->V - 2; i++)
    {
        for (int j = 0; j < graph->V - 2 - i; j++)
        {
            if (mobilityDistances[j].distance > mobilityDistances[j + 1].distance)
            {
                MobilityDistance temp = mobilityDistances[j];
                mobilityDistances[j] = mobilityDistances[j + 1];
                mobilityDistances[j + 1] = temp;
            }
        }
    }

    // Imprimir os meios de mobilidade elétrica ordenados pela distância ao cliente
    printf("Meios de mobilidade elétrica mais próximos ao cliente (ID: %d):\n", customerID);
    printf("ID    | Tipo                | Distância\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < graph->V - 1; i++)
    {
        printf("%-5d | %-20s | %d\n", mobilityDistances[i].mobility->id, mobilityDistances[i].mobility->type, mobilityDistances[i].distance);
    }

    // Libertar memória alocada
    free(distances);
    free(mobilityDistances);
    free(graph);
}

void listMobilityBelow50(Mobility *head2)
{
    Mobility *current = head2;
    GraphNode *graph = NULL;
    GraphNode *current_node = NULL;

    // Percorre a lista de meios de mobilidade elétrica
    while (current != NULL)
    {
        // Verifica se a bateria está abaixo de 50%
        if (current->battery < 50)
        {
            // Cria um novo nó para o grafo e preenche com os dados do meio de mobilidade
            GraphNode *new_node = (GraphNode *)malloc(sizeof(GraphNode));
            new_node->id = current->id;
            strcpy(new_node->type, current->type);
            strcpy(new_node->geocode, current->geocode);
            new_node->next = NULL;

            // Insere o novo nó no grafo
            if (graph == NULL)
            {
                // Se o grafo estiver vazio, o novo nó é definido como o primeiro e último nó
                graph = new_node;
                current_node = new_node;
            }
            else
            {
                // Caso contrário, o novo nó é adicionado ao final do grafo
                current_node->next = new_node;
                current_node = new_node;
            }
        }

        current = current->next; // Avança para o próximo meio de mobilidade
    }

    // Imprime os dados do grafo contendo os meios de mobilidade abaixo de 50% de bateria
    printf("--> Lista de meios de mobilidade abaixo de 50%% de bateria <--\n");
    printf("---------------------------------\n");
    printf("ID    | Tipo                | Localizacao\n");
    printf("---------------------------------\n");

    // Percorre o grafo e imprime os dados de cada nó
    current_node = graph;
    while (current_node != NULL)
    {
        printf("%-5d | %-20s | %-20s\n",
               current_node->id,
               current_node->type,
               current_node->geocode);

        current_node = current_node->next;
    }

    // Liberta a memória alocada para o grafo
    current_node = graph;
    while (current_node != NULL)
    {
        GraphNode *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
}
