#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __INFINITY__ INT_MAX
typedef struct {
    int x;
	int y;
} Stone;

double DistanceWithCell(int p_x, int p_y, int p2_x, int p2_y);
double min(double left, double right);
double max(double left, double right);



int main (void) {
    int __nb_stone__; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_stone__;
	int test_id = 1;
	while( __nb_stone__ > 0 ) {
		// printf("Case %d\n", test_id);

		Stone * stone_list = (Stone *) malloc(sizeof(Stone) * __nb_stone__);
		double ** distances = (double **) malloc(sizeof(double *) * __nb_stone__);

		for(int __stone_nb = 0; __stone_nb < __nb_stone__; ++__stone_nb) {
			Stone current_stone;
			getline(cin, line);
			stringstream myString(line);
			myString >> current_stone.x >> current_stone.y;
			// printf("-- Adding stone (%d,%d)\n", current_stone.x, current_stone.y);
			stone_list[__stone_nb] = current_stone;

			distances[__stone_nb] = (double *) malloc(sizeof(double) * __nb_stone__);
		}



		for(int i = 0; i < __nb_stone__; ++i) {
			for(int j = 0; j < __nb_stone__; ++j) {
				int x1,y1,x2,y2;

				x1 = stone_list[i].x;
				y1 = stone_list[i].y;
				x2 = stone_list[j].x;
				y2 = stone_list[j].y;
				distances[i][j] = DistanceWithCell(x1, y1, x2, y2);
				distances[j][i] = distances[i][j];
				// printf("[%d,%d] distance (%d,%d,%d,%d) %f\n", i, j, x1, y1, x2, y2, distances[i][j]);
			}
		}


		//	Floyd Warshall
		for(int k = 1; k < __nb_stone__; ++k) {

			for(int source_id = 0; source_id < __nb_stone__ / 2; ++source_id) {

				for(int target_id = 1; target_id < __nb_stone__; ++target_id) {

					double tmp = max(distances[source_id][k], distances[k][target_id]);
					// printf("tmp %f VS current %f\n", tmp, distances[source_id][target_id]);
					distances[source_id][target_id] = min(tmp, distances[source_id][target_id]);
				}
			}
		}
		printf("Scenario #%d\n", test_id);
		printf("Frog Distance: %.3f\n\n", distances[0][1]);


		getline(cin, line);
		stringstream myString(line);
		myString >> __nb_stone__;

		// for(int i = 0; i < __nb_stone__ - 1; i++) {
		// 	free(distances[i]);
		// }
		// free(distances);
		free(stone_list);

		test_id = test_id + 1;
	}


    return EXIT_SUCCESS;
}



double min(double left, double right) {
	if(left < right) {
		return left;
	}
	return right;
}

double max(double left, double right) {
	if(left > right) {
		return left;
	}
	return right;
}


double DistanceWithCell(int p_x, int p_y, int p2_x, int p2_y) {
    return sqrt( pow((p2_x - p_x), 2) + pow((p2_y - p_y), 2));
}