#include <iostream>
#include "De.hpp"
#include "Piece.hpp"
#include "Deck.hpp"
#include "Tirage.hpp"
#include "GameMaster.hpp"

int main() {
    // Étape 4
    De de(6);
    Piece piece(3);
    Deck deck(4, 13);

    ResultatTirage resDe = de.effectuerTirage();
    std::cout << "[Dé] Score: " << resDe.getScore() << " | Type: " << resDe.getType() << std::endl;

    ResultatTirage resPiece = piece.effectuerTirage();
    std::cout << "[Pièce] Score: " << resPiece.getScore() << " | Type: " << resPiece.getType() << std::endl;

    ResultatTirage resDeck = deck.effectuerTirage();
    std::cout << "[Deck] Score: " << resDeck.getScore() << " | Type: " << resDeck.getType() << std::endl;

    std::cout << "\n=== Tirage par GameMaster ===" << std::endl;

    // Étape 5
    GameMaster gm;
    ResultatGM resGM = gm.pleaseGiveMeACrit();

    std::cout << "[GameMaster] Objet : " << resGM.typeObjet
              << " | Score : " << resGM.resultat.getScore()
              << " | Statut : " << resGM.resultat.getType()
              << std::endl;

    return 0;
}
