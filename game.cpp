#include <iostream>
#include <vector>
#include <string>
#include "table.cpp"
#include "player_x.cpp"
#include "player_o.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
class Game {
public:
    int type;
    bool is_started;
    bool is_finished;
    bool w_l_or_d;
    int turn;
    int winner;
    std::vector<std::vector<int>> moves;
    std::vector<int> move_address;
    void set_type(int t) {
        type = t;
    }
    void end(Board b) {

        int x = 1;
        int o = -1;
        int size = b.rc;
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == 0 || i == 1 || i == size-2 || i == size-1) {
                    if(j == 0|| j == 1|| j== size-2 || j==size-1 ){
                        continue;
                    }
                }
                if (b.board[i][j].is_blank) {
                    continue;
                }
                std::vector<std::vector<int>> five_cells;
                if (i == 0 || i == 1 || i == size-2 || i == size-1) {
                    five_cells = {
                    {b.board[i][j-2].cell_value, b.board[i][j-1].cell_value, b.board[i][j].cell_value, b.board[i][j+1].cell_value, b.board[i][j+2].cell_value},
                    };
                } else if (j == 0 || j == 1 || j == size-2 || j == size-1) {
                    five_cells = {
                    {b.board[i-2][j].cell_value, b.board[i-1][j].cell_value, b.board[i][j].cell_value, b.board[i+1][j].cell_value, b.board[i+2][j].cell_value},
                    };
                }
                else {
                    five_cells = {
                    {b.board[i-2][j-2].cell_value, b.board[i-1][j-1].cell_value, b.board[i][j].cell_value, b.board[i+1][j+1].cell_value, b.board[i+2][j+2].cell_value},
                    {b.board[i-2][j].cell_value, b.board[i-1][j].cell_value, b.board[i][j].cell_value, b.board[i+1][j].cell_value, b.board[i+2][j].cell_value},
                    {b.board[i][j-2].cell_value, b.board[i][j-1].cell_value, b.board[i][j].cell_value, b.board[i][j+1].cell_value, b.board[i][j+2].cell_value},
                    {b.board[i-2][j+2].cell_value, b.board[i-1][j+1].cell_value, b.board[i][j].cell_value, b.board[i+1][j-1].cell_value, b.board[i+2][j-2].cell_value},
                    };
                }
                for (int k = 0; k < five_cells.size(); k++) {
                    std::cout<< "Cells blank" <<b.number_cell_blank<<std::endl;
                    if (five_cells[k] == std::vector<int>{x, x, x, x, x}) {
                        w_l_or_d = true;
                        winner = 1;
                        is_finished = true;
                        return;
                    } else if (five_cells[k] == std::vector<int>{o, o, o, o, o}) {
                        w_l_or_d = true;
                        winner = -1;
                        is_finished = true;
                        return;
                    }
                }
                if (b.number_cell_blank == 0) {
                    w_l_or_d = false;
                    is_finished = true;
                    return;
                } else {
                    
                }
                
            }
            // std::cout<< "Cells blank" <<b.number_cell_blank<<is_finished<<std::endl;
        }
    }
    Game( int t) {
        is_started = true;
        is_finished = false;
        w_l_or_d = false;
        turn = 0;
        winner = 0;
        moves = {};
        move_address = {};
        set_type(t);
    };


};

