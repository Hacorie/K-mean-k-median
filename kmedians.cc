/* k-median algorithm */

#include "standard.h"

int main()
{
	float closest, distance;

	// seed random number generator
	srand( time(NULL) );

	// number of clusters
//	int k = sqrt( MAX_PLANTS/2 );
    int k = 20;
	// array to store center of clusters
	int medians[k][MAX_STATES];

	// call function to store plant data
	int numPlants = StoreData();

	// create first cycle of means
	for( int i=0; i<k; ++i )
	{
		// determine which plant will be center
		int center = rand() % numPlants;

		for( int j=0; j<MAX_STATES; ++j )
			medians[i][j] = plants[center].states[j];

	}// end loop

	int countStuff = 0;
	int keepGoing = true;
	while(keepGoing && countStuff < 1000)
	{
		keepGoing = chooseCluster(k, medians, numPlants);

		//Update Cluster Medians
		newMedian(k, medians, numPlants);
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
	
	return 0;

}//end main
