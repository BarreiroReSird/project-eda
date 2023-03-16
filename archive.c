#include <stdio.h>
#include <stdlib.h>
#include "archive.h"
#include <string.h>

// Variaveis globais
int userTypeGlobal;
int signInTypeGlobal;
int managerTaskGlobal;

void menuArea()
{
    while (1)
    {
        printf("\n>>> MENU 1 <<<\n");
        printf("Areas disponiveis:\n");
        printf("1 (Area do Gestor)\n");
        printf("2 (Area do Cliente)\n");
        printf("0 (Sair)\n");
        printf("\nEscolha a Area que deseja abrir:\n");
        scanf("%d", &userTypeGlobal);
        switch (userTypeGlobal)
        {
        case 0:
            printf("\nA encerrar o programa...\n");
            exit(0);
            break;
        case 1:
            printf("\nA abrir a Area do Gestor...\n");
            menuSignIn();
        case 2:
            printf("\nA abrir a Area do Cliente...\n");
            menuSignIn();
        default:
            printf("\nErro, escolha invalida.\n");
            break;
        }
    }
}

void menuSignIn()
{
    while (1)
    {
        printf("\n>>> MENU 2 <<<\n");
        printf("Escolhas disponiveis:\n");
        printf("1 (Registo - Criar conta)\n");
        printf("2 (Login)\n");
        printf("0 (Sair)\n");
        printf("\nO que deseja fazer:\n");
        scanf("%d", &signInTypeGlobal);
        switch (signInTypeGlobal)
        {
        case 0:
            printf("\nA voltar ao menu 1...\n");
            menuArea();
        case 1:
            printf("\nA abrir a plataforma de registo...\n");
            if (userTypeGlobal == 1)
            {
                ManagerNode *head = NULL; // inicializa a lista com NULL;
                registerManager(&head);   // Chama a função do login;
            }
            if (userTypeGlobal == 2)
            {
                // Registo do cliente
            }
            menuSignIn();
        case 2:
            printf("\nA abrir a plataforma de login...\n");
            if (userTypeGlobal == 1)
            {
                // Login do gestor
                printf("\nLogin bem sucedido!\n");
                menuVehicles(); // Abrir o menu dos meios (imaginado que o login funciona)
            }
            if (userTypeGlobal == 2)
            {
                // Login do cliente
            }
            menuSignIn();
        default:
            printf("\nErro, escolha invalida.\n");
            break;
        }
    }
}

void menuVehicles()
{
    while (1)
    {
        printf("\n>>> MENU 3 <<<\n"); // Menu apenas de gestores
        printf("Escolhas disponiveis:\n");
        printf("1 (Ativar gestores)\n"); // Ativa contas de gestores criadas mas inativas
        printf("2 (Inserir Meio)\n");    //  Insere novo meio;
        printf("3 (Remover Meio)\n");    //  Remove um meio;
        printf("4 (Listar Meios)\n");    //  Pergunta se lista meios temporarios ou persistentes;
        printf("0 (Sair)\n");            //  Volta ao menu 1 (Area)
        printf("\nO que deseja fazer:\n");
        scanf("%d", &managerTaskGlobal);
        ElectricMobilityVehicle *head = NULL;
        switch (managerTaskGlobal)
        {
        case 0:
            printf("\nA voltar ao menu 1...\n");
            menuArea();
        case 1:
            // Ativar gestores
        case 2:
            // Inserir novo meio
            addElectricMobilityVehicle(&head);
        case 3:
            // Remover meio
        case 4:
            // Listar todos meio
        default:
            printf("\nErro, escolha invalida.\n");
            break;
        }
    }
}

void registerManager(ManagerNode **head)
{
    Manager newManager;
    printf("\nDigite o nome do utilizador: ");
    scanf("%s", newManager.name);
    printf("Digite a senha: ");
    scanf("%s", newManager.password);

    // Define o próximo ID disponível para gestores registrados
    int nextId = 1;           // Valor padrão, caso não existam gestores registrados
    int hasActive = 0;        // Verifica se existe algum gestor ativo
    int minInactiveId = 9999; // ID do gestor inativo com valor mais baixo
    ManagerNode *current = *head;
    while (current != NULL)
    {
        if (strcmp(current->manager.name, newManager.name) == 0)
        {
            printf("Já existe um gestor com esse nome.\n");
            menuSignIn();
            // return;
        }
        if (current->manager.id >= nextId)
        {
            nextId = current->manager.id + 1;
        }
        if (current->manager.active == 1)
        {
            hasActive = 1;
        }
        else
        {
            if (current->manager.id < minInactiveId)
            {
                minInactiveId = current->manager.id;
            }
        }
        current = current->next;
    }

    if (!hasActive && minInactiveId == 9999) // Nenhum gestor registrado ou ativo
    {
        newManager.id = 1;
        newManager.active = 1;
    }
    else if (!hasActive) // Nenhum gestor ativo
    {
        newManager.id = minInactiveId;
        newManager.active = 1;
    }
    else // Pelo menos um gestor ativo
    {
        newManager.id = nextId;
        newManager.active = 0;
    }

    ManagerNode *newNode = (ManagerNode *)malloc(sizeof(ManagerNode));
    newNode->manager = newManager;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Gestor registado com sucesso!\n");
    menuSignIn();
}

Manager *login(ManagerNode *head)
{
    char name[20];
    char password[20];
    printf("\nDigite o nome do utilizador: ");
    scanf("%s", name);
    printf("Digite a senha: ");
    scanf("%s", password);

    ManagerNode *current = head;
    while (current != NULL)
    {
        if (strcmp(current->manager.name, name) == 0 && strcmp(current->manager.password, password) == 0)
        {
            printf("Login bem sucedido!\n");
            return &(current->manager);
        }
        current = current->next;
    }

    printf("Nome de utilizador ou senha incorretos.\n");
    return NULL;
}

void addElectricMobilityVehicle(ElectricMobilityVehicle **head)
{
    ElectricMobilityVehicle *new_vehicle = malloc(sizeof(ElectricMobilityVehicle));
    if (new_vehicle == NULL)
    {
        printf("Erro ao alocar memória para novo veículo.\n");
        return;
    }

    printf("\nAdicionar novo veículo elétrico de mobilidade:\n");

    // Lê os dados do novo veículo
    printf("ID: ");
    scanf("%d", &new_vehicle->id);
    printf("Tipo: ");
    scanf("%s", new_vehicle->type);
    printf("Bateria: ");
    scanf("%d", &new_vehicle->battery);
    printf("Preço: ");
    scanf("%f", &new_vehicle->price);
    printf("Geocódigo: ");
    scanf("%s", new_vehicle->geocode);

    // Adiciona o novo veículo ao final da lista
    new_vehicle->next = NULL;
    if (*head == NULL)
    {
        *head = new_vehicle;
    }
    else
    {
        ElectricMobilityVehicle *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_vehicle;
    }

    printf("\nNovo veículo adicionado com sucesso!\n");
}