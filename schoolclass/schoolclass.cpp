#include "schoolclass.hpp"


    char* schoolclass::getClassname(){
        return cl;
    }
    int schoolclass::getMax_capa(){
        return max_capa;
    }
    void schoolclass::setCapa(int c){
        max_capa = c;
    }
