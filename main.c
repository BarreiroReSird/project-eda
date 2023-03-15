#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <limits.h>
#include "archive.h"

extern int managerLoginStatus; // Variavel externa que guarda se o login do gestor foi bem sucedido ou não;

int main()
{
    printf("\nBem-vindo!\n");

    while (1) // Loop sem condição;
    {
        int userType = menuArea();

        if (userType == 1) // Area dos gestores
        {
            int userChoice = menuRegLog();

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
                    while (1)
                    {
                        managerLoginStatus = 0;
                        int optionMenu = menuVehicle();
                        switch (optionMenu)
                        {
                        case 0:
                            printf("\n(W1) A voltar ao 1 menu ...\n");
                            break;
                        case 1:
                            addVehicle();
                            break;
                        case 2:
                            listVehicles();
                            break;
                        case 3:
                            removeVehicle();
                            break;
                        default:
                            printf("Opcao invalida, tente novamente.\n");
                        }
                        if (optionMenu == 0)
                        {
                            break;
                        }
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
            int userChoice = menuRegLog();

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