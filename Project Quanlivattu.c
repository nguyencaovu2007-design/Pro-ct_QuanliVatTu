//
// Created by Nguyen on 27/11/25.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_S 100
#include <math.h>
#include <stdlib.h>
#include <tgmath.h>

typedef struct Material {
    char matID[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
    char category[20];
}Material;
typedef struct Transaction {
    char transID[20];    // ma giao dich
    char matID[10];     // ma vat tu
    char type[5];
    char date[15];       // thoi gian giao dich
}Transaction;
void clearbuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// ========== kiem tra dieu kien cua ID ========
int isValidMaterial(char *id) {
    id[strcspn(id,"\n")] = '\0';
    if (strlen(id) != 5) return 0;
    if (strlen(id) == 0) return 0;
    if (id[0] == ' ' || id[0] == '-' || id[0] == '*' || id[0] == '_' || id[0] == '!' || id[0] == '@') return 0;
    if (id[0] == '#' || id[0] == '^' || id[0] == '&' || id[0] == '&') return 0;
    return 1;
}
// ======== Kiem Tra so nguyen nhap vao
int inputIntRange(int min, int max) {
    int x;
    while (1) {
        if (scanf("%d",&x) != 1) {
            printf("Khong hop le, vui long nhap lai!");
            clearbuffer();
            continue;
        }
        if (x < min || x > max) {
            printf("Chi duoc nhap tu [%d -> %d]",min,max);
            continue;
        }
        clearbuffer();
        return x;
    }
}
// ============= kiem tra ID co trung nhau hay khongg
int isDuplicateMaterial(Material *list, int count, char *id) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(list[i].matID,id) == 0)
            return 1;
    }
    return 0;
}
void menu() {
    printf("\n====== Quan Li Vat Tu ======\n");
    printf("1.Them ma hang moi\n");
    printf("2.Cap nhap thong tin\n");
    printf("3.Quan li trang thai\n");
    printf("4.Tim kiem tra cuu\n");
    printf("5.Danh sach vat tu\n");
    printf("6.Sap xep danh sach\n");
    printf("7.Giao dich\n");
    printf("8.Lich su nhap xuat\n");
    printf("0.Thoat\n");
    printf("=========================\n");
}
//        Nhap vat tu
void inputMaterial(Material *material, int materialCount, Material *list) {
    while (1) {
        printf("Nhap ID cua vat tu: ");
        fgets(material->matID, sizeof(material->matID), stdin);
        material->matID[strcspn(material->matID, "\n")] = '\0';

        if (!isValidMaterial(material->matID)) {
            printf("ID khong hop le, moi nhap lai!\n");        // Dieu kien cua ID
            continue;
        }
        if (isDuplicateMaterial(list, materialCount, material->matID)) {
            printf("ID da ton tai, moi nhap lai!\n");          // Tranh ID nhap vao bi trung lap
            continue;
        }
        break;
    }

    printf("Nhap vao ten san pham: ");
    fgets(material->name, sizeof(material->name), stdin);          // Doan nay nhap Name
    material->name[strcspn(material->name, "\n")] = '\0';

    printf("Nhap vao don vi vat tu: ");
    fgets(material->unit, sizeof(material->unit), stdin);
    material->unit[strcspn(material->unit, "\n")] = '\0';       // Nhap Don vi cho san pham ( Kg, Gam)
    printf("Nhap vao so luong vat tu: ");
    material->qty = inputIntRange(0, 100000000);       // gioi han so luong cho vat
    printf("Chon category:\n1. Do gia dung\n2. Do dien tu\n3. Do thiet yeu\nLua chon: ");
    int catChoice = inputIntRange(1,3);
    switch(catChoice){
        case 1: strcpy(material->category,"Do gia dung"); break;
        case 2: strcpy(material->category,"Do dien tu"); break;
        case 3: strcpy(material->category,"Do thiet yeu"); break;
    }
    material->status = 1;

    printf("Da them vat tu thanh cong, voi ma %s!\n", material->matID);
}
void updateMaterial(Material *list, int count) {
    char id[10];
    printf("Nhap ID can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].matID, id) == 0) {     // so sánh ID(i) với id mới nhập có trùng nhau không
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Khong tim thay ID!\n");
        return;
    }
    printf("Nhap ten moi: ");
    fgets(list[index].name, sizeof(list[index].name), stdin);
    list[index].name[strcspn(list[index].name, "\n")] = '\0';
    printf("Nhap don vi moi: ");
    fgets(list[index].unit, sizeof(list[index].unit), stdin);
    list[index].unit[strcspn(list[index].unit, "\n")] = '\0';
    printf("Nhap so luong moi: ");
    list[index].qty = inputIntRange(0, 100000000);
    printf("Cap nhat thanh cong!\n");
}
void printMaterial(Material *list, int count) {
    if (count == 0) {
        printf("Danh sach rong!");
        return;
    }
    int catChoice;
    printf("\nChon category:\n");
    printf("1. Do gia dung\n");
    printf("2. Do dien tu\n");
    printf("3. Do thiet yeu\n");
    printf("Nhap lua chon: ");
    scanf("%d", &catChoice);
    clearbuffer();
    char *catName;
    switch (catChoice) {
        case 1: catName = "Do gia dung"; break;
        case 2: catName = "Do dien tu"; break;        // Biến các catName thành các đồ dùng để lồng case
        case 3: catName = "Do thiet yeu"; break;
        default:
            printf("Lua chon khong hop le!\n");
            return;
    }
    int filteredIndexes[MAX_S];        //
    int filteredCount = 0;
    // Lọc danh sách theo category
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].category, catName) == 0) {
            filteredIndexes[filteredCount++] = i;   // nếu vật tư đúng categoty lưu i vào mảng filteredIndexes
            // filteredCount++ lien tuc tang dam bao cac index tiep theo duoc luu
        }
    }
    if (filteredCount == 0) {
        printf("Khong co vat tu trong category %s!\n", catName);
        return;
    }
    int page = 0, itemsPerPage = 10;
    int totalPages = filteredCount / itemsPerPage;    // chia lay nguyen 20 /10 duoc 2 trang con du 5 tinh sau
    if (filteredCount % itemsPerPage != 0) totalPages++; // chia lay du nhap du khi chia vao trang nay
    while (1) {
        printf("\n===== DANH SACH VAT TU - %s (Trang %d/%d) =====\n", catName, page + 1, totalPages);
        int start = page * itemsPerPage;
        int end = start + itemsPerPage;
        if (end > filteredCount) end = filteredCount;
        for (int i = start; i < end; i++) {
            int idx = filteredIndexes[i];
            printf("Ma: %s | Ten: %s | Don vi: %s | So luong: %d | Trang thai: %s\n",
                   list[idx].matID,
                   list[idx].name,
                   list[idx].unit,
                   list[idx].qty,
                   list[idx].status ? "Su dung" : "Het su dung");
        }
        printf("\n[N] Trang sau | [P] Trang truoc | [Q] Thoat: ");
        char c = getchar();
        clearbuffer();
        if (c == 'N' || c == 'n') {
            if (page + 1 < totalPages) page++;
        } else if (c == 'P' || c == 'p') {
            if (page > 0) page--;
        } else if (c == 'Q' || c == 'q') {
            break;
        }
    }
}
void managerStatus(Material *list, int count) {
    char id[10];
    int i, choice;
    if (count == 0) {
        printf("Chua co vat tu nao!");
        return;
    }
    printf("Nhap ID vat tu can quan li trang thai: ");
    fgets(id,sizeof(id),stdin);
    id [strcspn(id,"\n")] = '\0';
    for (i = 0; i < count; i++) {
        printf("Trang thai hien tai cua vat tu %s\n: %s",list[i].matID,list[i].status ? "Active" : "Locked");
    printf("Chon trang thai moi (1 = Active, 0 = Locket): ");
        choice = inputIntRange(0,1);
        list[i].status = choice;
        printf("Cap Nhap trang thai thanh cong!");
        return;
    }
    printf("Khong tim thay ma vat tu!");
}
void searchMaterialByID(Material *list, int count) {
    if (count == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    char id[20];
    printf("Nhap ID can tim: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].matID, id) == 0) {
            printf("\n=== THONG TIN VAT TU ===\n");
            printf("Ma: %s\n", list[i].matID);
            printf("Ten: %s\n", list[i].name);
            printf("Don vi: %s\n", list[i].unit);
            printf("So luong: %d\n", list[i].qty);
            printf("Trang thai: %s\n", list[i].status ? "Su dung" : "Het su dung");
            printf("Loai: %s\n", list[i].category);
            return;
        }
    }
    printf("Khong tim thay vat tu co ID %s!\n", id);
}
void searchMaterialByName(Material *list, int count) {
    if (count == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    char name[50];
    printf("Nhap ten can tim: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(list[i].name, name) != NULL) {    // tìm chuỗi con
            if (!found) printf("\n=== KET QUA TIM KIEM ===\n");
            found = 1;
            printf("Ma: %s | Ten: %s | Don vi: %s | So luong: %d | Loai: %s\n",
                   list[i].matID, list[i].name, list[i].unit, list[i].qty, list[i].category);
        }
    }
    if (!found) {
        printf("Khong tim thay vat tu ten chua: %s!\n", name);
    }
}
int main() {
    int choice;
    Material materials[MAX_S];
    Transaction transactions[MAX_S];
    int materialCount = 0;
    int transactionCount = 0;
    do {
        menu();
        printf("Nhap lua chon: ");
        choice = inputIntRange(0, 8);
        switch (choice) {
            case 1:
                inputMaterial(&materials[materialCount], materialCount, materials);
                materialCount++;
                break;
            case 2:
                updateMaterial(materials, materialCount);
                break;
            case 3:
                managerStatus(materials, materialCount);
                break;
            case 4:
                printf("\n=== TIM KIEM VAT TU ===\n");
                printf("1. Tim theo ID\n");
                printf("2. Tim theo Ten\n");
                printf("Nhap lua chon: ");
                int tk;
                tk = inputIntRange(1, 2);
                if (tk == 1)
                    searchMaterialByID(materials, materialCount);
                else
                    searchMaterialByName(materials, materialCount);
                break;
            case 5:
                printMaterial(materials, materialCount);
                break;
            case 0:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Chuc nang chua lam!\n");
        }
    } while (choice != 0);
    return 0;
}
