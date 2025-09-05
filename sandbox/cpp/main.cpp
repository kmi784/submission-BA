#include "system.hpp"


int main(int argc, char* argv[])
{
    std::ofstream fout;


    srand(std::stoul(argv[1]));                                             // PRNG-seed
    double Tmin = std::stod(argv[2]); double Tmax = std::stod(argv[3]);     // temperature-range
    double dT = std::stod(argv[4]);                                         // step-length to next temperature
    char initial_state = argv[5][0];                                        // initial state
                                                                            //  
    unsigned int Nchange = std::stoul(argv[6]);                             // number of changing-sweeps between two temperatures
    unsigned int Nsimu = std::stoul(argv[7]);                               // number simulation-sweeps
    unsigned int Nruns = std::stoul(argv[8]);                               // number of repetitions of dependent run 

    std::string dir = "L" + std::to_string(L) + "-"; dir += initial_state;  // Creates folder
    std::system(("mkdir -p " + dir).c_str());                               // './L___-_/' : {lattice-length}, {initial-state}
                                                                            // contains:   spin-correlation as function of sweeps*acceptance-rate 'T___.txt' : {Temperature*1000}





    unsigned int* seed = new unsigned int[Nruns];                               // generates seeds for the different dependent runs
    for(unsigned int i = 0; i < Nruns; ++i){
        *(seed+i) = i+1;//(unsigned int)(rand() % 10000);
    }

    vector<Run> Autocorrelation;                                                // vector of temperatures and quantities of interest
    std::cout << "Temperature in [";
    if(initial_state == 'F' || initial_state == 'H' || initial_state == 'V'){   // begins with cold temp. and ends with hot temp.
        for(double T = Tmin; T < Tmax+dT; T += dT){
            Autocorrelation.push_back(Run{T,Nsimu}); std::cout << T << ",";
        }
    }else{                                                                      // begins with hot temp. and ends with cold temp.
        for(double T = Tmax; T > Tmin-dT; T -= dT){
            Autocorrelation.push_back(Run{T,Nsimu}); std::cout << T << ",";
        }
    }
    std::cout << "\b]\n";
    



    for(unsigned int i = 0; i < Nruns; ++i){
        System system(initial_state, seed[i]);

        for(Run& run : Autocorrelation){
            double boltzmannweigh[25];                                                      // evaluates boltzmann-factors of chosen temperture
            for(int j = 0; j < 5; ++j){ 
                for(int k = 0; k < 5; ++k){
                    *(boltzmannweigh+k+5*j) = exp(-4*(J1*(j-2)+J2*(k-2))/run.Temperature);
                } 
            }

            //********** Simulation-run **********//
            #if LINEUPDATE
            system.lineupdate(boltzmannweigh, run.Temperature, Nchange);
            #else
            system.metropolis(boltzmannweigh, Nchange);
            #endif

            system.NS = 0; system.NL = 0;
            for(unsigned int j = 0; j < Nsimu; ++j){
                #if LINEUPDATE
                system.lineupdate(boltzmannweigh, run.Temperature);
                #else
                system.metropolis(boltzmannweigh);
                #endif

                Run::Orderparameter gamma = system.correlation(Nsimu);
                *(run.linear+j) += gamma;
                *(run.quadradic+j) += gamma*gamma;
            }
            run.acceptancerate(system.NS, system.NL);
        }
    }



    for(Run& run : Autocorrelation){
        run /= Nruns;
        fout.open(dir + "/T" + std::to_string((int)round(run.Temperature*1000))  + ".txt");     // stores spin-correlation as function of sweeps*acceptance-rate corresponding temp.
            for(unsigned int i = 0; i < Nsimu; ++i){
                fout << i << "\t" << run.RS*i << "\t" << run.RL*i 
                          << "\t" << run.linear[i].F << "\t" << sqrt((run.quadradic[i].F-run.linear[i].F*run.linear[i].F)/Nruns) 
                          << "\t" << run.linear[i].H << "\t" << sqrt((run.quadradic[i].H-run.linear[i].H*run.linear[i].H)/Nruns)
                          << "\t" << run.linear[i].V << "\t" << sqrt((run.quadradic[i].V-run.linear[i].V*run.linear[i].V)/Nruns) 
                          << "\n";
            }
        fout.close();
    }

    return 0;
}


