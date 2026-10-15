#pragma once
#include <vector>
#include <cstring>
using namespace std;

class schoolclass{
    private:
    char* cl;
    int max_capa;
    public:
    schoolclass(){
        cl = nullptr;
        max_capa = 0;
    }
    schoolclass(const char* c,int m) {
        cl = new char[strlen(c) + 1];
        strcpy(cl,c);
        max_capa = m;
    }
    char* getClassname();
    int getMax_capa();
    void setCapa(int c);
};