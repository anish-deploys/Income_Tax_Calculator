#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct taxpayer {
    int id;
    char name[50];
    float income;
    float tax;
};

int search_record(struct taxpayer records[], int num_records, int id) {
    for (int i = 0; i < num_records; i++) {
        if (records[i].id == id) {
            return i;
        }
    }
    return -1;
}

void add_record(struct taxpayer records[], int *num_records) {
    struct taxpayer new_record;
    printf("Enter ID: ");
    scanf("%d", &new_record.id);
    printf("Enter Name: ");
    fflush(stdin);
    fgets(new_record.name, 50, stdin);
    new_record.name[strcspn(new_record.name, "\n")] = 0; // remove trailing newline character
    printf("Enter Income: ");
    scanf("%f", &new_record.income);
    new_record.tax = 0.2 * new_record.income; // calculate tax based on income
    records[*num_records] = new_record;
    (*num_records)++;
    printf("Record added.\n");
}

void list_records(struct taxpayer records[], int num_records) {
    printf("ID\tName\t\tIncome\tTax\n");
    for (int i = 0; i < num_records; i++) {
        printf("%d\t%s\t%.2f\t%.2f\n", records[i].id, records[i].name, records[i].income, records[i].tax);
    }
}

void search_record_menu(struct taxpayer records[], int num_records) {
    int id;
    int index;
    printf("Enter the ID to search: ");
    scanf("%d", &id);
    index = search_record(records, num_records, id);
    if (index == -1) {
        printf("Record not found.\n");
    } else {
        printf("ID\tName\t\tIncome\tTax\n");
        printf("%d\t%s\t%.2f\t%.2f\n", records[index].id, records[index].name, records[index].income, records[index].tax);
    }
}

void edit_record(struct taxpayer records[], int num_records) {
    int id;
    int index;
    printf("Enter the ID to edit: ");
    scanf("%d", &id);
    index = search_record(records, num_records, id);
    if (index == -1) {
        printf("Record not found.\n");
    } else {
        printf("Enter new Name (or press enter to keep current value '%s'): ", records[index].name);
        fflush(stdin);
        fgets(records[index].name, 50, stdin);
        records[index].name[strcspn(records[index].name, "\n")] = 0; // remove trailing newline character
        printf("Enter new Income (or press enter to keep current value '%.2f'): ", records[index].income);
        fflush(stdin);
        char income_str[10];
        fgets(income_str, 10, stdin);
        if (income_str[0] != '\n') {
            sscanf(income_str, "%f", &records[index].income);
            records[index].tax = 0.2 * records[index].income; // update tax based on new income
        }
        printf("Record updated.\n");
    }
}

void delete_record(struct taxpayer records[], int *num_records){
    int id;
    int index;
    printf("Enter the ID to delete: ");
    scanf("%d", &id);
    index = search_record(records, *num_records, id);
    if (index == -1) {
        printf("Record not found.\n");
    } else {
        printf("Are you sure you want to delete this record? (Y/N): ");
        char confirmation;
        fflush(stdin);
        scanf("%c", &confirmation);
        if (confirmation == 'Y' || confirmation == 'y') {
            for (int i = index; i < *num_records - 1; i++) {
                records[i] = records[i + 1]; // shift all records after the deleted record one position to the left
            }
            (*num_records)--;
            printf("Record deleted.\n");
        } else {
            printf("Record deletion cancelled.\n");
        }
    }
}


int main() {
	struct taxpayer records[100];
	int num_records = 0;
	int choice;	
	do {
    printf("1. Add New Record\n");
    printf("2. List All Records\n");
    printf("3. Search Record\n");
    printf("4. Edit Record\n");
    printf("5. Delete Record\n");
    printf("6. Quit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add_record(records, &num_records);
            break;
        case 2:
            list_records(records, num_records);
            break;
        case 3:
            search_record_menu(records, num_records);
            break;
        case 4:
            edit_record(records, num_records);
            break;
        case 5:
            delete_record(records, &num_records);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice.\n");
    }

    printf("\n");
} while (choice != 6);

return 0;
}
