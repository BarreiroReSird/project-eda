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

#endif // ARCHIVE_H