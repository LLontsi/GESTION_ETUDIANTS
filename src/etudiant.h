#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <string>

struct Etudiant {
    int NCIN;
    std::string nom;
    std::string prenom;
    int age;
    std::string filiere;
    std::string niveau;
    float cotisations[5];
};

void saisir();
void ajouter(const Etudiant& etudiant);
void modifier(const int NCIN, const Etudiant& etudiant);
void supprimer(const int NCIN);
void afficherListeEtudiants();
void solvable();
void insolvable();
float pourcentageEtudiantsNonCotisants();
void supprimerNonCotisants();
void recherche(const int NCIN);

#endif // ETUDIANT_H
