/* kmeans++ algorithm */

#include "standard.h"

/*
    1. Choose one point uniformly at random from (x_1, x_2, ..., x_n), and add it to C.
    2. For each point x_i, set D(x_i) to be the distance between x_i and the nearest point in C.
    3. Choose a real number y uniformly at random between 0 and D(x_1)^2 + D(x_2)^2 + ... + D(x_n)^2.
    4. Find the unique integer i so that
         D(x_1)^2 + D(x_2)^2 + ... D(x_i)^2 >= y > D(x_1)^2 + D(x_2)^2 + ... + D(x_(i-1))^2.
    5. Add x_i to C.
    6. Repeat Steps 2-5 until we have chosen k centers.

*/

int main()
{
	float closest, distance;

	// seed random number generator
	srand( time(NULL) );

	// number of clusters
//	int k = sqrt( MAX_PLANTS/2 );
    int k = 20;
	// array to store center of clusters
	int kmeansplusplus[k][MAX_STATES];

	// call function to store plant data
	int numPlants = StoreData();

	int distArr[numPlants];
	//1. Choose one point uniformly at random from (x_1, x_2, ..., x_n), and add it to C.
	int center = rand() % numPlants;
	float dist = 0.0;
	float distsum = 0.0;
	for( int j=0; j<MAX_STATES; ++j )
		kmeansplusplus[0][j] = plants[center].states[j];
		
	//2. For each point x_i, set D(x_i) to be the distance between x_i and the nearest point in C.
	for(int i = 0; i < numPlants; i++)
	{
		distArr[i] = Distance(kmeansplusplus[0], plants[i].states);
		distsum += (distArr[i]*distArr[i]);
	}
	for(int j = 1; j<k; j++)
	{
		//3. Choose a real number y uniformly at random between 0 and D(x_1)^2 + D(x_2)^2 + ... + D(x_n)^2.
		int distsum2 = int(distsum);
		int y = rand() % distsum2;
		//cout << y << endl;
		//    4. Find the unique integer i so that
		//     D(x_1)^2 + D(x_2)^2 + ... D(x_i)^2 >= y > D(x_1)^2 + D(x_2)^2 + ... + D(x_(i-1))^2.
		float ysum = 0.0;
		for(int i = 0; i < numPlants; i++)
		{
			if(ysum < y)
				ysum+=(distArr[i]*distArr[i]);
			else
			{
				center = i;
				break;
			}
		}
		
		distsum = 0;
		//Add the new center to a cluster.
		for(int l = 0; l<MAX_STATES; l++)
		{
			kmeansplusplus[j][l] = plants[center].states[l];
		}
		
		for(int i = 0; i < numPlants; i++)
		{
			distArr[i] = Distance(kmeansplusplus[j], plants[i].states);
			distsum += (distArr[i]*distArr[i]);
		}
	}
	
	int countStuff = 0;
	int keepGoing = true;
	while(keepGoing && countStuff != 1000)
	{
		keepGoing = chooseCluster(k, kmeansplusplus, numPlants);

		//Update Cluster Medians
		UpdateClusters(k, kmeansplusplus, numPlants);
		countStuff++;
		cout << countStuff << endl;
	}

	for(int i = 0; i < k; i++)
	{
		printf("Cluster: %d\n", i);
		for(int j = 0; j < numPlants; j++)
		{
			if(plants[j].currentCluster == i)
			{
				cout << "\t" << plants[j].name << endl;
			}
		}
		printf("\n");
	}
	
	printf("The number of times we reclustered data before it converged: %d\n", countStuff);
	
/*	
	// create first cycle of means
	for( int i=0; i<k; ++i )
	{
		// determine which plant will be center
		int center = rand() % numPlants;

		for( int j=0; j<MAX_STATES; ++j )
			kmeansplusplus[i][j] = plants[center].states[j];

		
	}// end loop

	int countStuff = 0;
	int keepGoing = true;
	while(keepGoing)
	{
		keepGoing = chooseCluster(k, kmeansplusplus, numPlants);

		//Update Cluster Medians
		newMedian(k, kmeansplusplus, numPlants);
		countStuff++;
		cout << countStuff << endl;
	}

	for(int i = 0; i < k; i++)
	{
		printf("Cluster: %d\n", i);
		for(int j = 0; j < numPlants; j++)
		{
			if(plants[j].currentCluster == i)
			{
				cout << "\t" << plants[j].name << endl;
			}
		}
		printf("\n");
	}
	
	printf("The number of times we reclustered data before it converged: %d\n", countStuff);
*/	
	return 0;

}//end main
