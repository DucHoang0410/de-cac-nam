#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char name[41];
    int hours,minutes;
    struct Node *next;
}Node;
    Node *head;
    Node *tail;
void init(){
    head =NULL;
    tail =NULL;
}

Node* makeNode(char name1[41],int gio,int phut){
    Node* p=(Node*) malloc(sizeof(Node));
    p->next=NULL;
    strcpy(p->name,name1);
    p->hours = gio;
    p->minutes = phut;
    return p;
}
void addTail(Node *p){
    if(head == NULL){
        head=p;
        tail=p;
    }
    else{
        tail->next=p;
        tail=p;
    }
}

void nhap(){
    FILE *fp=fopen("log.txt","r");
    if(fp== NULL){
        printf("Can't open log.txt");
        return; 
    }
    char ten[41];
    int gio, phut;
    while(!feof(fp)){
        fscanf(fp,"%s %d %d",ten,&gio,&phut);
        Node* p=makeNode(ten,gio,phut);
        addTail(p);
    }
    fclose(fp);
}
void printNode(){
    if(head==NULL){
        return;
    }
    Node *temp=head;
    while(temp!=NULL){
        printf("%-50s %-10d %-10d\n",temp->name,temp->hours,temp->minutes);
        temp=temp->next;
    }
}
void findByName(){
    char ten[41];
    printf("Nhap dia diem can tim:\n");
    scanf("%s",ten);
    int count=0,i;
    int gio[10], phut[10];
    Node *temp=head;
    while(temp!=NULL){
        if(strcmp(ten,temp->name)==0){
            gio[count]=temp->hours;
            phut[count]=temp->minutes;
            count++;
        }
        temp=temp->next;
    }
    if(count==0){
        printf("Ban chua den dia diem do\n");
        return;
    }
    else{
        for(i=0;i<count-1;i++){
            printf("%d:%d,",gio[i],phut[i]);
        }
        printf("%d:%d",gio[count-1],phut[count-1]);
    }
}
void findByTime(){
    int gio, phut;
    do{
        printf("Nhap gio:\n");
        scanf("%d",&gio);
    }while(gio<0 || gio>=24);
    do{
        printf("Nhap phut:\n");
        scanf("%d",&phut);
    }while(phut<0 || phut>=60);
    Node *temp=head;
    while(temp!=NULL){
        if(temp->hours==gio && temp->minutes==phut){
            printf("%s\n",temp->name);
            return;
        }
        temp=temp->next;
    }
    printf("Khong tim thay lich su di chuyen\n");
}
int compare(char diaDiemNhap[41],int gioNhap,int phutNhap,char diaDiem[41],int gio,int phut) {
    if(strcmp(diaDiemNhap,diaDiem)==0){
        if(gioNhap<gio){
            return 1;
        }
        if(gioNhap==gio){
            if(phutNhap<phut){
                return 1;
            }
        }
        if(gioNhap>=gio){
            return 0;
        }
    }
    else{
        return 0;
    }
}
void truyVet(){
    char diaDiem[41];
    int gio,phut;
    printf("Nhap dia diem:\n");
    scanf("%s",diaDiem);
    printf("Nhap gio, phut:\n");
    scanf("%d %d",&gio,&phut);
    Node *temp=head;
    while(temp!=NULL){
        if(compare(diaDiem,gio,phut,temp->name,temp->hours,temp->minutes)){
            printf("Ban co kha nang lay nghiem covid!! Mau khai bao y te");
            return;
        }
        temp=temp->next;
    }
    printf("Lich su di chuyen cua ban OK\n");
}
void xoaBoNho(){
    Node *temp=head;
    while(head!=NULL){
        temp=head;
        head=head->next;
        free(temp);
    }
}
int main(){
    int cmd;
   
    init();
    while(1){
        printf("\n----------------------------------------------------------------\n");
        printf("Chuong trinh quan ly:\n");
        printf("1. Nap du lieu tu file log\n");
        printf("2. In ra lich su di chuyen\n");
        printf("3. Tim kiem lich su di chuyen theo dia diem\n");
        printf("4. Tim kiem thong tin di chuyen theo thoi gian\n");
        printf("5. Kiem tra truy vet moi nhat\n");
        printf("6. Thoat\n");
        printf("Nhap 1-6 de chon \n");
        printf("\n----------------------------------------------------------------\n");
        scanf("%d",&cmd);
        switch(cmd){
            case 1:
               nhap();
                break;
            case 2:
                printNode();
                break;
            case 3:
                findByName();
                break;
            case 4:
                findByTime();
                break;
            case 5:
                truyVet();
                break;
            case 6:
                xoaBoNho();
                printf("Tam Biet!!\n");
                return 0;
            default:
                printf("Nhap sai, vui long nhap tu 1-6\n");
        }
    }
}