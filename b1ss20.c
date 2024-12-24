#include <stdio.h>
#include <string.h>

typedef struct {
    char bookId[20];
    char title[50];
    char auth[50];
    float price;
    char category[50];
} Book;

void addBook(int n, Book book[]);
void showBook(int n, Book book[]);
void themBook(int *n, Book book[]);
void deleteBook(char *id, int *n, Book book[]);
void updateBook(char *id, int n, Book book[]);
void sortBooks(int n, Book book[], int ascending);
void searchBookByName(char *name, int n, Book book[]);

int main() {
    Book book[100];
    int menu;
    int n = 0;
    char id[20], name[50];

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (1: tang, 0: giam)\n");
        printf("7. Tim kiem sach theo ten\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &menu);
        getchar(); 

        switch (menu) {
            case 1:
                printf("Moi ban nhap vao so luong sach: ");
                scanf("%d", &n);
                getchar();
                addBook(n, book);
                break;
            case 2:
                printf("Thong tin sach la: \n");
                showBook(n, book);
                break;
            case 3:
                themBook(&n, book);
                break;
            case 4:
                printf("Moi ban nhap ma sach muon xoa: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0'; 
                deleteBook(id, &n, book);
                break;
            case 5:
                printf("Moi ban nhap ma sach can cap nhat: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0';
                updateBook(id, n, book);
                break;
            case 6:
                {
                    int ascending;
                    printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                    scanf("%d", &ascending);
                    sortBooks(n, book, ascending);
                    printf("Da sap xep xong.\n");
                }
                break;
            case 7:
                printf("Moi ban nhap ten sach can tim: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                searchBookByName(name, n, book);
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong co trong menu\n");
        }
    } while (menu != 8);

    return 0;
}

void addBook(int n, Book book[]) {
    for (int i = 0; i < n; i++) {
        printf("Moi ban nhap thong tin sach thu %d:\n", i + 1);
        printf("Ma Sach: ");
        fgets(book[i].bookId, sizeof(book[i].bookId), stdin);
        book[i].bookId[strcspn(book[i].bookId, "\n")] = '\0';

        printf("Ten Sach: ");
        fgets(book[i].title, sizeof(book[i].title), stdin);
        book[i].title[strcspn(book[i].title, "\n")] = '\0';

        printf("Ten Tac Gia: ");
        fgets(book[i].auth, sizeof(book[i].auth), stdin);
        book[i].auth[strcspn(book[i].auth, "\n")] = '\0';

        printf("Gia Tien: ");
        scanf("%f", &book[i].price);
        getchar();

        printf("The Loai: ");
        fgets(book[i].category, sizeof(book[i].category), stdin);
        book[i].category[strcspn(book[i].category, "\n")] = '\0';
    }
}

void showBook(int n, Book book[]) {
    for (int i = 0; i < n; i++) {
        printf("\nSACH %d\n", i + 1);
        printf("Ma Sach: %s\n", book[i].bookId);
        printf("Ten Sach: %s\n", book[i].title);
        printf("Tac Gia: %s\n", book[i].auth);
        printf("Gia Tien: %.2f\n", book[i].price);
        printf("The Loai: %s\n", book[i].category);
    }
}

void themBook(int *n, Book book[]) {
    int position;
    printf("Moi ban nhap vao vi tri can them: ");
    scanf("%d", &position);
    getchar();

    if (position < 1 || position > *n + 1) {
        printf("Vi tri khong hop le.\n");
        return;
    }

    for (int i = *n; i >= position; i--) {
        book[i] = book[i - 1];
    }

    (*n)++;
    printf("Moi ban nhap thong tin sach moi:\n");
    printf("Ma Sach: ");
    fgets(book[position - 1].bookId, sizeof(book[position - 1].bookId), stdin);
    book[position - 1].bookId[strcspn(book[position - 1].bookId, "\n")] = '\0';

    printf("Ten Sach: ");
    fgets(book[position - 1].title, sizeof(book[position - 1].title), stdin);
    book[position - 1].title[strcspn(book[position - 1].title, "\n")] = '\0';

    printf("Ten Tac Gia: ");
    fgets(book[position - 1].auth, sizeof(book[position - 1].auth), stdin);
    book[position - 1].auth[strcspn(book[position - 1].auth, "\n")] = '\0';

    printf("Gia Tien: ");
    scanf("%f", &book[position - 1].price);
    getchar();

    printf("The Loai: ");
    fgets(book[position - 1].category, sizeof(book[position - 1].category), stdin);
    book[position - 1].category[strcspn(book[position - 1].category, "\n")] = '\0';
}

void deleteBook(char *id, int *n, Book book[]) {
    int found = 0;

    for (int i = 0; i < *n; i++) {
        if (strcmp(book[i].bookId, id) == 0) {
            found = 1;
            for (int j = i; j < *n - 1; j++) {
                book[j] = book[j + 1];
            }
            (*n)--;
            printf("Xoa sach thanh cong.\n");
            break;
        }
    }

    if (!found) {
        printf("Khong tim thay sach voi ma \"%s\".\n", id);
    }
}

void updateBook(char *id, int n, Book book[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(book[i].bookId, id) == 0) {
            printf("Nhap thong tin moi cho sach:\n");
            printf("Ten Sach: ");
            fgets(book[i].title, sizeof(book[i].title), stdin);
            book[i].title[strcspn(book[i].title, "\n")] = '\0';

            printf("Ten Tac Gia: ");
            fgets(book[i].auth, sizeof(book[i].auth), stdin);
            book[i].auth[strcspn(book[i].auth, "\n")] = '\0';

            printf("Gia Tien: ");
            scanf("%f", &book[i].price);
            getchar();

            printf("The Loai: ");
            fgets(book[i].category, sizeof(book[i].category), stdin);
            book[i].category[strcspn(book[i].category, "\n")] = '\0';

            printf("Cap nhat thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sach voi ma \"%s\".\n", id);
}

void sortBooks(int n, Book book[], int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((ascending && book[i].price > book[j].price) ||
                (!ascending && book[i].price < book[j].price)) {
                Book temp = book[i];
                book[i] = book[j];
                book[j] = temp;
            }
        }
    }
}

void searchBookByName(char *name, int n, Book book[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(book[i].title, name) != NULL) {
            printf("\nMa Sach: %s\n", book[i].bookId);
            printf("Ten Sach: %s\n", book[i].title);
            printf("Tac Gia: %s\n", book[i].auth);
            printf("Gia Tien: %.2f\n", book[i].price);
            printf("The Loai: %s\n", book[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ten \"%s\".\n", name);
    }
}

