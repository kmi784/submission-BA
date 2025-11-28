#include "system.hpp"

int main(int argc, char *argv[])
{
    /***********************************************************************************
        Simulation Parameter Setup
        --------------------------
        Expected cli-arguments:
            argv[1]: PRNG-seed
            argv[2]: Temperature
            argv[3]: Initial state "F" -> ferromagnetic, "H" -> horizontal stripped,
                     "V" -> vertical stripped or "U" -> uniformly distributed (default)
            argv[4]: Number of equilibartion sweeps
            argv[5]: Number of simulation-sweeps
            argv[6]: Number of sweeps per block
            argv[7]: Output directory

        Output directory structure:
            {Output directory}/L{L}-{state}/T{1000*T}/

        The directory contains:
            - entire.txt     : full histogram over all sweeps
            - block_*.txt    : histogram for each block
            - save.txt       : save-point of the system and parameters

    ***********************************************************************************/

    std::ifstream fin;
    std::ofstream fout;

    unsigned int Seed = std::stoul(argv[1]);
    double T = std::stod(argv[2]);
    char initial_state = argv[3][0];
    unsigned int Nequi = std::stoul(argv[4]);
    unsigned int Nsimu = std::stoul(argv[5]);
    unsigned int Nsimu_old = 0;
    unsigned int Nblock = std::stoul(argv[6]);
    unsigned int Ncurr = 0;

    std::string dir = argv[7];
    dir += "/L" + std::to_string(L) + "-" + initial_state;
    std::system(("mkdir -p " + dir).c_str());
    dir += "/T" + std::to_string((int)round(T * 1000));
    std::system(("mkdir -p " + dir).c_str());

    System system(initial_state, Seed);
    Histogram histogram;

    // evaluates boltzmann weights of chosen temperature
    double boltzmannweights[25];
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            *(boltzmannweights + j + 5 * i) =
                exp(-4 * (J1 * (i - 2) + J2 * (j - 2)) / T);
        }
    }

    if (std::filesystem::exists(dir + "/save.txt")) {
        std::cout << std::boolalpha;
        std::cout << "Loading previous simulation run for  L=" << L
                  << ", J2=" << J2 << ", line=" << LINEUPDATE << " and T=" << T
                  << "...\n";
        std::cout << std::noboolalpha;

        // loads system of previous run
        fin.open(dir + "/save.txt");
        fin >> system;
        fin >> Seed >> Nequi >> Nsimu_old >> Nblock;
        Ncurr = Nsimu_old / Nblock;
        fin.close();

        // loads entire histogram of previous run
        fin.open(dir + "/entire.txt");
        fin >> system;
        fin >> histogram;
        fin.close();
    } else {
        // equilibrates new created system
        std::cout << std::boolalpha;
        std::cout << "Creating system for L=" << L
                  << ", J2=" << J2 << ", line=" << LINEUPDATE << " and T=" << T
                  << "...\n";
        std::cout << std::noboolalpha;




#if LINEUPDATE
        system.lineupdate(boltzmannweights, T, Nequi);
#else
        system.metropolis(boltzmannweights, Nequi);
#endif
    }

    // simulation run
    for (unsigned int i = 0; i < Nsimu / Nblock; ++i) {
        Histogram histogramJ;

        for (unsigned int j = 0; j < Nblock; ++j) {
#if LINEUPDATE
            system.lineupdate(boltzmannweights, T);
#else
            system.metropolis(boltzmannweights);
#endif

            system.count(histogram);
            system.count(histogramJ);
        }

        // stores blocked histograms
        fout.open(dir + "/block" + std::to_string(Ncurr + i + 1) + ".txt");
        fout << histogramJ;
        fout.close();
    }

    // stores entire histogram
    fout.open(dir + "/entire.txt");
    fout << histogram;
    fout.close();

    // stores save-point
    fout.open(dir + "/save.txt");
    fout << system << "\n";
    fout << Seed << " " << Nequi << " " << Nsimu + Nsimu_old << " " << Nblock;
    fout.close();

    return 0;
}
