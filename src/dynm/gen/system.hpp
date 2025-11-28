#ifndef system_hpp
#define system_hpp

// simulation algorithm
#ifndef LINEUPDATE
    #define LINEUPDATE true
#endif

// lattice-length
#ifndef LATTICE_LENGTH
    #define LATTICE_LENGTH 32
#endif

// NN-interaction
#ifndef NN_INTERACTION
    #define NN_INTERACTION 1.0
#endif

// NN-interaction
#ifndef NNN_INTERACTION
    #define NNN_INTERACTION -0.5
#endif

// threads
#ifndef THREADS
    #define THREADS 4
#endif

#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

using std::pair;
using std::vector;

const int L = LATTICE_LENGTH;
const double J1 = NN_INTERACTION;
const double J2 = NNN_INTERACTION;
const unsigned int Nthread = THREADS;



class System;
struct Run {
    struct Orderparameter {
        double F = 0.0, H = 0.0, V = 0.0;

        void operator+=(Orderparameter a) {F += a.F; H += a.H; V += a.V;}
        void operator/=(double a) {F /= a; H /= a; V /= a;}
        Orderparameter operator*(Orderparameter a) {return {F * a.F, H * a.H, V * a.V};}
    };

    double Temperature; // temperture of simulation point
    unsigned int Ndata; // number of collected measurements
    double RS1, RL1; // rate of accepted spin-, line-flip-proposals (linear)
    Orderparameter *linear; // pointer to spin-autocorrelation function
    double RS2, RL2; // rate of accepted spin-, line-flip-proposals (quadradic)
    Orderparameter
    *quadradic; // pointer to spin-autocorrelation function to the square (for error estimation)

    Run(double, unsigned int); // 1: Temperature   2: number of measurements
    Run(const Run &); // necessary for 'push_back()' function
    ~Run();
    void operator/=(double);
    void acceptancerate(long unsigned int, long unsigned int);
};


class System
{
    /***********************************************************************************
        Represents the L×L spin lattice used in the Monte Carlo simulation.

        Expected arguments:
            arg[0]: Initial state
                        "F" -> ferromagnetic
                        "H" -> horizontal striped
                        "V" -> vertical striped
                        "U" -> uniformly random (default)
            arg[1]: PRNG seed for the Mersenne–Twister engine

        Notes
        -----
        The class manages:
        - the spin lattice (Lattice) stored as a boolean array (true = +1, false = -1),
        - three types of magnetization:
                - ferromagnetic (MagnetizationF)
                - horizontal striped (MagnetizationH)
                - vertical   striped (MagnetizationV)
        - the PRNG engine (std::mt19937) together with distributions for:
                - single-spin selection,
                - line-spin selection,
                - Metropolis acceptance probability
        - a coordinate type providing periodic boundary conditions on the lattice

        Simulation algorithms:
            - Conventional single-spin Metropolis updates
            - Line-flip updates under periodic boundary conditions

        Measurements:
            - Energy and magnetization statistics
            - Autocorrelation evaluation (correlation function)

    ***********************************************************************************/

private:
    bool *Lattice;
    int MagnetizationF, MagnetizationH, MagnetizationV;

    std::mt19937 gen;
    std::uniform_int_distribution<int> Uds; // single-spin selection probabilty
    std::uniform_int_distribution<int> Udl; // line-spin selection probability
    std::uniform_real_distribution<double> Uc; // acceptance probability

    // lattice indices with periodic boundary-conditions
    struct coordinate {
        int c;
        coordinate(int i = 0) : c(i) {}
        bool operator==(coordinate x) {return c == x.c;}
        coordinate operator+(int i) {coordinate sum{(L + c + i) % L}; return sum;}
        coordinate operator-(int i) {coordinate dif{(L + c - i) % L}; return dif;}
        void operator++(void) {++c;}
        operator int() const {return c;}
    };

    // helper
    int Spin(coordinate x, coordinate y) const {return *(Lattice + x + L * y) ? 1 : -1;}
    pair<int, int> dS(coordinate, coordinate);
    void singleflip(coordinate, coordinate);
    pair<int, int> dL(int);
    void lineflip(int);

public:
    System(char = 'U', unsigned int = 1);
    System(const System &); // necessary for array initialization
    ~System();
    System &operator=(const System &); // necessary for array initialization
    void metropolis(double*, unsigned int = 1); // metropolis algorithm
    void lineupdate(double*, double, unsigned int = 1); // metropolis + lineflip algorithm
    long unsigned int NS, NL;

    // computes spin-autocorrelation function at time and temperture
    Run::Orderparameter correlation(unsigned int);
};

#endif
