#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct Node
{
    char name[31];
    int id, win, lose, point, n;
    struct Node *next;
} Node;
typedef struct vong
{
    int soVong;
    int id1[10];
    int id2[10];
} Vong;
Vong vong[10];
Node *head;
Node *tail;

int id1[10], id2[10], vongDau[10];
Node *makeNode(char name[], int id, int point, int win, int lose)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    p->id = id;
    p->win = win;
    p->lose = lose;
    p->next = NULL;
    return p;
}

void addTail(Node *p)
{
    if (head == NULL)
    {
        head = p;
        tail = p;
    }
    else
    {
        tail->next = p;
        tail = p;
    }
}

void readFile()
{
    int n, i, id;
    char name[31];
    FILE *fp = fopen("bongda.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open bongda.txt\n");
        return;
    }
    fscanf(fp, "%d\n", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d\t%s", &id, name);
        Node *p = makeNode(name, id, 0, 0, 0);
        addTail(p);
    }
}

void printNode()
{
    Node *temp = head;
    printf("%-5s%-15s%-12s%-12s%-12s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "SobanThua");
    while (temp)
    {
        printf("%-5d%-15s%-12d%-12d%-12d\n", temp->id, temp->name, temp->point, temp->win, temp->lose);
        temp = temp->next;
    }
}
Node *findById(int id)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void readFileThiDau(int nhap3)
{
    FILE *fp = fopen("bongda.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open bongda.txt\n");
        return;
    }
    int n, i, k, id, j, a, b;
    char name[31];
    fscanf(fp, "%d\n", &n);
    head->n = n;
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d\t%s", &id, name);
    }
    k = n / 2;

    for (i = 0; i <= k; i++)
    {
        fscanf(fp, "%s %d", vong, &(vong[i].soVong));
        printf("Vong %d\n", vong[i].soVong);
        for (j = 0; j < k; j++)
        {
            fscanf(fp, "%d %d", &vong[i].id1[j], &vong[i].id2[j]);
            Node *p1 = findById(vong[i].id1[j]);
            Node *p2 = findById(vong[i].id2[j]);
            if (p1 == NULL || p2 == NULL)
            {
                return;
            }
            printf("%s - %s\n", p1->name, p2->name);
            if (nhap3 == 1)
            {
                scanf("%d", &a);
                scanf("%d", &b);
                p1->win += a;
                int chenhLech = b - a;
                p1->lose += abs(chenhLech);
                p2->win += b;
                p2->lose += abs(chenhLech);
                if ((chenhLech) > 0)
                {
                    p2->point += 3;
                }
                else if ((chenhLech) < 0)
                {
                    p1->point += 3;
                }
                else
                {
                    p1->point += 1;
                    p2->point += 1;
                }
            }
        }
    }
}

/*
void update(int nhap3)
{
    int i, j;
    int n = head->n;
    int k = n / 2;
    int a, b;
    for (i = 0; i <= k; i++)
    {
        printf("Cap nhat ti so:\n");
        printf("Vong %d\n", i + 1);
        for (j = 0; j < k; j++)
        {
            Node *p1 = findById(vong[i].id1[j]);
            Node *p2 = findById(vong[i].id2[j]);
            if (p1 == NULL || p2 == NULL)
            {
                return;
            }
            printf("%s - %s\n", p1->name, p2->name);
            scanf("%d - %d", &a, &b);
            p1->win = a;
            p1->lose = abs(a - b);
            p2->win = b;
            p2->lose = abs(b - a);
            if ((b - a) > 0)
            {
                p2->point += 3;
            }
            else if ((b - a) < 0)
            {
                p1->point += 3;
            }
            else
            {
                p1->point += 1;
                p2->point += 1;
            }
        }
    }
}
*/
Node *findMin()
{
    Node *temp = head;
    Node *min = head;
    while (temp)
    {
        if (temp->point < min->point)
        {
            min = temp;
        }
        temp = temp->next;
    }
    return min;
}

void loaiBo()
{
    Node *min = findMin();
    Node *temp = head;
    printf("Da loai bo doi co diem thap nhat:\n");
    printf("%-5s%-15s%-12s%-12s%-12s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "SobanThua");
    printf("%-5d%-15s%-12d%-12d%-12d\n", min->id, min->name, min->point, min->win, min->lose);
    while (temp != NULL)
    {
        if (temp == head && temp->point == min->point)
        {
            head = temp->next;
            free(temp);
            return;
        }
        else if (temp->next == NULL && temp->point == min->point)
        {
            temp = NULL;
            free(temp);
            return;
        }
        else if (temp->next->point == min->point)
        {
            Node *p = temp->next;
            Node *q = temp->next->next;
            temp->next = q;
            free(p);
            return;
        }
        temp = temp->next;
    }
    free(min);
}

void xoaNode(){
    Node *node = head;
    while (node!= NULL){
        Node* temp =node;
        node=node->next;
        free(temp);
    }
    head=NULL;   
}

int main()
{
    int cmd;
    int nhap3 = 0;
    while (1)
    {
        printf("\n----------------------------------------------------------------\n");
        printf("Chuong trinh quan ly doi bong:\n");
        printf("1. In thong tin cac doi bong\n");
        printf("2. In thong tin lich thi dau\n");
        printf("3. Cap nhat ket qua\n");
        printf("4. Loai bo doi co diem thap nhat\n");
        printf("5. In danh sach cac doi\n");
        printf("6. Thoat\n");
        printf("Nhap 1-6 de chon \n");
        printf("\n----------------------------------------------------------------\n");
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 1:
            readFile();
            printNode();
            break;
        case 2:
            readFileThiDau(nhap3);
            break;
        case 3:
            nhap3 = 1;
            readFileThiDau(nhap3);
            break;
        case 4:
            loaiBo();
            break;
        case 5:
            printNode();
            break;
        case 6:
            xoaNode();
            return 0;
        }
    }
}