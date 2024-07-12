#ifndef SIMULATION_H
#define SIMULATION_H
#include <cassert>
#include <cstdlib>
#include "../queue/MyQueue.h"

void simulate_airport(bool debug = false);
void print_prologue(const unsigned int time_l,const unsigned int time_t,
    const double l_prop,const double t_prop, const unsigned int fuel,
    const unsigned int sim_time);

class Tarmac
{
    public:
        //how many seconds the Tarmac is occupied
        Tarmac(unsigned int sec = 0) : seconds_total(sec), seconds_left(0) {}

        void one_second() 
        {
            if (is_busy())
                --seconds_left;
        }
        // Precondition: The Tarmac is not busy.
        // Postcondition: The Tarmac has started simulating one landing / takeoff. 
        // Therefore, is_busy( ) will return true until the required number of 
        // simulated seconds has passed.
        void initiate(unsigned int x)
        {
            assert(!is_busy() && "OOPS: It was busy and you intialized the Tarmac!\n");
            seconds_total = x;
            seconds_left = seconds_total;
        }
        bool is_busy() const {return (seconds_left > 0); }
        std::string direction()
        {
            switch (seconds_total)
            {
            case 5:
                return "LANDING";
                break;
            case 15:
                return "TAKEOFF";
                break;
            default:
                return "NULL";
                break;
            }
        }
    private:
        unsigned int seconds_total;
        unsigned int seconds_left;
}; 
class Averager
{
    public:
        Averager() : sum(0), count(0) {}

        void next_number(double value) 
        {
            ++count;
            sum += value; 
        }
        unsigned int how_many_numbers() const { return count; }
        double average()const 
        { 
            assert(how_many_numbers() > 0);
            return (sum / count); 
        }
    private:
        unsigned int count;
        double sum;
};
class Bool_Source
{
    public:
        Bool_Source(double p = 0.0) : propability(p) 
        { 
        assert(p >= 0);
        assert(p <= 1);
        }
        
        //Postcondition: The return value is either true or false, 
        //with the probability of a true value being approximately 
        // p (from the constructor).
        bool query() const 
        {
            return (rand() < propability * RAND_MAX);
        }
    private:
        double propability;
};

void simulate_airport(bool debug)
{
    unsigned int time_to_land = 5, time_to_take_off = 15,
    fuel_limit = 20, simulation_time = 1440, currently = 1, 
    up_next = 0, next_departure = 0, planes_crashed = 0,
    up_next_departure = 0;

    double landing_probability = 0.10, takeoff_probability = 0.8;


    Bool_Source arrival(landing_probability);
    Bool_Source departure(takeoff_probability);

    Averager arrival_wait_times;
    Averager departure_wait_times;


    Tarmac tarmac;
    Queue<unsigned int> arrivals;
    Queue<unsigned int> departures;

    print_prologue(time_to_land, time_to_take_off, landing_probability, 
        takeoff_probability, fuel_limit, simulation_time);

    for (; currently <= simulation_time; currently++)
    {
        // Ask if plane is landing. . .
        if (arrival.query())
        {
            //push plane represented by current time in queue
            arrivals.push(currently);
        }
        //Ask if plane is departing. . .
        if (departure.query())
        {
            //push plane represented by current time in queue
            departures.push(currently);
        }


        //CHECK if tarmac is available 
        if ( !tarmac.is_busy() )
        {
            //No planes are landing -> plane can take off
            if ( arrivals.empty() )
            {
                    up_next_departure = departures.pop();
                    departure_wait_times.next_number(currently - up_next_departure);
                    tarmac.initiate(time_to_take_off);
            }else  //there are planes in the arrivals queue
            {
                up_next = arrivals.pop();
                //IF arriving plane exceeded fuel limit -> crashed
                if (currently - up_next > fuel_limit)
                    planes_crashed++;
                else
                {
                    //add the waiting time to the averager 
                    arrival_wait_times.next_number(currently - up_next);
                    //initate landing proceedure
                    tarmac.initiate(time_to_land);
                    next_departure = currently + 5;
                }
            }
        }
        tarmac.one_second();
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("%d planes landed\n", arrival_wait_times.how_many_numbers());
    printf("%d planes took off \n", departure_wait_times.how_many_numbers());
    printf("planes crashed!\t\t: %d\n", planes_crashed);
    cout << "Average waiting time to land:" << arrival_wait_times.average() << endl;
    cout << "Average waiting time to take off: " <<  departure_wait_times.average()<< endl;
}
void print_prologue(const unsigned int time_l,const unsigned int time_t,
    const double l_prop,const double t_prop, const unsigned int fuel,
    const unsigned int sim_time)
{
    printf("\n============================================");
    printf("\ntime to take off\t: %d", time_t);
    printf("\ntime to land\t\t: %d", time_l);
    printf("\npropabiltiy of landing  : %f", l_prop);
    printf("\npropability of takeoff  : %f", t_prop);
    printf("\nfuel - time to crash\t: %d", fuel);
    printf("\ntotal simulation time   : %d", sim_time);
    printf("\n\n");
}
#endif //SIMULATION_H

