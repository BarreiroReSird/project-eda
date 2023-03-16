#ifndef ARCHIVE_H
#define ARCHIVE_H

typedef struct ElectricMobilityVehicle
{
    int id;
    char type[20];
    int battery;
    
    float price;
    char geocode[20];
    struct ElectricMobilityVehicle *next;
} ElectricMobilityVehicle;
typedef struct
{
    int id;
    char name[50];
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
Manager *login(ManagerNode *head);
void addElectricMobilityVehicle(ElectricMobilityVehicle **head);

#endif // ARCHIVE_H