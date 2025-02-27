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


/**** Simulation-algorithm ****/ #define LINEUPDATE true
/**** lattice-length **********/ const int L = 120;
/**** NN-interaction **********/ const double J1 = 1.0;                                      
/**** NNN-interactions ********/ const double J2 = -0.5;
/**** Double precision ********/ const double epsilon = 1e-5;   






struct Histogram{
    vector<double> Energy;                      // energy-bins
    vector<unsigned int> Count;                 // histogram

    struct Orderparameter{
        double F,S;

        Orderparameter(int MF=0, int MH=0, int MV=0){
            F = (double)abs(MF)/(L*L);
            S = abs(MH)<=abs(MV) ? (double)abs(MV)/(L*L) : (double)abs(MH)/(L*L);
        }

        void operator+=(Orderparameter a){F+=a.F; S+=a.S;}
        Orderparameter operator*(Orderparameter a){
            Orderparameter out; out.F = F*a.F; out.S = S*a.S;
            return out;
        }
    };

    vector<Orderparameter> Magnetization1;      // first moment magnetization-list
    vector<Orderparameter> Magnetization2;      // second moment magnetization-list

    friend std::ostream& operator<<(std::ostream&, const Histogram&);
    friend std::istream& operator>>(std::istream&, Histogram&);

    void push_back(double E, unsigned int N, Orderparameter M){
        Energy.push_back(E); Count.push_back(N); Magnetization1.push_back(M); Magnetization2.push_back(M*M);
    }

    unsigned int size()const{return Energy.size();}
};






class System{
    private:
        bool* Lattice;                                          // spin-lattice
        double Energy;                                          // energy 
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

        friend std::ostream& operator<<(std::ostream&, const System&);
        friend std::istream& operator>>(std::istream&, System&);
        
        void metropolis(double*, unsigned int=1);           // conventional metropolis algorithm
        void lineupdate(double*, double, unsigned int=1);   // metropolis algorithm with line-flip changing-rule

        void count(Histogram&);                             // counts occurance energy and determines corresponding magnetization lists
};

#endif
