#include "Jeu.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() 
{
/*   
    Compiler :
        - g++ -c Jeu.cpp
        - g++ -c main.cpp
        - g++ -o main main.o Jeu.o
        
    Joueur J1 = Joueur("Robert", 1);
    Joueur J2 = Joueur("Kingo", -1);

    cout << J1.getNom() << "/" << J1.getPts() << endl;
    cout << J2.getNom() << endl;

    J1.changePts(3);
    cout << J1.getNom() << "/" << J1.getPts() << endl;*/

    Jeu puissance4;

    puissance4.ajouterJeton(5,0,1);
    puissance4.ajouterJeton(5,1,1);
    puissance4.ajouterJeton(5,2,1);
    puissance4.ajouterJeton(5,3,1);

    puissance4.printJeu();
    if (puissance4.verifierVictoire()) {
        cout << "Excuse me, miss." << endl;
    }

    puissance4.viderGrille();
    puissance4.printJeu();

    while (!puissance4.verifierVictoire()) {
        puissance4.printJeu();
        puissance4.voirJetonsParColonne();

        if(puissance4.getJoueurActuel() == 1) {
            cout << "Au tour du joueur 1" << endl;
        }
        else if (puissance4.getJoueurActuel() == -1) {
            cout << "Au tour du joueur 2" << endl;
        }

        int colonne = puissance4.COLONNES;
        bool colonneRemplie = false;
        do {
            cout << "Veuillez entrer la colonne dans laquelle mettre le jeton (entre 0 et 6) => " << endl;
            cin >> colonne;

            colonneRemplie = puissance4.colonneRemplie(colonne);

            if(colonneRemplie) {
                cout << "Colonne déjà remplie" << endl;
            }
        }
        while (colonne < 0 || colonne > 6 || colonneRemplie);

        puissance4.ajouterJeton(colonne);

        puissance4.changerJoueurActuel();
    }

    cout << "Fin de partie." << endl;
}