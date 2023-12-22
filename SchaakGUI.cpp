//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
#include <iostream>


// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    update();
}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {

    removeAllMarking();  // Alle markeringen weg
    clearBoard();        // Alle stukken weg
    //This loop will go through the game board and place the pieces on the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            SchaakStuk* piece = g.getPiece(i,j);
            if(piece != nullptr){
                setItem(i, j, piece);
            }

        }
    }

}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    // Wat hier staat is slechts een voorbeeldje dat wordt afgespeeld ter illustratie.
    // Jouw code zal er helemaal anders uitzien en zal enkel de aanpassing in de spelpositie maken en er voor
    // zorgen dat de visualisatie (al dan niet via update) aangepast wordt.

    // Volgende schaakstukken worden aangemaakt om het voorbeeld te illustreren.
    // In jouw geval zullen de stukken uit game g komen

    //This if statement will check if it's White's turn
    if(g.getTurn() == "wit"){
        if(g.getClick() == 0){
            int click1x = r;
            int click1y = k;
            std::pair<int,int> p (click1x, click1y);
            g.setFirstClickPos(p); //This will save the first clicked position

        }
        SchaakStuk* piece = g.getPiece(r,k);
        std::string t = g.getTurn();
        WhiteTurn(piece, t, r,k);
        return;
    }
    //This if statement will check if it's Black's turn
    if(g.getTurn() == "zwart"){
        if(g.getClick() == 0){
            int click1x = r;
            int click1y = k;
            std::pair<int,int> p (click1x, click1y);
            g.setFirstClickPos(p);
        }
        SchaakStuk* piece = g.getPiece(r,k);//This will save the first clicked position
        std::string t = g.getTurn();
        BlackTurn(piece, t, r,k);
        return;
    }







}

void SchaakGUI::newGame()
{
    ClearBord();
    g.setStartBord();
    update();
    g.setClick(0);
    g.setTurn("wit");
}


void SchaakGUI::save() {
    QFile file;
    QFile file2;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        int kolom = 0;
        for (const auto &v: g.getBord()) {
            for (auto piece: v) {
                if (piece == nullptr) {

                    out << QString(".");
                } else if (piece->piece().type() == Piece::Pawn && piece->getKleur() == zwart) {

                    out << QString("Pb");
                } else if (piece->piece().type() == Piece::Rook && piece->getKleur() == zwart) {

                    out << QString("Rb");
                } else if (piece->piece().type() == Piece::Knight && piece->getKleur() == zwart) {

                    out << QString("Hb");
                } else if (piece->piece().type() == Piece::Bishop && piece->getKleur() == zwart) {

                    out << QString("Bb");
                } else if (piece->piece().type() == Piece::Queen && piece->getKleur() == zwart) {

                    out << QString("Qb");
                } else if (piece->piece().type() == Piece::King && piece->getKleur() == zwart) {

                    out << QString("Kb");
                } else if (piece->piece().type() == Piece::Pawn && piece->getKleur() == wit) {

                    out << QString("Pw");
                } else if (piece->piece().type() == Piece::Rook && piece->getKleur() == wit) {

                    out << QString("Rw");
                } else if (piece->piece().type() == Piece::Knight && piece->getKleur() == wit) {

                    out << QString("Hw");
                } else if (piece->piece().type() == Piece::Bishop && piece->getKleur() == wit) {

                    out << QString("Bw");
                } else if (piece->piece().type() == Piece::Queen && piece->getKleur() == wit) {

                    out << QString("Qw");
                } else if (piece->piece().type() == Piece::King && piece->getKleur() == wit) {

                    out << QString("Kw");
                }

            }


        }
    }
    if(openFileToWrite(file2)){
        QDataStream out(&file2);
        out << QString(g.getTurn().c_str());
    }
}

void SchaakGUI::open() {
    ClearBord();
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            for (int i=0;i<8;i++) {
                for (int j=0;j<8;j++) {
                    QString piece;
                    in >> piece;
                    if(piece == QString("Pb")){
                        SchaakStuk* p1 = new Pion(zwart);
                        g.setPiece(i, j, p1);
                    }
                    if(piece == QString("Rb")){
                        SchaakStuk* t1 = new Toren(zwart);
                        g.setPiece(i, j, t1);
                    }
                    if(piece == QString("Hb")){
                        SchaakStuk* h1 = new Paard(zwart);
                        g.setPiece(i, j, h1);
                    }
                    if(piece == QString("Bb")){
                        SchaakStuk* l1 = new Loper(zwart);
                        g.setPiece(i, j, l1);
                    }
                    if(piece == QString("Qb")){
                        SchaakStuk* q = new Koningin(zwart);
                        g.setPiece(i, j, q);
                    }
                    if(piece == QString("Kb")){
                        SchaakStuk* k = new Koning(zwart);
                        g.setPiece(i, j, k);
                    }
                    if(piece == QString("Pw")){
                        SchaakStuk* p2 = new Pion(wit);
                        g.setPiece(i, j, p2);
                    }
                    if(piece == QString("Rw")){
                        SchaakStuk* t2 = new Toren(wit);
                        g.setPiece(i, j, t2);
                    }
                    if(piece == QString("Hw")){
                        SchaakStuk* h2 = new Paard(wit);
                        g.setPiece(i, j, h2);
                    }
                    if(piece == QString("Bw")){
                        SchaakStuk* l2 = new Loper(wit);
                        g.setPiece(i, j, l2);
                    }
                    if(piece == QString("Qw")){
                        SchaakStuk* q = new Koningin(wit);
                        g.setPiece(i, j, q);
                    }
                    if(piece == QString("Kw")){
                        SchaakStuk* k = new Koning(wit);
                        g.setPiece(i, j, k);
                    }
                }

                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Ongeldig formaat");
                    }
                }
            }
        catch (QString& Q) {
            message(Q);
        }
    }
    QFile file2;
    if(openFileToRead(file2)){
        QDataStream in(&file2);
        QString turn;
        in >> turn;
        g.setTurn(turn.toStdString());
    }
    update();
}


