#include "etudiant.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const string fichierEtudiants = "etudiants.txt";
const string fichierEtat = "etat.txt";
const string fichierMauvais = "mauvais.txt";

void saisir() {
    Etudiant etudiant;
    ofstream fichier(fichierEtudiants, ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }

    cout << "NCIN : ";
    cin >> etudiant.NCIN;
    cout << "Nom : ";
    cin >> etudiant.nom;
    cout << "Prénom : ";
    cin >> etudiant.prenom;
    cout << "Âge : ";
    cin >> etudiant.age;
    cout << "Filière : ";
    cin >> etudiant.filiere;
    cout << "Niveau : ";
    cin >> etudiant.niveau;
    cout << "Cotisations (5 valeurs) : ";
    for (int i = 0; i < 5; ++i) {
        cin >> etudiant.cotisations[i];
    }

    fichier << etudiant.NCIN << ";" << etudiant.nom << ";" << etudiant.prenom << ";" << etudiant.age << ";"
            << etudiant.filiere << ";" << etudiant.niveau << ";";
    for (int i = 0; i < 5; ++i) {
        fichier << etudiant.cotisations[i];
        if (i != 4) {
            fichier << ";";
        }
    }
    fichier << endl;
    fichier.close();
}

void ajouter(const Etudiant& etudiant) {
    ofstream fichier(fichierEtudiants, ios::app);
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }

    fichier << etudiant.NCIN << ";" << etudiant.nom << ";" << etudiant.prenom << ";" << etudiant.age << ";"
            << etudiant.filiere << ";" << etudiant.niveau << ";";
    for (int i = 0; i < 5; ++i) {
        fichier << etudiant.cotisations[i];
        if (i != 4) {
            fichier << ";";
        }
    }
    fichier << endl;
    fichier.close();
}

void modifier(const int NCIN, const Etudiant& etudiant) {
    ifstream fichierLecture(fichierEtudiants);
    ofstream fichierEcriture("temp.txt");
    if (!fichierLecture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }
    if (!fichierEcriture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier temporaire" << endl;
        return;
    }

    string ligne;
    bool trouve = false;
    while (getline(fichierLecture, ligne)) {
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // Lire le NCIN
        int ncin = stoi(champ);
        if (ncin == NCIN) {
            trouve = true;
            fichierEcriture << etudiant.NCIN << ";" << etudiant.nom << ";" << etudiant.prenom << ";" << etudiant.age << ";"
                             << etudiant.filiere << ";" << etudiant.niveau << ";";
            for (int i = 0; i < 5; ++i) {
                fichierEcriture << etudiant.cotisations[i];
                if (i != 4) {
                    fichierEcriture << ";";
                }
            }
            fichierEcriture << endl;
        } else {
            fichierEcriture << ligne << endl;
        }
    }
    fichierLecture.close();
    fichierEcriture.close();

    remove(fichierEtudiants.c_str());
    rename("temp.txt", fichierEtudiants.c_str());

    if (!trouve) {
        cout << "Aucun étudiant trouvé avec le NCIN " << NCIN << endl;
    }
}

void supprimer(const int NCIN) {
    ifstream fichierLecture(fichierEtudiants);
    ofstream fichierEcriture("temp.txt");
    if (!fichierLecture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }
    if (!fichierEcriture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier temporaire" << endl;
        return;
    }

    string ligne;
    bool trouve = false;
    while (getline(fichierLecture, ligne)) {
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // Lire le NCIN
        int ncin = stoi(champ);
        if (ncin != NCIN) {
            fichierEcriture << ligne << endl;
        } else {
            trouve = true;
        }
    }
    fichierLecture.close();
    fichierEcriture.close();

    remove(fichierEtudiants.c_str());
    rename("temp.txt", fichierEtudiants.c_str());

    if (!trouve) {
        cout << "Aucun étudiant trouvé avec le NCIN " << NCIN << endl;
    }
}

