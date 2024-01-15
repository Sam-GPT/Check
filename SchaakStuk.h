//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>


class Game;

enum zw{zwart,wit};

class SchaakStuk {
    int aantalMoves = 0;
public:
    explicit SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const;

    virtual std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const = 0;

    std::pair<int,int> getPosition(const Game &g) const;

   void IncrementMoves();

   void DecrementMoves();

   int getAantalMoves() const;

   virtual ~SchaakStuk();
private:
    zw kleur;
};

class Pion:public SchaakStuk {

public:
    explicit Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }


    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

    virtual ~Pion() override;


};

class Toren:public SchaakStuk {
public:
    explicit Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

   virtual ~Toren() override;
};

class Paard:public SchaakStuk {
public:
    explicit Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

    virtual ~Paard() override;
};

class Loper:public SchaakStuk {
public:
    explicit Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

    virtual ~Loper() override;
};

class Koning:public SchaakStuk {
public:
    explicit Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

    virtual ~Koning() override;
};

class Koningin:public SchaakStuk {
public:
    explicit Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    std::vector<std::pair<int,int>> geldige_zetten(const Game& g) const override;

    virtual ~Koningin() override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
