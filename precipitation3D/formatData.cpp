#include<bits/stdc++.h>
#include<fstream>

using namespace std;

int main(){
    ifstream r("precip.2017");
    ofstream w("output.dat");

    string line;
    while(getline(r, line)){
        string token;
        vector<string> tokens;
        stringstream strm(line);
        while(getline(strm, token, ' ')){
            if(token.size() > 1){
                tokens.push_back(token);
            }
        }

        double longitude, latitude;
        stringstream stringToDouble(tokens[0]);
        stringToDouble>>longitude;
        stringToDouble = stringstream(tokens[1]);
        stringToDouble>>latitude;

        double x1 = longitude-0.25, x2 = longitude+0.25, y1 = latitude-0.25, y2 = latitude+0.25; 
        string z1 = tokens[2], z2 = "0";
        string val = tokens[2];

        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl<<endl;

        w<<x1<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z2<<" "<<val<<endl<<endl;

        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl<<endl;

        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y1<<" "<<z1<<" "<<val<<endl<<endl;

        w<<x2<<" "<<y1<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z2<<" "<<val<<endl;
        w<<x2<<" "<<y1<<" "<<z1<<" "<<val<<endl<<endl;

        w<<x1<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z1<<" "<<val<<endl;
        w<<x2<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z2<<" "<<val<<endl;
        w<<x1<<" "<<y2<<" "<<z1<<" "<<val<<endl<<endl<<endl;
    }

    r.close();
    w.close();

    return 0;
}