#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    struct CARK {
        int value;
        struct CARK* next;
    };

    void carka_ekle(struct CARK** head, int value) {
    struct CARK* newCARK = (struct CARK*)malloc(sizeof(struct CARK));
    newCARK->value = value;

    if (*head == NULL) {
        *head = newCARK;
        newCARK->next = *head;
    }
    else {
        struct CARK* temp = *head;
        while (temp->next != *head)
            temp = temp->next;
        temp->next = newCARK;
        newCARK->next = *head;
    }
}

    void cark_yazdir(struct CARK* head) {
        struct CARK* temp = head;
        if (head != NULL) {
            do {
            printf("%d \t ", temp->value);
            temp = temp->next;
            } while (temp != head);
        }
    }


    void ortak_sayi_bul(struct CARK* cark1, struct CARK* cark2, struct CARK* cark3, int m) {
    struct CARK* temp1 = cark1;
    struct CARK* temp2 = cark2;
    struct CARK* temp3 = cark3;
    int x,y,z;
    int flag=0;
    x=0;




    while (x<m && flag==0) {
        temp2 = cark2;
        y=0;
        while (y<m && flag==0) {
            temp3 = cark3;
            z=0;
            while (z<m && flag==0) {
                if (temp1->value == temp2->value && temp2->value == temp3->value) {
                    flag=1;
                    printf("\n");
                    printf("Ortak sayi: %d \n",temp1->value);
                    printf("\n");
                    printf("1. Carktaki konumu: %d \n",konum_bul(cark1,temp1->value));
                    printf("2. Carktaki konumu: %d \n",konum_bul(cark2,temp2->value));
                    printf("3. Carktaki konumu: %d \n",konum_bul(cark3,temp3->value));

                }
                temp3 = temp3->next;
                z++;
            }
            temp2 = temp2->next;
            y++;
        }
        temp1 = temp1->next;
        x++;
    }


}

    int konum_bul(struct CARK* cark, int value) {
        int konum = 1;
        struct CARK* temp = cark;

        while (temp != NULL) {
            if (temp->value == value) {
                return konum;
            }
            konum++;
            temp = temp->next;

        }
    }

    void rotasyon_degerlerini_bul(struct CARK* cark1, struct CARK* cark2, struct CARK* cark3, int m){
        struct CARK* temp1 = cark1;
        struct CARK* temp2 = cark2;
        struct CARK* temp3 = cark3;
        int x,y,z;
        int flag = 0;
        x=0;
        int* rotasyon = malloc(3 * sizeof(int));




        while (x<m && flag==0) {
            temp2 = cark2;
            y=0;
            while (y<m && flag==0) {
                temp3 = cark3;
                z=0;
                while (z<m && flag==0) {
                    if (temp1->value == temp2->value && temp2->value == temp3->value) {
                        flag=1;
                        rotasyon[0]=konum_bul(cark1,temp1->value);
                        rotasyon[1]=konum_bul(cark2,temp2->value);
                        rotasyon[2]=konum_bul(cark3,temp3->value);

                    }
                    temp3 = temp3->next;
                    z++;
                }
                temp2 = temp2->next;
                y++;
            }
            temp1 = temp1->next;
            x++;
        }

        int a,b;
        a=rotasyon[1]-rotasyon[0];
        b=rotasyon[2]-rotasyon[0];

        if(a < 0){
            printf("2.Cark Saat yonunde %d adim cevrilmeli \n",abs(a));
            carki_dondur(&cark2,a,m);
        } else if(a > 0){
            printf("2.Cark Saatin ters yonunde %d adim cevrilmeli \n",a);
            carki_dondur(&cark2,a,m);
        } else {printf("2. Carkin cevrilmesine gerek yok.\n");}

        if(b < 0){
            printf("3.Cark Saat yonunde %d adim cevrilmeli \n",abs(b));
            carki_dondur(&cark3,b,m);
        } else if(b > 0){
            printf("3.Cark Saatin ters yonunde %d adim cevrilmeli \n",b);
            carki_dondur(&cark3,b,m);
        } else {printf("2. Carkin cevrilmesine gerek yok.\n");}


        printf("\n");
        printf("\n");
        printf("Carklarin Son hali:\n");
        printf("\nCarklar:\n");
        printf("Cark 1: \t");
        cark_yazdir(cark1);
        printf("\nCark 2: \t");
        cark_yazdir(cark2);
        printf("\nCark 3: \t");
        cark_yazdir(cark3);





        }




    void carki_dondur(struct CARK** cark,int cevirme_sayisi,int m){

            int k;

            if(cevirme_sayisi > 0){k=cevirme_sayisi;}
            else if(cevirme_sayisi < 0){k = (m + cevirme_sayisi) % m;}
            struct CARK* current = *cark;
            struct CARK* previous = NULL;

            for(int i=0;i<k;i++){
                previous = current;
                current = current->next;
            }

            struct CARK* last = current;
            while (last->next != *cark) {
                last = last->next;
                }
                last->next = *cark;
                *cark = current;
                previous->next = *cark;




    }


