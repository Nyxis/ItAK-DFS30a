#include <iostream>
#include "De.hpp"
#include "Piece.hpp"
#include "Deck.hpp"
#include "GameMaster.hpp"

int main() {
    De de(6);
    Piece piece(3);
    Deck deck(4, 13);

    ResultatTirage resDe = de.effectuerTirage();
    std::cout << "[Dé] Score: " << resDe.getScore()
              << " | Pourcentage: " << resDe.getPourcentage() << "%" << std::endl;

    ResultatTirage resPiece = piece.effectuerTirage();
    std::cout << "[Pièce] Score: " << resPiece.getScore()
              << " | Pourcentage: " << resPiece.getPourcentage() << "%" << std::endl;

    ResultatTirage resDeck = deck.effectuerTirage();
    std::cout << "[Deck] Score: " << resDeck.getScore()
              << " | Pourcentage: " << resDeck.getPourcentage() << "%" << std::endl;

    std::cout << "\n=== Tirage par GameMaster ===" << std::endl;

    GameMaster gm;
    ResultatGM resGM = gm.pleaseGiveMeACrit();

    std::cout << "[GameMaster] Objet : " << resGM.typeObjet
              << " | Score : " << resGM.resultat.getScore()
              << " | Pourcentage : " << resGM.resultat.getPourcentage() << "%"
              << " | Statut : " << resGM.statut << std::endl;

    return 0;
}
