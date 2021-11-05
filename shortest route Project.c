#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_CHAR 100
char *INPUT="segments.txt";
char *output="route.txt";
FILE *input;
struct List
{
    int weight;
    int first;
    struct List* next;
};
struct List_answer
{
    int first;
    int second;
    struct List* next;
};
struct HeapNode
{
    int  v;
    int dist;
};
struct Heap
{
    int size;
    int capacity;
    int *pos;
    struct HeapNode **array;
};
int count;
void number_of_line();
int count;
void insert(struct List** head, int first,  int cost);
void insert_Answer(struct List** head, int first,  int second);
struct List_answer*answer;
void dijkstra(struct List* list[], int src,int point,char *names[count][count],int *cost);
int isInHeap(struct Heap *Heap, int v);
void insert_data(struct Heap* Heap,int vert, int dist);
int isEmpty(struct Heap* minHeap);
void delete_min(struct Heap* Heap,int index);
struct Heap* createHeap(int capacity);
struct HeapNode* newNode(int v,int dist);
struct HeapNode* dequeue(struct Heap*Heap);
void swapNode(struct HeapNode** a,struct HeapNode** b);
int main( ) {
    number_of_line();
    char *names_city[count][count];
    struct List *adjacency_list[count];
    for (int i = 0; i < count; ++i) {
        adjacency_list[i] = NULL;
    }
    int src,dis,cost;
    char *str;
    input = fopen(INPUT, "r");
    if (input == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    char Data[MAX_CHAR];
    while (!feof(input)) {
        fgets(Data, MAX_CHAR, input);
        char num[256] = {'\0'};
        char name[256] = {'\0'};
        if (Data[0] == '\n') {
            continue;
        }
        str = strtok(Data, " ");
        src = atoi(str);
        str = strtok(NULL, " ");
        dis = atoi(str);
        str = strtok(NULL, "");
        for (int i = 0, j = 0; str[i]; i++) {
            if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
                name[i] = str[i];
            else if (str[i] >= 48 && str[i] <= 57) {
                num[j] = str[i];
                j++;
            } else
                name[i] = str[i];
        }
        char *string;
        string = malloc(sizeof(name) + 1);
        memset(&string[0], 0x00, sizeof(name) + 1);
        memcpy(&string[0], &name[0], sizeof(name));
        cost = atoi(num);
        if (!adjacency_list[src]) {
            adjacency_list[src] = (struct List *) malloc(sizeof(struct List));
            adjacency_list[src]->next = adjacency_list[src];
            adjacency_list[src] = NULL;
        }
        if (!adjacency_list[dis]) {
            adjacency_list[dis] = (struct List *) malloc(sizeof(struct List));
            adjacency_list[dis]->next = adjacency_list[dis];
            adjacency_list[dis] = NULL;
        }
        insert(&adjacency_list[src], dis, cost);
        insert(&adjacency_list[dis], src, cost);
        names_city[dis][src] = string;
        names_city[src][dis] = string;
    }
    fclose(input);
    printf("The Graph has been loaded.\n");
    int point1;
    int point2;
    int answer_cost;
    printf("Please enter point 1:");
    while (scanf("%d",&point1) != 1){
        printf("\nplease enter again point 1 : ");
        while(getchar() != '\n');
    }
    printf("\nPlease enter point 2:");
    while (scanf("%d",&point2) != 1){
        printf("\nplease enter again point 2 : ");
        while(getchar() != '\n');
    }
    FILE *out = fopen(output, "w");
    while (1) {
        if (point1 >= 0 && point1 < count && point2 >= 0 && point2 < count) {
                if(adjacency_list[point1]==NULL||adjacency_list[point2]==NULL){
                    printf("Sorry, There is no possible way between %d and %d\n",point1,point2);
                    printf("\n\nDo you want continue in the program ? enter y if yes : ");
                    scanf(" %[^\n]s", Data);
                    if (strcasecmp(Data, "y") != 0) {
                        printf("\nThank you,Good Bye!");
                        break;
                    } else {
                        printf("\nPlease enter point 1:");
                        while (scanf("%d",&point1) != 1){
                            printf("\nplease enter again point 1 : ");
                            while(getchar() != '\n');
                        }
                        printf("\nPlease enter point 2:");
                        while (scanf("%d",&point2) != 1){
                            printf("\nplease enter again point 2 : ");
                            while(getchar() != '\n');
                        }
                    }
                }
                dijkstra(adjacency_list, point1, point2, names_city, &answer_cost);
                struct List_answer *temp = answer;
                if(answer_cost!=INT_MAX) {
                    printf("\n______________________________________________________________________________________");
                    printf("\nThe Short path distance from %d to %d with cost %d:", point1, point2, answer_cost);
                    while (temp) {
                        printf(" -> %s", names_city[temp->first][temp->second]);
                        temp = temp->next;
                    }
                    printf("\n______________________________________________________________________________________");
                    printf("\n\nDo you want print the output in file ? enter y if yes : ");
                    scanf(" %[^\n]s", Data);
                    if (strcasecmp(Data, "y") == 0) {
                        temp = answer;
                        out = fopen(output, "a");
                        fprintf(out, "\nThe Short path distance from %d to %d with cost %d : ", point1, point2,
                                answer_cost);
                        while (temp) {
                            fprintf(out, " -> %s", names_city[temp->first][temp->second]);
                            temp = temp->next;
                        }
                        printf("\nThe output has been loaded to File\n");
                        fclose(out);
                    }
                } else{
                    printf("\nSorry, There is no possible way between %d and %d\n",point1,point2);
                }
            printf("\n\nDo you want continue in the program ? enter y if yes : ");
            scanf(" %[^\n]s", Data);
            if (strcasecmp(Data, "y") != 0) {
                printf("\nThank you,Good Bye!");
                break;
            } else {
                printf("\nPlease enter point 1:");
                while (scanf("%d",&point1) != 1){
                    printf("\nplease enter again point 1 : ");
                    while(getchar() != '\n');
                }
                printf("\nPlease enter point 2:");
                while (scanf("%d",&point2) != 1){
                    printf("\nplease enter again point 2 : ");
                    while(getchar() != '\n');
                }
            }
        }else {
            printf("\nThere is %d possible Points from 0 to %d. ", count-1, count-1);
            printf("\n\nDo you want continue in the program ? enter y if yes : ");
            scanf(" %[^\n]s", Data);
            if (strcasecmp(Data, "y") != 0) {
                printf("\nThank you,Good Bye!");
                break;
            } else {
                printf("\nPlease enter point 1:");
                while (scanf("%d",&point1) != 1){
                    printf("\nplease enter again point 1 : ");
                    while(getchar() != '\n');
                }
                printf("\nPlease enter point 2:");
                while (scanf("%d",&point2) != 1){
                    printf("\nplease enter again point 2 : ");
                    while(getchar() != '\n');
                }
            }

        }

    }

    return 0;
}
void number_of_line(){
    count=0;
    int num1;
    int num2;
    input = fopen(INPUT, "r");
    char *str;
    if (input == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    char Data[MAX_CHAR];
    while (!feof(input))
    {
        fgets(Data, MAX_CHAR, input);
        if (Data[0] == '\n')
            continue;
        str= strtok(Data," ");
        int y=atoi(str);
        if (count==0)
            num2= atoi(str);
        str= strtok(NULL," ");
        if (count==0)
            num1= atoi(str);
        count++;
        int z=atoi(str);
        ++count;
        if (num1<=z)
            num1= z;
        if (num2<=y)
            num2= y;
    }
    if(num2>=num1){
        count=num2+1;
    } else
        count=num1+1;
    fclose(input);
}
void insert(struct List** head, int first,  int cost)
{
    struct List* temp = (struct List*)malloc(sizeof(struct List));
    if (temp==NULL)
        printf("out of memory");
    temp->first=first;
    temp->weight=cost;
    temp->next = (*head);
    (*head) = temp;
}
void insert_Answer(struct List** head, int first,  int second)
{
    struct List_answer* temp = (struct List_answer*)malloc(sizeof(struct List_answer));
    if (temp==NULL)
        printf("out of memory");
    temp->first=first;
    temp->second=second;
    temp->next = (*head);
    (*head) = temp;
}
struct HeapNode* newNode(int v,int dist)
{
    struct HeapNode* minNode =(struct HeapNode*)malloc(sizeof(struct HeapNode));
    minNode->v = v;
    minNode->dist = dist;
    return minNode;
}
struct Heap* createHeap(int capacity)
{
    struct Heap* minHeap =(struct Heap*)malloc(sizeof(struct Heap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =(struct HeapNode**)malloc(capacity *sizeof(struct HeapNode*));
    return minHeap;
}
void swapNode(struct HeapNode** a,struct HeapNode** b){
    struct HeapNode* t = *a;
    *a = *b;
    *b = t;
}
void delete_min(struct Heap* Heap,int index){
    int small, left, right;
    small = index;
    left = 2 * index+ 1;
    right = 2 * index + 2;
    if (left < Heap->size &&Heap->array[left]->dist <Heap->array[small]->dist )
        small = left;
    if (right < Heap->size &&Heap->array[right]->dist <Heap->array[small]->dist )
        small = right;
    if (small!= index)
    {
        struct HeapNode *smallestNode =Heap->array[small];
        struct HeapNode *idxNode =Heap->array[index];
        Heap->pos[smallestNode->v] = index;
        Heap->pos[idxNode->v] = small;
        swapNode(&Heap->array[small],&Heap->array[index]);
        delete_min(Heap, small);
    }
}
int isEmpty(struct Heap* minHeap)
{
    return minHeap->size == 0;
}
struct HeapNode* dequeue(struct Heap*Heap)
{
    if (isEmpty(Heap))
        return NULL;
    struct HeapNode* root =Heap->array[0];
    struct HeapNode* lastNode =Heap->array[Heap->size - 1];
    Heap->array[0] = lastNode;
    Heap->pos[root->v] = Heap->size-1;
    Heap->pos[lastNode->v] = 0;
    --Heap->size;
    delete_min(Heap, 0);

    return root;
}
void insert_data(struct Heap* Heap,int vert, int dist){
    if (Heap->size == Heap->capacity) {
        printf("\n Could not insertKey\n");
        return;
    }
    int i = Heap->pos[vert];
    Heap->array[i]->dist = dist;
    while (i && Heap->array[i]->dist <Heap->array[(i - 1) / 2]->dist){
        Heap->pos[Heap->array[i]->v] =(i-1)/2;
        Heap->pos[Heap->array[(i-1)/2]->v] = i;
        swapNode(&Heap->array[i],&Heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int isInHeap(struct Heap *Heap, int v)
{
    if (Heap->pos[v] < Heap->size)
        return 1;
    return 0;
}
void dijkstra(struct List* list[], int src,int point,char *names[count][count],int *cost)
{
    int parent[count]; // Parent of a vertex
    int dist[count];
    struct Heap* Heap = createHeap(count);
    for (int v = 0; v < count; ++v)
    {
        parent[v]=0;
        dist[v] = INT_MAX;
        Heap->array[v] = newNode(v,dist[v]);
        Heap->pos[v] = v;
    }
    parent[src] = -1;
    Heap->array[src] =newNode(src, dist[src]);
    Heap->pos[src]   = src;
    dist[src] = 0;
    insert_data(Heap, src, dist[src]);

    Heap->size = count;

    while (!isEmpty(Heap))
    {
        struct HeapNode* HeapNode =
                dequeue(Heap);
        int u = HeapNode->v;
        if (point==u){
            break;
        }
        struct  List*new_list=list[u];
        while (new_list != NULL)
        {
            int v = new_list->first;
            if (isInHeap(Heap, v) &&dist[u] != INT_MAX&&new_list->weight + dist[u] < dist[v]){
                dist[v] = dist[u] + new_list->weight;
                parent[v] =u;
                insert_data(Heap, v, dist[v]);
            }
            new_list = new_list->next;
        }
    }
    int start_street=point;
    int end_street;
    answer=(struct List_answer*) malloc(sizeof (struct List_answer));
    answer->next=NULL;
    answer=answer->next;
    while (start_street!=src&&dist[point]!=INT_MAX){
        end_street=start_street;
        start_street=parent[end_street];
        insert_Answer(&answer,start_street,end_street);
    }
    *cost=dist[point];
}