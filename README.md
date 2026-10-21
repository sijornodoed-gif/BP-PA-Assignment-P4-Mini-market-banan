# BP-PA-Assignment-P4-Mini-market-banan

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
