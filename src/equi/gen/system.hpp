#ifndef system_hpp
#define system_hpp

// simulation algorithm
#ifndef LINEUPDATE
    #define LINEUPDATE true
#endif

// lattice-length
#ifndef LATTICE_LENGTH
    #define LATTICE_LENGTH 30
#endif

// NN-interaction
#ifndef NN_INTERACTION
    #define NN_INTERACTION 1.0
#endif

// NN-interaction
#ifndef NNN_INTERACTION
    #define NNN_INTERACTION -0.5
#endif

// double precision
#ifndef PRECISION
    #define PRECISION 1e-5
#endif

#include <iostream>
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
const double epsilon = PRECISION;


struct Histogram {
    struct Orderparameter {
        double F, S;

        Orderparameter(int MF = 0, int MH = 0, int MV = 0)
        {
            F = (double)abs(MF) / (L * L);
            S = abs(MH) <= abs(MV) ? (double)abs(MV) / (L * L) : (double)abs(MH) / (L * L);
        }

        void operator+=(Orderparameter a) {F += a.F; S += a.S;}
        Orderparameter operator*(Orderparameter a)
        {
            Orderparameter out; out.F = F * a.F; out.S = S * a.S;
            return out;
        }
    };

    vector<double> Energy; // energy-bins
    vector<unsigned int> Count; // histogram
    vector<Orderparameter> Magnetization1; // first moment magnetization-list
    vector<Orderparameter> Magnetization2; // second moment magnetization-list

    friend std::ostream &operator<<(std::ostream &, const Histogram &);
    friend std::istream &operator>>(std::istream &, Histogram &);

    void push_back(double E, unsigned int N, Orderparameter M)
    {
        Energy.push_back(E); Count.push_back(N); Magnetization1.push_back(M);
        Magnetization2.push_back(M * M);
    }

    unsigned int size()const {return Energy.size();}
};


class System
{
    /***********************************************************************************
        Represents the L×L spin lattice and provides all update and measurement routines
        for the Monte Carlo simulation.

        Expected arguments:
            arg[0]: Initial state "F" -> ferromagnetic, "H" -> horizontal stripped,
                    "V" -> vertical stripped or "U" -> uniformly distributed (default)
            arg[1]: PRNG seed

        Notes
        -----
        The class manages:
        - the spin lattice (`Lattice`) stored as a boolean array (true = +1, false = -1),
        - the total energy of the configuration,
        - three types of magnetization:
                - ferromagnetic
                - horizontal stripes
                - vertical   stripes
        - the PRNG engine (std::mt19937) and the distributions used for:
                - random spin selection,
                - random line selection,
                - Metropolis acceptance tests.


        Simulation algorithms:
            - Standard single-spin Metropolis algorithm.
            - Combined update scheme: Metropolis + optional line flips.

        Measurements:
            - Updates energy histograms and magnetization statistics.

    ***********************************************************************************/

private:
    bool *Lattice; // energy
    double Energy;
    int MagnetizationF; // ferromagnetic
    int MagnetizationH; // horizontal-stripped
    int MagnetizationV; // vertical-stripped

    std::mt19937 gen; // PRNG-engine Mersenne-Twister
    std::uniform_int_distribution<int> Uds; // single spin selection probability
    std::uniform_int_distribution<int> Udl; // line spin selection probability
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
    ~System();

    friend std::ostream &operator<<(std::ostream &, const System &);
    friend std::istream &operator>>(std::istream &, System &);

    void metropolis(double*, unsigned int = 1); // metropolis algorithm
    void lineupdate(double*, double, unsigned int = 1); // metropolis + lineflip algorithm

    // counts occurrence energy and determines corresponding magnetization lists
    void count(Histogram &);
};

#endif
