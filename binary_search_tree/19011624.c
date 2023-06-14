#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct KOVA {
    int en_ust;
    int kova_kapasitesi;
    int* kova_dizisi;
};

struct MEYVE {
    int agirlik;
    int kalan_agirlik;
    struct MEYVE *sol;
    struct MEYVE *sag;
};


struct MEYVE* meyveOlustur(int agirlik) {
    struct MEYVE* yeniMeyve = (struct MEYVE*)malloc(sizeof(struct MEYVE));
    yeniMeyve->agirlik = agirlik;
    yeniMeyve->kalan_agirlik = agirlik;
    yeniMeyve->sol = NULL;
    yeniMeyve->sag = NULL;
    return yeniMeyve;
}

struct MEYVE* agacaMeyveEkle(struct MEYVE* root, int agirlik) {
    if (root == NULL) {
        return meyveOlustur(agirlik);
    }
    if (agirlik < root->agirlik) {
        root->sol = agacaMeyveEkle(root->sol, agirlik);
    }
    else if (agirlik > root->agirlik) {
        root->sag = agacaMeyveEkle(root->sag, agirlik);
    }
    return root;
}


struct MEYVE* agacOlustur(int n, int m) {
    struct MEYVE* root = NULL;
    srand(time(0));
    int kullanilmis_degerler[m];
    for (int i = 0; i < m; i++) {
        int agirlik;
        do {
            agirlik = rand() % n + 1;
        } while (i > 0 && tekrarKontrolu(kullanilmis_degerler, i, agirlik));
        kullanilmis_degerler[i] = agirlik;
        root = agacaMeyveEkle(root, agirlik);
    }
    return root;
}

int tekrarKontrolu(int arr[], int size, int agirlik) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == agirlik) {
            return 1;
        }
    }
    return 0;
}


struct MEYVE* find_min(struct MEYVE* root) {
    while (root->sol != NULL) {
        root = root->sol;
    }
    return root;
}



struct MEYVE* meyveSil(struct MEYVE* root, int k, int p, int x, struct KOVA* kova) {


    if (root == NULL) return root;


    if (k < root->agirlik)
        root->sol = meyveSil(root->sol, k, p,x, kova);


    else if (k > root->agirlik)
        root->sag = meyveSil(root->sag, k, p,x, kova);


    else {


        if(root->kalan_agirlik - p< 1){


            if (root->sol == NULL) {
                struct MEYVE *temp = root->sag;
                free(root);
                if(x==k){
                    push(kova,x);
                }
                return temp;}


            else if (root->sag == NULL) {
                struct MEYVE *temp = root->sol;
                free(root);
                if(x==k){
                    push(kova,x);
                }

                return temp;

            }
            else{

                struct MEYVE *temp = find_min(root->sag);
                root->agirlik = temp->agirlik;
                root->kalan_agirlik = temp->kalan_agirlik;
                if(x==k){
                    push(kova,x);
                }

                root->sag = meyveSil(root->sag, temp->agirlik ,temp->agirlik,x, kova);
            }
        }
        else{
            root->kalan_agirlik = root->kalan_agirlik - p;
            return root;
        }


    }





    return root;
}







void inorder(struct MEYVE* root) {

    if (root == NULL) {
        return;
    }

    inorder(root->sol);
    printf("%d ", root->agirlik);
    inorder(root->sag);
}






void printTree(struct MEYVE* root, int level) {
    if (root == NULL) {
        return;
    }
    printTree(root->sag, level + 1);
    for (int i = 0; i < level; i++) {
        printf("     ");
    }
    printf("%d(%d)\n", root->agirlik,root->kalan_agirlik);
    printTree(root->sol, level + 1);
}





struct KOVA* kovaOlustur(int kova_kapasitesi)
{
    struct KOVA* kova = (struct KOVA*)malloc(sizeof(struct KOVA));
    kova->kova_kapasitesi = kova_kapasitesi;
    kova->en_ust = -1;
    kova->kova_dizisi = (int*)malloc(kova->kova_kapasitesi * sizeof(int));
    return kova;
}


int isFull(struct KOVA* kova)
{
    return kova->en_ust == kova->kova_kapasitesi - 1;
}


int isEmpty(struct KOVA* kova)
{
    return kova->en_ust == -1;
}



void push(struct KOVA* kova, int agirlik)
{
    if (isFull(kova))
        return;
    kova->kova_dizisi[++kova->en_ust] = agirlik;
    printf("%d kg olan meyve kovaya dustu\n", agirlik);
}


int pop(struct KOVA* kova)
{
    if (isEmpty(kova))
        return INT_MIN;
    return kova->kova_dizisi[kova->en_ust--];
}


int peek(struct KOVA* kova)
{
    if (isEmpty(kova))
        return INT_MIN;
    return kova->kova_dizisi[kova->en_ust];
}

void printKova(struct KOVA *kova)
{
    if(kova->en_ust<0){
        printf("\nKova bos\n");
    }
    else{
        printf("\nKova:\t");
        for(int i=kova->en_ust;i>-1;i--){

            printf("%d\t",kova->kova_dizisi[i]);

        }
    }
    printf("\n");

}












int main()
{
    int n,m,k,p;


    printf("1 den kaca kadar rastgele agirliklardan olusmasini istiyorsunuz:");
    scanf("%d", &n);
    printf("Agacin kac meyveden olusmasini istiyorsunuz: ");
    scanf("%d", &m);


    struct KOVA* kova = kovaOlustur(m);





    struct MEYVE* root = agacOlustur(n,m);


    printf("Root: %d \n",root->agirlik);
    printf("Binary Search Tree:\n");
    inorder(root);
    printf("\n");
    printf("\n");
    printf("AGAC:\n");
    printTree(root, 0);
    printKova(kova);

    while(root!= NULL){
        printf("--------------------------------------------------------------------------------------");
        printf("\nHangi meyveyi taslayacaksin?");
        scanf("%d", &k);
        printf("\nHangi kuvvetle taslayacaksin?");
        scanf("%d", &p);
        root=meyveSil(root,k,p,k, kova);
        printf("\n");
        printf("\n");
        printf("AGAC:\n");
        printf("--------------------------------------------------------------------------------------\n");
        printTree(root, 0);
        printf("--------------------------------------------------------------------------------------");
        printf("\n");
        printKova(kova);
    }
    printf("--------------------------------------------------------------------------------------");
    printf("\nAgacta meyve kalmadi.\n");
    printf("Kova: \t");

    for(int i = 0; i < kova->en_ust + 1; i++){
        printf("%d \t",kova->kova_dizisi[i]);
    }




    return 0;
}
