#include "system.hpp"

//*************************** Helpfunctions ***************************//

//********** Single-Spinflip **********//
inline pair<int,int> System::dS(coordinate x, coordinate y){
    int dS1 = 2*Spin(x,y) * (Spin(x+1,y) + Spin(x-1,y) + Spin(x,y+1) + Spin(x,y-1));
    int dS2 = 2*Spin(x,y) * (Spin(x+1,y+1) + Spin(x+1,y-1) + Spin(x-1,y+1) + Spin(x-1,y-1));
    return {dS1,dS2};
}

inline void System::singleflip(coordinate x, coordinate y){
    MagnetizationF -= 2*Spin(x,y);
    MagnetizationV -= y%2==1 ? 2*Spin(x,y) : -2*Spin(x,y);
    MagnetizationH -= x%2==1 ? 2*Spin(x,y) : -2*Spin(x,y);

    *(Lattice+x+L*y) = !*(Lattice+x+L*y);
    ++NS;
}


//********** Line-Spinflip **********//
inline pair<int,int> System::dL(int l){
    int dL1 = 0; int dL2 = 0;
    if(l/L==1){
        coordinate line(l%L);
        for(coordinate y = 0; y < L; ++y){
            dL1 += 2*Spin(line,y) * (Spin(line+1,y) + Spin(line-1,y));
            dL2 += 2*Spin(line,y) * (Spin(line+1,y+1) + Spin(line+1,y-1) + Spin(line-1,y+1) + Spin(line-1,y-1));
        }
    }else{
        coordinate line(l);
        for(coordinate x = 0; x < L; ++x){
            dL1 += 2*Spin(x,line) * (Spin(x,line+1) + Spin(x,line-1));
            dL2 += 2*Spin(x,line) * (Spin(x+1,line+1) + Spin(x+1,line-1) + Spin(x-1,line+1) + Spin(x-1,line-1));  
        }
    }
    return{dL1,dL2};
}

inline void System::lineflip(int l){
    if(l/L==1){
        coordinate line(l%L);
        for(coordinate y = 0; y < L; ++y){
            MagnetizationF -= 2*Spin(line,y);
            MagnetizationV -= y%2==1 ? 2*Spin(line,y) : -2*Spin(line,y);
            MagnetizationH -= line%2==1 ? 2*Spin(line,y) : -2*Spin(line,y);

            *(Lattice+line+L*y) = !*(Lattice+line+L*y);
        }
    }else{
        coordinate line(l);
        for(coordinate x = 0; x < L; ++x){
            MagnetizationF -= 2*Spin(x,line);
            MagnetizationV -= line%2==1 ? 2*Spin(x,line) : -2*Spin(x,line);
            MagnetizationH -= x%2==1 ? 2*Spin(x,line) : -2*Spin(x,line);

            *(Lattice+x+L*line) = !*(Lattice+x+L*line);
        }
    }
    ++NL;
}

//*********************************************************************//





//******************** Constructors and Destructor ********************//
System::System(char inital_state, unsigned int seed){
    Lattice = new bool[L*L];

    gen = std::mt19937(seed);
    Uds = std::uniform_int_distribution<int>(0,L*L-1);
    Udl = std::uniform_int_distribution<int>(0,2*L-1);
    Uc = std::uniform_real_distribution<double>(0.0,1.0);


    switch(inital_state){
        case 'F':                               // ferromagnetic state
            for(int i = 0; i < L*L; ++i){
                *(Lattice+i) = true;
            }
            break;

        case 'V':                               // vertical stripped state
            for(int i = 0; i < L*L; ++i){
                *(Lattice+i) = (i/L)%2==1;
            }
            break;
        
        case 'H':                               // horizonatal stripped state
            for(int i = 0; i < L*L; ++i){
                *(Lattice+i) = (i%L)%2==1;
            }
            break;
        
        default:                                // uniform distributed state 
            std::bernoulli_distribution B(0.5);
            for(int i = 0; i < L*L; ++i){
                *(Lattice+i) = B(gen);
            }
            break;
    }

    MagnetizationF = 0;
    MagnetizationV = 0;
    MagnetizationH = 0;
    for(coordinate y = 0; y < L; ++y){
        for(coordinate x = 0; x < L ;++x){
            MagnetizationF += Spin(x,y);
            MagnetizationV += y%2==1 ? Spin(x,y) : -Spin(x,y);
            MagnetizationH += x%2==1 ? Spin(x,y) : -Spin(x,y);
        }
    }
}

System::~System(){
    delete[] Lattice;
}

