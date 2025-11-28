#include "system.hpp"


// single spinflip
inline pair<int, int> System::dS(coordinate x, coordinate y)
{
    int dS1 = 2 * Spin(x, y) * (Spin(x + 1, y) + Spin(x - 1, y) + Spin(x, y + 1) + Spin(x,
                                y - 1));
    int dS2 = 2 * Spin(x, y) * (Spin(x + 1, y + 1) + Spin(x + 1, y - 1) + Spin(x - 1,
                                y + 1) + Spin(x - 1, y - 1));
    return {dS1, dS2};
}

inline void System::singleflip(coordinate x, coordinate y)
{
    MagnetizationF -= 2 * Spin(x, y);
    MagnetizationV -= y % 2 == 1 ? 2 * Spin(x, y) : -2 * Spin(x, y);
    MagnetizationH -= x % 2 == 1 ? 2 * Spin(x, y) : -2 * Spin(x, y);

    *(Lattice + x + L * y) = !*(Lattice + x + L * y);
    ++NS;
}


// line spinflip
inline pair<int, int> System::dL(int l)
{
    int dL1 = 0; int dL2 = 0;
    if (l / L == 1) {
        coordinate line(l % L);
        for (coordinate y = 0; y < L; ++y) {
            dL1 += 2 * Spin(line, y) * (Spin(line + 1, y) + Spin(line - 1, y));
            dL2 += 2 * Spin(line, y) * (Spin(line + 1, y + 1) + Spin(line + 1,
                                        y - 1) + Spin(line - 1, y + 1) + Spin(line - 1, y - 1));
        }
    } else {
        coordinate line(l);
        for (coordinate x = 0; x < L; ++x) {
            dL1 += 2 * Spin(x, line) * (Spin(x, line + 1) + Spin(x, line - 1));
            dL2 += 2 * Spin(x, line) * (Spin(x + 1, line + 1) + Spin(x + 1, line - 1) + Spin(x - 1,
                                        line + 1) + Spin(x - 1, line - 1));
        }
    }
    return{dL1, dL2};
}

inline void System::lineflip(int l)
{
    if (l / L == 1) {
        coordinate line(l % L);
        for (coordinate y = 0; y < L; ++y) {
            MagnetizationF -= 2 * Spin(line, y);
            MagnetizationV -= y % 2 == 1 ? 2 * Spin(line, y) : -2 * Spin(line, y);
            MagnetizationH -= line % 2 == 1 ? 2 * Spin(line, y) : -2 * Spin(line, y);

            *(Lattice + line + L * y) = !*(Lattice + line + L * y);
        }
    } else {
        coordinate line(l);
        for (coordinate x = 0; x < L; ++x) {
            MagnetizationF -= 2 * Spin(x, line);
            MagnetizationV -= line % 2 == 1 ? 2 * Spin(x, line) : -2 * Spin(x, line);
            MagnetizationH -= x % 2 == 1 ? 2 * Spin(x, line) : -2 * Spin(x, line);

            *(Lattice + x + L * line) = !*(Lattice + x + L * line);
        }
    }
    ++NL;
}






// constructors, copyconstructor and destructor
System::System(char inital_state, unsigned int seed)
{
    Lattice = new bool[L * L];

    gen = std::mt19937(seed);
    Uds = std::uniform_int_distribution<int>(0, L * L - 1);
    Udl = std::uniform_int_distribution<int>(0, 2 * L - 1);
    Uc = std::uniform_real_distribution<double>(0.0, 1.0);

    switch (inital_state) {
        // ferromagnetic state
        case 'F':
            for (int i = 0; i < L * L; ++i) {
                *(Lattice + i) = true;
            }
            break;

        // vertical stripped state
        case 'V':
            for (int i = 0; i < L * L; ++i) {
                *(Lattice + i) = (i / L) % 2 == 1;
            }
            break;

        // horizonatal stripped state
        case 'H':
            for (int i = 0; i < L * L; ++i) {
                *(Lattice + i) = (i % L) % 2 == 1;
            }
            break;

        // uniform distributed state
        default:
            std::bernoulli_distribution B(0.5);
            for (int i = 0; i < L * L; ++i) {
                *(Lattice + i) = B(gen);
            }
            break;
    }

    // computation of initial observables
    MagnetizationF = 0;
    MagnetizationV = 0;
    MagnetizationH = 0;
    for (coordinate y = 0; y < L; ++y) {
        for (coordinate x = 0; x < L ; ++x) {
            MagnetizationF += Spin(x, y);
            MagnetizationV += y % 2 == 1 ? Spin(x, y) : -Spin(x, y);
            MagnetizationH += x % 2 == 1 ? Spin(x, y) : -Spin(x, y);
        }
    }
}

System::System(const System& orginal)
{
    Lattice = new bool[L * L];
    for (int i = 0; i < L * L; ++i) {
        *(Lattice + i) = *(orginal.Lattice + i);
    }

    gen = orginal.gen;
    Uds = std::uniform_int_distribution<int>(0, L * L - 1);
    Udl = std::uniform_int_distribution<int>(0, 2 * L - 1);
    Uc = std::uniform_real_distribution<double>(0.0, 1.0);

    MagnetizationF = orginal.MagnetizationF;
    MagnetizationH = orginal.MagnetizationH;
    MagnetizationV = orginal.MagnetizationV;
}

System::~System()
{
    delete[] Lattice;
}

