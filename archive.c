#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "archive.h"

// Variáveis globais
int currentManagerId = -1;  // Armazena o ID do gestor logado;
int managerLoginStatus = 0; // Armazena se o login do gestor foi bem sucedido;

int menu()
{
    int optionMenu;
    printf("\nMENU:\n");
    printf("1 (Inserir Meio)\n");    //  Insere novo meio
    printf("2 (Listar Meios)\n");    //  Lista todos os meios
    printf("3 (Remover Meio)\n");    //  Remove um meio
    printf("4 (Guardar Meio)\n");    //  ??
    printf("5 (Ler Meios)\n");       //  ??
    printf("6 (Ativar gestores)\n"); // Ativa contas de gestores criadas mas inativas
    printf("0 (Sair)\n");            //  Volta ao inicio
    printf("\nOpcao:");
    scanf("%d", &optionMenu);
    return (optionMenu);
}

Manager managers[MAX_USERS]; // MAX_USERS = 100
int totalManagers = 0;
int currentManagerIndex = -1;

Customer customers[MAX_USERS]; // MAX_USERS = 100
int totalCustomers = 0;
int currentCustomerIndex = -1;

void registerManager()
{
    Manager newManager;
    printf("\nDigite o nome do utilizador: ");
    scanf("%s", newManager.name);
    printf("Digite a senha: ");
    scanf("%s", newManager.password);

    // Define o próximo ID disponível para gestores registrados
    int nextId = 1;              // Valor padrão, caso não existam gestores registrados
    int hasActive = 0;           // Verifica se existe algum gestor ativo
    int minInactiveId = INT_MAX; // ID do gestor inativo com valor mais baixo
    FILE *file = fopen("archive.txt", "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, "|");
            if (strcmp(token, "gestor") == 0)
            {
                token = strtok(NULL, "|"); // Nome do gestor
                token = strtok(NULL, "|"); // Senha do gestor
                token = strtok(NULL, "|"); // ID do gestor
                int id = atoi(token);
                if (id >= nextId)
                {
                    nextId = id + 1;
                }
                token = strtok(NULL, "|"); // Ativo ou inativo
                int active = atoi(token);
                if (active == 1)
                {
                    hasActive = 1;
                }
                else
                {
                    if (id < minInactiveId)
                    {
                        minInactiveId = id;
                    }
                }
            }
        }
        fclose(file);
    }

    if (!hasActive && minInactiveId == INT_MAX) // Nenhum gestor registrado ou ativo
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

    file = fopen("archive.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "gestor|%s|%s|%d|%d|\n", newManager.name, newManager.password, newManager.id, newManager.active);

    fclose(file);

    printf("Gerente registado com sucesso!\n");
}

// Login dos gestores
void loginManager()
{
    // Pergunta os dados de login
    Manager managerInfo;
    printf("\nInsira o seu nome: ");
    scanf("%s", managerInfo.name);
    printf("Insira a sua password: ");
    scanf("%s", managerInfo.password);

    // Verifica se o ficheiro txt existe
    FILE *file = fopen("archive.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Confirma que a linha não passa dos 100, procura linhas apenas com o primeiro campo "gestor",
    // , compara os nomes e passwords do ficheiro com o que foi inserido, verifica o estado da conta,
    // , e realiza ou nao o login.
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, "|");
        if (strcmp(token, "gestor") == 0)
        {
            token = strtok(NULL, "|"); // Nome do gestor
            if (strcmp(token, managerInfo.name) == 0)
            {
                token = strtok(NULL, "|"); // Senha do gestor
                if (strcmp(token, managerInfo.password) == 0)
                {
                    token = strtok(NULL, "|"); // ID do gestor
                    int managerId = atoi(token);
                    token = strtok(NULL, "|"); // Ativo ou inativo
                    int active = atoi(token);

                    if (active == 1)
                    {
                        currentManagerId = managerId;
                        fclose(file);
                        printf("Login realizado com sucesso!\n");
                        managerLoginStatus = 1;
                        return;
                    }
                    else
                    {
                        fclose(file);
                        printf("A sua conta esta inativa.\n");
                        managerLoginStatus = 2;
                        return;
                    }
                }
            }
        }
    }

    fclose(file);
    printf("Erro - Nome ou password invalidos.\n");
}

