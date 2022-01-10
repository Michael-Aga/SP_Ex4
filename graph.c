#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* When the user inserts "A" the program will create a new graph */
void build_graph_cmd(pnode *head)
{
    deleteGraph_cmd(head);

    int node_quantity = 0;
    char node_id;
    scanf("%d", &node_quantity); // get the number of nodes in the graph from the user

    for (int i = 0; i < node_quantity; i++)
    {
        scanf("%c", &node_id);
        insert_node_cmd(head);
    }
}

/* This is a helping function that help us find the index of the node we are looking for */
pnode get_graph_node(pnode *head, int node_id)
{
    pnode current_node = *head;
    while (current_node)
    {
        if (current_node->node_num == node_id)
        {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

/* For the "B" command, we will create a new vertex with the id number that the user will give us and the edges of the node */
void insert_node_cmd(pnode *head)
{
    int node_id;
    scanf("%d", &node_id);
    pnode new_node = get_graph_node(head, node_id);

    if (new_node == NULL) // If there isnt a node with that id create a new one
    {
        new_node = (pnode)malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Couldnt allocate memory !");
            return;
        }
        else
        {
            new_node->node_num = node_id;
            new_node->next = *head;
            new_node->edges = NULL;
            *head = new_node;
        }
    }

    else
    {
        pedge current_edge = new_node->edges;
        while (current_edge)
        {
            pedge temp_current_edge = current_edge->next;
            free(current_edge);
            current_edge = temp_current_edge;
        }
        new_node->edges = NULL;
    }

    pedge *last_edge = &(new_node->edges);
    int destination_node_id = -1;

    int finished = scanf("%d", &destination_node_id);

    while (finished != 0 && finished != EOF)
    {
        pnode destination_node = get_graph_node(head, destination_node_id);
        if (destination_node == NULL)
        {
            destination_node = (pnode)malloc(sizeof(node));
            if (destination_node == NULL)
            {
                printf("Couldnt allocate memory");
                return;
            }
            else
            {
                destination_node->node_num = destination_node_id;
                destination_node->edges = NULL;
                destination_node->next = *head;
                *head = destination_node;
            }
        }
        int chosen_edge_weight = -1;
        scanf("%d", &chosen_edge_weight);

        *last_edge = (pedge)malloc(sizeof(edge));
        if ((*last_edge) == NULL)
        {
            return;
        }
        (*last_edge)->endpoint = destination_node;
        (*last_edge)->weight = chosen_edge_weight;
        (*last_edge)->next = NULL;
        last_edge = &((*last_edge)->next);
        finished = scanf("%d", &destination_node_id);
    }
}

/* This function prints the graph for self debugging */
void printGraph_cmd(pnode head)
{
    pnode current_node = head;
    if (current_node == NULL)
    {
        printf("The graph is NULL check the code !");
    }

    while (current_node)
    {
        printf("Node %d: ", current_node->node_num);
        pedge current_edge = current_node->edges;

        while (current_edge != NULL)
        {
            printf("dest %d: weight %d, ", current_edge->endpoint->node_num, current_edge->weight);
            current_edge = current_edge->next;
        }
        printf("\n");
        current_node = current_node->next;
    }
}

/* This functuion deletes the garph*/
void deleteGraph_cmd(pnode *head)
{
    pnode current_node = *head;

    if (current_node == NULL)
    {
        return;
    }

    while (current_node)
    {
        pedge current_edge = current_node->edges;

        while (current_edge != NULL)
        {
            pedge temp_current_edge = current_edge->next;
            free(current_edge);
            current_edge = temp_current_edge;
        }

        pnode temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    *head = NULL;
}

/* For the command "D" with a successor number we will delete the vertex we received */
void delete_node_cmd(pnode *head)
{
    int node_to_delete;
    scanf("%d", &node_to_delete);

    pnode current_node = *head;
    pnode *delete_head = NULL;
    pnode prev_node = NULL;

    if (current_node->node_num == node_to_delete)
    {
        delete_head = head;
    }

    while (current_node != NULL)
    {
        if (current_node->next != NULL && current_node->next->node_num == node_to_delete)
        {
            prev_node = current_node;
        }

        if (current_node->edges != NULL && current_node->edges->endpoint->node_num == node_to_delete)
        {
            pedge temp_next_edge = current_node->edges->next;
            free(current_node->edges);
            current_node->edges = temp_next_edge;

            current_node = current_node->next;
            continue;
        }

        pedge current_edge = current_node->edges;

        if (current_edge != NULL)
        {
            while (current_edge->next)
            {
                if (current_edge->next->endpoint->node_num == node_to_delete)
                {
                    pedge temp = current_edge->next->next;
                    free(current_edge->next);
                    current_edge->next = temp;
                }

                else
                {
                    current_edge = current_edge->next;
                }
            }
        }
        current_node = current_node->next;
    }

    if (delete_head != NULL)
    {
        pedge head_edges = (*delete_head)->edges;
        while (head_edges)
        {
            pedge temp = head_edges->next;
            free(head_edges);
            head_edges = temp;
        }

        pnode temp_head = *delete_head;
        *delete_head = temp_head->next;
        free(temp_head);
    }

    else if (prev_node != NULL)
    {
        pnode remove_node = prev_node->next;
        pedge remove_node_edges = remove_node->edges;

        while (remove_node_edges)
        {
            pedge temp = remove_node_edges->next;
            free(remove_node_edges);
            remove_node_edges = temp;
        }

        prev_node->next = remove_node->next;
        free(remove_node);
    }
}
