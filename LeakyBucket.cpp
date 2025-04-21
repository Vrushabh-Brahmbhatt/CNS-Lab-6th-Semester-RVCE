#include <iostream>
#include <cstdlib>
#include <unistd.h> // for sleep()

using namespace std;

void leakyBucket(int &bucket, int packetSize, int bucketSize, int outputRate) {
    int time = 0;

    // Check if the packet fits
    if (bucket + packetSize > bucketSize) {
        cout << "\nBucket Overflow! Packet of size " << packetSize << " bytes is dropped.\n";
    } else {
        bucket += packetSize;
        cout << "\nPacket of size " << packetSize << " bytes added to the bucket.\n";
    }

    // Simulate leaky output
    while (bucket > 0) {
        sleep(1);
        time++;

        if (bucket >= outputRate) {
            bucket -= outputRate;
            cout << "\nTime " << time << " Sec: " << outputRate << " bytes Outputted from bucket.\n";
        } else {
            cout << "\nTime " << time << " Sec: " << bucket << " bytes Outputted (last packet).\n";
            bucket = 0;
        }
    }

    cout << "\nBucket Output Successful.\n";
}

int main() {
    int bucket = 0;
    int bucketSize, outputRate, numPackets, packetSize, delay, time = 0;

    cout << "Enter Bucket Size (Maximum Capacity): ";
    cin >> bucketSize;

    cout << "Enter Output Rate (bytes/sec): ";
    cin >> outputRate;

    cout << "Enter Number of Packets: ";
    cin >> numPackets;

    for (int i = 0; i < numPackets; ++i) {
        delay = rand() % 3;
        sleep(delay);
        time += delay;

        packetSize = rand() % 1000;
        cout << "\n---------------------------\n";
        cout << "Time " << time << " Sec\n";
        cout << "Packet Number " << i << "\n";
        cout << "Packet Size " << packetSize << " bytes\n";

        leakyBucket(bucket, packetSize, bucketSize, outputRate);
    }

    return 0;
}

