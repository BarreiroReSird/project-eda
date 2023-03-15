#ifndef ARCHIVE_H
#define ARCHIVE_H

#define MAX_USERS 100

typedef struct
{
    int id;
    char name[50];
    char password[50];
    float balance;
    char address[100];
    int NIF;
    int active;
} Customer;

typedef struct
{
    int id;
    char name[50];
    char password[50];
    int active;
} Manager;

typedef struct
{
    int id;
    int code;
    char type[50];
    float battery;
    float autonomy;
} Vehicle;

int menuVehicle();
int menuArea();
int menuRegLog();
void registerManager();
void loginManager();
void registerCustomer();
void loginCustomer();
void addVehicle();
void listVehicles();
void removeVehicle();

#endif // ARCHIVE_H
