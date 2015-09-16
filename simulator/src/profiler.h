#ifndef PROFILER
#define PROFILER

#include <chrono>
#include <fstream>
#include <string>
#include <ctime>

struct time_measurements {
    std::chrono::time_point<std::chrono::high_resolution_clock> start_global;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_global;
    std::chrono::time_point<std::chrono::high_resolution_clock> protocol_start_timestamp;
    std::chrono::time_point<std::chrono::high_resolution_clock> protocol_end_timestamp;
};

void begin_profile(time_measurements& timer) {
    //using nanoseconds = std::chrono::duration<uint64_t, std::ratio<1,1000000000>>;
    timer.start_global = std::chrono::high_resolution_clock::now();

}

void begin_protocol(time_measurements& timer) {

    timer.protocol_start_timestamp = std::chrono::high_resolution_clock::now();

    //std::clock_t ctime = std::chrono::high_resolution_clock::to_time_t(time.start_global);

    std::chrono::duration<uint64_t, std::ratio<1,1000000000>> elapsed_time = timer.protocol_start_timestamp - timer.start_global;

    std::ofstream time_log;
    time_log.open ("timelog.txt");
    time_log << elapsed_time.count();

}



void end_protocol(time_measurements& timer) {

    timer.protocol_end_timestamp = std::chrono::high_resolution_clock::now();
}

void end_profile() {

}


#endif // PROFILER

