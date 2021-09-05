#include<bits/stdc++.h>
#include<gnuplot-iostream.h>
#include<fstream>

int main(){
    Gnuplot gp;

    std::ifstream dataFile("precip.2017");
    gp<<"set terminal pngcairo size 2160,1440\n";
    gp<<"set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb \"white\" behind\n";
    gp<<"set output 'plot.png'\n";
    gp<<"set key right nobox\n";
    gp<<"set key font \",24\"\n";
    //gp<<"set key samplen 40\n";
    //gp<<"set border 0\n";
    gp<<"unset ytics\n";
    gp<<"unset xtics\n";

    std::string in;
    std::string plotString = "plot ";

    std::vector<std::vector<std::vector<double>>> q;
    std::vector<double> rain; 
    double maxRain = 0.0;
 
    while(getline(dataFile, in)){
        std::stringstream strm(in);
        std::string token;
        std::vector<std::string> tokens;
        while(getline(strm, token, ' ')){
            if(token.size() > 0){
                tokens.push_back(token);
            }
        }

        std::vector<std::vector<double>> coords;
        coords.push_back({std::stod(tokens[0])-0.25, std::stod(tokens[1])+0.25});
        coords.push_back({std::stod(tokens[0])-0.25, std::stod(tokens[1])-0.25});
        coords.push_back({std::stod(tokens[0])+0.25, std::stod(tokens[1])-0.25});
        coords.push_back({std::stod(tokens[0])+0.25, std::stod(tokens[1])+0.25});
        
        q.push_back(coords);
        double totalRain = 0.0;
        for(int i = 2; i < tokens.size(); i++){
            totalRain += std::stod(tokens[i]);
        }
        if(totalRain > maxRain){
            maxRain = totalRain;
        }
        rain.push_back(totalRain);
    }

    for(int u = 0; u < rain.size(); u++){
        double preci = ((rain[u])/maxRain);

        std::string ans;
        std::stringstream stm;
        
        if(preci <= 0.01){
            ans = "0.01";
        }else{
            stm<<std::fixed<<std::setprecision(2)<<preci;
            ans = stm.str();
        }
        //std::cout<<ans<<std::endl;
        plotString += "'-' with filledcurves fc rgb \"blue\" fs transparent solid " + ans + " noborder notitle, ";
    }
    std::stringstream st;
    st<<std::fixed<<std::setprecision(2)<<maxRain;
    std::string maxString = st.str();
    maxString += "mm";
    plotString += "'data.dat' index 0 with lines lc \"black\" lw 1 notitle, '' index 1 with filledcurves fc \"white\" fs solid 1 border lc \"black\" lw 1 notitle, NaN with filledcurves fc \"blue\" title \"" + maxString + "\"\n";
    gp<<plotString;
    for(int i = 0; i < q.size(); i++){
        gp.send1d(q[i]);
    }

    return 0;
}