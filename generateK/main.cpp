#include "system.hpp"


int main(int argc, char* argv[])
{  
    std::ifstream fin;
    std::ofstream fout;


    unsigned int Seed = std::stoul(argv[1]);                                // PRNG-seed
    double T = std::stod(argv[2]);                                          // Temperature of simulation point
    char initial_state = argv[3][0];                                        // initial state 
                                                                            //
    unsigned int Nequi  = std::stoul(argv[4]);                              // number of equilibartion-sweeps
    unsigned int Nsimu  = std::stoul(argv[5]); unsigned int Nsimu_old = 0;  // number of simulation-sweeps
    unsigned int Nblock = std::stoul(argv[6]); unsigned int Ncurr = 0;      // number of sweeps within a block
    
    std::string dir = "L" + std::to_string(L) + "-";    dir += initial_state;                               // Creates folder-system:
    std::system(("mkdir -p " + dir).c_str());           dir += "/T" + std::to_string((int)round(T*1000));   //  './L___-_/T_/' : {lattice-length}, {initial-state}, {Temperature*1000}
    std::system(("mkdir -p " + dir).c_str());                                                               //  contains:   entire histogram 'entire.txt' 
                                                                                                            //              blocked histograms 'block_.txt' : {number of block}
                                                                                                            //              save-point of system and chosen parameter 'save.txt'      




    System system(initial_state, Seed);
    Histogram histogram;
    double boltzmannweigh[25];                                          // evaluates boltzmann-factors of chosen temperture
    for(int i = 0; i < 5; ++i){ 
        for(int j = 0; j < 5; ++j){
            *(boltzmannweigh+j+5*i) = exp(-4*(J1*(i-2)+J2*(j-2))/T);
        } 
    }

    if(std::filesystem::exists(dir + "/save.txt")){                             
        std::cout << "SYSTEM LOADED FOR L=" << L << " AND T=" << T << "\n";

        fin.open(dir + "/save.txt");                        // loads system of previous run
            fin >> system;
            fin >> Seed >> Nequi >> Nsimu_old >> Nblock; 
            Ncurr = Nsimu_old/Nblock;
        fin.close();

       
        fin.open(dir + "/entire.txt");                      // loads entire histogram of previous run
            fin >> system;
            fin >> histogram;
        fin.close();

    }else{                                                                      
        std::cout << "SYSTEM CREATED FOR L=" << L << " AND T=" << T << "\n";
        #if LINEUPDATE
        system.lineupdate(boltzmannweigh, T, Nequi);    // equilibrates new created system
        #else
        system.metropolis(boltzmannweigh, Nequi);
        #endif
    }



    //********** Simulation-run **********//
    for(unsigned int i = 0; i < Nsimu/Nblock; ++i){
        Histogram histogramJ;

        for(unsigned int j = 0; j < Nblock; ++j){
            #if LINEUPDATE
            system.lineupdate(boltzmannweigh, T);
            #else
            system.metropolis(boltzmannweigh);
            #endif

            system.count(histogram);
            system.count(histogramJ);
        }

        fout.open(dir + "/block" + std::to_string(Ncurr+i+1) + ".txt");     // stores blocked histograms
            fout << histogramJ;
        fout.close();
    }




    fout.open(dir + "/entire.txt");                                         // stores entire histogram
        fout << histogram;
    fout.close();




    fout.open(dir + "/save.txt");                                           // stores save-point
        fout << system << "\n";
        fout << Seed << " " << Nequi << " " << Nsimu + Nsimu_old << " " << Nblock;
    fout.close();

    return 0;
}



