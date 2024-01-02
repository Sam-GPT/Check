//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
#include <iostream>


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

//This function increments the amount of moves a piece has made
void SchaakStuk::IncrementMoves() {
    aantalMoves++;
}

//This function returns the amount of moves a piece has made
int SchaakStuk::getAantalMoves() const {
    return aantalMoves;
}

void SchaakStuk::DecrementMoves() {
    aantalMoves--;
}

SchaakStuk::~SchaakStuk() = default;


//This function returns the valid moves of a pawn
std::vector<std::pair<int, int>> Pion::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};
    if(this->getKleur() == zwart){
        //This if statement will check if Black's pawn can move forward by one
        if(x+1 <= 7 ){
            std::pair <int, int> geldig (x+1, y);
            if(g.getPiece(geldig.first, geldig.second) == nullptr){
                zetten.push_back(geldig);
            }

        }

        //This if statement will check if Black's pawn can move forward by two but this will only be
        //allowed if it's the pawn's first move.
        if(x+2 <= 7 && this->getAantalMoves() ==0){
            std::pair <int, int> geldig (x+2, y);
            zetten.push_back(geldig);
        }

        //This if statement will check if Black's pawn is able to capture a piece in a different colum.
        if(x+1 <= 7 && y-1 >=0){
            if(g.getPiece(x+1, y-1) != nullptr && g.getPiece(x+1, y-1)->getKleur() != this->getKleur()){
                std::pair <int, int> geldig (x+1, y-1);
                zetten.push_back(geldig);
            }
        }

        //This if statement will check if Black's pawn is able to capture a piece in a different colum.
        if(x+1 <= 7 && y+1 >=0){
            if(g.getPiece(x+1, y+1) != nullptr && g.getPiece(x+1, y+1)->getKleur() != this->getKleur()){
                std::pair <int, int> geldig (x+1, y+1);
                zetten.push_back(geldig);
            }
        }
    }
    if(this->getKleur() == wit){
        //This if statement will check if White's pawn can move forward by one
        if(x-1 >= 0 ){
            std::pair <int, int> geldig (x-1, y);
            if(g.getPiece(geldig.first, geldig.second) == nullptr){
                zetten.push_back(geldig);
            }
        }

        //This if statement will check if Black's pawn can move forward by two but this will only be
        //allowed if it's the pawn's first move.
        if(x-2 >= 0 && this->getAantalMoves() ==0){
            std::pair <int, int> geldig (x-2, y);
            zetten.push_back(geldig);

        }
        //This if statement will check if Black's pawn is able to capture a piece in a different colum.
        if(x-1 <= 7 && y-1 >=0){
            if(g.getPiece(x-1, y-1) != nullptr && g.getPiece(x-1, y-1)->getKleur() != this->getKleur()){
                std::pair <int, int> geldig (x-1, y-1);
                zetten.push_back(geldig);
            }
        }
        //This if statement will check if Black's pawn is able to capture a piece in a different colum.
        if(x-1 <= 7 && y+1 >=0){
            if(g.getPiece(x-1, y+1) != nullptr && g.getPiece(x-1, y+1)->getKleur() != this->getKleur()){
                std::pair <int, int> geldig (x-1, y+1);
                zetten.push_back(geldig);
            }
        }
    }


    return zetten;
}

Pion::~Pion() = default;


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

Toren::~Toren() = default;

//This function returns the valid moves of a horse
std::vector<std::pair<int, int>> Paard::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    //Right->2, Up->1
    if(y+2 <= 7 && x-1 >=0){
        std::pair <int, int> geldig (x-1, y+2);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }


    }
    //Right->2, Down->1
    if(y+2 <= 7 && x+1 <=7){
        std::pair <int, int> geldig (x+1, y+2);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Left-> two, Up->1
    if(y-2 >=0 && x-1 >=0){
        std::pair <int, int> geldig (x-1, y-2);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Left-> two, Down->1
    if(y-2 >=0 && x+1 <=7){
        std::pair <int, int> geldig (x+1, y-2);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Up-> two, Right->1
    if(x-2 >= 0 && y+ 1 <= 7){
        std::pair <int, int> geldig (x-2, y+1);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Down-> two, Right->1
    if(x+2 <=7  && y+ 1 <= 7){
        std::pair <int, int> geldig (x+2, y+1);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Up-> two, Left->1
    if(x-2 >= 0 && y-1 >= 0){
        std::pair <int, int> geldig (x-2, y-1);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    //Down-> two, Left->1
    if(x+2 <=7  && y-1 >= 0){
        std::pair <int, int> geldig (x+2, y-1);
        if(g.getPiece(geldig.first, geldig.second) == nullptr){
            zetten.push_back(geldig);
        }else{
            if (g.getPiece(geldig.first, geldig.second)->getKleur() != this->getKleur()) {
                zetten.push_back(geldig);
            }
        }
    }
    return zetten;
}

Paard::~Paard() = default;

//This function returns the valid moves of a bishop
std::vector<std::pair<int, int>> Loper::geldige_zetten(const Game &g) const {
    std::pair<int,int> position = this->getPosition(g);
    int x = position.first;
    int y = position.second;
    std::vector<std::pair<int, int>> zetten = {};

    // Check all four diagonal directions
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            for (int step = 1; step < 8; step++) {
                int newX = x + step * i;
                int newY = y + step * j;

                // Check if the new position is within the board
                if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
                    break;  // Outside the board, exit the loop
                }

                std::pair<int, int> geldig(newX, newY);

                if (g.getPiece(newX, newY) == nullptr) {
                    zetten.push_back(geldig);
                } else {
                    if (g.getPiece(newX, newY)->getKleur() != this->getKleur()) {
                        zetten.push_back(geldig);
                    }
                    break;
                }
            }
        }
    }

    return zetten;
}

Loper::~Loper() = default;


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

Koning::~Koning() = default;

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

Koningin::~Koningin() = default;

