
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <cmath>
#include <set>


using std::vector;
using std::pair;
using std::string;
namespace fs = std::filesystem;

/**** Double precision ********/ const double epsilon = 1e-5;   

std::ifstream fin;
std::ofstream fout;

struct Quantitites{
    struct Initial{
        double F = 0.0, S = 0.0;

        void operator+=(Initial a){F += a.F; S += a.S;}
        void operator/=(double a){F /= a; S /= a;}
        Initial operator*(double a){
            return {F*a, S*a};
        }
    };

    Initial m1, m2;

    friend std::istream& operator>>(std::istream& is, Quantitites& m){

        is >> m.m1.F >> m.m1.S >> m.m2.F >> m.m2.S; 

        return is;
    }
};




class Multihistogram{
    private :                                       //        T[0]      T[1]    ...  T[M]   
        vector<double> Temperature;                 // E[0] | H[0][0]  H[0][1]  ...  H[0][M] | <f(m)>(E[0])
        vector<double> Energy;                      // E[1] | H[1][0]  H[1][1]  ...  H[1][M] | <f(m)>(E[1])
        vector<vector<unsigned int>> Counts;        // ...  | ...      ...      ...  ...     | ...
                                                    // E[N] | H[N][0]  H[N][1]  ...  H[N][M] | <f(m)>(E[M])
        
        
    public :
        unsigned int Nener, Ntemp;
        vector<Quantitites> Magnetiziation;         

        Multihistogram(string, string);     // load Temperature dependent histogramm 'entire.txt' or 'block_.txt' 
                                            // in 'T__/' in target folder L__-_/

        static double logplus(double a, double b){
            return a > b ? a+log(1+exp(b-a)) : b+log(1+exp(a-b));
        }

        pair<double,double>* compute_logDOS(double=epsilon);    // computes logarithm density of states
};




int main(int argc, char* argv[]){

    string target = argv[1];                                            // 'relative path + name' of target-folder
    string output = argv[2];                                            // 'relative path + name' of output-file
    double T1 = std::stod(argv[3]); double T2 = std::stod(argv[4]);     // temperature-range of output-data
    unsigned int Ndata = std::stoul(argv[5]);                           // number of output-datapoints


    double L = std::stod(target.substr(target.find("L")+1));
    Multihistogram data(target, "entire.txt");
    pair<double, double>* logOmega = data.compute_logDOS(1e-10);




    //******************** Data examination ********************//
    fout.open(output);
        for(unsigned int i = 0; i < Ndata; ++i){
            double T = T1 + i*(T2-T1)/Ndata;
            double logZ = logOmega[0].second - logOmega[0].first/T;


            for(unsigned int E = 1; E < data.Nener; ++E){ 
                logZ = Multihistogram::logplus(logZ, logOmega[E].second-logOmega[E].first/T); 
            }

            //***** Determination of energy, heat, magnetization and susceptibility *****/
            double E1 = 0.0; double E2 = 0.0;
            Quantitites::Initial M1; Quantitites::Initial M2;
            for(unsigned int E = 0; E < data.Nener; ++E)
            {
                E1 += logOmega[E].first * exp(logOmega[E].second-logOmega[E].first/T-logZ);
                E2 += logOmega[E].first*logOmega[E].first * exp(logOmega[E].second-logOmega[E].first/T-logZ);

                M1 += data.Magnetiziation[E].m1 * exp(logOmega[E].second-logOmega[E].first/T-logZ);
                M2 += data.Magnetiziation[E].m2 * exp(logOmega[E].second-logOmega[E].first/T-logZ);
            }

            fout << T << "\t" << E1/(L*L) << "\t" << (E2-E1*E1)/(L*L*T*T)     
                      << "\t" << M1.F     << "\t" << (L*L)*(M2.F-M1.F*M1.F)/T
                      << "\t" << M1.S     << "\t" << (L*L)*(M2.S-M1.S*M1.S)/T << "\n";
        }
    fout.close();

    delete[] logOmega;
    
    return 0;
}






