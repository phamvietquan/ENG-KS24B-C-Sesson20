#include <stdio.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    float importPrice;
    float sellingPrice;
    int quantity;
} Product;

void addProduct(int *n, Product products[], float *revenue);
void showProducts(int n, Product products[]);
void importProduct(int n, Product products[], float *revenue);
void updateProduct(int n, Product products[]);
void sortProducts(int n, Product products[], int ascending);
void searchProduct(int n, Product products[]);
void sellProduct(int n, Product products[], float *revenue);

int main() {
    Product products[100];
    int n = 0;
    float revenue = 0;
    int menu;

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &menu);
        getchar();

        switch (menu) {
        case 1:
            addProduct(&n, products, &revenue);
            break;
        case 2:
            showProducts(n, products);
            break;
        case 3:
            importProduct(n, products, &revenue);
            break;
        case 4:
            updateProduct(n, products);
            break;
        case 5:
            {
                int ascending;
                printf("Nhap 1 de sap xep tang dan, 0 de sap xep giam dan: ");
                scanf("%d", &ascending);
                sortProducts(n, products, ascending);
            }
            break;
        case 6:
            searchProduct(n, products);
            break;
        case 7:
            sellProduct(n, products, &revenue);
            break;
        case 8:
            printf("Doanh thu hien tai: %.2f\n", revenue);
            break;
        case 9:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (menu != 9);

    return 0;
}

void addProduct(int *n, Product products[], float *revenue) {
    int count;
    printf("Nhap so luong san pham: ");
    scanf("%d", &count);
    getchar();

    for (int i = 0; i < count; i++) {
        printf("Nhap thong tin san pham %d:\n", i + 1);
        printf("Ma san pham: ");
        fgets(products[*n].id, sizeof(products[*n].id), stdin);
        products[*n].id[strcspn(products[*n].id, "\n")] = '\0';

        printf("Ten san pham: ");
        fgets(products[*n].name, sizeof(products[*n].name), stdin);
        products[*n].name[strcspn(products[*n].name, "\n")] = '\0';

        printf("Gia nhap: ");
        scanf("%f", &products[*n].importPrice);
        getchar();

        printf("Gia ban: ");
        scanf("%f", &products[*n].sellingPrice);
        getchar();

        printf("So luong: ");
        scanf("%d", &products[*n].quantity);
        getchar();

        *revenue -= products[*n].importPrice * products[*n].quantity;
        (*n)++;
    }
}

void showProducts(int n, Product products[]) {
    printf("\nDanh sach san pham:\n");
    for (int i = 0; i < n; i++) {
        printf("Ma: %s, Ten: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
               products[i].id, products[i].name, products[i].importPrice, products[i].sellingPrice, products[i].quantity);
    }
}

void importProduct(int n, Product products[], float *revenue) {
    char id[20];
    int quantity;

    printf("Nhap ma san pham can them: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Nhap so luong can them: ");
            scanf("%d", &quantity);
            getchar();

            products[i].quantity += quantity;
            *revenue -= products[i].importPrice * quantity;
            return;
        }
    }

    printf("San pham khong ton tai.\n");
}

void updateProduct(int n, Product products[]) {
    char id[20];
    printf("Nhap ma san pham can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Cap nhat thong tin san pham:\n");
            printf("Ten san pham: ");
            fgets(products[i].name, sizeof(products[i].name), stdin);
            products[i].name[strcspn(products[i].name, "\n")] = '\0';

            printf("Gia nhap: ");
            scanf("%f", &products[i].importPrice);
            getchar();

            printf("Gia ban: ");
            scanf("%f", &products[i].sellingPrice);
            getchar();

            printf("So luong: ");
            scanf("%d", &products[i].quantity);
            getchar();
            return;
        }
    }

    printf("San pham khong ton tai.\n");
}

void sortProducts(int n, Product products[], int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((ascending && products[i].sellingPrice > products[j].sellingPrice) ||
                (!ascending && products[i].sellingPrice < products[j].sellingPrice)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

void searchProduct(int n, Product products[]) {
    char name[50];
    printf("Nhap ten san pham can tim: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strstr(products[i].name, name) != NULL) {
            printf("Ma: %s, Ten: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
                   products[i].id, products[i].name, products[i].importPrice, products[i].sellingPrice, products[i].quantity);
        }
    }
}

void sellProduct(int n, Product products[], float *revenue) {
    char id[20];
    int quantity;

    printf("Nhap ma san pham can ban: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Nhap so luong can ban: ");
            scanf("%d", &quantity);
            getchar();

            if (products[i].quantity == 0) {
                printf("San pham da het hang.\n");
            } else if (products[i].quantity < quantity) {
                printf("Khong du so luong hang.\n");
            } else {
                products[i].quantity -= quantity;
                *revenue += products[i].sellingPrice * quantity;
                printf("Ban thanh cong.\n");
            }
            return;
        }
    }

    printf("San pham khong ton tai.\n");
}