void registerCustomer()
{
    if (totalCustomers >= MAX_USERS)
    {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Customer newCustomer;
    printf("Digite o nome do utilizador: ");
    scanf("%s", newCustomer.name);
    printf("Digite a senha: ");
    scanf("%s", newCustomer.password);

    // A função "fflush(stdin)" limpa o buffer do teclado antes de utilizar a função "fgets()"
    // A função "strcspn()" substitui o caracter da nova linha por \0 para remover esse caracter da string
    printf("Digite a morada: ");
    fflush(stdin);
    fgets(newCustomer.address, 50, stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = '\0';

    printf("Digite o NIF: ");
    scanf("%d", &newCustomer.NIF);

    newCustomer.balance = 0.0;
    newCustomer.id = totalCustomers + 1;
    newCustomer.active = 1;

    FILE *file = fopen("archive.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "cliente|%s|%s|%s|%d|%.2f|%d|\n", newCustomer.name, newCustomer.password, newCustomer.address, newCustomer.NIF, newCustomer.balance, newCustomer.id);

    fclose(file);

    totalCustomers++;

    printf("Cliente registado com sucesso!\n");
}

void loginCustomer()
{
    char name[50];
    char password[50];

    printf("\nDigite o nome do utilizador: ");
    scanf("%s", name);
    printf("Digite a senha: ");
    scanf("%s", password);

    FILE *file = fopen("archive.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "cliente|", 8) == 0)
        {
            Customer customer;
            char *token = strtok(line + 8, "|");
            strcpy(customer.name, token);
            token = strtok(NULL, "|");
            strcpy(customer.password, token);
            token = strtok(NULL, "|");
            strcpy(customer.address, token);
            token = strtok(NULL, "|");
            customer.NIF = atoi(token);
            token = strtok(NULL, "|");
            customer.balance = atof(token);
            token = strtok(NULL, "|");
            customer.id = atoi(token);
            token = strtok(NULL, "|");

            if (strcmp(customer.name, name) == 0 && strcmp(customer.password, password) == 0 && customer.active)
            {
                currentCustomerIndex = i;
                fclose(file);
                printf("Login realizado com sucesso!\n");
                return;
            }

            i++;
        }
    }

    fclose(file);

    printf("Nome do utilizador ou senha inválidos, ou conta inativa.\n");
}

void addVehicle()
{
    Vehicle newVehicle;
    printf("Digite o tipo do veiculo: ");
    scanf("%s", newVehicle.type);
    printf("Digite a carga da bateria: ");
    scanf("%f", &newVehicle.battery);
    printf("Digite a autonomia do veiculo: ");
    scanf("%f", &newVehicle.autonomy);

    int nextId = 1; // Valor padrão, caso não existam veículos registrados
    FILE *file = fopen("archive.txt", "r");
    if (file != NULL)
    {
        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, "|");
            if (strcmp(token, "meio") == 0)
            {
                token = strtok(NULL, "|"); // Tipo do veículo
                token = strtok(NULL, "|"); // Carga da bateria
                token = strtok(NULL, "|"); // Autonomia do veículo
                token = strtok(NULL, "|"); // ID do veículo
                int id = atoi(token);
                if (id >= nextId)
                {
                    nextId = id + 1;
                }
            }
        }
        fclose(file);
    }

    newVehicle.id = nextId;

    file = fopen("archive.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(file, "meio|%s|%.2f|%.2f|%d|\n", newVehicle.type, newVehicle.battery, newVehicle.autonomy, newVehicle.id);

    fclose(file);

    printf("Veiculo adicionado com sucesso!\n");
}

void listVehicles()
{
    FILE *file = fopen("archive.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[100];
    printf("\nTipo|Bateria|Autonomia|ID\n");
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, "|");
        if (strcmp(token, "meio") == 0)
        {
            token = strtok(NULL, "|"); // Tipo do veículo
            printf("%s|", token);
            token = strtok(NULL, "|"); // Carga da bateria
            printf("%.2f|", atof(token));
            token = strtok(NULL, "|"); // Autonomia do veículo
            printf("%.2f|", atof(token));
            token = strtok(NULL, "|"); // ID do veículo
            printf("%s\n", token);
        }
    }
    fclose(file);
}