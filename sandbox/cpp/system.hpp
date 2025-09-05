#ifndef system_hpp
#define system_hpp

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <filesystem>


using std::pair;
using std::vector;


/**** Simulation-algorithm ****/ #define LINEUPDATE false
/**** lattice-length **********/ const int L = 120;
/**** NN-interaction **********/ const double J1 = 1.0;                                      
/**** NNN-interactions ********/ const double J2 = -0.5;
                                                                                                        



struct Run{
    double Temperature;     // temperture of simulation point
    unsigned int Ndata;     // number of collected measurements
    double RS, RL;          // rate of accepted spin-, line-flip-proposals 

    struct Orderparameter{
        double F = 0.0, H = 0.0, V = 0.0;

        void operator+=(Orderparameter a){F += a.F; H += a.H; V += a.V;}
        void operator/=(double a){F /= a; H /= a; V /= a;}
        Orderparameter operator*(Orderparameter a){return {F*a.F, H*a.H, V*a.V};}
    };

    Orderparameter* linear;         // pointer to spin-autocorrelation function
    Orderparameter* quadradic;      // pointer to spin-autocorrelation function to the square (for error estimation)


    Run(double, unsigned int);      // Constructor of simulation point 1: Temperature   2: number of measurements 
    Run(const Run&);                // Copy-constructor necessary for 'push_back()' function
    ~Run();                         // Destructor


    void operator/=(double);                                        // normalization for the mean of the runs 
    void acceptancerate(long unsigned int, long unsigned int);      // evaluation rate of accepted spin-, line-flip-proposals 
};






class System{
    private:
        bool* Lattice;                                          // spin-lattice
        int MagnetizationF, MagnetizationH, MagnetizationV;     // ferromagnetic-, horizontal-stripped- and vertical-stripped magnetization

        std::mt19937 gen;                                       // PRNG-engine Mersenne-Twister
        std::uniform_int_distribution<int> Uds;                 // single-spin selection probabilty
        std::uniform_int_distribution<int> Udl;                 // line-spin selection probability
        std::uniform_real_distribution<double> Uc;              // acceptance probability


        struct coordinate{                                                          // lattice indices with periodic boundary-conditions
            int c;                                                                  //
                                                                                    //
            coordinate(int i=0) : c(i){}                                            //
            bool operator==(coordinate x){return c==x.c;}                           //
            coordinate operator+(int i){coordinate sum{(L+c+i)%L}; return sum;}     //
            coordinate operator-(int i){coordinate dif{(L+c-i)%L}; return dif;}     //
            void operator++(void){++c;}                                             //
            operator int() const{return c;}                                         //
        };



        int Spin(coordinate x, coordinate y) const{return *(Lattice+x+L*y) ? 1 : -1;}   // help-functions
        pair<int,int> dS(coordinate, coordinate);                                       //
        void singleflip(coordinate, coordinate);                                        //
        pair<int,int> dL(int);                                                          //
        void lineflip(int);                                                             //


    public:
        System(char='U', unsigned int=1);   // Constructor of the system 1: 'F'=ferromagnetic,      'H'=horizonatal-stripped, 
                                            //                              'V'=vertical-stripped,  'U'= high temperature initial state 
                                            //                           2: PRNG-engine seed
        ~System();                          // Destructur of the system
        
        void metropolis(double*, unsigned int=1);           // conventional metropolis algorithm
        void lineupdate(double*, double, unsigned int=1);   // metropolis algorithm with line-flip changing-rule
        long unsigned int NS, NL;                           // number of accepted spinflips, lineflips


        Run::Orderparameter correlation(unsigned int);      // computes spin-autocorrelation function at time and temperture
};

#endif
