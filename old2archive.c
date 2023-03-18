// Variaveis globais
int userTypeGlobal;
int signInTypeGlobal;
int managerTaskGlobal;

typedef struct CustomerNode
{
    int id;
    char name[50];
    char password;
    char address[100];
    char nif[9];
    float balance;
    struct CustomerNode *next;
} CustomerNode;

CustomerNode *head = NULL;

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
                // Registo do gestor
                ManagerNode *head = NULL; // inicializa a lista com NULL;
                registerManager(&head);   // Chama a função do login;
            }
            if (userTypeGlobal == 2)
            {
                // Registo do cliente
                void registerCustomer();
            }
            menuSignIn();
        case 2:
            printf("\nA abrir a plataforma de login...\n");
            if (userTypeGlobal == 1)
            {
                // Login do gestor
                printf("\nLogin bem sucedido!\n");
                menuVehicles(); // Abrir o menu dos ElectricMobilityVehicles (imaginado que o login funciona)
            }
            if (userTypeGlobal == 2)
            {
                // Login do cliente
                void loginCustomer();
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
    int case0 = 0, case1 = 0, case2 = 0, case3 = 0, case4 = 0;
    while (1)
    {
        printf("\n>>> MENU 3 <<<\n"); // Menu apenas de gestores
        printf("Escolhas disponiveis:\n");
        printf("1 (Ativar gestores)\n"); // Ativa contas de gestores criadas mas inativas;
        printf("2 (Inserir meios)\n");   //  Insere novo meio;
        printf("3 (Remover meios)\n");   //  Remove um meio;
        printf("4 (Listar meios)\n");    //  Pergunta se lista meios temporarios ou persistentes;
        printf("5 (Guardar Meios)\n");   // Guarda meios da lista ligada num txt;
        printf("6 (Ler Meios)\n");       // Le meios do txt para a lista ligada;
        printf("0 (Sair)\n");            //  Volta ao menu 1 (Area)
        printf("\nO que deseja fazer:\n");
        scanf("%d", &managerTaskGlobal);
        ElectricMobilityVehicle *head = NULL;
        switch (managerTaskGlobal)
        {
        case 0:
            // Volta ao menu 1 (escolha de gestor ou cliente);
            case0 = 1;
            printf("\nA voltar ao menu 1...\n");
            break;
        case 1:
            case1 = 1;
            // Ativa gestores com a conta desativada;
            printf("\nEsta funcionalidade ainda nao funciona...\n");
            break;
        case 2:
            case2 = 1;
            // Insere um novo meio
            addElectricMobilityVehicle(&head);
            break;
        case 3:
            // Remove um dos meios ja criados;
            removeElectricMobilityVehicle(&head);
            break;
        case 4:
            // Lista todos os meios criados guardados na lista ligada
            listElectricMobilityVehicles(head);
            break;
        case 5:
            // Guarda os meios da lista ligada num ficheiro txt
            saveElectricMobilityVehiclesToFile(head);
            break;
        case 6:
            // Carregar ElectricMobilityVehicles de um ficheiro de texto
            loadElectricMobilityVehiclesFromFile(&head, "data.txt");
            break;
        default:
            // Avisa que escolha deu erro e reinicia
            printf("\nErro, escolha invalida.\n");
            continue;
        }
        if (case0 == 1 || case1 == 1 || case2 == 1 || case3 == 1 || case4 == 1)
        {
            break;
        }
    }
    if (case0 == 1)
    {
        menuArea();
    }
    if (case1 == 1 || case2 == 1 || case3 == 1 || case4 == 1)
    {
        menuVehicles();
    }
}

