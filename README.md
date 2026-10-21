# BP-PA-Assignment-P4-Mini-market-banan

## MINI-CHALLENGES 1 - 6:

```c
#include <stdio.h>

int main() {
    int number = 10;
    // ptrNumber stores the address of 'number'. Use the & (Reference) symbol.
    int *ptrNumber = &number; 

    printf("Initial number value: %d\n", number);
    printf("Memory address of number: %p\n", &number);
    
    // Using the * (Dereference) symbol to view its value
    printf("Value pointed to by ptrNumber: %d\n", *ptrNumber);

    // Changing the value directly in its original memory via pointer
    *ptrNumber = 25;
    printf("\nNumber value after being changed via pointer: %d\n", number);

    // --- Pointers and Arrays ---
    int arr[3] = {100, 200, 300};
    // The array name itself represents the address of the first element, so no & is needed
    int *ptrArr = arr; 
    printf("\nFirst element of array: %d\n", *ptrArr);
    printf("Second element of array: %d\n", *(ptrArr + 1));
    

    // 🎯 TODO MINI-CHALLENGE 1:
    // Try to change the value of the THIRD array element (the number 300) to 999 using the ptrArr pointer!
    // Write your code below and print the result:
    *(ptrArr + 2) = 999;
    printf("Third element of array: %d\n", *(ptrArr + 2));
    
    return 0;
}
```
```c
#include <stdio.h>

// Pass by Value (Only sends a photocopy / copy of the data)
void addValue(int x) {
    x = x + 10;
}

// Pass by Reference (Sends the access key to the original address)
void addReference(int *x) {
    *x = *x + 10;
}

void subtractReference(int *x){
    *x = *x - 2;
}

int main() {
    int score1 = 5;
    int score2 = 5;

    addValue(score1);
    printf("After Pass by Value: %d (BE CHANGED)\n", score1);

    // Must use & to send its address
    addReference(&score2); 
    printf("After Pass by Reference: %d (CHANGED!)\n", score2);

    // 🎯 TODO MINI-CHALLENGE 2:
    // 1. Create a new function called 'subtractReference(int *x)' above int main().
    // 2. Make the function subtract the value by 2.
    // 3. Call the function to reduce score2, then print the result!
    
    subtractReference(&score2);
    printf("Skibidi trying: %d (BAWAW!!!)\n", score2);

    return 0;
}
```
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char nama[50];
    int umur;
    float ipk;
    // 🎯 TODO MINI-CHALLENGE 3 (Bagian 1):
    // Tambahkan atribut baru yaitu 'IPK' dengan tipe data float di sini!
} Mahasiswa;

int main() {
    Mahasiswa mhs1;
    
    // Ingat! Tipe data char array tidak bisa diisi pakai tanda = (sama dengan).
    // Kita WAJIB menggunakan strcpy (String Copy)
    strcpy(mhs1.nama, "Budi Santoso"); 
    mhs1.umur = 20;
    mhs1.ipk = 3.85;
    
    // 🎯 TODO MINI-CHALLENGE 3 (Bagian 2):
    // Berikan nilai IPK (misal: 3.85) untuk mhs1, lalu print bersama nama dan umurnya!

    printf("Nama: %s, Umur: %d, IPK: %.2f\n", mhs1.nama, mhs1.umur, mhs1.ipk);
    return 0;
}
```
```c
#include <stdio.h>
#include <string.h>

typedef struct {
	char namaJalan[50];
	int kodePos;
} Alamat;

typedef struct {
	char nama[50];
	Alamat rumah; // Memasukkan struct Alamat ke dalam struct Karyawan
} Karyawan;

int main() {
	Karyawan k1;
	strcpy(k1.nama, "Anisa");
	strcpy(k1.rumah.namaJalan, "Jl. Raya ITS");
	k1.rumah.kodePos = 60115;

	printf("%s tinggal di %s (%d)\n", k1.nama, k1.rumah.namaJalan, k1.rumah.kodePos);

	// 🎯 TODO MINI-CHALLENGE 4:
	// Coba ubah kodePos rumah Anisa menjadi 60115, lalu print ulang kalimat di atas!

	return 0;
}
```
// Slight hiccup there!
```c
#include <stdio.h>

typedef struct {
    int id;
    int score;
} ExamData;

