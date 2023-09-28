// Date-
// Author- Saksham_Mahto

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

Node *createNode(int val)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = val;
    new->next = NULL;
    return new;
}

void addList(List **adjList, int u, int v)
{
    Node *new1, *new2, *temp;
    new1 = createNode(v);
    new2 = createNode(u);
    if (adjList[u]->head == NULL)
        adjList[u]->head = new1;
    else
    {
        temp = adjList[u]->head;
        while (temp->next)
            temp = temp->next;
        temp->next = new1;
    }
    if (adjList[v]->head == NULL)
        adjList[v]->head = new2;
    else
    {
        temp = adjList[v]->head;
        while (temp->next)
            temp = temp->next;
        temp->next = new2;
    }
}

void bfs(List *adjList[], int *vistited, int s_node, int *ans, int N, int ansIndex)
{
    int *queue = (int *)malloc(N * sizeof(int));
    int f = -1, r = -1;
    queue[++r] = s_node;
    vistited[s_node] = 1;
    while (f < r)
    {
        int frontnode = queue[++f];
        ans[ansIndex++] = frontnode;
        Node *temp = adjList[frontnode]->head;
        while (temp)
        {
            if (!vistited[temp->data])
            {
                queue[++r] = temp->data;
                vistited[temp->data] = 1;
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int n, e;
    printf("Enter the no. of nodes ans no. of edge in graph\n");
    scanf("%d%d", &n, &e);
    fflush(stdin);

    List **adjList = (List **)calloc(n, sizeof(List *));
    for (int i = 0; i < n; i++)
    {
        adjList[i] = (List *)malloc(sizeof(List));
        adjList[i]->head = NULL;
    }

    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        fflush(stdin);
        addList(adjList, u, v);
    }

    for (int i = 0; i < n; i++)
    {
        Node *temp = adjList[i]->head;
        printf("%d -> ", i);
        while (temp)
        {
            printf("%d, ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }

    int *ans = (int *)malloc(n * sizeof(int));
    int *visited = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            bfs(adjList, visited, i, ans, n, i);
    }
    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    
    for (int i = 0; i < n; i++)
    {
        Node *temp = adjList[i]->head;
        while (temp)
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
        free(adjList[i]);
    }
    free(adjList);
    free(visited);
    free(ans);

    return 0;
}