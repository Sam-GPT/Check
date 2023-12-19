//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
#include <iostream>

//This function returns the valid moves of a piece
std::vector<std::pair<int, int>> SchaakStuk::geldige_zetten(const Game &g) const {}

//This function returns the position of the piece on the board
std::pair<int, int> SchaakStuk::getPosition(const Game &g) const {
    int x = 0;
    int y = 0;
    bool pieceFound = false;
    for(int i = 0; i < 8 && !pieceFound; i++){
        for(int j = 0; j < 8; j++){
            if(g.getBord()[i][j] == this){
                x = i;
                y = j;
                pieceFound = true;
                break;
            }
        }
    }
    std::pair<int, int> position (x,y);
    return position;

}



//This function returns the valid moves of a pawn
std::vector<std::pair<int, int>> Pion::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};
    if(this->getKleur() == zwart){
        if(x+1 <= 7 ){
            std::pair <int, int> geldig (x+1, y);
            zetten.push_back(geldig);
        }

        if(x+2 <= 7){
            std::pair <int, int> geldig (x+2, y);
            zetten.push_back(geldig);
        }
    }
    if(this->getKleur() == wit){
        if(x-1 >= 0 ){
            std::pair <int, int> geldig (x-1, y);
            zetten.push_back(geldig);
        }

        if(x-2 >= 0){
            std::pair <int, int> geldig (x-2, y);
            zetten.push_back(geldig);
        }
    }


    return zetten;
}

//This function returns the valid moves of a tower
std::vector<std::pair<int, int>> Toren::geldige_zetten(const Game &g) const {
    std::pair<int, int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    // Check moves to the left of the tower
    for (int i = 1; y - i >= 0; i++) {
        std::pair<int, int> geldig(x, y - i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Check moves to the right of the tower
    for (int i = 1; y + i <= 7; i++) {
        std::pair<int, int> geldig(x, y + i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Check moves above the tower
    for (int i = 1; x - i >= 0; i++) {
        std::pair<int, int> geldig(x - i, y);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Check moves below the tower
    for (int i = 1; x + i <= 7; i++) {
        std::pair<int, int> geldig(x + i, y);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    return zetten;
}

//This function returns the valid moves of a horse
std::vector<std::pair<int, int>> Paard::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};


    if(y+2 <= 7 && x-1 >=0){
        std::pair <int, int> geldig (x-1, y+2);
        zetten.push_back(geldig);
    }
    if(y+2 <= 7 && x+1 <=7){
        std::pair <int, int> geldig (x+1, y+2);
        zetten.push_back(geldig);
    }

    if(y-2 >=0 && x-1 >=0){
        std::pair <int, int> geldig (x-1, y-2);
        zetten.push_back(geldig);
    }
    if(y-2 >=0 && x+1 <=7){
        std::pair <int, int> geldig (x+1, y-2);
        zetten.push_back(geldig);
    }

    if(x-2 >= 0 && y+ 1 <= 7){
        std::pair <int, int> geldig (x-2, y+1);
        zetten.push_back(geldig);
    }
    if(x+2 <=7  && y+ 1 <= 7){
        std::pair <int, int> geldig (x+2, y+1);
        zetten.push_back(geldig);
    }
    if(x-2 >= 0 && y-1 >= 0){
        std::pair <int, int> geldig (x-2, y-1);
        zetten.push_back(geldig);
    }
    if(x+2 <=7  && y-1 >= 0){
        std::pair <int, int> geldig (x+2, y-1);
        zetten.push_back(geldig);
    }
    return zetten;
}

//This function returns the valid moves of a bishop
std::vector<std::pair<int, int>> Loper::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    std::cout << this->getKleur() << std::endl;
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    //Right-Down Diagonal
    for(int i = 1; i < 8 ; i++){
        if(x+i <=7 && y+i <=7){
            std::pair <int, int> geldig (x+i, y+i);
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            } else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
                break;
            }
        }
    }
    //Left-Up Diagonal
    for(int i = 8; i >= 0 ; i--){
        if(x-i >= 0 && y-i >=0){
            std::pair <int, int> geldig (x-i, y-i);
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            } else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
                break;
            }
        }
    }
    //Right-Up Diagonal
    for(int i = 1, j = 1; i<8 && j<8; i++, j++ ){
        if(x-i >=0 && y + j <=7){
            std::pair <int, int> geldig (x-i, y+j);
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            } else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
                break;
            }
        }
    }
    //Left-Down Diagonal
    for(int i = 1, j = 1; i<8 && j<8; i++, j++ ){
        if(y-i >=0 && x + j <=7){
            std::pair <int, int> geldig (x+j, y-i);
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            } else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
                break;
            }
        }
    }
    return zetten;
}

