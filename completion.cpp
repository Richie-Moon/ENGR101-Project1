#include <iostream> // input-output library
#include <fstream>
#include <string>
#include <math.h>  // library for sin function
#include <vector>  // if using vectors
#include "wav.hpp" // make sure to include this helper library
// " " instead of <> means that library is in the same folder as your program

using namespace std;

// BPM: 110

int main(){
    int sample_rate = 44100; // samples per second, select value which provides good quality sound
    double duration = 0.5; // how long [seconds] it will sound
    double n_samples = duration * sample_rate; // if sound is "duration" seconds long and there are "sample_rate" samples per second
    // - how many samples are there altogether? What type should this variable be?
    double dt = duration/n_samples; // time between samples

    vector<int> waveform;

    int high_frequency = 1200; // pitch of the sound
    int low_frequency = 700;
    int volume = 6000;// 6000 is loud enough

    int cycles = 4; // number of high->low cycles
    const double pi = 3.1415926535;
    for (int num_cycle = 0; num_cycle < cycles ; num_cycle++) {
        for ( int i_sample = 0; i_sample < n_samples ; i_sample++){
            waveform.push_back(volume * sin(2 * pi * high_frequency * i_sample * dt));
        }
        for ( int i_sample = 0; i_sample < n_samples ; i_sample++){
            waveform.push_back(volume * sin(2 * pi * low_frequency * i_sample * dt));
        }
    }

    // generates sound file from waveform array, writes n_samples numbers
    // into sound wav file
    // should know sample_rate for sound timing
    // if using vector
    MakeWavFromVector("ambulance.wav",sample_rate, waveform); //file name can be changed but keep extension .wav

    waveform.clear(); //if using vectors
    return 0;
}