System &System::operator=(const System& orginal)
{
    for (int i = 0; i < L * L; ++i) {
        *(Lattice + i) = *(orginal.Lattice + i);
    }

    gen = orginal.gen;
    Uds = std::uniform_int_distribution<int>(0, L * L - 1);
    Udl = std::uniform_int_distribution<int>(0, 2 * L - 1);
    Uc = std::uniform_real_distribution<double>(0.0, 1.0);

    MagnetizationF = orginal.MagnetizationF;
    MagnetizationH = orginal.MagnetizationH;
    MagnetizationV = orginal.MagnetizationV;

    return *this;
}


// mc-simulation
void System::metropolis(double* boltzmannweights, unsigned int sweeps)
{
    for (unsigned int i = 0; i < sweeps; ++i) {
        for (int j = 0; j < L * L; ++j) {
            int spin = Uds(gen);
            coordinate x(spin % L); coordinate y(spin / L);

            pair<int, int> dFaktor = dS(x, y);
            double dEnergy = J1 * dFaktor.first + J2 * dFaktor.second;

            if (dEnergy <= 0) {
                singleflip(x, y);
            } else if (Uc(gen) < * (boltzmannweights + 5 * (dFaktor.first / 4 + 2) + dFaktor.second / 4
                                    + 2)) {
                singleflip(x, y);
            }
        }
    }
}

void System::lineupdate(double* boltzmannweights, double T, unsigned int sweeps)
{

    // L instead of L/2, because same time unite as metropolis
    for (unsigned int i = 0; i < sweeps; ++i) {
        for (int j = 0; j < L; ++j) {
            pair<int, int> dFaktor; double dEnergy;

            for (int k = 0; k < L; ++k) {
                int spin = Uds(gen);
                coordinate x(spin % L); coordinate y(spin / L);

                dFaktor = dS(x, y);
                dEnergy = J1 * dFaktor.first + J2 * dFaktor.second;

                if (dEnergy <= 0) {
                    singleflip(x, y);
                } else if (Uc(gen) < * (boltzmannweights + 5 * (dFaktor.first / 4 + 2) + dFaktor.second / 4
                                        + 2)) {
                    singleflip(x, y);
                }
            }

            int line = Udl(gen);
            dFaktor = dL(line);
            dEnergy = J1 * dFaktor.first + J2 * dFaktor.second;

            if (dEnergy <= 0) {
                lineflip(line);
            } else if (Uc(gen) < exp(-dEnergy / T)) {
                lineflip(line);
            }
        }
    }
}


// correlation
Run::Orderparameter System::correlation(unsigned int Nsimu)
{
    static unsigned int calls = 1;
    static bool Lattice0[L * L];
    static int MF0; static int MH0; static int MV0;


    double gammaF, gammaH, gammaV;
    if (calls == 1) {
        for (int i = 0; i < L * L; ++i) {
            Lattice0[i] = *(Lattice + i);
        }

        MF0 = MagnetizationF;
        MH0 = MagnetizationH;
        MV0 = MagnetizationV;

        gammaF = 1.0;
        gammaH = 1.0;
        gammaV = 1.0;

    } else {
        int sum = 0;
        for (int i = 0; i < L * L; ++i) {
            sum += Lattice0[i] != Lattice[i] ? -1 : 1;
        }

        auto gamma = [sum](int M0, int Mt) {
            return (L * L * sum - M0 * Mt) == (L * L * L * L - M0 * Mt) ? 1.0 : (double)(
                       L * L * sum - M0 * Mt) / (L * L * L * L - M0 * Mt);
        };

        gammaF = gamma(MF0, MagnetizationF);
        gammaH = gamma(MH0, MagnetizationH);
        gammaV = gamma(MV0, MagnetizationV);
    }


    calls < Nsimu ? ++calls : calls = 1;
    return {gammaF, gammaH, gammaV};
}

Run::Run(double T, unsigned int N)
{
    Temperature = T; Ndata = N; RS1 = 0.0; RL1 = 0.0; RS2 = 0.0; RL2 = 0.0;
    linear = new Orderparameter[N]; quadradic = new Orderparameter[N];
}

Run::~Run()
{
    delete [] linear; delete[] quadradic;
}

Run::Run(const Run& orginal)
{
    Temperature = orginal.Temperature;
    Ndata = orginal.Ndata;
    RS1 = orginal.RS1; RL1 = orginal.RL1;
    RS2 = orginal.RS2; RL2 = orginal.RL2;
    linear = new Orderparameter[orginal.Ndata];
    quadradic = new Orderparameter[orginal.Ndata];
    for (unsigned int t = 0; t < orginal.Ndata; ++t) {
        *(linear + t) = *(orginal.linear + t);
        *(quadradic + t) = *(orginal.quadradic + t);
    }
}

void Run::operator/=(double a)
{
    RS1 /= a; RL1 /= a;
    RS2 /= a; RL2 /= a;
    for (unsigned int i = 0; i < Ndata; ++i) {
        *(linear + i) /= a; *(quadradic + i) /= a;
    }
}

void Run::acceptancerate(long unsigned int ns, long unsigned int nl)
{
    RS1 += (double)ns / (L * L * Ndata);
    RL1 += (double)nl / (L * Ndata);
    RS2 += (double)ns / (L * L * Ndata) * (double)ns / (L * L * Ndata);
    RL2 += (double)nl / (L * Ndata) * (double)nl / (L * Ndata);
}