int main(){
    int m,n,i;

    printf("1'den kaca kadar rastgele sayilari kullanmak istersiniz: ");
    scanf("%d", &n);
    printf("Carklar kac sayilik olmalidir: ");
    scanf("%d", &m);

    while(n/2 < m || m < 2 || n < 4){
        printf("Girmis oldugunuz sayilarla carklarin olusturulmasi mumkun degil.\n");
        printf("1'den kaca kadar rastgele sayilari kullanmak istersiniz: ");
        scanf("%d", &n);
        printf("Carklar kac sayilik olmalidir: ");
        scanf("%d", &m);

    }

    int* dizi = malloc(3*m * sizeof(int));
    dizi=dizi_olustur(m,n);

    struct CARK *cark1 = NULL;
    struct CARK *cark2 = NULL;
    struct CARK *cark3 = NULL;

    for(i=0;i<m;i++){
        carka_ekle(&cark1, dizi[i]);
        carka_ekle(&cark2, dizi[m+i]);
        carka_ekle(&cark3, dizi[2*m+i]);

    }

    printf("\nCarklar:\n");
    printf("Cark 1: \t");
    cark_yazdir(cark1);
    printf("\nCark 2: \t");
    cark_yazdir(cark2);
    printf("\nCark 3: \t");
    cark_yazdir(cark3);

    printf("\n");
    printf("\n");
    ortak_sayi_bul(cark1,cark2,cark3,m);


    printf("\n");
    printf("\n");

    rotasyon_degerlerini_bul(cark1,cark2,cark3,m);




    free(cark1);
    free(cark2);
    free(cark3);
    free(dizi);

    return 0;



}




int dizi_olustur(int m,int n) {

    int ortak;


    int* dizi = malloc(3*m * sizeof(int));

    int* dizi1 = malloc(m * sizeof(int));
    int* dizi2 = malloc(m * sizeof(int));
    int* dizi3 = malloc(m * sizeof(int));
    srand(time(NULL));


    int i, j;





    for (i = 0; i < m; i++) {
        dizi1[i] = rand() % n + 1;
        j=0;


        while((j<i) && (dizi1[i] != dizi1[j]) ) {j++;}
            if (dizi1[i] == dizi1[j] && i!=j) {
                i--;
                }

    }


    for (i = 0; i < m; i++) {
        dizi2[i] = rand() % n + 1;
        j = 0;

        while((j<i) && (dizi2[i] != dizi2[j]) ) {j++;}
            if (dizi2[i] == dizi2[j] && i!=j) {
                i--;
                }
        j = 0;

        while(j<m && dizi2[i]!=dizi1[j]){j++;}{
            if (dizi2[i] == dizi1[j]) {
                i--;
                }
        }
    }


    for (i = 0; i < m; i++) {
        dizi3[i] = rand() % n + 1;
        j = 0;

        while(j<i  &&  dizi3[i]!=dizi3[j]) {j++;}
            if (dizi3[i] == dizi3[j] && i!=j) {
                i--;
            }
        }


    int x = rand() % m;
    ortak = dizi1[x];

    x = rand() % m;
    dizi2[x] = ortak;

    int flag = 0;

    for(i=0;i < m;i++){
        if(dizi3[i]==ortak){
            flag = 1;
        }
    }

    if(flag==0){
        x = rand() % m;
        dizi3[x] = ortak;
    }

    for (i = 0; i < m; i++) {
            dizi[i]=dizi1[i];
            dizi[m+i]=dizi2[i];
            dizi[2*m+i]=dizi3[i];

    }
    free(dizi1);
    free(dizi2);
    free(dizi3);

        return dizi;
    }
