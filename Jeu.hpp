#include <iostream>

class Jeu 
{
	public:
    	static const int LIGNES = 6;
    	static const int COLONNES = 7; 

    	void printJeu();
    	void ajouterJeton (int ligne, int colonne, int jeton);
    	bool colonneRemplie(int colonne) {return jetonsParColonnes[colonne] == LIGNES;};
    	void ajouterJeton (int colonne);
    	bool verifierVictoire();
    	bool verifierVictoireDepuisPos();
    	void viderGrille();
    	int getJoueurActuel() {return joueurActuel;}
    	void changerJoueurActuel() {joueurActuel *= -1;};
    	void voirJetonsParColonne();

    private:
	    int grille[LIGNES][COLONNES] = {0};
	    int jetonsParColonnes[COLONNES] = {0}; // indique les jetons déjà insérés dans la colonne
	    int joueurActuel = 1;

};