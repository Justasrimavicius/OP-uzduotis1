#include "functions.h"
#include "vector"
using namespace std;


struct studentas {
    string vardas;
    string pavarde;
    string egzaminoRez;
    vector<string> ndRez;
    string ndKiekis;
    double galutinisBalas;
};

void duomenysIvedamiKonsoleje(vector<studentas>& visiStudentai, string studSkaicius);
void duomenysIsFailo(vector<studentas>& visiStudentai, string fileName);
int compareStudents(const studentas& s1, const studentas& s2);
void quicksort(std::vector<studentas>& arr, int low, int high);
int partition(std::vector<studentas>& arr, int low, int high);


int main() {
    string studSkaicius;
    string dataFaileArIvesti;
    vector<studentas> visiStudentai;

    cout << "Ar norite duomenis nuskaityti is failo? Mygtukas 'f' - duomenys vedami konsoleje. Bet kas kitas - failo pavadinimas(.txt gale nebereikia - bus automatiskai prideta)" << endl;
    cin >> dataFaileArIvesti; // arba "f", arba failo pavadinimas
    if(dataFaileArIvesti != "f"){
        duomenysIsFailo(visiStudentai, dataFaileArIvesti);
        studSkaicius = to_string(visiStudentai.size());

    } else {
        studentuSkIvedimas:
        cout << "Studentu skaicius: ";
        cin >> studSkaicius;
        if(!isNumber(studSkaicius)){
            cout << "Studentu skaicius turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
            goto studentuSkIvedimas;
        }

        duomenysIvedamiKonsoleje(visiStudentai, studSkaicius);
    }

    // rusiavimas pagal varde/pavarde
    quicksort(visiStudentai, 0, visiStudentai.size() - 1);


    cout << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis(vid.)" << setw(20) << "Galutinis(med.)" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;




    for(int i = 0; i < stoi(studSkaicius); i++){
        cout << setw(15) << visiStudentai[i].vardas;
        cout << setw(15) << visiStudentai[i].pavarde;
        cout << setw(20) << fixed << setprecision(2) << visiStudentai[i].galutinisBalas; // Galutinis(vid.)
        if(stoi(visiStudentai[i].ndKiekis) % 2 == 0){ // Galutinis(med.)
            cout << setw(20) << fixed << setprecision(2) << (double)(stoi(visiStudentai[i].ndRez.at(stoi(visiStudentai[i].ndKiekis)/2)) + stoi(visiStudentai[i].ndRez.at(stoi(visiStudentai[i].ndKiekis)/2 - 1)))/2 * 0.4 + (stoi(visiStudentai[i].egzaminoRez) * 0.6);
        } else {
            cout << setw(20) << fixed << setprecision(2) <<  (stoi(visiStudentai[i].ndRez.at(stoi(visiStudentai[i].ndKiekis)/2)) * 0.4) + (stoi(visiStudentai[i].egzaminoRez) * 0.6);
        }
        cout << endl;
    }

    return 0;
}

void duomenysIvedamiKonsoleje(vector<studentas>& visiStudentai, string studSkaicius){

    srand(time(0));

    for (int i = 0; i < stoi(studSkaicius); i++){
        string atsitiktiniaiRez;
        studentas studentas;
        cout << "iveskite " << i + 1 << " studento informacija:" << endl;
        cout << "Vardas: ";
        cin >> studentas.vardas;
        cout << "Pavarde: ";
        cin >> studentas.pavarde;

        egzaminoRezIvedimas:
        cout << "Egzamino rezultatas: ";
        cin >> studentas.egzaminoRez;
        if(!isNumber(studentas.egzaminoRez)){
            cout << "Egzamino rezultatas turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
            goto egzaminoRezIvedimas;
        }
        if(stoi(studentas.egzaminoRez) > 10 || stoi(studentas.egzaminoRez) < 1){
            cout << "Egzamino rezultatas turi buti tarp 1 ir 10. Iveskite is naujo." << endl;
            goto egzaminoRezIvedimas;
        }

        cout << "Ar generuoti namu darbu rezultatus atsitiktinai? 't' jei taip, bet koks kitas simbolis jei ne: ";
        cin >> atsitiktiniaiRez;

        NDIvedimas:
        cout << "Namu darbu kiekis: ";
        cin >> studentas.ndKiekis;
        if(!isNumber(studentas.ndKiekis)){
            cout << "Namu darbu kiekis turi buti sveikasis skaicius. Iveskite is naujo." << endl; 
            goto NDIvedimas;
        } else if(stoi(studentas.ndKiekis) <= 0){
            cout << "Namu darbu kiekis turi buti daugiau uz nuli. Iveskite is naujo." << endl;
            goto NDIvedimas;
        }
        
        
        int bendrasNDbalas = 0;

        if(atsitiktiniaiRez == "t"){
            vector<string> ndRez;
            for (int j = 0; j < stoi(studentas.ndKiekis); j++) {
                studentas.ndRez.push_back(to_string(rand() % 10 + 1));
                bendrasNDbalas = stoi(studentas.ndRez.at(j)) + bendrasNDbalas;
            }
        } else{
            vector<string> ndRez;

            for (int j = 0; j < stoi(studentas.ndKiekis); j++) {
                uzdRezIvedimas:
                cout << "Rezultatas uzduoties " << j + 1 << ": ";
                string val;
                cin >> val;
                studentas.ndRez.push_back(val);

                if(!isNumber(studentas.ndRez.at(j))){
                    cout << "Uzduoties rezultatas turi buti sveikasis skaicius. Iveskite is naujo." << endl;
                    goto uzdRezIvedimas;
                } else {
                    bendrasNDbalas = bendrasNDbalas + stoi(studentas.ndRez.at(j));
                }
            }
        }
        studentas.galutinisBalas = ((double)bendrasNDbalas/stoi(studentas.ndKiekis)) * 0.4 + (stoi(studentas.egzaminoRez) * 0.6);

        visiStudentai.push_back(studentas);
    }
}

void duomenysIsFailo(vector<studentas>& visiStudentai, string fileName){
    ifstream failas(fileName + ".txt");
    string eilute;

    getline(failas, eilute);
    istringstream iss(eilute);
    vector<string> headers;
    string header;
    while (iss >> header) {
        headers.push_back(header);
    }

    while (getline(failas, eilute)){
        istringstream iss(eilute);
        studentas studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        string nd;
        int bendrasNDbalas = 0;
        int ndQty = 0;
        for (int i = 0; i < headers.size() - 3; ++i) {
            iss >> nd;
            studentas.ndRez.push_back(nd);
            bendrasNDbalas += stoi(nd);
            nd = "";
            ndQty++;
        }

        iss >> studentas.egzaminoRez;
        studentas.ndKiekis = to_string(ndQty);
        studentas.galutinisBalas = ((double)bendrasNDbalas/stoi(studentas.ndKiekis)) * 0.4 + (stoi(studentas.egzaminoRez) * 0.6);

        visiStudentai.push_back(studentas);
    }

    failas.close();

}

int compareStudents(const studentas& s1, const studentas& s2) {
    int cmp = s1.vardas.compare(s2.vardas);
    if (cmp != 0) return cmp;
    return s1.pavarde.compare(s2.pavarde);
}

int partition(vector<studentas>& arr, int low, int high) {
    studentas pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (compareStudents(arr[j], pivot) <= 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(vector<studentas>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}