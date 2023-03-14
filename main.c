#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "archive.h"

extern int managerLoginStatus; // Variavel externa que guarda se o login do gestor foi bem sucedido ou não;

int main()
{
    int userType = 0, userChoice = 0; // userType -> Gestor ou Cliente, userChoice -> Registo ou Login;

    printf("\nBem-vindo!\n");

    while (1) // Loop sem condição;
    {
        printf("\nMENU - Area\n");
        printf("1 (Gestor)\n");
        printf("2 (Cliente)\n");
        printf("0 (Sair)\n");
        printf("\nEscolha a sua area:");
        scanf("%d", &userType);

        if (userType == 1) // Area dos gestores
        {
            printf("\nMENU\n");
            printf("1 - Registar\n");
            printf("2 - Login\n");
            printf("0 - Voltar\n");
            printf("\nEscolha o que deseja realizar:");
            scanf("%d", &userChoice);

            switch (userChoice)
            {
            case 0:
                printf("\nA voltar ao 1 menu ...\n");
                break;
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
                    case 2:
                        listVehicles();
                        break;
                    default:
                        printf("Opcao invalida, tente novamente.\n");
                    }
                }
                managerLoginStatus = 0;
                break;
            default:
                printf("\nErro! Escolha invalida.\n");
                printf("A voltar ao 1 menu ...\n");
            }
        }
        else if (userType == 2) // Area dos clientes
        {
            printf("\n1 - Registar\n");
            printf("2 - Login\n");
            printf("0 - Sair\n");
            printf("\nEscolha uma opcao:");
            scanf("%d", &userChoice);
            switch (userChoice)
            {
            case 0:
                printf("A voltar ao 1 menu ...\n");
                break;
            case 1:
                registerCustomer();
                break;
            case 2:
                loginCustomer();
                break;
            default:
                printf("\nErro! Escolha invalida.\n");
                printf("A voltar ao 1 menu ...\n");
            }
        }
        else if (userType == 0) // Area de saida do programa
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

// Login cliente não funciona;
// Ao criar meio, na bateria posso colocar bateria infinita, bloquear a 100 (%);