#ifndef PROFILER
#define PROFILER

#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <fstream>
#include <string>
#include <QElapsedTimer>

struct time_measurements {
    QElapsedTimer start_global;
    QElapsedTimer end_global;
    QElapsedTimer protocol_start_timestamp;
    QElapsedTimer protocol_end_timestamp;

};

void begin_profile(time_measurements& timer) {

    timer.start_global.start();

}

void begin_protocol(time_measurements& timer) {

    timer.protocol_start_timestamp.start();
    //qint64 local = timer.start_global.nsecsElapsed();
    /*std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "local ";
    time_log << local;
    time_log << "\n";*/
}

void end_protocol(time_measurements& timer) {

    //timer.protocol_end_timestamp.start();
    qint64 protocol = timer.protocol_start_timestamp.nsecsElapsed();
    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "protocol ";
    time_log << protocol;
    time_log << "\n";

}

void end_profile(time_measurements& timer) {

    //qint64 local = timer.protocol_end_timestamp.nsecsElapsed();
    qint64 end = timer.start_global.nsecsElapsed();
    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
   /* time_log << "local ";
    time_log << local;
    time_log << "\n";*/
    time_log << "end ";
    time_log << end;
    time_log << "\n";
}


#endif // PROFILER
