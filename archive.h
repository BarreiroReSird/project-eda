#ifndef ARCHIVE_H_INCLUDED
#define ARCHIVE_H_INCLUDED

#define MAX_USERS 100

typedef struct {
    int id;
    char name[50];
    char password[50];
    float balance;
    char address[100];
    int NIF;
    int active;
} Customer;

typedef struct {
    int id;
    char name[50];
    char password[50];
    int active;
} Manager;

void registerCustomer();
void loginCustomer();
void registerManager();
void loginManager();

#endif // ARCHIVE_H_INCLUDED
