
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cmath>
#include <set>


using std::vector;
using std::pair;
using std::string;
namespace fs = std::filesystem;

std::ifstream fin;
std::ofstream fout;

double L;


class Quantities
{
private :
    struct Observables {
        double e1  = 0.0, e2  = 0.0;
        double mF1 = 0.0, mF2 = 0.0;
        double mS1 = 0.0, mS2 = 0.0;


        void operator+=(Observables a)
        {
            e1  += a.e1;  e2  += a.e2;
            mF1 += a.mF1; mF2 += a.mF2;
            mS1 += a.mS1; mS2 += a.mS2;

        }

        void operator*=(double a)
        {
            e1  *= a; e2  *= a;
            mF1 *= a; mF2 *= a;
            mS1 *= a; mS2 *= a;
        }

        void operator/=(double a)
        {
            e1  /= a; e2  /= a;
            mF1 /= a; mF2 /= a;
            mS1 /= a; mS2 /= a;
        }

        Observables operator*(Observables a)
        {
            return{e1  * a.e1,  e2  * a.e2,
                   mF1 * a.mF1, mF2 * a.mF2,
                   mS1 * a.mS1, mS2 * a.mS2};
        }

        Observables operator-(Observables a)
        {
            return{e1  - a.e1,  e2  - a.e2,
                   mF1 - a.mF1, mF2 - a.mF2,
                   mS1 - a.mS1, mS2 - a.mS2};
        }
    };

    vector<Observables> Timeseries;
    unsigned int N = 0, nJ = 0, NJ = 0;

public :
    Quantities(string);
    string jackknife(double);
};


int main(int argc, char* argv[])
{
    /***********************************************************************************
        mean Parameter Setup
        --------------------------
        Expected cli-arguments:
            argv[1]: 'relative path + name' of target-folder
            argv[2]: 'relative path + name' of output-file
            argv[3]: Lattice length

    ***********************************************************************************/

    std::string target = argv[1];
    std::string output = argv[2];
    L = std::stod(target.substr(target.find("L") + 1));

    std::set<fs::path> chronological;
    for (const auto& entry : fs::directory_iterator(target)) {
        chronological.insert(entry.path());
    }

    fout.open(output);
    for (string folder : chronological) {
        if (folder.find("T") != string::npos) {
            double T = std::stod(folder.substr(folder.find("T") + 1)) / 1000;
            Quantities simu_point(folder);
            fout << simu_point.jackknife(T) << "\n";
        }
    }
    fout.close();

    return 0;
}





Quantities::Quantities(string directory)
{
    for (const auto&  entry : fs::directory_iterator(directory)) {
        string file = fs::path(entry);


        if (file.find("block") != string::npos) {
            Observables input;

            fin.open(file);
            double E; unsigned int C;
            double MF1, MS1, MF2, MS2;
            nJ = 0;
            while (fin >> E >> C >> MF1 >> MS1 >> MF2 >> MS2) {

                input.e1  += E * (double)C / (L * L); input.e2  += E * E * (double)C / (L * L * L * L);
                input.mF1 += MF1;               input.mF2 += MF2;
                input.mS1 += MS1;               input.mS2 += MS2;

                nJ += C;
            }
            fin.close();

            ++NJ;
            Timeseries.push_back(input);
        }
    }

    N = NJ * nJ;
}


string Quantities::jackknife(double T)
{

    Observables mean;
    for (Observables o : Timeseries) {mean += o;}
    mean /= N;

    Observables observable{mean.e1, (L * L)*(mean.e2  - mean.e1 * mean.e1) / (T * T),
                           mean.mF1, (L * L)*(mean.mF2 - mean.mF1 * mean.mF1) / T,
                           mean.mS1, (L * L)*(mean.mS2 - mean.mS1 * mean.mS1) / T};
    mean *= N;

    Observables sigma;
    for (Observables o : Timeseries) {
        o = mean - o;
        o /= (double)(nJ * (NJ - 1));

        o.e2  = (L * L) * (o.e2  - o.e1 * o.e1) / (T * T);
        o.mF2 = (L * L) * (o.mF2 - o.mF1 * o.mF1) / T;
        o.mS2 = (L * L) * (o.mS2 - o.mS1 * o.mS1) / T;

        sigma += (o - observable) * (o - observable);
    }
    sigma *= (double)(NJ - 1) / NJ;

    std::stringstream out;
    out << T << "\t" << observable.e1  << "\t" << sqrt(sigma.e1)  << "\t" << observable.e2
        << "\t" << sqrt(sigma.e2)  << "\t"
        << observable.mF1 << "\t" << sqrt(sigma.mF1) << "\t" << observable.mF2 << "\t" << sqrt(
            sigma.mF2) << "\t"
        << observable.mS1 << "\t" << sqrt(sigma.mS1) << "\t" << observable.mS2 << "\t" << sqrt(
            sigma.mS2) << "\t";

    return out.str();
}