void SchaakGUI::undo() {
    g.setCurrentState(g.getBord());
    SchaakStuk* piece = g.getLastMovedPiece();
    std::pair<int,int> pos = g.getLastMovedPiecePos();
    std::pair<int,int> pos2 = g.getDeadPiecePos();
    SchaakStuk* resurectedPiece = nullptr;

        if(g.getDeadPieceType() != Piece::None){
            if(g.getDeadPieceType() == Piece::Pawn){
                resurectedPiece = new Pion(g.getDeadPieceKleur());
            }
            if(g.getDeadPieceType() == Piece::Rook){
                resurectedPiece = new Toren(g.getDeadPieceKleur());
            }
            if(g.getDeadPieceType() == Piece::Knight){
                resurectedPiece = new Paard(g.getDeadPieceKleur());
            }
            if(g.getDeadPieceType() == Piece::Bishop){
                resurectedPiece = new Loper(g.getDeadPieceKleur());
            }
            if(g.getDeadPieceType() == Piece::Queen){
                resurectedPiece = new Koningin(g.getDeadPieceKleur());
            }
            if(g.getDeadPieceType() == Piece::King){
                resurectedPiece = new Koning(g.getDeadPieceKleur());
            }
        }




    if(g.getTurn() == "wit"){
        if(piece->piece().type() == Piece::Pawn && piece->getAantalMoves() == 1){
            piece->DecrementMoves();
        }
        g.setTurn("zwart");
        g.setBord(g.getLastState());
        if(g.getDeadPieceType() != Piece::None){
            g.setPiece(pos2.first, pos2.second, resurectedPiece);
        }
        update();
        return;

    }
    if(g.getTurn() == "zwart"){
        if(piece->piece().type() == Piece::Pawn && piece->getAantalMoves() == 1){
            piece->DecrementMoves();
        }
        g.setTurn("wit");
        g.setBord(g.getLastState());
        if(g.getDeadPieceType() != Piece::None){
            g.setPiece(pos2.first, pos2.second, resurectedPiece);
        }
        update();
    }

}

void SchaakGUI::redo() {
    if(g.getTurn() == "wit"){
        g.setTurn("zwart");
        g.setBord(g.getCurrentState());
        update();
        return;
    }
    if(g.getTurn() == "zwart"){
        g.setTurn("wit");
        g.setBord(g.getCurrentState());
        update();
    }

}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Nieuwe settings : ")+visstring);
}

//This function will check if the move is valid and if it is it will move the piece
void SchaakGUI::WhiteTurn(SchaakStuk* &s, std::string &turn, int x, int y) {
    //This if statement will check if the click is the first click or the second click
    if(g.getClick() ==0 ){
        removeAllMarking();
        if(s != nullptr && g.schaakmat(s->getKleur())){
            message("CheckMate!, Game Over!");
            return;
        }
        if(s != nullptr && g.schaak(s->getKleur())){
            message("Schaak! White's King");
        }
        if(s!= nullptr && g.pat(s->getKleur())){
            message("Pat!, Game Over!");
            return;
        }


        if(displayMoves()){
            if(s!= nullptr){
                std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
                for(auto pair : zetten){
                    setTileFocus(pair.first, pair.second, true);
                }
            }

        }

        if(displayThreats()){
            if(s!= nullptr){
                CheckTileThreat(s);
            }

        }

        //This if statement will check if the piece is a white piece and if it is white's turn
        if(s!= nullptr && s->getKleur() == wit && turn == "wit") {
            g.SavePiece(s); //This will save the piece that was clicked
            if (s->getKleur() == wit && turn == "wit") {
                setTileSelect(x, y, true);
            }
            g.setClick(1);
            return;

        //This else statement will give a message if it's White's turn but the piece is black
        }else{
            if(s == nullptr){
                message("No Piece Selected!");
                return;
            }
            message("White's Turn!");
            removeAllMarking();
            return;
        }
    }
    //This if statement will check if the click is the second click
    if(g.getClick() == 1){
        std::pair<int,int> pos = g.getFirstClickPos();
        if(pos.first == x && pos.second==y){
            setTileSelect(x,y, false);
            removeAllMarking();
            g.setClick(0);
            return;
        }

        bool geldig = g.move(g.RetrivePiece(), x, y);
        //This if statement will check if the move is valid
        if(geldig){
            g.setClick(0);
            g.setTurn("zwart");
            g.SavePiece(nullptr);
            update();
            if(displayKills()){
                CheckPieceThreat();
            }
            return;

        }
        //This else statement will give a message if the move is not valid
        else{
            message("Move niet geldig White");

        }
    }
}

