//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include <iostream>

Game::Game() {
    setStartBord();
}

Game::~Game() {
    for(const auto& p1 : bord){
        for(auto p2 : p1){
            delete p2;
        }
    }
}

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
    std::pair<int,int> position = s->getPosition(*this);

    for(auto zet : geldigZetten){
        if(getPiece(r,k) != nullptr && getPiece(r,k)->getKleur() == KleurPiece){
            return false;
        }else{
            if(zet == pair1){
                //This piece will delete the piece that is on the position where the piece will move
                SchaakStuk* defeted = getPiece(r,k);
                if(defeted != nullptr){
                    DeadPiecePos = defeted->getPosition(*this);
                    DeadPieceKleur = defeted->getKleur();
                    DeadPieceType = defeted->piece().type();
                    delete defeted;
                    bord[r][k] = nullptr;
                }else{
                    DeadPiecePos = std::pair<int,int>(-1,-1);
                    DeadPieceType = Piece::None;
                }


                //This piece will move the piece to the new position
                lastMovedPiece = s;
                lastMovedPiecePos = position;
                lastState = bord;
                setPiece(r, k, s);
                aantalUndo = 0;
                aantalRedo = 0;
                s->IncrementMoves();
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
bool Game::schaakmat(zw kleur) const {
    SchaakStuk* koning = getKoning(kleur);
    if(schaak(kleur) && koning->geldige_zetten(*this).empty()){
        return true;
    }
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) const {
    SchaakStuk* koning = getKoning(kleur);
    if(!schaak(kleur) && koning->geldige_zetten(*this).empty()){
        if(koning->getAantalMoves() >0){
            return true;
        }

    }
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

//This function will return the board
const std::vector<std::vector<SchaakStuk *>> &Game::getBord() const {
    return bord;
}

//This function will save the position of the first click
void Game::setFirstClickPos(const std::pair<int, int> &firstClickPos) {
    Game::firstClickPos = firstClickPos;
}

//This function will return the position of the first click
const std::pair<int, int> &Game::getFirstClickPos() const {
    return firstClickPos;
}

//This function will return the number of clicks
int Game::getClick() const {
    return click;
}

//This function will save the number of clicks
void Game::setClick(int click) {
    Game::click = click;
}

//This function will return the piece that was clicked
SchaakStuk *Game::RetrivePiece() const {
    return piece;
}

//This function will save the piece that was clicked
void Game::SavePiece(SchaakStuk *piece) {
    Game::piece = piece;
}

//This function will return who's turn it is
const std::string &Game::getTurn() const {
    return turn;
}

//This function will save who's turn it is
void Game::setTurn(const std::string &turn) {
    Game::turn = turn;
}


//This function will return the king of the given color
SchaakStuk *Game::getKoning(zw kleur) const {
    for(const auto& p1 : bord){
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

                //Down
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
                //Left-Down Diagonal
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

void Game::setBord(const std::vector<std::vector<SchaakStuk *>> &bord) {
    Game::bord = bord;

}

const std::pair<int, int> &Game::getLastMovedPiecePos() const {
    return lastMovedPiecePos;
}

SchaakStuk *Game::getLastMovedPiece() const {
    return lastMovedPiece;
}


std::vector<std::vector<SchaakStuk *>> Game::getLastState() const {
    return lastState;
}

std::pair<int, int> Game::getDeadPiecePos() const {
    return DeadPiecePos;
}

Piece::Type Game::getDeadPieceType() const {
    return DeadPieceType;
}

zw Game::getDeadPieceKleur() const {
    return DeadPieceKleur;
}

const std::vector<std::vector<SchaakStuk *>> &Game::getCurrentState() const {
    return currentState;
}

void Game::setCurrentState(const std::vector<std::vector<SchaakStuk *>> &currentState) {
    Game::currentState = currentState;
}

int Game::getAantalUndo() const {
    return aantalUndo;
}

void Game::setAantalUndo(int aantalUndo) {
    Game::aantalUndo = aantalUndo;
}

int Game::getAantalRedo() const {
    return aantalRedo;
}

void Game::setAantalRedo(int aantalRedo) {
    Game::aantalRedo = aantalRedo;
}

