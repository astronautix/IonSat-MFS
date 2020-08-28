#include <iostream>

#include "RFF.h"
#include "SGP4.h"


struct TimerEvent{ std::clock_t emissionTime; };
struct RequirePropagate{ };

void propagator(RequirePropagate const& propagation) {
    std::cout << "Initializing propagator" << std::endl;
    auto start = RFF::getTickCount();

    auto tle = Tle{"ISS (ZARYA)", "1 25544U 98067A   20237.19927083  .00000402  00000-0  15362-4 0  9990", "2 25544  51.6471  11.8824 0001577  59.0436 306.4808 15.49181383242568"};
    auto endTime = tle.Epoch().AddHours(6);
    SGP4 sgp4(tle);

    std::cout << "Starting propagation" << std::endl;
    auto calculated_pos = sgp4.FindPosition(endTime);
    std::cout << calculated_pos.ToGeodetic() << std::endl;

    auto end =  RFF::getTickCount();
    std::cout << "Propagation time : " << (end-start)/configTICK_RATE_HZ << std::endl;


}

void timerHandler(TimerEvent const& evt) {
    RFF::emit(RequirePropagate{});
}

void timer_15sec(void*) {
    while(1) {
        
        RFF::emit(TimerEvent{std::clock()});

        for(unsigned int cur = 0; cur < 15; cur++) {
            RFF::delay(1000);
            std::cout << cur << std::endl;
        }
        
    }
}

RFF::Task<9, 2048> timerTask{timer_15sec, "TimerTask"};

RFF::EventHandler<TimerEvent, 2> PropagatorTimer{timerHandler};
RFF::EventHandler<RequirePropagate> Propagator{propagator};
RFF::Module PropagationModule{PropagatorTimer, Propagator};

RFF::Setup setup{PropagationModule};

void rff_main() {}