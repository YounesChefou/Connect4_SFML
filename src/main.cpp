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

    puissance4.addToken(5,0,1);
    puissance4.addToken(5,1,1);
    puissance4.addToken(5,2,1);
    puissance4.addToken(5,3,1);

    puissance4.printJeu();
    if (puissance4.checkVictory()) {
        cout << "Excuse me, miss." << endl;
    }

    puissance4.emptyGrid();
    puissance4.printJeu();

    // int row = 0;
    // int column = 0;
    while (!puissance4.checkVictory()) {
        puissance4.printJeu();
        puissance4.printNumberOfTokensInColumn();

        if(puissance4.getCurrentPlayer() == 1) {
            cout << "Au tour du joueur 1" << endl;
        }
        else if (puissance4.getCurrentPlayer() == -1) {
            cout << "Au tour du joueur 2" << endl;
        }

        int column = COLUMNS;
        bool colonneRemplie = false;
        do {
            cout << "Veuillez entrer la colonne dans laquelle mettre le jeton (entre 0 et 6) => " << endl;
            cin >> column;

            colonneRemplie = puissance4.filledColumn(column);

            if(colonneRemplie) {
                cout << "Colonne déjà remplie" << endl;
            }
        }
        while (column < 0 || column >= COLUMNS || colonneRemplie);

        puissance4.addToken(column);

        puissance4.changeCurrentPlayer();
    }

    cout << "Fin de partie." << endl;
}