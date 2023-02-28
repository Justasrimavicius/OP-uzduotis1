#include "functions.h"
using namespace std;

struct studentas {
    string vardas;
    string pavarde;
    string egzaminoRez;
    string* ndRez;
    string ndKiekis;
    double galutinisBalas;
};

int main() {
    string studSkaicius;

    studentuSkIvedimas:
    cout << "Studentu skaicius: ";
    cin >> studSkaicius;
    if(!isNumber(studSkaicius)){
        cout << "Studentu skaicius turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
        goto studentuSkIvedimas;
    }

    studentas* visiStudentai = new studentas[stoi(studSkaicius)];
	srand(time(0));

    for (int i = 0; i < stoi(studSkaicius); i++) {
        string atsitiktiniaiRez;

        cout << "iveskite " << i + 1 << " studento informacija:" << endl;
        cout << "Vardas: ";
        cin >> visiStudentai[i].vardas;
        cout << "Pavarde: ";
        cin >> visiStudentai[i].pavarde;

        egzaminoRezIvedimas:
        cout << "Egzamino rezultatas: ";
        cin >> visiStudentai[i].egzaminoRez;
        if(!isNumber(visiStudentai[i].egzaminoRez)){
            cout << "Egzamino rezultatas turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
            goto egzaminoRezIvedimas;
        }
        if(stoi(visiStudentai[i].egzaminoRez) > 10 || stoi(visiStudentai[i].egzaminoRez) < 1){
            cout << "Egzamino rezultatas turi buti tarp 1 ir 10. Iveskite is naujo." << endl;
            goto egzaminoRezIvedimas;
        }
       


        cout << "Ar generuoti namu darbu rezultatus atsitiktinai? 't' jei taip, bet koks kitas simbolis jei ne: ";
        cin >> atsitiktiniaiRez;

        NDIvedimas:
        cout << "Namu darbu kiekis: ";
        cin >> visiStudentai[i].ndKiekis;
        if(!isNumber(visiStudentai[i].ndKiekis)){
            cout << "Namu darbu kiekis turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
            goto NDIvedimas;
        } else if(stoi(visiStudentai[i].ndKiekis) <= 0){
            cout << "Namu darbu kiekis turi buti daugiau uz nuli. Iveskite is naujo." << endl;
            goto NDIvedimas;
        }
        
        
        int bendrasNDbalas = 0;
        if(atsitiktiniaiRez == "t"){
            visiStudentai[i].ndRez = new string[stoi(visiStudentai[i].ndKiekis)];
            for (int j = 0; j < stoi(visiStudentai[i].ndKiekis); j++) {
                visiStudentai[i].ndRez[j] = to_string(rand() % 10 + 1);
                bendrasNDbalas = stoi(visiStudentai[i].ndRez[j]) + bendrasNDbalas;
            }
        } else{
            visiStudentai[i].ndRez = new string[stoi(visiStudentai[i].ndKiekis)];

            for (int j = 0; j < stoi(visiStudentai[i].ndKiekis); j++) {
                uzdRezIvedimas:
                cout << "Rezultatas uzduoties " << j + 1 << ": ";
                cin >> visiStudentai[i].ndRez[j];
                if(!isNumber(visiStudentai[i].ndRez[j])){
                    cout << "Uzduoties rezultatas turi buti sveikasis skaicius. Iveskite is naujo." << endl;
                    goto uzdRezIvedimas;
                } else {
                    bendrasNDbalas = bendrasNDbalas + stoi(visiStudentai[i].ndRez[j]);
                }
            }
        }
        visiStudentai[i].galutinisBalas = ((double)bendrasNDbalas/stoi(visiStudentai[i].ndKiekis)) * 0.4 + (stoi(visiStudentai[i].egzaminoRez) * 0.6);
    }


    for(int i = 0; i < stoi(studSkaicius); i++){
        string medArVid;
        cout << "Galutinio balo rodymas - skaiciuoti naudojant mediana ar imti vidutini namu darbu bala? m - mediana, v - vidutinis." << endl;
        medVidIvedimas:
        cin >> medArVid;
        if(medArVid != "m" && medArVid != "v"){
            cout << "Netinkamas ivedimas - iveskite tik m arba v." << endl;
            goto medVidIvedimas;
        }
        if(medArVid == "m"){
            if(stoi(visiStudentai[i].ndKiekis) % 2 == 0){
                visiStudentai[i].galutinisBalas =  (double)(stoi(visiStudentai[i].ndRez[stoi(visiStudentai[i].ndKiekis)/2]) + stoi(visiStudentai[i].ndRez[stoi(visiStudentai[i].ndKiekis)/2 - 1]))/2 * 0.4 + (stoi(visiStudentai[i].egzaminoRez) * 0.6);
            } else {
                visiStudentai[i].galutinisBalas = stoi(visiStudentai[i].ndRez[stoi(visiStudentai[i].ndKiekis)/2]) * 0.4 + (stoi(visiStudentai[i].egzaminoRez) * 0.6);
            }
        }


        cout << "------------" << endl;
        cout << "vardas: " << visiStudentai[i].vardas << endl;
        cout << "pavarde: " << visiStudentai[i].pavarde << endl;
        if(medArVid == "v"){
            cout << "Balas(vid.): " << fixed << setprecision(2) << visiStudentai[i].galutinisBalas << endl;
        } else {
            cout << "Balas(med.): " << fixed << setprecision(2) << visiStudentai[i].galutinisBalas << endl;
        }

        cout << endl;
    }

    delete[] visiStudentai;

    return 0;
}