Multihistogram::Multihistogram(string directory, string file){

    std::set<fs::path> chronological;
    for(const auto& entry : fs::directory_iterator(directory)){
        chronological.insert(entry.path());
    }

    for(string folder : chronological){

        if(folder.find("T") != string::npos){
            Temperature.push_back(std::stod(folder.substr(folder.find("T")+1))/1000);
            for(vector<unsigned int>& h : Counts){h.push_back(0);}

            fin.open(folder + "/" + file);
                double E; unsigned int C; Quantitites m;

                if(Energy.size()==0){
                    while(fin >> E >> C >> m){
                        Energy.push_back(E);

                        vector<unsigned int> help(Temperature.size(),0); Counts.push_back(help);
                        Counts[Energy.size()-1][Temperature.size()-1] = C;

                        Magnetiziation.push_back(m);
                    }
                }else{
                    while(fin >> E >> C >> m){

                        bool append = true;
                        for(unsigned int i = 0; i < Energy.size(); ++i){
                            if(abs(Energy[i]-E)<epsilon){
                                Counts[i][Temperature.size()-1] = C;

                                Magnetiziation[i].m1 += m.m1;
                                Magnetiziation[i].m2 += m.m2;

                                append = false; break;
                            }
                        }

                        if(append){
                            Energy.push_back(E);

                            vector<unsigned int> help(Temperature.size(),0); Counts.push_back(help);
                            Counts[Energy.size()-1][Temperature.size()-1] = C;

                            Magnetiziation.push_back(m);
                        }
                    }
                }
            fin.close();
        }
    }

    Nener = Energy.size();
    Ntemp = Temperature.size();


    for(unsigned int E = 0; E < Nener; ++E){
        double Norm = 0.0;
        for(unsigned int T = 0; T < Ntemp; ++T){
            Norm += Counts[E][T];
        }
        Magnetiziation[E].m1 /= Norm; 
        Magnetiziation[E].m2 /= Norm;
    }
}





pair<double,double>* Multihistogram::compute_logDOS(double precision){

    pair<double,double>* logOmega = new pair<double,double>[Nener];     // output-pointer
    pair<double,double>* logZ = new pair<double,double>[Ntemp];         // logarithm of partionfunction
    double* logN = new double[Ntemp];                                   // logarithm of normalization constant of the histogram


    for(unsigned int T = 0; T < Ntemp; ++T){
        logZ[T] = {100.0, 0.0};
        logN[T] = 0.0;
        for(unsigned int E = 0; E < Nener; ++E){
            logN[T] += Counts[E][T];
        }
        logN[T] = log(logN[T]);
    }


    unsigned int accuracy; do{

        //********** Computing log(density of states) with current log(Z) **********//
        for(unsigned int E = 0; E < Nener; ++E){
            double logZaehler = Counts[E][0];
            double logNenner  = -Energy[E]/Temperature[0]-logZ[0].first+logN[0];

            for(unsigned int T = 1; T < Ntemp; ++T){
                logZaehler += Counts[E][T];
                logNenner = logplus(logNenner, -Energy[E]/Temperature[T]-logZ[T].first+logN[T]);
            }

            logZaehler = log(logZaehler);
            logOmega[E] = {Energy[E], logZaehler-logNenner};
        }


        //************** Computing next log(Z) with current log(dos) ***************//
        for(unsigned int T = 0; T < Ntemp; ++T){
            logZ[T].second = logZ[T].first;
            logZ[T].first = logOmega[0].second - logOmega[0].first/Temperature[T];

            for(unsigned int E = 1; E < Nener; ++E){
                logZ[T].first = logplus(logZ[T].first, logOmega[E].second - logOmega[E].first/Temperature[T]);
            }
        }


        //*************************** Computing accuracy ***************************//
        accuracy = 0;
        for(unsigned int T = 0; T < Ntemp; ++T ){
            if(abs(logZ[T].first-logZ[T].second) < precision){++accuracy;}
        }

    }while(accuracy < Ntemp);


    delete[] logZ;
    delete[] logN;

    return logOmega;
}



