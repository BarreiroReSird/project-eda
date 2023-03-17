#ifndef ARCHIVE_H
#define ARCHIVE_H

typedef struct ElectricMobilityVehicle
{
    int id;
    char type[20];
    float battery;
    float autonomy;
    float price;
    char geocode[20];
    struct ElectricMobilityVehicle *next;
} ElectricMobilityVehicle;

typedef struct
{
    int id;
    char name[50];
    char password;
    char address[100];
    char nif[9];
    float balance;
} Customer;
typedef struct
{
    int id;
    char name[50];
    char password[20];
    int active;
} Manager;

typedef struct ManagerNode
{
    Manager manager;
    struct ManagerNode *next;
} ManagerNode;

void menuArea();
void menuSignIn();
void menuVehicles();
void registerManager(ManagerNode **head);
Manager *loginManager(ManagerNode *head);
void registerCustomer();
void loginCustomer();
void addElectricMobilityVehicle(ElectricMobilityVehicle **head);
void listElectricMobilityVehicles(ElectricMobilityVehicle *head);
void removeElectricMobilityVehicle(ElectricMobilityVehicle **head);
int saveElectricMobilityVehiclesToFile(ElectricMobilityVehicle *head);
int loadElectricMobilityVehiclesFromFile(ElectricMobilityVehicle **head, const char *filename);

/*CODIGO TEMPORARIO APENAS PARA A FASE 1*/
struct CustomerV2
{
    int id;
    char name[50];
    char password;
    int NIF;
    float balance;
    char address[100];
    struct CustomerV2 *next;
};

typedef struct Mobility
{
    int id;
    char type[20];
    float battery;
    float autonomy;
    float price;
    char geocode[20];
    struct Mobility *next;
} Mobility;

typedef struct CustomerV2 CustomerV2;

CustomerV2 *createCustomer(int id, char *name, char password, int NIF, float balance, char *address);

void insertCustomer(CustomerV2 **head, CustomerV2 *newCustomer);

void printList(CustomerV2 *head);

int checkData(CustomerV2 *head);

int menuFase1();

void insertMobility(Mobility **head);

void listMobility(Mobility *head);

CustomerV2 *findCustomer(CustomerV2 *head, int id);

void addBalance(CustomerV2 *head);

Mobility *findMobility(Mobility *head, int id);

void rentMobility(CustomerV2 *head1, Mobility *head2);

void updateMobility(Mobility *head2);
/*CODIGO TEMPORARIO APENAS PARA A FASE 1*/

#endif // ARCHIVE_H