//This function will check if the move is valid and if it is it will move the piece
void SchaakGUI::BlackTurn(SchaakStuk *&s, std::string &turn, int x, int y) {
    removeAllMarking();
    //This if statement will check if the click is the first click or the second click
    if (g.getClick() == 0) {
        //This if statement will check if Black is in checkmate
        if(s != nullptr && g.schaakmat(s->getKleur())){
            message("CheckMate!, Game Over!");
            return;
        }
        //This if statement will check if Black is in check
        if(s != nullptr && g.schaak(s->getKleur())){
            message("Schaak! Black's King");
        }
        //This if statement will check if Black is in stalemate
        if(s!= nullptr && g.pat(s->getKleur())){
            message("Pat!, Game Over!");
            return;
        }



        if(displayMoves()){
            if(s!= nullptr){
                std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
                for(auto pair : zetten){
                    setTileFocus(pair.first, pair.second, true);
                }
            }
        }


        if(displayThreats()){
            if(s!= nullptr){
                CheckTileThreat(s);
            }

        }
        if(s != nullptr && s->getKleur() == zwart && turn == "zwart") {
            g.SavePiece(s);//This will save the piece that was clicked
            if (s->getKleur() == zwart && turn == "zwart") {
                setTileSelect(x, y, true);
            }

            g.setClick(1);
            return;

        //This else statement will give a message if it's Black's turn but the clicked piece is white
        }else{
            if(s== nullptr){
                message("No Piece Selected!");
                return;
            }
            message("Black's Turn!");
            removeAllMarking();

            return;
        }

    }

    if(g.getClick() == 1){
        std::pair<int,int> pos = g.getFirstClickPos();
        //This if statement will check if the player clicked on the same place twice
        //If that's the case then it will deselect the selected piece.
        if(pos.first == x && pos.second==y){
            setTileSelect(x,y, false);
            removeAllMarking();
            g.setClick(0);
            return;
        }
        bool geldig = g.move(g.RetrivePiece(), x, y);
        if(geldig){
            g.setClick(0);
            g.setTurn("wit");
            g.SavePiece(nullptr);
            update();
            if(displayKills()){
                CheckPieceThreat();
            }
            return;

        }
        //This else statement will give a message if the move is not valid
        else{
            message("Move niet geldig Black");

        }

    }
}

//This function will the position at which the selected piece will be at risk of capture
void SchaakGUI::CheckTileThreat(SchaakStuk *&s) {
    std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
    for(const auto& v : g.getBord()){
        for(auto piece : v){
            if(piece != nullptr && piece->getKleur() != s->getKleur()){
                std::vector<std::pair<int,int>> zettenOpp = piece->geldige_zetten(g);
                for(auto zet : zetten){
                    for(auto zetOpp : zettenOpp){
                        if(zet == zetOpp){
                            setTileThreat(zet.first, zet.second, true);
                        }
                    }
                }
            }
        }
    }
}

//This function will color the piece(s) that are at risk of capture
void SchaakGUI::CheckPieceThreat() {
    for(const auto& v : g.getBord()){
        for(auto piece : v){
            if(piece!= nullptr){
                auto position = piece->getPosition(g);
                CheckPieceThreat_HelpFunction(piece->getKleur(), position);
            }

        }
    }

}

//This function helps the CheckPieceThreat function
void SchaakGUI::CheckPieceThreat_HelpFunction(zw kleur,std::pair<int, int> pos) {
    for(const auto& v : g.getBord()){
        for(auto piece : v){
            if(piece!= nullptr && piece->getKleur() != kleur){
                auto zetten = piece->geldige_zetten(g);
                for(auto zet : zetten){
                    if(zet == pos){
                        setPieceThreat(pos.first, pos.second, true);
                    }
                }
            }

        }
    }

}

//This function will delete all the pieces on the board. It is used when the open function is called
void SchaakGUI::ClearBord() {
    for(const auto& p1 : g.getBord()){
        for(auto p2 : p1){
            auto position = p2->getPosition(g);
            delete p2;
        }
    }

    std::vector<std::vector<SchaakStuk*>> Newbord = {{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
                                                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}};

    g.setBord(Newbord);


}