//*********************************************************************//





//********************** Monte-Carlo Simualtions **********************//
void System::metropolis(double* boltzmannweigh, unsigned int sweeps){
    for(unsigned int i = 0; i < sweeps; ++i){
        for(int j = 0; j < L*L; ++j){
            int spin = Uds(gen);
            coordinate x(spin%L); coordinate y(spin/L);

            pair<int,int> dFaktor = dS(x,y);
            double dEnergy = J1*dFaktor.first + J2*dFaktor.second;

            if(dEnergy <= 0){
                singleflip(x,y);
            }else if(Uc(gen) < *(boltzmannweigh+5*(dFaktor.first/4+2)+dFaktor.second/4+2)){
                singleflip(x,y);
            }
        }
    }
}



void System::lineupdate(double* boltzmannweigh, double T, unsigned int sweeps){

    for(unsigned int i = 0; i < sweeps; ++i){
        for(int j = 0; j < L/2; ++j){
            pair<int,int> dFaktor; double dEnergy;

            for(int k = 0; k < L; ++k){
                int spin = Uds(gen);
                coordinate x(spin%L); coordinate y(spin/L);

                dFaktor = dS(x,y);
                dEnergy = J1*dFaktor.first + J2*dFaktor.second;

                if(dEnergy <= 0){
                    singleflip(x,y);
                }else if(Uc(gen) < *(boltzmannweigh+5*(dFaktor.first/4+2)+dFaktor.second/4+2)){
                    singleflip(x,y);
                }
            }

            int line = Udl(gen);
            dFaktor = dL(line);
            dEnergy = J1*dFaktor.first + J2*dFaktor.second;
            
            if(dEnergy <= 0){
                lineflip(line);
            }else if(Uc(gen) < exp(-dEnergy/T)){
                lineflip(line);
            }
        }
    }
}

//*********************************************************************//







//**************************** Correlation ****************************//
Run::Orderparameter System::correlation(unsigned int Nsimu){
    static unsigned int calls = 1;
    static bool Lattice0[L*L];
    static int MF0; static int MH0; static int MV0;


    double gammaF, gammaH, gammaV;
    if(calls==1){
        for(int i = 0; i < L*L; ++i){
            Lattice0[i] = *(Lattice+i);
        }

        MF0 = MagnetizationF;
        MH0 = MagnetizationH;
        MV0 = MagnetizationV;

        gammaF = 1.0;
        gammaH = 1.0;
        gammaV = 1.0;

    }else{
        int sum = 0;
        for(int i = 0; i < L*L; ++i){
            sum += Lattice0[i] != Lattice[i] ? -1 : 1;
        }

        auto gamma = [sum](int M0, int Mt){
            return (L*L*sum-M0*Mt)==(L*L*L*L-M0*Mt) ? 1.0 : (double)(L*L*sum-M0*Mt)/(L*L*L*L-M0*Mt);
        };

        gammaF = gamma(MF0, MagnetizationF);
        gammaH = gamma(MH0, MagnetizationH);
        gammaV = gamma(MV0, MagnetizationV);
    }
    
    
    calls < Nsimu ? ++calls : calls = 1;
    return {gammaF, gammaH, gammaV};
}


Run::Run(double T, unsigned int N){
    Temperature = T; Ndata = N; RS = 0.0; RL = 0.0;
    linear = new Orderparameter[N]; quadradic = new Orderparameter[N];
}

Run::~Run(){
    delete [] linear; delete[] quadradic;
}

Run::Run(const Run& orginal){
    Temperature = orginal.Temperature; 
    Ndata = orginal.Ndata; 
    RS = orginal.RS; RL = orginal.RL;
    linear = new Orderparameter[orginal.Ndata]; quadradic = new Orderparameter[orginal.Ndata];
    for(unsigned int t = 0; t < orginal.Ndata; ++t){
        *(linear+t) = *(orginal.linear+t);
        *(quadradic+t) = *(orginal.quadradic+t);
    }
}


void Run::operator/=(double a){
    RS /= a; RL /= a;
    for(unsigned int i = 0; i < Ndata; ++i){
        *(linear+i) /= a; *(quadradic+i) /= a;
    }
}

void Run::acceptancerate(long unsigned int ns, long unsigned int nl){
    #if LINEUPDATE
    RS += (double)ns/(L*L*Ndata/2); RL += (double)nl/(L*Ndata/2); 
    #else
    RS += (double)ns/(L*L*Ndata); 
    #endif    
}
//*********************************************************************//





