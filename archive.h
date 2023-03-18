#ifndef ARCHIVE_H
#define ARCHIVE_H

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

struct Admin
{
    int id;
    char name[20];
    char password[20];
    int active;
    struct Admin *next;
};

typedef struct CustomerV2 CustomerV2;

typedef struct Admin Admin;

CustomerV2 *createCustomer(int id, char *name, char password, int NIF, float balance, char *address);

void insertCustomer(CustomerV2 **head, CustomerV2 *newCustomer);

int checkData(CustomerV2 *head);

int menuFase1();

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

void listMobilityByAutonomy(Mobility *head2);
/*CODIGO TEMPORARIO APENAS PARA A FASE 1*/

#endif // ARCHIVE_H