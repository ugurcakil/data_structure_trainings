#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



// Trie Node
struct TrieNode {
    const char* character;
    struct TrieNode* children[10];
    bool isEndOfWord;
};

// Function to create a new TrieNode
struct TrieNode* createTrieNode(char chars) {
    // Allocate memory for the new node
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    // Initialize the children array
    for (int i = 0; i < 10; i++) {
        newNode->children[i] = NULL;
    }

    // Set isEndOfWord to false
    newNode->isEndOfWord = false;

    return newNode;
}

// Map a character to a number
int mapCharToNumber(char character) {
    int x;
    if (character == '#') {
        x = 0;
    } else if (character == '-' || character == '*' || character == ',') {
        x = 1;
    } else if (character == 'a' || character == 'b' || character == 'c') {
        x = 2;
    } else if (character == 'd' || character == 'e' || character == 'f') {
        x = 3;
    } else if (character == 'g' || character == 'h' || character == 'i') {
        x = 4;
    } else if (character == 'j' || character == 'k' || character == 'l') {
        x = 5;
    } else if (character == 'm' || character == 'n' || character == 'o') {
        x = 6;
    } else if (character == 'p' || character == 'r' || character == 's') {
        x = 7;
    } else if (character == 't' || character == 'u' || character == 'v') {
        x = 8;
    } else if (character == 'w' || character == 'x' || character == 'y' || character == 'z') {
        x = 9;
    }
    return x;
}


void insert(struct TrieNode *root,char* word, int len) {
    struct TrieNode* current = root;

    int i = 0;

    for(i=0; i<len;i++) {
        int index = mapCharToNumber(word[i]);

        if (current->children[index]== NULL) {
            current->children[index] = createTrieNode('\0');
        }
        current = current->children[index];
        if((current->isEndOfWord == true) && (i == len-1)){
            current->children[0] = createTrieNode('\0');
            current = current->children[0];
            current->character = (char*)malloc((len + 1) * sizeof(char));
            strcpy(current->character, word);

        }
        else if(i == len-1){
            current->isEndOfWord = true;
            //current->character=word;
            current->character = (char*)malloc((len-1) * sizeof(char));
            strcpy(current->character, word);
        }
        printf("%d",index);
    }

    printf(", %s",current->character);
    printf("\n");
}

// Search for a word in the Trie using integer mapping
void search(struct TrieNode* root, int number) {
    struct TrieNode* current = root;
    int i = 0;
    int j=0;
    int *sayilar =(int)malloc(sizeof(int));
    while(number!=0){
        sayilar[j]=number%10;
        number = number/10;

        j++;
    }
    int temp=0;
    for(i=0;i<j/2;i++){

        temp=sayilar[i];
        sayilar[i] = sayilar[j-i-1];
        sayilar[j-i-1]=temp;
    }



    i=0;
    for(i=0;i<j;i++) {
        if(current->children[sayilar[i]]==NULL){
            current->children[sayilar[i]] = createTrieNode('\0');
        }
        current=current->children[sayilar[i]];

    }




    if(current->isEndOfWord==true){
        printf("\t%s\n",current->character);
        current = current->children[0];
        while(current!=NULL){
            printf("\t%s\n",current->character);
            current =current->children[0];
        }
    }
    else if(current->isEndOfWord==false || current->isEndOfWord==NULL){
        printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.");
    }


}



int main() {
    // Trie
    struct TrieNode* trieRoot = createTrieNode('\0');

    // Read words from file
    FILE* file = fopen("sozluk.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char* word= (char*)malloc(sizeof(char));
    printf("Sozluk:\n");
    while ((fscanf(file, "%s", word) == 1)) {
        // Remove newline character if present

        int len = strlen(word);

        if (word[len - 1] == '\n') {
            len=len-1;
        }
        insert(trieRoot, word,len);
    }

    fclose(file);
    printf("\n");
    printf("\n");
    printf("\n");

    char flag='c';
    int find;
    printf("Cikmak icin 'q' kelime bulmak icin 'c' yaziniz:\n>");
    while(flag!='q'){

        scanf("%c",&flag);
        if(flag=='q'){}
        else if(flag=='c'){
            printf(">");
            scanf("%d",&find);
            search(trieRoot,find);
            printf("\n\n");
            printf("Cikmak icin 'q' kelime bulmak icin 'c' yaziniz:\n>");
        }

    }







    return 0;
}
