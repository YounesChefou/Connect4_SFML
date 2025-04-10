#include "Jeu.hpp"
using namespace std;

void Jeu::printJeu() {

        for(int i = 0; i < LIGNES; i++) {
            cout << "| ";
            for(int j = 0; j < COLONNES; j++) {
                if (grille[i][j] >= 0) {
                    cout << " ";
                }
                cout << grille[i][j] << " | ";
            }
            cout << endl;
        }
        for(int j = 0; j < COLONNES; j++) {
            cout << "  (" << j << ")";
        }
        cout << endl;
    }

void Jeu::ajouterJeton (int ligne, int colonne, int jeton) {
        if (this->jetonsParColonnes[colonne] < LIGNES) {
            this->grille[ligne][colonne] = jeton;
            this->jetonsParColonnes[colonne] += 1;
        }
        else {
            cout << " La colonne est déjà remplie de jetons ! " << endl;
        }
            
    }

 void Jeu::ajouterJeton (int colonne) {
/*        cout << "Coordonnees : ";
       	 cout << "Ligne = " << LIGNES - jetonsParColonnes[colonne] << endl;
        cout << "Colonne = " << colonne << endl;*/
    ajouterJeton (LIGNES - jetonsParColonnes[colonne] - 1, colonne, joueurActuel);
 }

     // Conditions de victoire
    /*
    1/ Vertical
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 0 | 0 | 0 | 0 |
    
        qd victoire => grille[0][0] + grille[1][0] + grille[2][0] + grille[3][0] = 4
    2/ Horizontal
        | 1 | 1 | 1 | 1 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
        qd victoire => grille[0][0] + grille[0][1] + grille[0][2] + grille[0][3] = 4
    3/ Diagonale
        | 1 | 0 | 0 | 1 | 0 | 0 | 0 |
        | 0 | 1 | 1 | 0 | 0 | 0 | 0 |
        | 0 | 1 | 1 | 0 | 0 | 0 | 0 |
        | 1 | 0 | 0 | 1 | 0 | 0 | 0 |


        v1 : on verifie toutes les cases
    */
bool Jeu::verifierVictoire() {
    for(int i = 0; i < LIGNES; i++) {
        for(int j = 0; j < COLONNES; j++) {
            // Vertical
            if ((i+3) < LIGNES && abs(grille[i][j] + grille[i+1][j] + grille[i+2][j] + grille[i+3][j]) == 4) {
                return true;
            }
            // Horizontal
            if ((j+3) < COLONNES && abs(grille[i][j] + grille[i][j+1] + grille[i][j+2] + grille[i][j+3]) == 4) {
                return true;
            }

            // Diagonale
            if ((i+3) < LIGNES && (j+3) < COLONNES && abs(grille[i][j] + grille[i+1][j+1] + grille[i+2][j+2] + grille[i+3][i+3]) == 4) {
                return true;
            }

            if ((i+3) > LIGNES && (j-3) >= 0 && abs(grille[i][j] + grille[i+1][j-1] + grille[i+2][j-2] + grille[i+3][i-3]) == 4) {
                return true;
            }
        }
    }
    return false;
    }

// Verifier s'il y a une com
bool Jeu::verifierVictoireDepuisPos() {
    return false;
    }

void Jeu::viderGrille() {
        for(int i = 0; i < LIGNES; i++) {
            this->jetonsParColonnes[i] = 0;
            for(int j = 0; j < COLONNES; j++) {
                this->grille[i][j] = 0;
            }
        }
    }

void Jeu::voirJetonsParColonne() {
    for(int i = 0; i < COLONNES; i++) {
        cout << "(" << jetonsParColonnes[i] << ") ";
    }
    cout << endl;
}