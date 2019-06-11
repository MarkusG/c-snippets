#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_NODES 13
#define TRUE 1
#define FALSE 0

// Given a map of nodes from stdin, find the shortest route from point A to B

void print_usage(char* arg0)
{
	printf("Usage: %s <origin> <destination>\n\n", arg0);
	printf("Finds the shortest route from origin to destination\n");
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		print_usage(argv[0]);
		return -1;
	}

	int distance[MAX_NODES][MAX_NODES]; // distance[i][j] is adjacent distance from node i to node j
	for (int i = 0; i < MAX_NODES; i++)
		for (int j = 0; j < MAX_NODES; j++)
		{
			if (i == j)
				distance[i][j] = 0;
			else
				distance[i][j] = INT_MAX;
		}

	// parse stdin as node adjacencies
	int a, b, c;
	while (scanf("%d %d %d\n", &a, &b, &c) > 0)
	{
		distance[a][b] = c;
		distance[b][a] = c;
	}

	int unvisited[MAX_NODES];
	for (int i = 0; i < MAX_NODES; i++)
		unvisited[i] = 1;

	int origin = atoi(argv[1]);
	int destination = atoi(argv[2]);
	int current = origin;

	int distance_from_origin[MAX_NODES];
	for (int i = 0; i < MAX_NODES; i++)
		distance_from_origin[i] = distance[origin][i];

	while (TRUE)
	{
		int shortest = INT_MAX;
		int shortest_node;
		for (int i = 0; i < MAX_NODES; i++)
		{
			if (!unvisited[i]) continue;
			if (current == i) continue;
			if (distance[current][i] < INT_MAX)
			{
				int cur_distance = distance_from_origin[current];
				int i_distance = distance_from_origin[i];
				int tentative_distance = cur_distance + distance[current][i];
				// Set distance of from origin to i to our newly calculated distance through the current node
				// if it's shorter; leave its previous distance if it's not
				distance_from_origin[i] = tentative_distance < i_distance ? tentative_distance : i_distance;
				if (distance_from_origin[i] < shortest)
				{
					shortest = distance_from_origin[i];
					shortest_node = i;
				}
			}
		}
		
		unvisited[current] = 0;
		current = shortest_node;
		printf("%d\n", current);
		if (shortest_node == destination) break; // we made it to the destination
	}
}
