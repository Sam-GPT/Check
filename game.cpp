//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include <iostream>

Game::Game() {
    setStartBord();
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    //Set Black Pawns
    for(int i = 0; i < 8; i++){
        SchaakStuk* p1 = new Pion(zwart);
        setPiece(1, i, p1);
    }
    //Set Black Towers
    SchaakStuk* t1 = new Toren(zwart);
    SchaakStuk* t2 = new Toren(zwart);
    setPiece(0,0, t1);
    setPiece(0,7, t2);


    //Set Black Horses
    SchaakStuk* h1 = new Paard(zwart);
    SchaakStuk* h2 = new Paard(zwart);
    setPiece(0,1, h1);
    setPiece(0,6, h2);


    //Set Black Bishops
    SchaakStuk* l1 = new Loper(zwart);
    SchaakStuk* l2 = new Loper(zwart);
    setPiece(0,2, l1);
    setPiece(0,5, l2);


    //Set Black King and Queen
    SchaakStuk* k = new Koning(zwart);
    setPiece(0,3, k);
    SchaakStuk* q = new Koningin(zwart);
    setPiece(0,4, q);



    //Set Black Pawns
    for(int i = 0; i < 8; i++){
        SchaakStuk* p2 = new Pion(wit);
        setPiece(6, i, p2);
    }
    //Set White Towers
    SchaakStuk* t1w = new Toren(wit);
    SchaakStuk* t2w = new Toren(wit);
    setPiece(7, 0, t1w);
    setPiece(7, 7, t2w);


    //Set White Horses
    SchaakStuk* h1w = new Paard(wit);
    SchaakStuk* h2w = new Paard(wit);
    setPiece(7, 1, h1w);
    setPiece(7, 6, h2w);


    //Set White Bishops
    SchaakStuk* l1w = new Loper(wit);
    SchaakStuk* l2w = new Loper(wit);
    setPiece(7, 2, l1w);
    setPiece(7, 5, l2w);


    //Set White King and Queen
    SchaakStuk* kw = new Koning(wit);
    setPiece(7, 3, kw);
    SchaakStuk* qw = new Koningin(wit);
    setPiece(7, 4, qw);


}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    zw KleurPiece = s->getKleur();
    std::pair<int,int> pair1 (r,k);
    std::vector<std::pair<int, int>> geldigZetten = s->geldige_zetten(*this);

    for(auto zet : geldigZetten){
        if(getPiece(r,k) != nullptr && getPiece(r,k)->getKleur() == KleurPiece){
            return false;
        }else{
            if(zet == pair1){
                setPiece(r, k, s);
                bord[firstClickPos.first][firstClickPos.second] = nullptr;
                return true;
            }
        }

    }
    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) const{
    SchaakStuk* koning = getKoning(kleur);
    std::pair<int,int> koningPosition = koning->getPosition(*this);

    for(const auto& v : bord){
        for(auto p : v){
            if(p!= nullptr && p->getKleur() != kleur){
                for(auto pos: p->geldige_zetten(*this)){
                    if(koningPosition == pos){
                        return true;
                    }
                }
            }

        }
    }
    return false;
}


// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    SchaakStuk* koning = getKoning(kleur);
    if(schaak(kleur) && koning->geldige_zetten(*this).empty()){
        return true;
    }
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) const{
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    SchaakStuk* stuk = bord[r][k];
    if (dynamic_cast<SchaakStuk*>(stuk) != nullptr ){
        return stuk;
    }else{
        return nullptr;
    }

}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    // Hier komt jouw code om een stuk neer te zetten op het bord
    bord[r][k] = s;
}

const std::vector<std::vector<SchaakStuk *>> &Game::getBord() const {
    return bord;
}

void Game::setFirstClickPos(const std::pair<int, int> &firstClickPos) {
    Game::firstClickPos = firstClickPos;
}

const std::pair<int, int> &Game::getFirstClickPos() const {
    return firstClickPos;
}

int Game::getClick() const {
    return click;
}

void Game::setClick(int click) {
    Game::click = click;
}

SchaakStuk *Game::getPiece1() const {
    return piece;
}

void Game::setPiece1(SchaakStuk *piece) {
    Game::piece = piece;
}

const std::string &Game::getTurn() const {
    return turn;
}

void Game::setTurn(const std::string &turn) {
    Game::turn = turn;
}


SchaakStuk *Game::getKoning(zw kleur) const {
    for(auto p1 : bord){
        for(auto p2 : p1){
            if(p2 != nullptr){
                if(p2->getKleur() == kleur && dynamic_cast<Koning*>(p2) != nullptr){
                    return p2;
                }
            }
        }
    }
}

//This function will return the possible moves of the opponent pieces
std::vector<std::vector<std::pair<int, int>>> Game::TegenStanderPositions(zw &kleur, const Game &g) const {
    auto dynamicVector = std::vector<std::vector<std::pair<int, int>>>();
    for(const auto& v : bord){
        for(auto p : v){
            //This if statement will check if the piece is a king and if it's the opponent's king.
            //The reason is because the code will enter into an infinite loop if it's the opponent's king
            if(dynamic_cast<Koning*>(p) != nullptr && p->getKleur() != kleur){
                std::pair<int,int> position = p->getPosition(g);
                int x = position.first;
                int y = position.second;
                std::vector<std::pair<int, int>> zetten = {};

                if(x+1 <= 7){
                    std::pair <int, int> geldig (x+1, y);
                    zetten.push_back(geldig);
                }

                //Up
                if(x-1 >=0){
                    std::pair <int, int> geldig (x-1, y);
                    zetten.push_back(geldig);
                }

                //Right
                if(y+1 <= 7){
                    std::pair <int, int> geldig (x, y+1);
                    zetten.push_back(geldig);

                }

                //Left
                if(y-1 >=0){
                    std::pair <int, int> geldig (x, y-1);
                    zetten.push_back(geldig);
                }

                //Right-Up Diagonal
                if(x-1 >=0 && y+1 <=7){
                    std::pair <int, int> geldig (x-1, y+1);
                    zetten.push_back(geldig);

                }

                //Right-Down Diagonal
                if(x+1 <=7 && y+1 <=7){
                    std::pair <int, int> geldig (x+1, y+1);
                    zetten.push_back(geldig);

                }

                //Left-Up Diagonal
                if(x-1 >=0 && y-1 >=0){
                    std::pair <int, int> geldig (x-1, y-1);
                    zetten.push_back(geldig);
                }

                if(x+1 <=7 && y-1 >=0){
                    std::pair <int, int> geldig (x+1, y-1);
                    zetten.push_back(geldig);

                }
                dynamicVector.push_back(zetten);
            }else{
                if(p != nullptr && p->getKleur() != kleur){
                    dynamicVector.push_back(p->geldige_zetten(g));
                }
            }

        }
    }
    return dynamicVector;
}