void registerManager(ManagerNode **head)
{
    Manager newAdmin;
    printf("\nInsira o nome do utilizador: ");
    scanf("%s", newAdmin.name);
    printf("Insira a senha: ");
    scanf("%s", newAdmin.password);

    // Define o próximo ID disponível para gestores registrados
    int nextId = 1;           // Valor padrão, caso não existam gestores registrados
    int hasActive = 0;        // Verifica se existe algum gestor ativo
    int minInactiveId = 9999; // ID do gestor inativo com valor mais baixo
    ManagerNode *current = *head;
    while (current != NULL)
    {
        if (strcmp(current->manager.name, newAdmin.name) == 0)
        {
            printf("Já existe um gestor com esse nome.\n");
            menuSignIn();
            return;
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
        newAdmin.id = 1;
        newAdmin.active = 1;
    }
    else if (!hasActive) // Nenhum gestor ativo
    {
        newAdmin.id = minInactiveId;
        newAdmin.active = 1;
    }
    else // Pelo menos um gestor ativo
    {
        newAdmin.id = nextId;
        newAdmin.active = 0;
    }

    ManagerNode *newNode = (ManagerNode *)malloc(sizeof(ManagerNode));
    newNode->manager = newAdmin;
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

Manager *loginManager(ManagerNode *head)
{
    char name[20];
    char password[20];
    printf("\nInsira o nome do utilizador: ");
    scanf("%s", name);
    printf("Insira a senha: ");
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

void registerCustomer()
{
    char name[50];
    char password[50];
    char address[100];
    char nif[9];

    printf("Insira o nome do utilizador: ");
    scanf("%s", name);
    printf("Insira a senha: ");
    scanf("%s", password);
    printf("Insira a morada: ");
    fflush(stdin);
    fgets(address, 100, stdin);
    address[strcspn(address, "\n")] = '\0';
    printf("Insira o NIF: ");
    scanf("%s", nif);

    CustomerNode *newCustomer = malloc(sizeof(CustomerNode));
    newCustomer->id = head == NULL ? 1 : head->id + 1;
    strcpy(newCustomer->name, name);
    strcpy(&newCustomer->password, password);
    strcpy(newCustomer->address, address);
    strcpy(newCustomer->nif, nif);
    newCustomer->balance = 0.0;
    newCustomer->next = NULL;

    if (head == NULL)
    {
        head = newCustomer;
    }
    else
    {
        CustomerNode *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newCustomer;
    }

    printf("Cliente registado com sucesso!\n");
}

void loginCustomer()
{
    char name[50];
    char password[50];

    printf("Insira o nome do utilizador: ");
    scanf("%s", name);
    printf("Insira a senha: ");
    scanf("%s", password);

    CustomerNode *current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0 && strcmp(&current->password, password) == 0)
        {
            printf("Bem-vindo, %s!\n", current->name);
            return;
        }
        current = current->next;
    }

    printf("Utilizador ou senha incorretos.\n");
}

// Insere meios na lista ligada
void addElectricMobilityVehicle(ElectricMobilityVehicle **head)
{
    static int nextId = 1; // variável estática para gerar o id
    ElectricMobilityVehicle *newVehicle = (ElectricMobilityVehicle *)malloc(sizeof(ElectricMobilityVehicle));

    printf("Tipo de meio (bicicleta, trotinete, etc): ");
    scanf("%s", newVehicle->type);
    printf("Bateria restante: ");
    scanf("%d", &newVehicle->battery);
    printf("Custo: ");
    scanf("%f", &newVehicle->price);
    printf("Geocode: ");
    scanf("%s", newVehicle->geocode);

    // atribui o próximo id e incrementa o contador
    newVehicle->id = nextId++;
    newVehicle->next = NULL;
    if (*head == NULL)
    {
        *head = newVehicle;
    }
    else
    {
        ElectricMobilityVehicle *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newVehicle;
    }
}

// Listar o conteúdo da lista ligada
void listElectricMobilityVehicles(ElectricMobilityVehicle *head)
{
    ElectricMobilityVehicle *current = head;
    printf("\n--- Lista de meios ---\n");
    while (current != NULL)
    {
        printf("ID: %d\n", current->id);
        printf("Tipo: %s\n", current->type);
        printf("Bateria: %d\n", current->battery);
        printf("Custo: %.2f\n", current->price);
        printf("Geocode: %s\n", current->geocode);
        printf("\n");
        current = current->next;
    }
}

void removeElectricMobilityVehicle(ElectricMobilityVehicle **head)
{
    // Verifica se a lista ligada está vazia
    if (*head == NULL)
    {
        printf("A lista ligada está vazia.\n");
        return;
    }

    int id;
    printf("Insira o ID do elemento a ser removido: ");
    scanf("%d", &id);

    ElectricMobilityVehicle *current = *head;
    ElectricMobilityVehicle *previous = NULL;

    // Procura o elemento na lista
    while (current != NULL && current->id != id)
    {
        previous = current;
        current = current->next;
    }

    // Se o elemento não foi encontrado, retorna
    if (current == NULL)
    {
        printf("Elemento com o ID %d não encontrado.\n", id);
        return;
    }

    // Remove o elemento da lista
    if (previous == NULL)
    {
        // O elemento a ser removido é o primeiro da lista
        *head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    // Libera a memória alocada para o elemento
    free(current);

    printf("Elemento com o ID %d removido com sucesso.\n", id);
}

// Guarda os dados da lista ligada no ficheiro txt
int saveElectricMobilityVehiclesToFile(ElectricMobilityVehicle *head)
{
    const char *filename = "data.txt";
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro %s\n", filename);
        return -1;
    }

    ElectricMobilityVehicle *current = head;
    while (current != NULL)
    {
        fprintf(fp, "%d;%s;%d;%.2f;%s\n", current->id, current->type, current->battery, current->price, current->geocode);
        current = current->next;
    }

    fclose(fp);
    printf("Dados guardados no ficheiro %s\n", filename);
    return 0;
}

// Le os dados do ficheiro txt e guarda na lista ligada;
int loadElectricMobilityVehiclesFromFile(ElectricMobilityVehicle **head, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro %s\n", filename);
        return -1;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        // Extrai informações da linha;
        char *token = strtok(line, ";");
        int id = atoi(token);

        token = strtok(NULL, ";");
        char type[20];
        strcpy(type, token);

        token = strtok(NULL, ";");
        int battery = atoi(token);

        token = strtok(NULL, ";");
        float price = atof(token);

        token = strtok(NULL, "\n");
        char geocode[20];
        strcpy(geocode, token);

        // Verifica se já existe um veículo com o mesmo ID na lista ligada;
        ElectricMobilityVehicle *current = *head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                // Já existe um veículo com o mesmo ID, então o substitui;
                strcpy(current->type, type);
                current->battery = battery;
                current->price = price;
                strcpy(current->geocode, geocode);
                break;
            }
            current = current->next;
        }

        if (current == NULL)
        {
            // Não encontrou um veículo com o mesmo ID, então adiciona um novo nó à lista ligada
            ElectricMobilityVehicle *newVehicle = (ElectricMobilityVehicle *)malloc(sizeof(ElectricMobilityVehicle));
            newVehicle->id = id;
            strcpy(newVehicle->type, type);
            newVehicle->battery = battery;
            newVehicle->price = price;
            strcpy(newVehicle->geocode, geocode);
            newVehicle->next = *head;
            *head = newVehicle;
        }
    }

    fclose(fp);
    printf("Dados guardados: %s\n", filename);
    return 0;
}