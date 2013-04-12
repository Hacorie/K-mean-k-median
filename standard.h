#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <cstdlib>

using namespace std;

const int MAX_PLANTS = 32000;
const int MAX_STATES = 70;

struct plant
{
	string name;
	int    states[MAX_STATES];
	int    currentCluster;
	int	   oldCluster;

}plants[MAX_PLANTS];

int StoreData()
{
	char junk;
	int numPlants;

	ifstream ifs;
	ifs.open( "plants2.data" );

	if( !ifs.is_open() )
	{
		cout << "Error opening file." << endl;
		return -1;
	}

	for( int i=0; !ifs.eof(); ++i )
	{
		getline( ifs, plants[i].name, '\t' );

		for( int j=0; j<70; ++j )
		{
			ifs >> plants[i].states[j];

		}// end reading in states

		ifs.get(junk);
		numPlants = i;

	}// end reading in plants

	ifs.close();	

	return numPlants;

}//end StoreData

float Distance( int x[], int y[] )
{
	int a = 0;
	int b = 0;
	int c = 0;

	for( int i=0; i<MAX_STATES; ++i )
	{
		if( x[i] == 1 )
			if( y[i] == 1 )
				++a;
			else
				++b;
		else
			if( y[i] == 1 )
				++c;
	}

	return ( (b+c) / float(a+b+c) );

}//end Distance

void newMedian(int k, int medians[][MAX_STATES], int numPlants)
{
	int arr[70];
	int counter = 0;
	for(int i = 0; i < 70; i++)
		arr[i] = 0;
		
	for(int i = 0; i < k; i++)
	{
		counter = 0;
		for(int j = 0; j < MAX_PLANTS; j++)
		{
			if(plants[j].currentCluster == i)
			{
				counter++;
				for(int l = 0; l<70; l++)
				{
						arr[l]+=plants[j].states[l];
				}
			}
		}
		
		for(int m = 0; m< 70; m++)
		{
			if( arr[m] > (counter/2) )
				medians[i][m] = 1;
			else
				medians[i][m] = 0;
		}
		
	}
}

bool chooseCluster(int k, int medians[][MAX_STATES], int numPlants)
{
	float closest;
	float distance;
	bool changed = false;
	// determine which cluster each plant goes into
	for( int i=0; i<numPlants; ++i )
	{
		closest = Distance( plants[i].states, medians[0] );
		plants[i].oldCluster = plants[i].currentCluster;
		plants[i].currentCluster = 0;
		for( int j=1; j<k; ++j )
		{
			distance = Distance( plants[i].states, medians[j] );
			if( distance < closest )
			{
				closest = distance;
				plants[i].currentCluster = j;

			}// end if

		}// end inner loop
		if(!changed && (plants[i].oldCluster != plants[i].currentCluster) )
			changed = true;
	}// end outer loop
	return changed;
}

void UpdateClusters(int k, int means[][MAX_STATES], int numPlants)
{
	int center[MAX_STATES] = {0};
	int numInCluster;
	
	for(int i = 0; i < k; i++)
	{
		numInCluster = 0;
		
		for(int j=0;j<numPlants;j++)
		{
			if(plants[j].currentCluster == i)
			{
				numInCluster++;
				for(int l = 0; l < MAX_STATES; l++)
				{
					center[l] += plants[j].states[l];
				}
			}
		}
		
		for(int j=0; j<MAX_STATES;j++)
		{
			float mean = float(center[j]) / numInCluster;
			if(mean < .5)
				means[i][j] = 0;
			else
				means[i][j] = 1;
		}
	}
}