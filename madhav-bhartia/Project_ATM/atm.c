#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Atm Functionalities:(add_acc, delete_acc),(auth),(chk_bal, deposit, withdraw).
int createFileIfNotExists();
int addAcc(int accNum, int pin, float initBal);
int delAcc(int accNum, int pin);
bool isAuth(int accNum, int pin);
float chkBal(int accNum);
float deposit(int accNum, float amt);
float withdraw(int accNum, float amt);

int main(){
    if(createFileIfNotExists() == -1){
        return -1;
    }
    int choice = 0, accNum = 0, pin = 0;
    float amount = 0.0f, balance = 0.0f;
    printf("Welcome to the ATM System\n");
    do{
        printf("1. Add Account\n2. Delete Account\n3. Authenticate\n9. Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printf("Enter PIN: ");
                scanf("%d", &pin);
                printf("Enter Initial Balance: ");
                scanf("%f", &amount);
                int res = addAcc(accNum, pin, amount);
                if(res == 0){
                    printf("Account added successfully!\n");
                } else if(res == 1){
                    printf("Account already exists\n");
                } else {
                    printf("Failed to add account.\n");
                }
                break;
            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printf("Enter PIN: ");
                scanf("%d", &pin);
                if(delAcc(accNum, pin) == 0){
                    printf("Account deleted successfully!\n");
                } else {
                    printf("Failed to delete account.\n");
                }
                break;
            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &accNum);
                printf("Enter PIN: ");
                scanf("%d", &pin);
                if(isAuth(accNum, pin)){
                    printf("Authentication successful!\n");
                    do{
                        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Go Back\n");
                        scanf("%d", &choice);
                        switch(choice){
                            case 1:
                                balance = chkBal(accNum);
                                if(balance != -1){
                                    printf("Current Balance: %.2f\n", balance);
                                } else {
                                    printf("Account not found.\n");
                                }
                                break;
                            case 2:
                                printf("Enter Amount to Deposit: ");
                                scanf("%f", &amount);
                                balance = deposit(accNum, amount);
                                if(balance != -1){
                                    printf("New Balance after deposit: %.2f\n", balance);
                                } else {
                                    printf("Deposit failed. Account not found.\n");
                                }
                                break;
                            case 3:
                                printf("Enter Amount to Withdraw: ");
                                scanf("%f", &amount);
                                balance = withdraw(accNum, amount);
                                if(balance != -1){
                                    printf("New Balance after withdrawal: %.2f\n", balance);
                                } else {
                                    printf("Withdrawal failed. Insufficient funds or account not found.\n");
                                }
                                break;
                            case 4:
                                printf("Going back...\n");
                                break;
                            default:
                                printf("Invalid choice\n");
                                break;
                        }
                    } while(choice != 4);
                } else {
                    printf("Authentication failed!\n");
                }                       
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        } 
    } while(choice != 9); 
    return 0;
}


int createFileIfNotExists(){
    FILE *pFile = fopen("accounts.csv", "r");
    if(pFile == NULL){
        pFile = fopen("accounts.csv", "w");
        if(pFile == NULL){
            printf("Error creating file!\n");
            return -1;
        }
    }
    fclose(pFile);
    return 0;
}



int addAcc(int accNum, int pin, float initBal){
    FILE *pFile = fopen("accounts.csv", "r");
    if(pFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char line[100];
    bool found = false;
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum){
            found = true;
            break;
        }
    }
    fclose(pFile);
    if(found){
        return 1;
    }

    pFile = fopen("accounts.csv", "a");
    if(pFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    fprintf(pFile, "%d,%d,%.2f\n", accNum, pin, initBal);
    fclose(pFile);
    return 0;
}

int delAcc(int accNum, int pin){
    FILE *pFile = fopen("accounts.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if(pFile == NULL || tempFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char line[100];
    bool found = false;
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum && p == pin){
            found = true;
            continue; // Skip writing this line to delete the account
        }
        fputs(line, tempFile);
    }
    fclose(pFile);
    fclose(tempFile);
    remove("accounts.csv");
    rename("temp.csv", "accounts.csv");
    return found ? 0 : -1;
}

bool isAuth(int accNum, int pin){
    FILE *pFile = fopen("accounts.csv", "r");
    if(pFile == NULL){
        printf("Error opening file!\n");
        return false;
    }
    char line[100];
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum && p == pin){
            fclose(pFile);
            return true;
        }
    }
    fclose(pFile);
    return false;
}

float chkBal(int accNum){
    FILE *pFile = fopen("accounts.csv", "r");
    if(pFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char line[100];
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum){
            fclose(pFile);
            return bal;
        }
    }
    fclose(pFile);
    return -1;
}

float deposit(int accNum, float amt){
    FILE *pFile = fopen("accounts.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if(pFile == NULL || tempFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char line[100];
    bool found = false;
    float new_bal = -1;
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum){
            bal += amt;
            new_bal = bal;
            found = true;
        }
        fprintf(tempFile, "%d,%d,%.2f\n", acc, p, bal);
    }
    fclose(pFile);
    fclose(tempFile);
    remove("accounts.csv");
    rename("temp.csv", "accounts.csv");
    return found ? new_bal : -1;
}

float withdraw(int accNum, float amt){
    FILE *pFile = fopen("accounts.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if(pFile == NULL || tempFile == NULL){
        printf("Error opening file!\n");
        return -1;
    }
    char line[100];
    bool found = false;
    float new_bal = -1;
    while(fgets(line, sizeof(line), pFile)){
        int acc, p;
        float bal;
        sscanf(line, "%d,%d,%f", &acc, &p, &bal);
        if(acc == accNum){
            if(bal >= amt){
                bal -= amt;
                new_bal = bal;
                found = true;
            } else {
                fclose(pFile);
                fclose(tempFile);
                remove("temp.csv");
                return -1;
            }
        }
        fprintf(tempFile, "%d,%d,%.2f\n", acc, p, bal);
    }
    fclose(pFile);
    fclose(tempFile);
    remove("accounts.csv");
    rename("temp.csv", "accounts.csv");
    return found ? new_bal : -1;
}