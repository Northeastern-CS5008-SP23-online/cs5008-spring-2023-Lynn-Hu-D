/*Lingyu Hu*/
/*hu.lingyu@northeastern.edu*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*structure represents a node to store the names and pointer to next node*/
typedef struct node
{
    char name[50];
    struct node* next;
}node;

/* Structure represents a Graph with an array of adjacency lists.Size of the array will be number of vertices.*/
typedef struct Graph
{
    int numberOfVertices;
    struct node** adjLists;
}Graph;

/*A function to create a newnode*/
node* createNode(char* name)
{
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        exit(0);
    } else {
        strcpy(newNode->name,name);
        newNode-> next = NULL;
    return newNode;
    }
    
}

/*A function to create a graph with an array of adjacency lists which is= numberof vertices*/
Graph* createGraph(int vertices)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        exit(0);
    } else {
        graph->numberOfVertices = vertices;
        // allocate memory for linkedlist
        graph->adjLists=(node**)malloc(vertices * sizeof(node*));
        for (int i = 0; i < vertices; i++) {
            graph->adjLists[i] = NULL;
        }
        return graph;
    }
    
}

/* function to count Number of listspresent in the graph */
int countNumberofLists(Graph* graph)
{   
    int j = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjLists[i] != NULL) {
            j++;
        }
    }
    return j;
   
}
/*searching the persons who are already there in the list*/
int search(char* name, Graph* graph)
{
     // pos of person, if not present return -1
    for (int i = 0; i < countNumberofLists(graph); i++) {
       if (strcmp(graph->adjLists[i]->name, name) == 0) {
        return i;
       }
    }
    return -1;
    
}

/*adds an edge to an undirected graph*/
void addConnection(Graph* graph, char* person, char* friend){
    int p = search(person, graph);//search for the person in the graph
    int n=countNumberofLists(graph); // nums of lists present in the graph
    
    
/*insert your code here*/
    node* newPerson = createNode(person);
    node* newFriend = createNode(friend);
    if (n == 0) {
        graph->adjLists[0] = newPerson;
        newPerson->next = newFriend;

    } else {
        if (p >= 0) {
            node* cur = graph->adjLists[p];
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newFriend;
        } 
        if (p < 0) {
            graph->adjLists[n] = newPerson;
            newPerson->next = newFriend;
        }

    }


}

/*function to print the adjacency list representation of a graph*/
void printGraph(Graph* graph)
{
    int i;
    for (i = 0; i<graph->numberOfVertices;i++)
    {
    /*print the current vertex and all its neighbors*/
    struct node* temp = graph->adjLists[i];
    printf("\n%s---",graph->adjLists[i]->name );
    while((temp->next)!=NULL)
    {
    printf("%s-", temp->next->name);
    temp = temp->next;
    }
    printf("NULL\n");
    }
}

void graphDestroy(Graph *graph)
{
    int i;
    node* p;
    /*Go to each list and free the memory*/
    for(i=0; i<graph->numberOfVertices;i++){
        node *temp=graph->adjLists[i];
        while(temp!=NULL){
            p=temp;
            temp=temp->next;
            free(p);
        }
    }
    free(graph->adjLists);
        free(graph);
    }


int main()
{
    
    int Num=7; // number of vertices
    /*construct a graph*/
    Graph* graph = createGraph(Num);
    /*function to add edge*/
    addConnection(graph, "personA", "personB");
    addConnection(graph, "personA", "personG");
    addConnection(graph, "personA", "personE");
    addConnection(graph, "personB", "personA");
    addConnection(graph, "personB", "personE");
    addConnection(graph, "personB", "personC");
    addConnection(graph, "personB", "personG");
    addConnection(graph, "personC", "personB");
    addConnection(graph, "personC", "personD");
    addConnection(graph, "personC", "personE");
    addConnection(graph, "personD", "personC");
    addConnection(graph, "personD", "personE");
    addConnection(graph, "personD", "personF");
    addConnection(graph, "personE", "personA");
    addConnection(graph, "personE", "personB");
    addConnection(graph, "personE", "personC");
    addConnection(graph, "personE", "personD");
    addConnection(graph, "personE", "personF");
    addConnection(graph, "personE", "personG");
    addConnection(graph, "personF", "personE");
    addConnection(graph, "personF", "personG");
    addConnection(graph, "personF", "personD");
    addConnection(graph, "personG", "personB");
    addConnection(graph, "personG", "personA");
    addConnection(graph, "personG", "personE");
    addConnection(graph, "personG", "personF");
    /*function to print the adjacency list representation of a graph*/
    printGraph(graph);
    /*function to free memory*/
    graphDestroy(graph);
	return 0;
}

    
    
    
    
    

    