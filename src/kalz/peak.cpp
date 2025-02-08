
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
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

class Multihistogram{
    private :                                       //        T[0]      T[1]    ...  T[M]   
        vector<double> Temperature;                 // E[0] | H[0][0]  H[0][1]  ...  H[0][M] 
        vector<double> Energy;                      // E[1] | H[1][0]  H[1][1]  ...  H[1][M] 
        vector<vector<unsigned int>> Counts;        // ...  | ...      ...      ...  ...     
                                                    // E[N] | H[N][0]  H[N][1]  ...  H[N][M] 
        
        
    public :
        unsigned int Nener, Ntemp;

        Multihistogram(string, string);     // load Temperature dependent histogramm 'entire.txt' or 'block_.txt' 
                                            // in 'T__/' in target folder L__-_/

        static double logplus(double a, double b){
            return a > b ? a+log(1+exp(b-a)) : b+log(1+exp(a-b));
        }

        pair<double,double>* compute_logDOS(double=epsilon);    // computes logarithm density of states

        Multihistogram operator-(const Multihistogram&)const;
};




int main(int argc, char* argv[]){

    string target = argv[1];                                            // 'relative path + name' of target-folder
    string output = argv[2];                                            // 'relative path + name' of output-file
    unsigned int Nblock = std::stoul(argv[3]);                          // number of Jackknife blocks
    double T1 = std::stod(argv[4]); double T2 = std::stod(argv[5]);     // temperature-range of output-data
    unsigned int Ndata = std::stoul(argv[6]);                           // number of output-datapoints



    Multihistogram data_entire(target, "entire.txt");
    int L = std::stoi(target.substr(target.find("L")+1));



    //******************** Data examination ********************//
    double Tmax = 0.0, Cmax = 0.0; 
    pair<double,double>* peaks = new pair<double,double>[Nblock];
    for(unsigned int i = 1; i <= Nblock; ++i){

        Multihistogram data_block(target, "block" + std::to_string(i) + ".txt");
        data_block = data_entire-data_block;

        pair<double,double>* logOmega = data_block.compute_logDOS(1e-10);
        

        //***** Heat-data-Determination *****/
        vector<pair<double,double>> heat;
        for(unsigned int j = 0; j < Ndata; ++j){
            double T = T1 + j*(T2-T1)/Ndata;
            double logZ = logOmega[0].second - logOmega[0].first/T;

            for(unsigned int E = 1; E < data_block.Nener; ++E){ 
                logZ = Multihistogram::logplus(logZ, logOmega[E].second-logOmega[E].first/T); 
            }

            double E1 = 0.0; double E2 = 0.0;
            for(unsigned int E = 0; E < data_block.Nener; ++E){
                E1 += logOmega[E].first * exp(logOmega[E].second-logOmega[E].first/T-logZ);
                E2 += logOmega[E].first*logOmega[E].first * exp(logOmega[E].second-logOmega[E].first/T-logZ);
            }

            heat.push_back({T, (E2-E1*E1)/(T*T*L*L)});
        }

        delete[] logOmega;


        //***** Maximum-Determination  *****/
        pair<double,double> maximum = heat[0];
        for(pair<double,double> point : heat){
            if(maximum.second < point.second){
                maximum = point;
            }
        }

        peaks[i-1] = maximum;
        Tmax += maximum.first; Cmax += maximum.second;
        std::cout << "Tmax = " << maximum.first  << "\t" 
                  << "Cmax = " << maximum.second << "\n";
    }
    Tmax /= Nblock; Cmax /= Nblock;


    pair<double,double> sigma{0.0, 0.0};
    for(unsigned int i = 0; i < Nblock; ++i){
        sigma.first  += (Tmax-peaks[i].first)*(Tmax-peaks[i].first);
        sigma.second += (Cmax-peaks[i].second)*(Cmax-peaks[i].second);
    }
    sigma.first  = sqrt((Nblock-1)*sigma.first/Nblock); 
    sigma.second = sqrt((Nblock-1)*sigma.second/Nblock); 

    delete[] peaks;



    //***** Storeing data *****/
    std::stringstream ss;
    ss << Tmax << "\t" << sigma.first << "\t" << Cmax << "\t" << sigma.second;
    pair<int, string> entry_new{L, ss.str()};
    

    vector<pair<int,string>> data;
    fin.open(output);{
        string line; pair<int,string> entry; bool append = true;
        while(getline(fin, line)){
            ss.clear(); ss.str(line); 
            ss >> entry.first; ss.ignore(); getline(ss, entry.second);
            if(L==entry.first){
                data.push_back(entry_new);
                append = false;
            }else{
                data.push_back(entry);
            }
        }

        if(append){
            data.push_back(entry_new);
            std::sort(data.begin(),data.end());
        }
    }fin.close();


    fout.open(output);
        for(pair<int,string> entry : data){
            fout << entry.first << "\t" << entry.second << "\n";
        }
    fout.close();
    
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
                double E; unsigned int C;

                if(Energy.size()==0){
                    while(fin >> E >> C){
                        fin.ignore(200, '\n');

                        Energy.push_back(E);

                        vector<unsigned int> help(Temperature.size(),0); Counts.push_back(help);
                        Counts[Energy.size()-1][Temperature.size()-1] = C;
                    }
                }else{
                    while(fin >> E >> C){
                        fin.ignore(200, '\n');

                        bool append = true;
                        for(unsigned int i = 0; i < Energy.size(); ++i){
                            if(abs(Energy[i]-E)<epsilon){
                                Counts[i][Temperature.size()-1] = C;

                                append = false; break;
                            }
                        }

                        if(append){
                            Energy.push_back(E);

                            vector<unsigned int> help(Temperature.size(),0); Counts.push_back(help);
                            Counts[Energy.size()-1][Temperature.size()-1] = C;
                        }
                    }
                }
            fin.close();
        }
    }

    Nener = Energy.size();
    Ntemp = Temperature.size();
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


Multihistogram Multihistogram::operator-(const Multihistogram& input)const{
    Multihistogram output = *this;

    vector<unsigned int> deleting;
    for(unsigned int E1 = 0; E1 < output.Nener; ++E1){
        for(unsigned int E2 = 0; E2 < input.Nener; ++E2){

            if(abs(output.Energy[E1]-input.Energy[E2])<1e-10){

                unsigned int Nzero = 0;
                for(unsigned int T = 0; T < Ntemp; ++T){
                    output.Counts[E1][T] -= input.Counts[E2][T];
                    if(output.Counts[E1][T]==0){++Nzero;}
                }

                if(Nzero==Ntemp){
                    deleting.push_back(E1);
                }

                break;
            }
        }
    }

    for(unsigned int index : deleting){
        if(index == output.Nener-1){
            output.Energy.pop_back();
            output.Counts.pop_back();
        }else{
            output.Energy.erase(output.Energy.begin()+index);
            output.Counts.erase(output.Counts.begin()+index);  
        }   
    }
 
    output.Nener = output.Energy.size();

    return output;
}
