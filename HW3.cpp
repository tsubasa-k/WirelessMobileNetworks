#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h> 

using namespace std;

// Constants for the simulation
const int MIN_DEVICES = 20;
const int MAX_DEVICES = 70;
const int NUM_CHANNELS = 79;
const int SENSING_TIME = 4;

int main() {
// Seed the random number generator
srand(time(NULL));

// Generate a random number of devices between MIN_DEVICES and MAX_DEVICES
int numDevices[] = {20, 30, 40, 50, 60, 70};
for(int n = 0; n < 6; n++){
	char out[20];
	stringstream ss;
    // 輸出檔
	ss << "ans_"<< (n+1) << ".txt";
	string s;
	ss >> s; 
	strcpy(out, s.c_str());
	ofstream os(out);

	cout << "Device = " << numDevices[n] << endl;
	os << "Device = " << numDevices[n] << endl;
	// Generate the hopping patterns for each device
	int hoppingPatterns[numDevices[n]];
	for (int i = 0; i < numDevices[n]; i++) {
	hoppingPatterns[i] = i % NUM_CHANNELS;
	}


	// Simulate different values of ζ between 0.1 and 0.9
	for (double ζ = 0.1; ζ <= 0.9; ζ += 0.1) {
	// Mark the channels that are occupied for more than ζ as bad channels
	bool channels[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++) {
	channels[i] = (rand() / (double)RAND_MAX) < ζ;
	}

	// Continuously sense the channels for a period of 4 seconds to mark bad channels
	for (int t = 0; t < SENSING_TIME; t++) {
	  for (int i = 0; i < numDevices[n]; i++) {
	    // Use the channel re-mapping function to select a normal channel if the current channel is bad
	    int currentChannel = hoppingPatterns[i];
	    if (channels[currentChannel]) {
	      // Find the closest normal channel
	      int closestNormalChannel = -1;
	      int closestDistance = NUM_CHANNELS;
	      for (int j = 0; j < NUM_CHANNELS; j++) {
		if (!channels[j]) {
		  int distance = abs(currentChannel - j);
		  if (distance < closestDistance) {
		    closestNormalChannel = j;
		    closestDistance = distance;
		  }
		}
	      }

	      // If a normal channel was found, use it
	      if (closestNormalChannel != -1) {
		hoppingPatterns[i] = closestNormalChannel;
	      }
	    }
	  }
	}

	// Calculate the average collision probability for each device
	double collisionProbabilities[numDevices[n]];
	for (int i = 0; i < numDevices[n]; i++) {
	// Calculate the total number of collisions and the total number of times the channel is occupied
	int collisions = 0;
	int occupancy = 0;
	for (int j = 0; j < numDevices[n]; j++) {
	if (i != j && hoppingPatterns[i] == hoppingPatterns[j]) {
	collisions++;
	}
	occupancy++;
	}

	// Calculate the average collision probability for the device
	collisionProbabilities[i] = (double)collisions / occupancy;
	}

	// Print the results
	cout << "ζ = " << ζ << endl;
	cout << "Average collision probabilities: ";
	os << "ζ = " << ζ << endl;
	os << "Average collision probabilities: ";
	double sum = 0;
	for (int i = 0; i < numDevices[n]; i++) {
	//cout << "Device " << i << ": " << collisionProbabilities[i] << endl;
		sum += collisionProbabilities[i];
	}
	cout << sum/numDevices[n] << endl;
	os << sum/numDevices[n] << endl;
	}
	
}	

return 0;
}
