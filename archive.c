#include <stdio.h>
#include <stdlib.h>
#include "archive.h"
#include <string.h>
#include <math.h>

/*CODIGO TEMPORARIO PARA A FASE 1*/
CustomerV2 *createCustomer(int id, char *name, char password, int NIF, float balance, char *address)
{
    CustomerV2 *newCustomer = (CustomerV2 *)malloc(sizeof(CustomerV2));
    newCustomer->id = id;
    strcpy(newCustomer->name, name);
    newCustomer->password = password;
    newCustomer->NIF = NIF;
    newCustomer->balance = balance;
    strcpy(newCustomer->address, address);
    newCustomer->next = NULL;
    return newCustomer;
}

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

int menuFase1()
{
    int choice;
    printf("\n--> MENU <--\n");
    printf("1 para inserir dados sobre os meios de mobilidade eletrica\n"); // Fase2: Apenas para Gestores
    printf("2 para listar todos os dados sobre os meios de mobilidade eletrica\n");
    printf("3 para carregar saldo de um cliente escolhido\n");                                                                             // Fase2: determina id apartir do login
    printf("4 para alugar meio de mobilidade eletrica (Recomendado listar primeiro todos os meios para saber o id do meio pretendido)\n"); // Fase2: determina id apartir do login
    printf("5 para alterar meio de mobilidade eletrica\n");                                                                                // Fase2: apenas para gestores
    printf("6 para remover meio de mobilidade eletrica\n");                                                                                // Fase2: apenas para gestores
    printf("7 para localizar meio de mobilidade eletrica\n");                                                                              // Fase2: funcional com o what3words e apenas para gestores
    printf("8 para remover cliente por id\n");
    printf("9 para remover gestor por id\n");
    printf("10 para alterar dados do cliente por id\n");
    printf("11 para alterar dados do gestor por id\n");
    printf("12 para listar os meios de mobilidade eletrica por ordem decrescente de autonomia\n");
    printf("0 para encerrar o programa\n");
    printf("\nA sua escolha:");
    scanf("%d", &choice);
    return (choice);
}

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

    printf("Insira o geocodigo do meio de mobilidade: (What3Words sera aplicado brevemente)");
    scanf(" %s", &newMobility->geocode);

    newMobility->next = *head2;
    *head2 = newMobility;
}

void listMobility(Mobility *head2)
{
    Mobility *current = head2;

    if (current == NULL)
    {
        printf("\nNenhum meio de mobilidade encontrado!\n");
    }
    else
    {
        printf("\n--> Lista de meios de mobilidade <--\n");
        printf("ID\tTipo\tBateria\tAutonomia\tPreco\tGeocode\n");

        while (current != NULL)
        {
            printf("%d\t%s\t%.2f\t%.2f\t\t%.2f\t%s\n", current->id, current->type, current->battery, current->autonomy, current->price, current->geocode);
            current = current->next;
        }
    }
}

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

            printf("Cliente editado com sucesso!\n");
            return;
        }

        current_customer = current_customer->next;
    }

    printf("Cliente com ID %d nao encontrado.\n", id);
}

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

/*CODIGO TEMPORARIO PARA A FASE 1*/