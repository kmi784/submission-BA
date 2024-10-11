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
}
//*********************************************************************//








//************ Constructors, Destructor and Streamoperator ************//
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

    //********** Computes initial observabels **********//
    Energy = 0.0;
    MagnetizationF = 0; MagnetizationV = 0; MagnetizationH = 0;
    for(coordinate y = 0; y < L; ++y){
        for(coordinate x = 0; x < L ;++x){
            Energy += -J1*Spin(x,y)*(Spin(x,y+1)+Spin(x+1,y))  
                      -J2*Spin(x,y)*(Spin(x+1,y+1)+Spin(x+1,y-1));
            MagnetizationF += Spin(x,y);
            MagnetizationV += y%2==1 ? Spin(x,y) : -Spin(x,y);
            MagnetizationH += x%2==1 ? Spin(x,y) : -Spin(x,y);
        }
    }
}



System::~System(){
    delete[] Lattice;
}



std::ostream& operator<<(std::ostream& os, const System& s){
    os << s.gen << " ";                 // stores current state of PRNG-engine

    for(int i = 0; i < L*L; ++i){       // stores current state 
        os << *(s.Lattice + i) << " ";
    }

    os << s.Energy << " "               // stores current observales
       << s.MagnetizationF << " "
       << s.MagnetizationH << " "
       << s.MagnetizationV;

    return os;
}



std::istream& operator>>(std::istream& is, System& s){
    is >> s.gen;                    // loads current state of PRNG-engine

    for(int i = 0; i < L*L; ++i){   // loads current state 
        is >> *(s.Lattice + i);
    }

    is >> s.Energy                  // loads current observales
       >> s.MagnetizationF
       >> s.MagnetizationH
       >> s.MagnetizationV;
       
    return is;
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
                Energy += dEnergy;
            }else if(Uc(gen) < *(boltzmannweigh+5*(dFaktor.first/4+2)+dFaktor.second/4+2)){
                singleflip(x,y);
                Energy += dEnergy;
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
                    Energy += dEnergy;
                }else if(Uc(gen) < *(boltzmannweigh+5*(dFaktor.first/4+2)+dFaktor.second/4+2)){
                    singleflip(x,y);
                    Energy += dEnergy;
                }
            }

            int line = Udl(gen);
            dFaktor = dL(line);
            dEnergy = J1*dFaktor.first + J2*dFaktor.second;
            
            if(dEnergy <= 0){
                lineflip(line);
                Energy += dEnergy;
            }else if(Uc(gen) < exp(-dEnergy/T)){
                lineflip(line);
                Energy += dEnergy;
            }
        }
    }
}
//*********************************************************************//







//***************************** Histogram *****************************//
void System::count(Histogram& h){                           // counts energy histogram and magnetization-lists
    if(h.size()==0)
    {
        h.push_back(
            Energy, 1, 
            Histogram::Orderparameter{MagnetizationF, MagnetizationH, MagnetizationV}
        );
    }
    else
    {
        for(unsigned int i = 0; i < h.size(); ++i)
        {
            if(abs(Energy-h.Energy[i])<epsilon)
            {
                ++h.Count[i];
                h.Magnetization1[i] += Histogram::Orderparameter{MagnetizationF, MagnetizationH, MagnetizationV};
                h.Magnetization2[i] += Histogram::Orderparameter{MagnetizationF, MagnetizationH, MagnetizationV}*
                                       Histogram::Orderparameter{MagnetizationF, MagnetizationH, MagnetizationV};
                break;
            }
            else
            {
                if(i==h.size()-1)
                { 
                    h.push_back(
                        Energy, 1,
                        Histogram::Orderparameter{MagnetizationF, MagnetizationH, MagnetizationV}
                    );
                    break; 
                }
            }
        }
    }
}



std::istream& operator>>(std::istream& is, Histogram& h){       // load energy histogram and magnetization lists
    double E; unsigned int C; 
    Histogram::Orderparameter M1, M2;
    
    while(is >> E >> C >> M1.F >> M1.S >> M2.F >> M2.S){
        h.Energy.push_back(E); h.Count.push_back(C);
        h.Magnetization1.push_back(M1); h.Magnetization2.push_back(M2);
    }
     
    return is;
}



std::ostream& operator<<(std::ostream& os, const Histogram& h){     // stores energy histogram and magnetization lists
    for(unsigned int i = 0; i < h.size(); ++i){
        os << h.Energy[i] << "\t"
           << h.Count[i]  << "\t"
           << h.Magnetization1[i].F << "\t" << h.Magnetization1[i].S << "\t"
           << h.Magnetization2[i].F << "\t" << h.Magnetization2[i].S << "\n";  
    }

    return os;
}
//*********************************************************************//