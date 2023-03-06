#include <stdio.h>

int choice = 0;

// Estrutura de dados do cliente
struct customer
{
    int customerId;
    char name[50];
    char address[100];
    float balance;
    int NIF;
};

// Menu inicial
void startMenu();

// Registo do cliente
void customerRegistration(struct customer *u);

// Base do programa
int main()
{
    char option, answer;
    while (option != 'S' && option != 's')
    {
        startMenu();
        printf("Deseja encerrar o programa (S/N)? ");
        scanf(" %c", &option);
    }
    printf("A encerrar o programa ...\n");
    return 0;
}

// Menu inicial
void startMenu()
{
    int optionMenu;
    printf("\nBem-vindo!\n");
    printf("Escolha a sua area.\n");
    printf("1 - Area do gestor\n");
    printf("2 - Area do cliente\n");
    scanf("%d", &optionMenu);
    switch (optionMenu)
    {
    case 1:
        printf("Entrou na area do gestor.\n");
        choice = 1;
        break;
    case 2:
        printf("Entrou na area do cliente.\n");
        choice = 2;
        break;
    default:
        printf("Erro! Escolha invalida.\n");
        choice = 0;
        break;
    }
}

// Registo do cliente
void customerRegistration(struct customer *u)
{
    static int currentId = 0;
    u->customerId = ++currentId;
    printf("Insira o seu nome: ");
    scanf("%s", u->name);
    printf("Insira a sua morada: ");
    scanf("%s", u->address);
    u->balance = 0.0;
    printf("Insira o nome: ");
    scanf("%d", u->NIF);
    FILE *archive = fopen("customers.txt", "a");
    if (archive == NULL)
    {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }
    fprintf(archive, "%d;%s;%s;%f;%d\n", u->customerId, u->name, u->address, u->balance, u->NIF);
    fclose(archive);
    printf("Cliente registado com sucesso!\n");
}

// Codigo por acabar, colocar em principio na linha 30.
/*
    if (choice == 1) {
        printf("Ja esta registado no sistema (S/N)? ");
        scanf(" %c", &answer);
        if (answer=='S' || answer=='s') {
            // Sistema de login
        } else if (answer=='N' || answer=='n') {
            // Sistema de registo, mas que a conta fica inativa ate que outro gestor a ative.
        } else {
            printf("Erro! Escolha invalida.\n");
        }
    }
*/