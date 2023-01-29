
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits.h> 
using namespace std;


void operator += (vector<bool> &v1, const vector<bool> &v2){
    for (int i=0; i<v2.size(); i++)
        v1.push_back(v2[i]);
}       

void vector_bool_to_file(vector<bool> v, string file_name){
    ofstream f = ofstream(file_name);
    long num_bits = v.size();
    unsigned char c;
    long inic;
    f << num_bits<<endl;
    for(int i = 0;i< num_bits/CHAR_BIT; i++){
        c = 0;
        inic = i*CHAR_BIT;
        for(int j = CHAR_BIT-1;j>=0;j--){ 
           c = c*2+v[inic+j];
        }
        f<<c;
    }
    c = 0;
    inic = (num_bits/CHAR_BIT)*CHAR_BIT;
    for(int j = num_bits%CHAR_BIT-1;j>=0;j--){
        c = c *2 + v[inic + j];
    }
    f << c;
    f.close();
}

vector<bool> file_to_vector_bool(string file_name){
    long num_bits;
    vector<bool> result;
    ifstream f = ifstream(file_name);
    f >> num_bits;
    unsigned char c;
    string s;
    getline(f,s); 
    long pos = 0;
    for(long i =0; i<num_bits/CHAR_BIT; i++){
         c = f.get();
         for(long j = 0 ; j<CHAR_BIT;j++){
              result.push_back(c % 2);
              c = c/2;
              pos++;
         }
    }
    c = f.get();
    for(long j = num_bits%CHAR_BIT-1;j>=0;j--){
        result.push_back(c % 2);
        c = c/2;
    }
    f.close();
    return result; 
}