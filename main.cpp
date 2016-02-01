//
//  main.cpp
//  coding_challenge_riffsy
//
//  Created by Justin Platz on 2/1/16.
//  Copyright © 2016 ioJP. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAX_ROW = 5;
const int MAX_COL = 6;

class Piece{
private:
    char piece_value;
    pair<int, int> piece_location;
public:
    Piece(char, pair<int, int>);
    Piece(const Piece&);
    
    char get_piece_value() const;
    pair<int, int> get_piece_location() const;
    
};

Piece::Piece(char piece_val, pair<int, int> piece_loc){
    piece_value = piece_val;
    piece_location = piece_loc;
}

Piece::Piece(const Piece& piece){
    piece_value = piece.get_piece_value();
    piece_location = piece.get_piece_location();
}

char Piece::get_piece_value() const{
    return piece_value;
}

pair<int, int> Piece::get_piece_location() const{
    return piece_location;
}


class Board{
private:
    map<pair<int, int>, char> game_board;
public:
    Board();
    void initBoard();
    void printBoard();
    bool checkValidMove(int);
    bool addPiece(int, char);
    bool isLineStartingAtLocation(pair<int, int>);
    bool findWinner(pair<int, int>, int, int);
    bool checkWinner();
};

Board::Board(){
    initBoard();
}

void Board::initBoard(){
    for(int i = 0; i <= MAX_ROW; i++){
        for(int j = 0; j <= MAX_COL; j++){
            pair<int,int> location;
            location.first = i;
            location.second = j;
            game_board[location] = '*';
        }
    }
};

void Board::printBoard(){
    cout << endl;

    for(int j = 0; j <= MAX_COL; j++){
        cout << j << " ";
    }
    cout << endl;
    
    for(int i = 0; i <= MAX_ROW; i++){
        for(int j = 0; j <= MAX_COL; j++){
            pair<int,int> location;
            location.first = i;
            location.second = j;
            cout << game_board[location] << " ";
        }
        cout << endl;
    }


}

bool Board::checkValidMove(int requested_col){
    
    //Check that the requested_move is in valid range
    if (requested_col < 0 || requested_col > MAX_COL) {
        return false;
    }
    
    //Check that the request_move is in a col which is not full
    for (int i = 0; i <= MAX_ROW; i++) {
        pair<int,int> location;
        location.first = i;
        location.second = requested_col;
        
        //if there is an empty space in the desired col
        if (game_board[location] == '*') {
            return true;
        }
    }
    
    cout << endl << "**Sorry** This Col is entirely filled" << endl;
    return false;
}

bool Board::addPiece(int requested_col, char piece_value){
    //If the col is not entirely filled
    if (checkValidMove(requested_col)) {
        //Find the lowest available space in the col
        for (int i = MAX_ROW; i >= 0; i--) {
            pair<int, int> location;
            location.first = i;
            location.second = requested_col;
            if (game_board[location] == '*') {
                game_board[location] = piece_value;
                return true;
            }
            
        }
    }
    return false;
}

bool Board::findWinner(pair<int, int> piece_location, int stepX, int stepY){
    const char starting_location = game_board[piece_location];
    
    for (int i = 1; i < 4; ++i) {
        pair<int,int> location;
        location.first = piece_location.first + i * stepX;
        location.second = piece_location.second + i * stepY;
        if (game_board[location] != starting_location) {
            return false;
        }
        if (game_board[location] == '*') {
            return false;
        }
    }
    
    //We have found a winner!
    cout << endl << "***WE HAVE A WINNER!!***" << endl;
    printBoard();
    return true;
    
}

bool Board::isLineStartingAtLocation(pair<int, int> loc){
    return findWinner(loc, 1, 0) || //Horizontal
    findWinner(loc, 0, 1) || //Vertical
    findWinner(loc, 1, 1) || //Diagonal Down
    findWinner(loc, 1, -1); //Diagonal Up
}

bool Board::checkWinner(){
    for(int i = MAX_ROW; i >= 0; i--){
        for(int j = MAX_COL; j >= 0; j--){
            pair<int,int> location;
            location.first = i;
            location.second = j;
            if(isLineStartingAtLocation(location)){
                return true;
            };
        }
    }
    return false;
}

void displayRules(){
    cout << "Welcome! How To Play:" << endl;
    cout << "It is X's turn first" << endl;
    cout << "To enter desired move:Col" << endl;
    cout << "Have Fun!" << endl << endl;
}


bool isValidInput(string desired_move){
    char col = desired_move[0];

    //This is invalid input
    if (!isdigit(col)) {
        cout << endl << "*Sorry* Please enter an int [0,6]" << endl;
        return false;
    }
    
    int Col = col - '0';
    if (Col < 0 || Col > MAX_COL) {
        cout << endl << "*Sorry* Col must be [0,6]" << endl;
        return  false;
    }
    
    return true;

}

int createPiece(string desired_move){
    char col_char = desired_move[0];
    int Col= col_char - '0';
    return Col;
}



int main(int argc, const char * argv[]) {
    
    displayRules();
    Board gameBoard;
    int player_turn = 0;
    bool game_is_over = false;
    
    while (!game_is_over) {
        if (player_turn % 2 == 1) {
            cout << endl << "It is O's turn" << endl;
        }
        else{
            cout << endl << "It is X's turn" << endl;
        }
        cout << "Current Board: " << endl;
        gameBoard.printBoard();
        
        string desired_move;
        cin >> desired_move;
        int desired_col;
        if(isValidInput(desired_move)){
            desired_col = createPiece(desired_move);
            
            if (player_turn % 2 == 0) {
                if(gameBoard.addPiece(desired_col, 'X')){
                    game_is_over = gameBoard.checkWinner();
                    player_turn += 1;
                }
            }
            else
                if(gameBoard.addPiece(desired_col, 'O')){
                    game_is_over = gameBoard.checkWinner();
                    player_turn += 1;
                }
        }
        
    }
    
    return 0;
}
