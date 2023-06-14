#include <stdio.h>
#include <stdlib.h>


struct AdjList {
    int course_no;
    struct AdjList* next;
};


struct GRAPH {
    int course_number;
    int *indegree;
    struct AdjList** adj;
};




// Create AdjList
struct AdjList* createAdjList(int v) {
  struct AdjList* newAdjList = malloc(sizeof(struct AdjList));
  newAdjList->course_no = v;
  newAdjList->next = NULL;
  return newAdjList;
}



// Create a graph
struct GRAPH* createGraph(int course_number) {
  struct GRAPH* graph = malloc(sizeof(struct GRAPH));
  graph->course_number = course_number;
  graph->adj = malloc(course_number * sizeof(struct AdjList*));
  graph->indegree = malloc(course_number * sizeof(int));
    int i;
    for (i = 0; i < course_number; i++) {
        graph->adj[i] = NULL;
        graph->indegree[i] = 0;
    }

  return graph;
}


// Add Condition
void addPrecondition(struct GRAPH* graph, int main_course, int condition) {
  // Add edge from s to d
  struct AdjList* newAdj = createAdjList(condition);
  newAdj->next = graph->adj[main_course];
  graph->adj[main_course] = newAdj;
  graph->indegree[main_course]++;



}




// Print the graph
void printGraph(struct GRAPH* graph) {
  int v;
  for (v = 0; v < graph->course_number; v++) {
    struct AdjList* temp = graph->adj[v];
    if(graph->indegree[v] > -1){
        printf("\n Ders %d kosullari: ", v+1);

        while (temp) {
        printf("Ders:%d \t ", temp->course_no+1);
        temp = temp->next;
        }
        printf("\n");
    }
  }
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
}



int** createMatrix(const char* filename, int N) {
    // Open the file
    FILE *file = fopen(filename, "r");


    // Create a matrix dynamically
    int **matrix = (int **)malloc(N * sizeof(int *));


    // Read values from the file and store in the matrix
    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(N * sizeof(int));
        if (matrix[i] == NULL) {
            fclose(file);
            return NULL;
        }

        for (int j = 0; j < N; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {

                fclose(file);
                return NULL;
            }
        }
    }


    // Close the file
    fclose(file);

    return matrix;
}


void deleteCondition(struct GRAPH** temp, int condition) {
    struct GRAPH* den = *temp;

    for (int i = 0; i < den->course_number; i++) {

        if (i == condition) {
            continue;
        } else {
            struct AdjList* current = den->adj[i];
            struct AdjList* prev = NULL;

            while (current != NULL) {
                if (current->course_no == condition) {
                    if (prev == NULL) {
                        den->adj[i] = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    free(current);

                    den->indegree[i]--;

                    break;
                }
                prev = current;
                current = current->next;
            }
        }

    }

    *temp = den;
}

void takeCourse(struct GRAPH** graph){
   int* array;


   struct GRAPH* temp = *graph;
   array = malloc(temp->course_number * sizeof(int));
   int j=0;

   for(int i=0;i < temp->course_number;i++){



        if(temp->indegree[i]==0){
            array[j]=i;
            j++;


        }
   }

   for(int i=0;i<j;i++){
   temp->indegree[array[i]]=-1;
   deleteCondition(&temp,array[i]);
   printf("%d. Ders\n",array[i]+1);

   }
   *graph = temp;

}

int main() {

    int N;
    int E;
    int semester = 1;
    int i, j, count = 1;

    printf("Toplam ders sayisi:");
    scanf("%d",&N);
    printf("\nToplam kosul sayisi:");
    scanf("%d",&E);





    int** adj_matrix = createMatrix("matrix3.txt",N);


    printf("Komsuluk Matrisi:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }

    struct GRAPH* graph = createGraph(N);


    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(adj_matrix[i][j] == 1){
                addPrecondition(graph,j,i);

                printf("%d -> %d\n",i+1,j+1);
            }
        }

    }
    printf("\n\nMufredat:");
    printGraph(graph);

    int check = 0;
    while(check==0){
        printf("%d. Donem alinacak dersler:\n",semester);
        check = 1;

        takeCourse(&graph);
        for(i = 0;i < graph->course_number;i++){
            if(graph->indegree[i] > -1){
                check = 0;
            }
        }
        semester++;
        printf("Kalan Dersler:\n");
        printGraph(graph);

    }

    printf("Alinacak ders kalmadi");
    printf("\n%d Donemde okul biter.",semester-1);






    for (i = 0; i < N; i++) {
        free(adj_matrix[i]);
    }
    free(adj_matrix);



    return 0;
}
