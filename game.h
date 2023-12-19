//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAAK_GAME_H
#define SCHAAK_GAME_H

#include "SchaakStuk.h"



class Game {
// variabelen om de status van het spel/bord te bewaren
protected:
    std::pair<int,int> firstClickPos;
    int click = 0;
    SchaakStuk* piece = nullptr;
    std::string turn = "wit";
public:
    const std::string &getTurn() const;

    void setTurn(const std::string &turn);

public:
    SchaakStuk *getPiece1() const;

    void setPiece1(SchaakStuk *piece);


    SchaakStuk* getKoning(zw kleur) const;


public:
    Game();

    int getClick() const;

    void setClick(int click);

    void setFirstClickPos(const std::pair<int, int> &firstClickPos);

    const std::pair<int, int> &getFirstClickPos() const;

    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur) const;
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();
    std::vector<std::vector<std::pair<int, int>>> TegenStanderPositions(zw &kleur, const Game &g) const;

    SchaakStuk* getPiece(int r, int k) const;
    void setPiece(int r, int k, SchaakStuk* s);
    const std::vector<std::vector<SchaakStuk *>> &getBord() const;

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