//This function returns the valid moves of a king
std::vector<std::pair<int, int>> Koning::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    zw kleur = this->getKleur();
    std::vector<std::vector<std::pair<int, int>>> tp = g.TegenStanderPositions(kleur, g);


    //Down
    if(x+1 <= 7){
        std::pair <int, int> geldig (x+1, y);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }


    }
    //Up
    if(x-1 >=0){
        std::pair <int, int> geldig (x-1, y);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }
    }
    //Right
    if(y+1 <= 7){
        std::pair <int, int> geldig (x, y+1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }
    }
    //Left
    if(y-1 >=0){
        std::pair <int, int> geldig (x, y-1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }

    }
    //Right-Up Diagonal
    if(x-1 >=0 && y+1 <=7){
        std::pair <int, int> geldig (x-1, y+1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }

    }
    //Right-Down Diagonal
    if(x+1 <=7 && y+1 <=7){
        std::pair <int, int> geldig (x+1, y+1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }
    }
    //Left-Up Diagonal
    if(x-1 >=0 && y-1 >=0){
        std::pair <int, int> geldig (x-1, y-1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }
    }
    //Left-Down Diagonal
    if(x+1 <=7 && y-1 >=0){
        std::pair <int, int> geldig (x+1, y-1);
        //This if statement makes sure the king doesn't move to a position where he can be taken(Schaak)
        if (std::find_if(tp.begin(), tp.end(), [&](const std::vector<std::pair<int, int>>& v) {
            return std::find(v.begin(), v.end(), geldig) != v.end();
        }) == tp.end()) {
            if (g.getPiece(geldig.first, geldig.second) == nullptr) {
                zetten.push_back(geldig);
            }else {
                if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                    zetten.push_back(geldig);
                }
            }
        }
    }

    return zetten;
}

//This function returns the valid moves of a queen
std::vector<std::pair<int, int>> Koningin::geldige_zetten(const Game &g) const {
    std::pair<int, int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    // Right-Down Diagonal
    for (int i = 1; x + i <= 7 && y + i <= 7; i++) {
        std::pair<int, int> geldig(x + i, y + i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Left-Up Diagonal
    for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
        std::pair<int, int> geldig(x - i, y - i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Right-Up Diagonal
    for (int i = 1; x - i >= 0 && y + i <= 7; i++) {
        std::pair<int, int> geldig(x - i, y + i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // Left-Down Diagonal
    for (int i = 1; x + i <= 7 && y - i >= 0; i++) {
        std::pair<int, int> geldig(x + i, y - i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // This loop checks the moves to the right of the Queen
    for (int i = 1; y + i <= 7; i++) {
        std::pair<int, int> geldig(x, y + i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // This loop checks the moves to the left of the Queen
    for (int i = 1; y - i >= 0; i++) {
        std::pair<int, int> geldig(x, y - i);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            if(this->getKleur() == zwart){
                std::cout << geldig.first << " " << geldig.second << "Test" << std::endl;
            }
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // This loop checks the moves below the Queen
    for (int i = 1; x + i <= 7; i++) {
        std::pair<int, int> geldig(x + i, y);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    // This loop checks the moves above the Queen
    for (int i = 1; x - i >= 0; i++) {
        std::pair<int, int> geldig(x - i, y);
        if (g.getPiece(geldig.first, geldig.second) == nullptr) {
            zetten.push_back(geldig);
        } else {
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
            break;
        }
    }

    return zetten;
}

