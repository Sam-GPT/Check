//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"


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
            g.setFirstClickPos(p);

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
        SchaakStuk* piece = g.getPiece(r,k);
        std::string t = g.getTurn();
        BlackTurn(piece, t, r,k);
        return;
    }







}

void SchaakGUI::newGame()
{

}


void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Ongeldig formaat");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}


void SchaakGUI::undo() {
    message("UNDO");
}

void SchaakGUI::redo() {
    message("REDO");
}


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Nieuwe settings : ")+visstring);
}

//This function will check if the move is valid and if it is it will move the piece
void SchaakGUI::WhiteTurn(SchaakStuk* &s, std::string &turn, int x, int y) {
    //This if statement will check if the click is the first click or the second click
    if(g.getClick() ==0 ){
        if(s != nullptr && g.schaakmat(s->getKleur())){
            message("Game Over!!");
            return;
        }
        if(s != nullptr && g.schaak(s->getKleur())){
            message("Schaak! White's King");
        }
        if(displayMoves()){
            std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
            for(auto pair : zetten){
                setTileFocus(pair.first, pair.second, true);
            }
        }
        if(displayKills()){
            CheckCanKill(s);
        }
        if(displayThreats()){
            CheckTileThreat(s);
        }

        //This if statement will check if the piece is a white piece and if it is white's turn
        if(s->getKleur() == wit && turn == "wit") {
            //This if statement will check if the piece is not a nullptr
            if (s != nullptr) {
                g.setPiece1(s);
                if (s->getKleur() == wit && turn == "wit") {
                    setTileSelect(x, y, true);
                }
            }
            g.setClick(1);
            return;

        //This else statement will give a message if it's White's turn but the piece is black
        }else{
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

        bool geldig = g.move(g.getPiece1(), x, y);
        //This if statement will check if the move is valid
        if(geldig){
            g.setClick(0);
            g.setTurn("zwart");
            g.setPiece1(nullptr);
            update();
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
    //This if statement will check if the click is the first click or the second click
    if (g.getClick() == 0) {
        if(s != nullptr && g.schaakmat(s->getKleur())){
            message("Game Over!!");
            return;
        }
        if(s != nullptr && g.schaak(s->getKleur())){
            message("Schaak! Black's King");
        }
        if(displayMoves()){
            std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
            for(auto pair : zetten){
                setTileFocus(pair.first, pair.second, true);
            }
        }
        if(displayKills()){
            CheckCanKill(s);
        }
        if(displayThreats()){
            CheckTileThreat(s);
        }
        if(s->getKleur() == zwart && turn == "zwart") {
            if (s != nullptr) {
                g.setPiece1(s);
                if (s->getKleur() == zwart && turn == "zwart") {
                    setTileSelect(x, y, true);
                }
            }
            g.setClick(1);
            return;

        //This else statement will give a message if it's Black's turn but the piece is white
        }else{
            message("Black's Turn!");
            removeAllMarking();

            return;
        }

    }

    if(g.getClick() == 1){
        std::pair<int,int> pos = g.getFirstClickPos();
        if(pos.first == x && pos.second==y){
            setTileSelect(x,y, false);
            removeAllMarking();
            g.setClick(0);
            return;
        }
        bool geldig = g.move(g.getPiece1(), x, y);
        if(geldig){
            g.setClick(0);
            g.setTurn("wit");
            g.setPiece1(nullptr);
            update();

        }
        //This else statement will give a message if the move is not valid
        else{
            message("Move niet geldig Black");

        }

    }
}

void SchaakGUI::CheckTileThreat(SchaakStuk *&s) {
    std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
    for(auto v : g.getBord()){
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

void SchaakGUI::CheckCanKill(SchaakStuk *&s) {
    std::vector<std::pair<int,int>> zetten = s->geldige_zetten(g);
    for(auto v : g.getBord()){
        for(auto piece : v){
            if(piece != nullptr && piece->getKleur() != s->getKleur()){
                for(auto zet : zetten){
                    if(piece->getPosition(g) == zet){
                        setPieceThreat(zet.first,zet.second, true);
                    }
                }
            }
        }
    }
}












