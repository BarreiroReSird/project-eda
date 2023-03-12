#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "archive.h"

int main()
{
    int option = 0;    // Registo ou Login ;
    char userType[20]; // Gestor ou Cliente ;

    printf("Bem-vindo!\n");

    while (1)   // Loop infinito sem condição
    {
        printf("\nEscolha a sua area:\n");
        printf("1 - Gestor\n");
        printf("2 - Cliente\n");
        printf("3 - Sair do programa\n");
        scanf("%s", userType);

        if (strcmp(userType, "1") == 0) // Area dos gestores
        {
            printf("\nEscolha uma opcao:\n");
            printf("1 - Registar\n");
            printf("2 - Login\n");
            printf("3 - Sair\n");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                registerManager();
                break;
            case 2:
                loginManager();
                break;
            case 3:
                printf("A voltar ao 1 menu ...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
            }
        }
        else if (strcmp(userType, "2") == 0)  // Area dos clientes
        {
            printf("\nEscolha uma opcao:\n");
            printf("1 - Registar\n");
            printf("2 - Login\n");
            printf("3 - Sair\n");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                registerCustomer();
                break;
            case 2:
                loginCustomer();
                break;
            case 3:
                printf("A voltar ao 1 menu ...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
            }
        }
        else if (strcmp(userType, "3") == 0) // Area de saida do programa
        {
            printf("A encerrar ...\n");
            exit(0);
            break;
        }
        else
        {
            printf("Tipo de utilizador invalido, tente novamente.\n");
        }
    };

    return 0;
}
