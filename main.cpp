#include <iostream> // input-output library
#include <fstream>
#include <math.h>  // library for sin function
#include <vector>  // if using vectors
#include "wav.hpp" // make sure to include this helper library
// " " instead of <> means that library is in the same folder as your program

using namespace std;

// https://dsp.stackexchange.com/questions/46598/mathematical-equation-for-the-sound-wave-that-a-piano-makes

int main() {
    int sample_rate = 44100; // samples per second, select value which provides good quality sound
    double tempoBPM = 144.0;
    double tempoBPS = tempoBPM/60.0;
    double duration = 1/tempoBPS; // how long [seconds] it will sound
    double n_samples = duration * sample_rate; // if sound is "duration" seconds long and there are "sample_rate" samples per second


    // - how many samples are there altogether? What type should this variable be?
    double dt = duration/n_samples; // time between samples

    vector<int> waveform;

    ifstream frequencies;
    frequencies.open("../odetojoy.txt");
    string text;
    while (getline (frequencies, text)) {
        double frequency = stod(text);

        int volume = 25 ;

        const double pi = 3.1415926535;
        for ( int i_sample = 0; i_sample < n_samples ; i_sample++) {

            double time = i_sample * dt;
            double exponential = exp(-0.0004 * 5 * pi * frequency * time);

            double y = volume * sin(2 * pi * frequency * time) * exponential;

            // Overtones
            for (int i = 1; i < 6; i++) {
                y += sin((i + 1) * 2 * pi * frequency * time) * exponential / pow(2, i);
            }
            y += sin(0.5 * 2 * pi * frequency * time) * exponential * 2;

            // Saturation
            y += y * y * y;
            y *= 1 + 16 * time * exp(-6 * time);

            waveform.push_back(y);
        }

    }



    // generates sound file from waveform array, writes n_samples numbers
    // into sound wav file
    // should know sample_rate for sound timing
    // if using vector
    MakeWavFromVector("piano.wav",sample_rate, waveform); //file name can be changed but keep extension .wav

    waveform.clear();
    return 0;
}