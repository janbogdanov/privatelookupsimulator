#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */
#include <fstream>
#include <string>
#include <QElapsedTimer>

QElapsedTimer stopper;

/*struct time_measurements {
    QElapsedTimer start_global;
    QElapsedTimer end_global;
    QElapsedTimer protocol_start_timestamp;
    QElapsedTimer protocol_end_timestamp;

};*/

void begin_profile() {

    stopper.start();

}

void begin_protocol() {

    qint64 protocol_start_timestamp = stopper.nsecsElapsed();
    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "local ";
    time_log << protocol_start_timestamp;
    time_log << "\n";
    stopper.start();
}

void end_protocol() {

    //timer.protocol_end_timestamp.start();
    qint64 protocol_end_timestamp = stopper.nsecsElapsed();
    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
    time_log << "protocol ";
    time_log << protocol_end_timestamp;
    time_log << "\n";
    stopper.start();

}

void end_profile() {

    //qint64 local = timer.protocol_end_timestamp.nsecsElapsed();
    qint64 end = stopper.nsecsElapsed();
    std::ofstream time_log;
    time_log.open ("timelog.txt", std::ios_base::app);
   /* time_log << "local ";
    time_log << local;
    time_log << "\n";*/
    time_log << "local ";
    time_log << end;
    time_log << "\n";
}
