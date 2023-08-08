#include <iostream>
#include <random>

const int NUM_CHANNELS = 79;  // Number of channels in the frequency hopping sequence
const int NUM_HOPS = 10000;   // Number of hops to simulate

int main() {
  // Seed the random number generator
  std::mt19937 rng(std::random_device{}());

  // Initialize the devices' channels
  std::uniform_int_distribution<int> channel_dist(0, NUM_CHANNELS - 1);  // Distribution for choosing a channel
  int device1_channel = channel_dist(rng);
  int device2_channel = channel_dist(rng);

  // Simulate the hops
  int num_collisions = 0;  // Number of collisions
  for (int i = 0; i < NUM_HOPS; ++i) {
    // Hop the devices
    device1_channel = channel_dist(rng);
    device2_channel = channel_dist(rng);

    // Check for a collision
    if (device1_channel == device2_channel) {
      ++num_collisions;
    }
  }

  // Calculate and print the collision probability
  double collision_probability = static_cast<double>(num_collisions) / NUM_HOPS;
  std::cout << "Collision probability: " << collision_probability << std::endl;

  return 0;
}

