
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include "iomanip"
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <cmath>
#include <vector>
#include <string>

struct studentas {
    std::string vardas;
    std::string pavarde;
    std::string egzaminoRez;
    std::vector<std::string> ndRez;
    std::string ndKiekis;
    double galutinisBalas;
};

bool isNumber(const std::string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

int partition(std::vector<studentas>& arr, int low, int high){
    studentas pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (strcmp((arr[j].vardas).c_str(), (pivot.vardas).c_str()) < 0) {
            i++;
            std::swap(arr[i], arr[j]);
        } else if(strcmp((arr[j].vardas).c_str(), (pivot.vardas).c_str()) == 0){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(std::vector<studentas>& arr, int low, int high){
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}