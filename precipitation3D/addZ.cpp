#include<bits/stdc++.h>
#include<fstream>
#include<gnuplot-iostream.h>

using namespace std;

double distance(double x1, double y1, double x2, double y2){
    double mag = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
    mag = sqrt(mag);
    return mag;
}

int main(){
    // ifstream worldData("data.dat");
    // ofstream worldData3D("data3d.dat");

    // string line;

    // while(getline(worldData, line)){
    //     if(line.size() > 1){
    //         line += " 0";
    //     }
    //     worldData3D<<line<<endl;
    // }

    ifstream precipitationData("precip.2017");
    string temp;
    double max = 0;
    int r = 100, c = 100;
    double rl = 360/(double)r, cl = 360/(double)c;
    vector<vector<pair<vector<string>, double>>> data(r, vector<pair<vector<string>, double>>(c, pair<vector<string>, double>(vector<string>(2, "2147483647"), 0)));
    while(getline(precipitationData, temp)){
        stringstream tokenStream(temp);
        string token; 
        vector<string> tokens;
        while(getline(tokenStream, token, ' ')){
            if(token.size() > 1){
                tokens.push_back(token);
            }
        }

        double longitude, latitude, val, oLat, oLong;
        stringstream convert(tokens[0]);
        convert>>longitude;
        convert = stringstream(tokens[1]);
        convert>>latitude;
        convert = stringstream(tokens[2]);
        convert>>val;

        int ri = (int)((latitude+180)/rl);
        int ci = (int)((longitude+180)/cl);

        convert = stringstream(data[ri][ci].first[0]);
        convert>>oLong;
        convert = stringstream(data[ri][ci].first[1]);
        convert>>oLat;

        data[ri][ci].second += val;
        if(max < data[ri][ci].second){
            max = data[ri][ci].second;
        }

        double distNew = distance(cl*ci + cl/2-180, rl*ri + rl/2-180, longitude, latitude);
        double distOld = distance(cl*ci + cl/2-180, rl*ri + rl/2-180, oLong, oLat);
        if(distNew < distOld){
            data[ri][ci].first[0] = tokens[0];
            data[ri][ci].first[1] = tokens[1];
        }

    }

    ofstream w("precipitationData3D.dat");
    if(w){
        for(int i = 0; i < data.size(); i++){
            for(int j = 0; j < data[i].size(); j++){
                stringstream check(data[i][j].first[1]);
                double lat, longi;
                check>>lat;
                check = stringstream(data[i][j].first[0]);
                check>>longi;

                if(!(lat > 180 || lat < -180)){
                    double x1 = longi, x2 = longi+1, y1 = lat, y2 = lat+1, val = (data[i][j].second/max)*50, z2 = 0, z1 = val;

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
                    // string coords = data[i][j].first[0] + " " + data[i][j].first[1];
                    // dataFile<<coords<<" 0.0"<<endl;
                    // dataFile<<coords<<" "<<to_string(data[i][j].second/max)<<endl<<endl<<endl;
                }
            }
        }
    }

    // worldData.close();
    // worldData3D.close();
    precipitationData.close();
    w.close();



    return 0;
}