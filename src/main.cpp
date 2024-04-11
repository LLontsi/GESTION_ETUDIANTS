#include "etudiant.h"
#include <iostream>

using namespace std;

int main() {
    int choix;
    do {
            cout << "\nMenu :\n";
        cout << "1. Saisir un nouvel étudiant\n";
        cout << "2. Afficher la liste des étudiants et le total de leurs cotisations\n";
        cout << "3. Générer le fichier 'etat.txt' avec le total des cotisations pour chaque étudiant\n";
        cout << "4. Générer le fichier 'mauvais.txt' avec les noms des étudiants non cotisants\n";
        cout << "5. Afficher le pourcentage des étudiants non cotisants\n";
        cout << "6. Supprimer les étudiants non cotisants\n";
        cout << "7. Rechercher un étudiant par NCIN\n";
        cout << "8. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                saisir();
                break;
            case 2:
                afficherListeEtudiants();
                break;
            case 3:
                solvable();
                break;
            case 4:
                insolvable();
                break;
            case 5: {
                float pourcentage = pourcentageEtudiantsNonCotisants();
                if (pourcentage != -1) {
                    cout << "Pourcentage d'étudiants non cotisants : " << pourcentage << "%" << endl;
                }
                break;
            }
            case 6:
                supprimerNonCotisants();
                break;
            case 7: {
                int NCIN;
                cout << "Entrez le NCIN de l'étudiant : ";
                cin >> NCIN;
                recherche(NCIN);
                break;
            }
            case 8:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 8);

    return 0;
}
