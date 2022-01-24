#include <stdio.h>
#include <string.h>

typedef struct Data {
    int so[8][8];   
    int xr,yr;
}data;

void khoitao(data *puz, int n){
     for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            puz->so[i][j] = -1;
        }
}
int check(int p, int a, int b, data *puz){
    for(int i=0; i<=a; i++)
        for(int j=0; j<b; j++){
            if(puz->so[i][j]==p) return 0;
        }
    return 1;
}
void nhap(int n, data* puz){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("puz->so[%d][%d] = ", i, j);
            scanf("%d", &puz->so[i][j]);
            while(check(puz->so[i][j], i, j, puz)==0 || puz->so[i][j]<0 || puz->so[i][j]>=n*n){
                printf("Nhap lai puz->so[%d][%d] = ", i, j);
                scanf("%d", &puz->so[i][j]);
            }
            if(puz->so[i][j]==0){
                puz->yr=j;
                puz->xr=i;
            }
        }
    }
}

void xuat(data* puz, int n){
    printf("*******\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(puz->so[i][j]==0) printf("* ");
            else printf("*%d", puz->so[i][j]);
        }
        printf("*\n");
    }
    printf("*******\n");
}

void phai (data *puz, int n){

       if (puz->xr==0){
           printf("Khong hop le\n");
       } 
       else {
                  puz->so[puz->yr][puz->xr]=puz->so[puz->yr][puz->xr+1];
                  puz->so[puz->yr][puz->xr+1]=0;
                  puz->xr++;
                  }
}
void trai (data *puz, int n){//
       if (puz->xr==n){
           printf("Khong hop le\n");
       } 
       else {
                  puz->so[puz->yr][puz->xr]=puz->so[puz->yr][puz->xr-1];
                  puz->so[puz->yr][puz->xr-1]=0;
                  puz->xr--;    
                       }
}
void xuong (data *puz, int n){
       if (puz->yr==n) {
           printf("Khong hop le\n");
       } 
       else {
                  puz->so[puz->yr][puz->xr]=puz->so[puz->yr+1][puz->xr];
                  puz->so[puz->yr+1][puz->xr]=0;
                  puz->yr++;
                       }
}
void len (data *puz, int n){
      if (puz->yr==0) {
           printf("Khong hop le\n");
       } 
       else {
                  puz->so[puz->yr][puz->xr]=puz->so[puz->yr-1][puz->xr];
                  puz->so[puz->yr-1][puz->xr]=0;
                  puz->yr--;
                       }
}

int main(){
    data* puz;
    int n, B;
    int count=0;
    int cmd, daNhap=0;
    char* p[10];
    while(1){
        printf("-------------------------------");
        printf("Chuong trinh tro choi Puzzle\n");
        printf("1. Nhap so luong cac o theo hang doc.\n");
        printf("2. Nhap cac so vao bang.\n");
        printf("3. Di chuyen o trong(U,D,L,R)\n");
        printf("4. Quay lai B buoc.\n");
        printf("5. In ra cau hinh game hien tai.\n");
        printf("6. Thoat game\n");
        printf("-------------------------------");
        printf("Nhap so tu 1-6 de chon!!!\n");
        scanf("%d", &cmd);
        switch(cmd){
            case 1:
                if(daNhap==0){
                    do{
                    printf("Nhap N la so cot cua ma tran N*N\n");
                    scanf("%d",&n);
                    daNhap=1;
                    }while(n<3 || n>7);
                }
                else{
                    printf("Ban da nhap N roi!!\n");
                }
                break;
            case 2:
                if(daNhap==1){
                    khoitao(puz, n);
                    nhap(n, puz);
                }
                else{
                    printf("Ban chua nhap N la so cot cua ma tran\n");
                    printf("Vui long chon 1 de nhap!!\n");
                    break;
                }
                break;
            case 3:
                if(daNhap){
                    
                    while(strcmp(p[count],"Q")!=0){
                        printf("Nhap U D L R de di chuyen, nhap Q de thoat.\n");
                        scanf("%c", p[count]);
                        
                        if(strcmp(p[count],"U")==0){
                            len(puz,n); count++;
                        } else
                        if(strcmp(p[count],"D")==0){
                            xuong(puz,n); count++;
                        } else
                        if(strcmp(p[count],"L")==0){
                            trai(puz,n); count++;
                        } else
                        if(strcmp(p[count],"R")==0){
                            phai(puz,n); count++;
                        }else
                        if(strcmp(p[count],"Q")==0){
                            break;
                        }
                        else{
                            printf("Nhap lai!");
                        }
                    }
                }
                else{
                    printf("Ban chua nhap N la so cot cua ma tran\n");
                    printf("Vui long chon 1 de nhap!!\n");
                    break;
                }
                break;
            case 4:
                printf("Nhap B: "); scanf("%d", &B);
                if(B<=count) { 
                    count=B;
                }
                for(int i = 1; i<count; i++){
                    char tmp=*p[count-i+1];
                    if(strcmp(&tmp,"U")==0){
                        xuong(puz,n); 
                    } else
                    if(strcmp(&tmp,"D")==0){
                        len(puz,n); 
                    } else
                    if(strcmp(&tmp,"L")==0){
                        phai(puz,n); 
                    } else
                    if(strcmp(&tmp,"R")==0){
                        trai(puz,n); 
                    }
                }
                break;
            case 5:
                if(daNhap){
                    xuat(puz, n);
                }
                else{
                    printf("Ban chua nhap N la so cot cua ma tran\n");
                    printf("Vui long chon 1 de nhap!!\n");
                    break;
                }
                break;
            case 6:
                printf("Tam biet!\n");
                return 0;
            default:
                printf("Nhap sai, vui long nhap cac so tu 1-6\n");
        }
    }
    return 0;
}