#ifndef ARCHIVE_H
#define ARCHIVE_H

#define MAX_VERTICES 100
#define MAX_VERTICES 100
#define INFINITY 9999

/*CODIGO TEMPORARIO APENAS PARA A FASE 1*/

// Estrutura do cliente
struct CustomerV2
{
    int id;
    char name[50];
    char password;
    int NIF;
    float balance;
    char address[100];
    char geocode[25];
    struct CustomerV2 *next;
};

// Estrutura do meio
typedef struct Mobility
{
    int id;
    char type[20];
    float battery;
    float autonomy;
    float price;
    char geocode[25];
    struct Mobility *next;
} Mobility;

// Estrutura do gestor
struct Admin
{
    int id;
    char name[20];
    char password[20];
    int active;
    struct Admin *next;
};

typedef struct GraphNode
{
    int id;
    char name[50];
    char type[50];
    char geocode[20];
    struct GraphNode *next;
} GraphNode;

typedef struct
{
    int distance;
    Mobility *mobility;
} MobilityDistance;

typedef struct
{
    int V;                                           // número de vértices
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; // matriz de adjacência
} Graph;

typedef struct CustomerV2 CustomerV2;

typedef struct Admin Admin;

typedef struct Mobility Mobility;

CustomerV2 *createCustomer(int id, char *name, char password, int NIF, float balance, char *address, char *geocode);

void insertCustomer(CustomerV2 **head, CustomerV2 *newCustomer);

int checkData(CustomerV2 *head);

int menuFase();

void insertMobility(Mobility **head);

void listMobility(Mobility *head);

CustomerV2 *findCustomer(CustomerV2 *head, int id);

void addBalance(CustomerV2 *head);

Mobility *findMobility(Mobility *head, int id);

void rentMobility(CustomerV2 *head1, Mobility *head2);

void updateMobility(Mobility *head2);

void deleteMobility(Mobility **head2);

Admin *createAdmin(int id, char *name, char *password, int active);

void insertAdmin(Admin **head, Admin *newAdmin);

void removeCustomer(CustomerV2 **head);

void removeAdmin(Admin **head);

void updateCustomer(CustomerV2 *head);

void updateAdmin(Admin **head);

// void listMobilityByAutonomy(Mobility *head2);

/*CODIGO TEMPORARIO APENAS PARA A FASE 1*/

void listMobility4geocode(Mobility *head2);

void listMobilityByAutonomy(Mobility *head2);

void listCustomer(CustomerV2 *head);

void listData(CustomerV2 *head, Mobility *head2);

void saveDataToFile(Mobility *head2, CustomerV2 *head);

void saveDataToFileBinary(Mobility *head2, CustomerV2 *head);

void insertDefaultMobility(Mobility **head2);

void addEdge(Graph *graph, int src, int dest);

Graph *buildGraph(CustomerV2 *customers, Mobility *mobility);

int *calculateDistancesBFS(Graph *graph, int source);

void listDataV2(CustomerV2 *head, Mobility *head2);

void listMobilityBelow50(Mobility *head2);

#endif // ARCHIVE_H
