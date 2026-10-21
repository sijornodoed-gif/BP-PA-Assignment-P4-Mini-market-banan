/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>

#define PRODUCT_COUNT 5
#define MEMBER_COUNT 2

typedef struct { char name[50]; int price; int stock; } Product;
typedef struct { char name[50]; int points; } Member;

void checkProduct(Product db[], int size) {
    printf("\n--- Product Catalog ---\n");
    for(int i=0; i<size; i++) {
        printf("%d. %s - Rp%d (Stock: %d)\n", i+1, db[i].name, db[i].price, db[i].stock);
    }
}
void checkMember(Member db[], int size) {
    printf("\n--- Member Data ---\n");
    for(int i=0; i<size; i++) {
        printf("%d. %s - Points: %d\n", i+1, db[i].name, db[i].points);
    }
}

// CHALLENGE 1: Admin function: price update!!!
void updatePrice(Product *p, int newPrice) {
    printf("\n[ADMIN] Price of %s changed: Rp%d -> Rp%d\n", p->name, p->price, newPrice);
    p->price = newPrice;
}

// CHALLENGE 3: buyProduct DISCOUNTS!!!!!!!
void buyProduct(Product *p, Member *m, int qty) {
    if (p->stock >= qty) {
        p->stock -= qty;
        int total = p->price * qty;
        printf("\n[TRANSACTION] %d %s Sold. Subtotal: Rp%d\n", qty, p->name, total);

        if (m != NULL && m->points >= 1000) {
            int discount = total / 10;
            total -= discount;
            m->points -= 1000;
            printf("  -> %s redeemed 1000 points! Discount: Rp%d | New total: Rp%d\n",
                   m->name, discount, total);
        }

        printf("  -> Total to pay: Rp%d\n", total);

        if (total >= 20000 && m != NULL) {
            m->points += 100;
            printf("  -> Member %s earned +100 Points!\n", m->name);
        }
    } else {
        printf("\n[FAILED] Stock for %s (Remaining: %d) is not enough to buy %d!\n", p->name, p->stock, qty);
    }
}

// --- BONUS ---

// Reads one integer safely. Returns 1 on success, 0 on invalid input (e.g. letters),
// -1 if the input stream has ended (EOF).
int readInt(int *out) {
    int result = scanf("%d", out);
    if (result == EOF) return -1;
    // Throw away anything left on the line (also clears bad input like "abc")
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return result == 1 ? 1 : 0;
}

void buyMenu(Product dbProduct[], Member dbMember[]) {
    int prodChoice, memberChoice, qty;

    checkProduct(dbProduct, PRODUCT_COUNT);
    printf("\nChoose product number (1-%d): ", PRODUCT_COUNT);
    if (readInt(&prodChoice) != 1 || prodChoice < 1 || prodChoice > PRODUCT_COUNT) {
        printf("[ERROR] Invalid product number!\n");
        return;
    }

    checkMember(dbMember, MEMBER_COUNT);
    printf("\nChoose member number (1-%d, or 0 for non-member): ", MEMBER_COUNT);
    if (readInt(&memberChoice) != 1 || memberChoice < 0 || memberChoice > MEMBER_COUNT) {
        printf("[ERROR] Invalid member number!\n");
        return;
    }

    printf("Quantity: ");
    if (readInt(&qty) != 1 || qty <= 0) {
        printf("[ERROR] Quantity must be a positive number!\n");
        return;
    }

    // Pass the ADDRESS of the chosen struct; NULL means non-member
    Product *p = &dbProduct[prodChoice - 1];
    Member *m = (memberChoice == 0) ? NULL : &dbMember[memberChoice - 1];
    buyProduct(p, m, qty);
}

void priceMenu(Product dbProduct[]) {
    int prodChoice, newPrice;

    checkProduct(dbProduct, PRODUCT_COUNT);
    printf("\nChoose product number to update (1-%d): ", PRODUCT_COUNT);
    if (readInt(&prodChoice) != 1 || prodChoice < 1 || prodChoice > PRODUCT_COUNT) {
        printf("[ERROR] Invalid product number!\n");
        return;
    }

    printf("New price (Rp): ");
    if (readInt(&newPrice) != 1 || newPrice <= 0) {
        printf("[ERROR] Price must be a positive number!\n");
        return;
    }

    updatePrice(&dbProduct[prodChoice - 1], newPrice);
}

int main() {
    // 1. Setup Database (Anisa has 1200 points so the redeem feature can be tested)
    Product dbProduct[PRODUCT_COUNT] = { {"Soap", 5000, 10}, {"Shampoo", 15000, 5}, {"Bread", 12000, 8}, {"Milk", 25000, 15}, {"Coffee", 22000, 20} };
    Member dbMember[MEMBER_COUNT] = { {"Anisa", 1200}, {"Budi", 100} };

    printf("=== WELCOME TO THE MINIMARKET ===\n");

    // 2. Interactive loop: repeats until the user chooses 4 (Exit)
    int choice;
    do {
        printf("\n==============================================================\n");
        printf("[1] View Products | [2] Buy Product | [3] Check Members | [4] Exit\n");
        printf("[5] Admin: Update Price\n");
        printf("==============================================================\n");
        printf("Your choice: ");

        int status = readInt(&choice);
        if (status == -1) {          // input ended (Ctrl+D / piped input finished)
            choice = 4;
        } else if (status == 0) {    // user typed letters, etc.
            choice = 0;
        }

        switch (choice) {
            case 1:
                checkProduct(dbProduct, PRODUCT_COUNT);
                break;
            case 2:
                buyMenu(dbProduct, dbMember);
                break;
            case 3:
                checkMember(dbMember, MEMBER_COUNT);
                break;
            case 4:
                printf("\nThank you for shopping! Goodbye.\n");
                break;               // leaves the switch; the while condition then ends the loop
            case 5:
                priceMenu(dbProduct);
                break;
            default:
                printf("\n[ERROR] Invalid menu choice, please try again!\n");
        }
    } while (choice != 4);

    return 0;
}




