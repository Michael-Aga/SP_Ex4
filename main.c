#include <stdio.h>
#include "graph.h"

int main()
{
    pnode temp_head = NULL;
    pnode *head = &temp_head;
    char command_from_user;

    while (scanf("%c", &command_from_user) != EOF)
    {
        if (command_from_user == 'A')
        {
            build_graph_cmd(head);
        }

        else if (command_from_user == 'B')
        {
            insert_node_cmd(head);
        }

        else if (command_from_user == 'D')
        {
            delete_node_cmd(head);
        }

        else if (command_from_user == 'S')
        {
            int src, dest;
            scanf("%d %d", &src, &dest);
            printf("Dijsktra shortest path: %d \n", shortsPath_cmd(*head, src, dest));
        }

        else if (command_from_user == 'T')
        {
            printf("TSP shortest path: %d \n", TSP_cmd(*head));
        }
    }
    deleteGraph_cmd(head);
    return 0;
}