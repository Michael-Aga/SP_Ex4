#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define INF 2147483647
#define TRUE 1
#define FALSE 0

int weight = INF;
int size;
pnode my_graph;

/* This is a little "modified" pnode */
typedef struct di_node
{
    pnode node;
    int in_use;
    int weight;
    struct di_node *prev_node;
    struct di_node *next;
} dnode, *pdnode;

/* This is a "comfy" function to release the list of nodes */
void free_list(pdnode pd_node_list)
{
    while (pd_node_list != NULL)
    {
        pdnode temp_list = pd_node_list;
        pd_node_list = pd_node_list->next;
        free(temp_list);
    }
}

/* This function give us the pd node */
pdnode get_pd_node(pdnode di_node_list, int node_id)
{
    while (di_node_list != NULL)
    {
        if (di_node_list->node->node_num == node_id)
        {
            return di_node_list;
        }

        di_node_list = di_node_list->next;
    }

    return NULL;
}

/* This function gives us the min pdnode */
pdnode min_pd(pdnode head)
{
    pdnode selected_min_pd = NULL;

    while (head != NULL)
    {
        if (!head->in_use && head->weight < INF && (selected_min_pd == NULL || selected_min_pd->weight < head->weight))
        {
            selected_min_pd = head;
        }
        head = head->next;
    }

    if (selected_min_pd != NULL)
    {
        selected_min_pd->in_use = TRUE;
    }

    return selected_min_pd;
}

/* This function bring us back a list of dijkstra nodes */
pdnode dijkstra_node_list(pnode start, int src)
{
    pdnode head = NULL;
    pdnode *current_node = &head;

    while (start != NULL)
    {
        (*current_node) = (pdnode)malloc(sizeof(dnode));
        if ((*current_node) == NULL)
        {
            printf("Couldnt allocate memory !");
            return NULL;
        }

        (*current_node)->node = start;
        if (start->node_num == src)
        {
            (*current_node)->prev_node = (*current_node);
            (*current_node)->weight = 0;
        }
        else
        {
            (*current_node)->prev_node = NULL;
            (*current_node)->weight = INF;
        }
        (*current_node)->in_use = FALSE;
        (*current_node)->next = NULL;
        current_node = &((*current_node)->next);
        start = start->next;
    }
    return head;
}

/* This function gives us the shortest path between 2 nodes */
int shortsPath_cmd(pnode head, int src, int dest)
{
    pdnode di_node_list = dijkstra_node_list(head, src);
    pdnode min_di = min_pd(di_node_list);

    while (min_di != NULL)
    {
        pedge min_edges = min_di->node->edges;

        while (min_edges != NULL)
        {
            pdnode min_di_node = get_pd_node(di_node_list, min_edges->endpoint->node_num);
            int distance = min_di->weight + min_edges->weight;

            if (min_di_node->weight > distance)
            {
                min_di_node->weight = distance;
                min_di_node->prev_node = min_di;
            }

            min_edges = min_edges->next;
        }
        min_di = min_pd(di_node_list);
    }

    int dis = get_pd_node(di_node_list, dest)->weight;
    free_list(di_node_list);
    if (dis == INF)
    {
        return -1;
    }
    else
    {
        return dis;
    }
}

/* This functuion gives us an arrray with a memory */
int *create_an_array(int size)
{
    int *new_arr = (int *)malloc(sizeof(int) * size);
    if (new_arr == NULL)
    {
        printf("Couldnt allocate memory for the array !");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &new_arr[i]);
    }

    return new_arr;
}

/* Just a helping function to copy an array */
int *copy_an_array(int *arr)
{
    int *copy_of_an_array = (int *)malloc(sizeof(int) * size);
    if (copy_of_an_array == NULL)
    {
        printf("Couldnt allocate memory for copying an array !");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        copy_of_an_array[i] = arr[i];
    }

    return copy_of_an_array;
}

/* Basic swap functuion */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Gives us back the sum of the weights */
void sum_weight(int *arr)
{
    int sum_of_weight = 0;

    for (int i = 0; i < size - 1; i++)
    {
        int distance = shortsPath_cmd(my_graph, arr[i], arr[i + 1]);
        if (distance == -1)
        {
            sum_of_weight = INF;
            return;
        }
        sum_of_weight += distance;
    }

    if (sum_of_weight < weight)
    {
        weight = sum_of_weight;
    }
}

/* This function gives us the permutations */
void permutations(int start, int *arr)
{
    if (start == size - 1)
    {
        sum_weight(arr);
        return;
    }

    for (int i = start; i < size; i++)
    {
        int *copy_of_an_array = copy_an_array(arr);
        swap(&copy_of_an_array[start], &copy_of_an_array[i]);
        permutations(start + 1, copy_of_an_array);
        free(copy_of_an_array);
    }
}

/* Given the "T" command followed by a k number followed by k nodes, we will print the length of the shortest route */
int TSP_cmd(pnode head)
{
    weight = INF;
    my_graph = head;
    size = -1;
    scanf("%d", &size);
    int *arr = create_an_array(size);
    int *copy = copy_an_array(arr);
    permutations(0, copy);
    free(arr);
    free(copy);
    if (weight == INF)
    {
        return -1;
    }
    else
    {
        return weight;
    }
}
