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
const int NUM_BAD_CHANNELS = 40;
const double POISSON_PROBABILITY = 0.3;

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
	// Generate the channels
	bool channels[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++) {
	// Randomly select 39 channels that are not disturbed by noise
	if (i < NUM_CHANNELS - NUM_BAD_CHANNELS) {
	channels[i] = false;
	}
	// The remaining channels may be corrupted by noise with probability POISSON_PROBABILITY
	else {
	channels[i] = (rand() / (double)RAND_MAX) < POISSON_PROBABILITY;
	}
	}

	// Simulate different values of ζ between 0.1 and 0.9
	for (double ζ = 0.1; ζ <= 0.9; ζ += 0.1) {
	// Mark the channels that are occupied for more than ζ as bad channels
	int numBadChannels = 0;
	for (int i = 0; i < NUM_CHANNELS; i++) {
	if (channels[i] && (rand() / (double)RAND_MAX) > ζ) {
	numBadChannels++;
	}
	}
	// Calculate the average collision probability for each channel
	double collisionProbabilities[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++) {
	  // Calculate the total number of collisions and the total number of times the channel is occupied
	  int collisions = 0;
	  int occupancy = 0;
	  for (int j = 0; j < numDevices[n]; j++) {
	    if (channels[i]) {
	      collisions++;
	    }
	    occupancy++;
	  }

	  // Calculate the average collision probability for the channel
	  collisionProbabilities[i] = (double)collisions / occupancy;
	}

	// Print the results
	cout << "ζ = " << ζ << endl;
	cout << "Number of bad channels: " << numBadChannels << endl;
	cout << "Average collision probabilities: ";
	os << "ζ = " << ζ << endl;
	os << "Number of bad channels: " << numBadChannels << endl;
	//os << "Average collision probabilities: " ;
	int sum = 0;
	for (int i = 0; i < NUM_CHANNELS; i++) {
		cout << "Channel " << i+1 << ": " << collisionProbabilities[i] << endl;
		os << "Channel " << i+1 << ": " << collisionProbabilities[i] << endl;
		if (collisionProbabilities[i] == 1)
			sum += 1;
	}
	//cout << (double)sum/NUM_CHANNELS << endl;
	
	}
	cout << endl;
}

return 0;
}
