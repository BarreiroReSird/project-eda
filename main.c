#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "archive.h"

extern int managerLoginStatus;

int main()
{
    int userType = 0, userChoice = 0; // userType -> Gestor ou Cliente, userChoice -> Registo ou Login;

    printf("Bem-vindo!\n");

    while (1) // Loop sem condição;
    {
        printf("\nMENU - Area\n");
        printf("1 - Gestor\n");
        printf("2 - Cliente\n");
        printf("3 - Sair do programa\n");
        printf("\nEscolha a sua area:\n");
        scanf("%d", &userType);

        if (userType == 1) // Area dos gestores
        {
            printf("\nMENU - Procedimento\n");
            printf("1 - Registar\n");
            printf("2 - Login\n");
            printf("3 - Sair\n");
            printf("\nEscolha o procedimento que deseja realizar:\n");
            scanf("%d", &userChoice);

            switch (userChoice)
            {
            case 1:
                registerManager();
                break;
            case 2:
                loginManager();
                if (managerLoginStatus == 1)
                {
                    managerLoginStatus = 0;
                    int optionMenu = menu();
                    switch (optionMenu)
                    {
                    case 1:
                        addVehicle();
                        break;
                    default:
                        printf("Opcao invalida, tente novamente.\n");
                    }
                }
                managerLoginStatus = 0;
                break;
            case 3:
                printf("A voltar ao 1 menu ...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
            }
        }
        else if (userType == 2) // Area dos clientes
        {
            printf("\nEscolha uma opcao:\n");
            printf("1 - Registar\n");
            printf("2 - Login\n");
            printf("3 - Sair\n");
            scanf("%d", &userChoice);
            switch (userChoice)
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
        else if (userType == 3) // Area de saida do programa
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
};