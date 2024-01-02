//  Student:
//  Rolnummer:
//  Opmerkingen: Bij de Save methode in SchaakGUI wordt er twee files aangemaakt. De eerste file slaagt de toestand van
// het bord op. De tweede file slaagt wie zijn beurt het is op. Dit is nodig omdat de GUI niet weet wie zijn beurt het is.
//

#ifndef SCHAAK_GAME_H
#define SCHAAK_GAME_H

#include "SchaakStuk.h"



class Game {
// variabelen om de status van het spel/bord te bewaren
protected:
    std::pair<int,int> firstClickPos; // positie van eerste klik
    int click = 0; // aantal keren geklikt
    SchaakStuk* piece = nullptr;
    std::string turn = "wit";
    SchaakStuk* lastMovedPiece = nullptr; // laatst verplaatste stuk
    std::pair<int,int> lastMovedPiecePos; // positie van laatst verplaatste stuk
    std::vector<std::vector<SchaakStuk*>> lastState = {}; // laatste toestand van het bord
    std::vector<std::vector<SchaakStuk*>> currentState = {}; // huidige toestand van het bord
    std::pair<int,int> DeadPiecePos; // positie van het gedode stuk
    Piece::Type DeadPieceType; // type van het gedode stuk
    zw DeadPieceKleur; // kleur van het gedode stuk
    int aantalUndo;
    int aantalRedo;


public:
    const std::string &getTurn() const; // geeft de kleur van de speler die aan de beurt is

    void setTurn(const std::string &turn); // verandert de kleur van de speler die aan de beurt is

    const std::pair<int, int> &getLastMovedPiecePos() const; // geeft de positie van het laatst verplaatste stuk


    SchaakStuk *getLastMovedPiece() const; // geeft het laatst verplaatste stuk

    std::vector<std::vector<SchaakStuk*>> getLastState() const; // geeft de laatste toestand van het bord

    std::pair<int,int> getDeadPiecePos() const; // geeft de positie van het gedode stuk

    Piece::Type getDeadPieceType() const; // geeft het type van het gedode stuk

    zw getDeadPieceKleur() const; // geeft de kleur van het gedode stuk

    const std::vector<std::vector<SchaakStuk *>> &getCurrentState() const; // geeft de huidige toestand van het bord

    void setCurrentState(const std::vector<std::vector<SchaakStuk *>> &currentState); // verandert de huidige toestand van het bord

    int getAantalUndo() const;

    void setAantalUndo(int aantalUndo);

    int getAantalRedo() const;

    void setAantalRedo(int aantalRedo);


public:
    SchaakStuk *RetrivePiece() const; // geeft het stuk dat verplaatst is

    void SavePiece(SchaakStuk *piece); // slaagt het stuk dat verplaatst is op


    SchaakStuk* getKoning(zw kleur) const; // geeft de koning van de gegeven kleur


public:
    Game();

    int getClick() const;

    void setClick(int click);

    void setFirstClickPos(const std::pair<int, int> &firstClickPos);

    const std::pair<int, int> &getFirstClickPos() const;

    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur) const;

    bool schaakmat(zw kleur) const;

    bool pat(zw kleur) const;

    void setStartBord();

    std::vector<std::vector<std::pair<int, int>>> TegenStanderPositions(zw &kleur, const Game &g) const; // geeft de posities van de stukken van de tegenstander

    SchaakStuk* getPiece(int r, int k) const;

    void setPiece(int r, int k, SchaakStuk* s);

    const std::vector<std::vector<SchaakStuk *>> &getBord() const;

    void setBord(const std::vector<std::vector<SchaakStuk *>> &bord);

private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren ...
    std::vector<std::vector<SchaakStuk*>> bord = {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};
};

#endif //SCHAKEN_GAME_H


