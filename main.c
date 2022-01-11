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
            int src = -1, dest = -1;
            scanf("%d %d", &src, &dest);
            int shortest_path_len = shortsPath_cmd(*head, src, dest);
            printf("Dijsktra shortest path: %d \n", shortest_path_len);
        }

        else if (command_from_user == 'T')
        {
            int tsp_shortest_path_len = 0;
            tsp_shortest_path_len = TSP_cmd(*head);
            printf("TSP shortest path: %d \n", tsp_shortest_path_len);
        }
    }
    deleteGraph_cmd(head);
    return 0;
}