void afficherListeEtudiants() {
    ifstream fichier(fichierEtudiants);
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        istringstream ss(ligne);
        string champ;
        while (getline(ss, champ, ';')) {
            cout << champ << " ";
        }
        cout << endl;
    }
    fichier.close();
}

float calculerTotalCotisations(const Etudiant& etudiant) {
    float total = 0;
    for (int i = 0; i < 5; ++i) {
        total += etudiant.cotisations[i];
    }
    return total;
}

void solvable() {
    ifstream fichierLecture(fichierEtudiants);
    ofstream fichierEcriture(fichierEtat);
    if (!fichierLecture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }
    if (!fichierEcriture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtat << endl;
        return;
    }

    string ligne;
    while (getline(fichierLecture, ligne)) {
        Etudiant etudiant;
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // NCIN
        etudiant.NCIN = stoi(champ);
        getline(ss, etudiant.nom, ';');
        getline(ss, etudiant.prenom, ';');
        getline(ss, champ, ';'); // Âge
        etudiant.age = stoi(champ);
        getline(ss, etudiant.filiere, ';');
        getline(ss, etudiant.niveau, ';');
        for (int i = 0; i < 5; ++i) {
            getline(ss, champ, ';');
            etudiant.cotisations[i] = stof(champ);
        }
        float totalCotisations = calculerTotalCotisations(etudiant);
        fichierEcriture << "NCIN: " << etudiant.NCIN << ", Nom: " << etudiant.nom << ", Prénom: " << etudiant.prenom
                         << ", Total cotisations: " << totalCotisations << endl;
    }
    fichierLecture.close();
    fichierEcriture.close();
    cout << "Fichier etat.txt créé avec succès." << endl;
}

void insolvable() {
    ifstream fichierLecture(fichierEtudiants);
    ofstream fichierEcriture(fichierMauvais);
    if (!fichierLecture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }
    if (!fichierEcriture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierMauvais << endl;
        return;
    }

    string ligne;
    while (getline(fichierLecture, ligne)) {
        Etudiant etudiant;
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // NCIN
        etudiant.NCIN = stoi(champ);
        getline(ss, etudiant.nom, ';');
        getline(ss, etudiant.prenom, ';');
        getline(ss, champ, ';'); // Âge
        etudiant.age = stoi(champ);
        getline(ss, etudiant.filiere, ';');
        getline(ss, etudiant.niveau, ';');
        bool nonCotisant = false;
        for (int i = 0; i < 5; ++i) {
            getline(ss, champ, ';');
            float cotisation = stof(champ);
            if (cotisation == 0) {
                nonCotisant = true;
                break;
            }
        }
        if (nonCotisant) {
            fichierEcriture << etudiant.nom << endl;
        }
    }
    fichierLecture.close();
    fichierEcriture.close();
    cout << "Fichier mauvais.txt créé avec succès." << endl;
}

float pourcentageEtudiantsNonCotisants() {
    ifstream fichier(fichierEtudiants);
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return -1;
    }

    int totalEtudiants = 0;
    int nonCotisants = 0;
    string ligne;
    while (getline(fichier, ligne)) {
        totalEtudiants++;
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // NCIN
        getline(ss, champ, ';'); // Nom
        for (int i = 0; i < 5; ++i) {
            getline(ss, champ, ';');
            float cotisation = stof(champ);
            if (cotisation == 0) {
                nonCotisants++;
                break;
            }
        }
    }
    fichier.close();

    if (totalEtudiants == 0) {
        cout << "Aucun étudiant dans le fichier." << endl;
        return -1;
    }

    return static_cast<float>(nonCotisants) / totalEtudiants * 100;
}

