#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cau truc san pham
typedef struct Product {
    char name[50];
    int size;
    float price;
} Product;

// Cau truc Node
typedef struct Node {
    Product *p;         // Con tro toi danh sach san pham
    int productCount;   // Tong so luong san pham cua khach hang
    float totalPrice;   // Tong gia tien cua khach hang
    struct Node *next;  // Con tro toi Node tiep theo
} Node;

// Cau truc hang doi
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

// Kiem tra hang doi rong
int checkEmpty(Queue *q) {
    return q->front == NULL;
}

// Khoi tao hang doi
Queue *initQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Khong du bo nho de khoi tao hang doi.\n");
        exit(EXIT_FAILURE);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Dem so luong san pham trong mang
int countProducts(Product *p) {
    int count = 0;
    while (p[count].size != 0 || p[count].price != 0 || p[count].name[0] != '\0') {
        count++;
    }
    return count;
}

// Tinh tong tien cho danh sach san pham
float calculateSumPrice(Product *p) {
    float sum = 0;
    int i = 0;
    while (p[i].size != 0 || p[i].price != 0 || p[i].name[0] != '\0') {
        sum += p[i].price * p[i].size;
        i++;
    }
    return sum;
}

// Them khach hang vao hang doi
void enqueue(Queue *q, Product *p) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Khong du bo nho de them khach hang.\n");
        exit(EXIT_FAILURE);
    }

    newNode->p = p;
    newNode->productCount = countProducts(p);
    newNode->totalPrice = calculateSumPrice(p);
    newNode->next = NULL;

    if (checkEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Loai bo khach hang khoi hang doi
void dequeue(Queue *q) {
    if (checkEmpty(q)) {
        printf("Hang doi rong, khong the xoa.\n");
        return;
    }

    Node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

// Tinh tong tien thu ngan da thu
float TotalPrice(Queue *q) {
    float total = 0;
    Node *temp = q->front;
    while (temp != NULL) {
        total += temp->totalPrice;
        temp = temp->next;
    }
    return total;
}

// Dem so luong san pham theo ten
int CountProducts(Queue *q, const char *name) {
    int count = 0;
    Node *temp = q->front;
    while (temp != NULL) {
        for (int i = 0; i < temp->productCount; i++) {
            if (strcmp(temp->p[i].name, name) == 0) {
                count += temp->p[i].size;
            }
        }
        temp = temp->next;
    }
    return count;
}

// In danh sach khach hang
void printQueue(Queue *q) {
    if (checkEmpty(q)) {
        printf("Hang doi trong.\n");
        return;
    }

    Node *temp = q->front;
    int customerIndex = 1;

    while (temp != NULL) {
        printf("Khach hang %d:\n", customerIndex++);
        for (int i = 0; i < temp->productCount; i++) {
            printf("  - Ten: %s, So luong: %d, Gia: %.2f\n",
                   temp->p[i].name, temp->p[i].size, temp->p[i].price);
        }
        printf("  Tong tien: %.2f\n\n", temp->totalPrice);
        temp = temp->next;
    }
}

// Giai phong hang doi
void freeQueue(Queue *q) {
    while (!checkEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

// Chuong trinh chinh
int main() {
    Queue *q = initQueue();

    Product products1[] = {{"Apple", 2, 1.5}, {"Banana", 3, 0.5}, {0}};
    Product products2[] = {{"Orange", 5, 0.8}, {"Apple", 1, 1.5}, {0}};
    Product products3[] = {{"Banana", 4, 0.5}, {0}};

    enqueue(q, products1);
    enqueue(q, products2);
    enqueue(q, products3);

    printf("Danh sach khach hang trong hang doi:\n");
    printQueue(q);
    float totalRevenue1 = TotalPrice(q);
    printf("Tong tien thu ngan da thu: %.2f\n", totalRevenue1);
    int appleCount1 = CountProducts(q, "Apple");
    printf("Tong so san pham 'Apple' da ban: %d\n", appleCount1);
    dequeue(q);

    printf("Danh sach khach hang sau khi xu ly:\n");
    printQueue(q);

    int appleCount = CountProducts(q, "Apple");
    printf("Tong so san pham 'Apple' da ban: %d\n", appleCount);

    freeQueue(q);
    return 0;
}
