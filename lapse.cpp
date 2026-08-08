#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
using namespace std;

class Record{
    public:
    int record(){
        int interval_seconds = 5;

    
        while (true) {
            // 1. Get current time
            auto now = chrono::system_clock::now();
            // 2. Convert to seconds since 1970 (Unix timestamp)
            auto duration = now.time_since_epoch();
            auto seconds = chrono::duration_cast<chrono::seconds>(duration).count();
            // 3. Build the filename (e.g., "frame_1715102000.jpeg")
            string filename = "frame_" + to_string(seconds) + ".jpeg";

            // Take screenshot
            string command = "grim -t jpeg -q 80 " + filename;
            system(command.c_str());

            cout << "Captured: " << filename << endl;

            // Stop thread for the defined time difference
            this_thread::sleep_for(chrono::seconds(interval_seconds));
        }

        return 0;
    }
};

class Stitch{
    public:
    int stitch(){
        string output_filename;
        cout << "Enter output video filename (e.g., output.mp4): ";
        cin >> output_filename;
        string command = "ffmpeg -framerate 30 -pattern_type glob -i 'frame_*.jpeg' -c:v libx264 -pix_fmt yuv420p " + output_filename;
        system(command.c_str());
        return 0;
    }
};

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "record") {
        Record record;
        record.record();
    }
    else if (argc > 1 && string(argv[1]) == "ffmpeg") {
        Stitch stitch;
        stitch.stitch();
    }
    else {
        cout << "Usage: ./lapse [record|ffmpeg|help]" << endl;
        cout << "record: Start recording screenshots every 5 seconds." << endl;
        cout << "ffmpeg: Stitch the recorded screenshots into a video." << endl;
        cout << "help: Show this help message." << endl;
    }
    return 0;
}