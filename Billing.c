#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_ITEMS 10
#define TAX_RATE 0.05 
typedef struct {
    char customer_id[20];
    char name[50];
    char mobile_number[15];
} Customer;
typedef struct {
    char item_name[30];
    float price;
    int quantity;
} Item;
int validate_customer_id(char *id) {
    for (int i = 0; id[i] != '\0'; i++) {
        if (!isdigit(id[i])) return 0;
    }
    return 1;
}
int validate_mobile_number(char *mobile) {
    if (strlen(mobile) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(mobile[i])) return 0;
    }
    return 1;
}
float calculate_bill(Item items[], int item_count) {
    float total = 0.0;
    for (int i = 0; i < item_count; i++) {
        total += items[i].price * items[i].quantity;
    }
    return total;
}
float calculate_tax(float total) {
    return total * TAX_RATE;
}
void display_bill(Customer customer, Item items[], int item_count, float total_bill, float tax_amount) {
    printf("\n--- Grocery Bill ---\n");
    printf("Customer ID: %s\n", customer.customer_id);
    printf("Customer Name: %s\n", customer.name);
    printf("Mobile Number: %s\n", customer.mobile_number);
    printf("\nItems Purchased:\n");
    for (int i = 0; i < item_count; i++) {
        printf("%s (Price: ₹%.2f, Quantity: %d)\n", items[i].item_name, items[i].price, items[i].quantity);
    }
    printf("\nTotal Bill Amount (before tax): ₹%.2f\n", total_bill);
    printf("Tax Amount (5%%): ₹%.2f\n", tax_amount);
    printf("Total Bill Amount (after tax): ₹%.2f\n", total_bill + tax_amount);
    printf("--------------------------\n");
}
int validate_price(char *input, float *price) {
    char *endptr;
    *price = strtof(input, &endptr);
    return *endptr == '\0' && *price >= 0;
}
int validate_quantity(char *input, int *quantity) {
    char *endptr;
    *quantity = strtol(input, &endptr, 10);
    return *endptr == '\0' && *quantity > 0;
}
int main() {
    Customer customer;
    Item items[MAX_ITEMS];
    int item_count;
    do {
        printf("Enter Customer ID (numeric only): ");
        scanf("%s", customer.customer_id);
        if (!validate_customer_id(customer.customer_id)) {
            printf("Invalid input! Please enter a valid customer ID.\n");
        }
    } while (!validate_customer_id(customer.customer_id));
    printf("Enter Customer Name: ");
    scanf(" %[^\n]%*c", customer.name);
     do {
        printf("Enter Mobile Number (10 digits): ");
        scanf("%s", customer.mobile_number);
        if (!validate_mobile_number(customer.mobile_number)) {
            printf("Invalid input! Please enter a correct mobile number.\n");
        }
    } while (!validate_mobile_number(customer.mobile_number));
    do {
        printf("Enter number of items purchased (max %d): ", MAX_ITEMS);
        scanf("%d", &item_count);
        if (item_count < 1 || item_count > MAX_ITEMS) {
            printf("Invalid input! Please enter a number between 1 and %d.\n", MAX_ITEMS);
        }
    } while (item_count < 1 || item_count > MAX_ITEMS);
    for (int i = 0; i < item_count; i++) {
        printf("Enter item %d name: ", i + 1);
        scanf(" %[^\n]%*c", items[i].item_name);
        char price_input[20];
        while (1) {
            printf("Enter price of %s: ", items[i].item_name);
            scanf("%s", price_input);
            if (validate_price(price_input, &items[i].price)) {
                break; 
            } else {
                printf("Invalid input! Please enter a valid price.\n");
            }
        }
         char quantity_input[20];
        while (1) {
            printf("Enter quantity of %s: ", items[i].item_name);
            scanf("%s", quantity_input);
            if (validate_quantity(quantity_input, &items[i].quantity)) {
                break; 
            } else {
                printf("Invalid input! Please enter a valid quantity.\n");
            }
        }
    }
    float total_bill = calculate_bill(items, item_count);
    float tax_amount = calculate_tax(total_bill);
    display_bill(customer, items, item_count, total_bill, tax_amount);
    return 0;
}