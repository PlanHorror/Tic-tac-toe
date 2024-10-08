#include <vector>
#include <iostream>
#include "cell.cpp"
#include "player_x.cpp"
#include "player_o.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
class Board {
public:
    int cells, rc;
    int board_size;
    int number_cell_blank;
    int number_cell_non_blank;
    int space_between_cells;
    int total_space_between_cells;
    std::vector<std::vector<Cell>> board;
    void render_board(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
        for (int i = 0; i < rc; i++) {
            for (int j = 0; j < rc; j++) {
                board[i][j].render_cell(renderer, (i * (board_size*299/419/rc + space_between_cells)+(SCREEN_WIDTH*185/789  )), (j * (board_size*299/419/rc + space_between_cells) + (SCREEN_HEIGHT*101/622 )), board_size*299/419/rc,   board_size*299/419/rc);
            }   
        }
    }
    void set_cell(int row, Cell value) {
        board[row].push_back( value);
    }
    void print_board() {
        for (int i = 0; i < rc; i++) {
            for (int j = 0; j < rc; j++) {
                std::cout << board[i][j].cell_value << " ";
            }
            std::cout << std::endl;
        }
    }
    void set_cell_value(int row, int col, int value) {
        board[row][col].cell_value = value;
        board[row][col].is_blank = false;
    }
    bool check_cell(int row, int col) {
        if (board[row][col].is_blank) {
            return true;
        } else {
            std::cout << "Cell is non-blank" << std::endl;
            return false;
        }
    };
    void make_move(int row, int col, int value) {
        set_cell_value(row, col, value);
        number_cell_blank--;
        number_cell_non_blank++;
        
    }
    Board (int size, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
        
        this->number_cell_non_blank = 0;
        this->rc = size;
        this->number_cell_blank = rc * rc;
        this->board_size =  SCREEN_HEIGHT*419/622;
        this->total_space_between_cells = SCREEN_HEIGHT*120/622;
        this->space_between_cells = total_space_between_cells / (rc-1);
        for (int i = 0; i < size; i++) {
            this->board.push_back({});
            for (int j = 0; j < size; j++) {
                Cell cell {i * size + j, i, j, "src/SDL_material/cell.png",(i * (board_size*299/419/rc + space_between_cells)+(SCREEN_WIDTH*185/789  )), (j * (board_size*299/419/rc + space_between_cells) + (SCREEN_HEIGHT*101/622 )), board_size*299/419/rc,   board_size*299/419/rc};
                set_cell(i, cell);
            }
        }
        
    }
};