int main() {
    // Instant initialization for an array of structs
    ExamData classData[3] = {
        {101, 85},
        {102, 90},
        {103, 78}
    };
    
    int totalScore = 0;
    for(int i = 0; i < 3; i++) {
        totalScore = totalScore + classData[i].score;
    }
    
    // i = 0, totalScore = 0 + 85
    // i = 1, totalScore = 85 + 90
    // i = 2, totalScore = 175 + 78
    // i stops before 3 as per condition. So totalScore = 253
    
    printf("The average score is: %d", totalScore);

    // 🎯 TODO MINI-CHALLENGE 5:
    // Create a 'totalScore' variable, then loop through the 'classData' array to sum all the scores.
    // After the loop finishes, print the average score!

    return 0;
}
```
```c
#include <stdio.h>
#include <string.h>

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
void buyProduct(Product *p, Member *m, int qty) {
    if (p->stock >= qty) {
        p->stock -= qty;
        int total = p->price * qty;
        printf("\n[TRANSACTION] %d %s Sold. Total: Rp%d\n", qty, p->name, total);
        if (total >= 20000 && m != NULL) {
            m->points += 100;
            printf("  -> Member %s earned +100 Points!\n", m->name);
        }
    } else {
        printf("\n[FAILED] Stock for %s (Remaining: %d) is not enough to buy %d!\n", p->name, p->stock, qty);
    }
}

int main() {
    // 1. Setup Database
    Product dbProduct[5] = { {"Soap", 5000, 10}, {"Shampoo", 15000, 5}, {"Bread", 12000, 8}, {"Milk", 25000, 15}, {"Coffee", 22000, 20} };
    Member dbMember[2] = { {"Anisa", 500}, {"Budi", 100} };

    printf("=== WELCOME TO THE MINIMARKET ===\n");
    checkProduct(dbProduct, 5);
    checkMember(dbMember, 2);

    // 2. Transaction Simulation
    // REMEMBER! Use the & (Reference) symbol to pass the struct address from the array!
    buyProduct(&dbProduct[3], &dbMember[1], 2); // Budi buys 2 Milk (50k) -> Gets points
    buyProduct(&dbProduct[0], &dbMember[0], 1); // Anisa buys 1 Soap (5k) -> No points
    buyProduct(&dbProduct[2], NULL, 3);         // Non-member buyer buys 3 Bread (36k)
    buyProduct(&dbProduct[1], &dbMember[1], 10); // Budi buying 10 Shampoos?!

    // 🎯 TODO MINI-CHALLENGE 6:
    // Try simulating Budi buying 10 "Shampoo" below (It will definitely fail because stock is only 5).


    // 3. Prove that the data has been modified
    printf("\n=== DATA UPDATE AFTER TRANSACTIONS ===");
    checkProduct(dbProduct, 5);
    checkMember(dbMember, 2);

    return 0;
}
```


## Mandatory 1: Update Product Price

```c
void updatePrice(Product *p, int newPrice) {
    p->price = newPrice;  // modifies the original struct via pointer ->
}
```

Called with `updatePrice(&dbProduct[i], newPrice)`, so the change is permanent in the array.

## Mandatory 3: Points >= 1000 = 10% Off

Inside `buyProduct()`:

- If the member has >= 1000 points → 10% discount off the total
- Deduct 1000 points from the member
- Still give +100 points if the (discounted) total is >= Rp20,000
- Only applies when the purchase succeeds (stock is enough)

## Bonus: Interactive Menu (CLI Looping)

- Loop with `do { ... } while (choice != 4);`
- Shows the menu every iteration and uses `switch-case`:
  - `[1]` View Products
  - `[2]` Buy Product
  - `[3]` Check Members
  - `[4]` Exit
  - `[5]` Admin: Update Price
- `readInt()` safely reads input, so typing letters doesn't break the program

## Important codes to keep in mind...!!!

| Line | Concept |
|------|---------|
| `typedef struct` | Creates a type alias for the struct so the code is shorter |
| `#define PRODUCT_COUNT 5` | Named constant; change the size in one place |
| `buyProduct(&dbProduct[i], m, qty)` | **Reference operator (`&`)** passes the struct's address to a pointer parameter |
| `p->stock -= qty` | **Arrow operator (`->`)** accesses and modifies the struct through a pointer |
| `m != NULL && m->points >= 1000` | NULL check comes first, because a non-member is passed as `NULL` |
| `m->points -= 1000` | Deducts the redeemed points from the original member data |
| `if (total >= 20000 && m != NULL)` | Earns +100 points based on the total after discount |
| `Member *m = (choice == 0) ? NULL : &dbMember[choice-1]` | Picks the member's address, or NULL for a non-member |
| `do { ... } while (choice != 4)` | Repeats the menu until the user chooses Exit |


## SCREENSHOTS...!!!

<img width="1853" height="923" alt="Screenshot 2026-10-22 003739" src="https://github.com/user-attachments/assets/495c2fe8-40b5-4e88-adb6-9c1d6a015b05" />
<img width="1854" height="867" alt="Screenshot 2026-10-22 003807" src="https://github.com/user-attachments/assets/8aef1a85-9a4a-4ecf-be78-187843f66802" />