void supprimerNonCotisants() {
    ifstream fichierLecture(fichierEtudiants);
    ofstream fichierEcriture("temp.txt");
    if (!fichierLecture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }
    if (!fichierEcriture.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier temporaire" << endl;
        return;
    }

    string ligne;
    while (getline(fichierLecture, ligne)) {
        istringstream ss(ligne);
        string champ;
        bool cotisant = false;
        for (int i = 0; i < 6; ++i) { // On vérifie les 6 premiers champs
            getline(ss, champ, ';');
            if (i >= 6) continue; // On saute les champs de cotisation
            if (i == 0) continue; // On saute le champ NCIN
            if (champ != "0") {
                cotisant = true;
                break;
            }
        }
        if (cotisant) {
            fichierEcriture << ligne << endl;
        }
    }
    fichierLecture.close();
    fichierEcriture.close();

    remove(fichierEtudiants.c_str());
    rename("temp.txt", fichierEtudiants.c_str());

    // Suppression dans etat.txt
    ifstream fichierLectureEtat(fichierEtat);
    ofstream fichierEcritureEtat("tempEtat.txt");
    if (!fichierLectureEtat.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtat << endl;
        return;
    }
    if (!fichierEcritureEtat.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier temporaire pour etat.txt" << endl;
        return;
    }

    string ligneEtat;
    while (getline(fichierLectureEtat, ligneEtat)) {
        istringstream ss(ligneEtat);
        string champ;
        getline(ss, champ, ':'); // NCIN
        int ncin = stoi(champ.substr(6)); // Ignorer "NCIN: "
        bool supprimer = false;
        for (int i = 0; i < 6; ++i) { // On vérifie les 6 premiers champs
            getline(ss, champ, ',');
            if (i >= 6) continue; // On saute les champs de cotisation
            if (i == 0) continue; // On saute le champ NCIN
            if (champ != "0") {
                supprimer = true;
                break;
            }
        }
        if (supprimer) {
            fichierEcritureEtat << ligneEtat << endl;
        }
    }
    fichierLectureEtat.close();
    fichierEcritureEtat.close();

    remove(fichierEtat.c_str());
    rename("tempEtat.txt", fichierEtat.c_str());

    // Suppression dans mauvais.txt
    ifstream fichierLectureMauvais(fichierMauvais);
    ofstream fichierEcritureMauvais("tempMauvais.txt");
    if (!fichierLectureMauvais.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierMauvais << endl;
        return;
    }
    if (!fichierEcritureMauvais.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier temporaire pour mauvais.txt" << endl;
        return;
    }

    string nom;
    while (getline(fichierLectureMauvais, nom)) {
        bool supprimer = false;
        ifstream fichierLectureEtudiants(fichierEtudiants);
        string ligne;
        while (getline(fichierLectureEtudiants, ligne)) {
            istringstream ss(ligne);
            string champ;
            getline(ss, champ, ';'); // Nom
            if (champ == nom) {
                supprimer = true;
                break;
            }
        }
        fichierLectureEtudiants.close();
        if (supprimer) {
            fichierEcritureMauvais << nom << endl;
        }
    }
    fichierLectureMauvais.close();
    fichierEcritureMauvais.close();

    remove(fichierMauvais.c_str());
    rename("tempMauvais.txt", fichierMauvais.c_str());

    cout << "Suppression des étudiants non cotisants effectuée avec succès." << endl;
}

void recherche(const int NCIN) {
    ifstream fichier(fichierEtudiants);
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fichierEtudiants << endl;
        return;
    }

    string ligne;
    bool trouve = false;
    while (getline(fichier, ligne)) {
        istringstream ss(ligne);
        string champ;
        getline(ss, champ, ';'); // Lire le NCIN
        int ncin = stoi(champ);
        if (ncin == NCIN) {
            trouve = true;
            cout << "Données de l'étudiant avec NCIN " << NCIN << " : ";
            while (getline(ss, champ, ';')) {
                cout << champ << " ";
            }
            cout << endl;
            break;
        }
    }
    fichier.close();

    if (!trouve) {
        cout << "Aucun étudiant trouvé avec le NCIN " << NCIN << endl;
    }
}

