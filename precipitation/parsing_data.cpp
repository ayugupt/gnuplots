#include<bits/stdc++.h>
#include<fstream>

using namespace std;

int main(){

    ifstream dataFile("world_no_borders.csv");
    string line;

    unordered_map<string, unordered_map<string, vector<vector<string>>>> data;
    unordered_map<string, unordered_map<string, unordered_map<string, vector<vector<string>>>>> rings;


    bool first = true;
    unordered_map<string, int> indexMap;
    set<string> countries;

    //string prevX, prevY;

    while(getline(dataFile, line)){
        stringstream stringStream(line);
        string token;
        vector<string> tokens;
        while(getline(stringStream, token, ',')){
            //cout<<token<<" ";
            tokens.push_back(token);
        }

        if(first){
            for(int i = 0; i < tokens.size(); i++){
                indexMap[tokens[i]] = i;
            }
            //cout<<indexMap["country_name"];
        }else{
            string country = tokens[indexMap["country_name"]];
            string vertex = tokens[indexMap["vertex_part"]];
            string x = tokens[indexMap["x"]];
            string y = tokens[indexMap["y"]];
            string ring = tokens[indexMap["vertex_part_ring"]];
            countries.insert(country);
            //cout<<country<<" "<<vertex<<" "<<x<<" "<<y<<endl;
            if(data[country].find(vertex) == data[country].end()){
                data[country][vertex] = vector<vector<string>>();
            }

            // float dist = pow(pow(atof(prevX.c_str())-atof(x.c_str()), 2) + pow(atof(prevY.c_str())-atof(y.c_str()), 2), 0.5);
            // cout<<dist<<endl;
            if(ring == "\"0\""){
                data[country][vertex].push_back({x, y});
            }else{
                if(rings[country][ring].find(vertex) == rings[country][ring].end()){
                    rings[country][ring][vertex] = vector<vector<string>>();
                }
                rings[country][ring][vertex].push_back({x, y});
            }

            // if(dist < 1){
            //     data[country][vertex].push_back({x, y});
            //     prevX = x;
            //     prevY = y;
            // }
            
        }
        first = false;
    }

    dataFile.close();

    ofstream newFile("data.dat");
    //ofstream placeFile("places.dat");

    if(newFile){
        for(set<string>::iterator i = countries.begin(); i != countries.end(); ++i){

            string vertex_part = "\"0\"";
            int j = 0;
            while(data[*i].find(vertex_part) != data[*i].end()){
                for(int k = 0; k < data[*i][vertex_part].size(); k++){
                    string input = data[*i][vertex_part][k][0] + " " +  data[*i][vertex_part][k][1];
                    newFile<<input<<endl;
                }

                newFile<<endl;
                j++;
                vertex_part = "\"";
                vertex_part += to_string(j);
                vertex_part += "\"";
            }
        }
        newFile<<endl;

        for(auto it = rings.begin(); it != rings.end(); ++it){
            for(auto it2 = rings[it->first].begin(); it2 != rings[it->first].end(); ++it2){
                for(auto it3 = rings[it->first][it2->first].begin(); it3 != rings[it->first][it2->first].end(); ++it3){
                    for(int j = 0; j < rings[it->first][it2->first][it3->first].size(); j++){
                        newFile<<rings[it->first][it2->first][it3->first][j][0]<<" "<<rings[it->first][it2->first][it3->first][j][1]<<endl;
                    }
                    newFile<<endl;
                }
            }
        }


    }

    newFile.close();
    //placeFile.close();

    return 0;
}