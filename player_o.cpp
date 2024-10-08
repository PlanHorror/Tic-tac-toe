#ifndef PLAYER_O_H
#define PLAYER_O_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
class PlayerO{
public:
    bool win;
    std::vector<std::vector<int>> moves;
    int val;
    void set_move(int row, int col) {
        std::vector<int> move_address(2);
        move_address[0] = row;
        move_address[1] = col;
        moves.push_back(move_address);
        
    }
    void set_win(bool w) {
        win = w;
    }
    void render(SDL_Renderer* renderer, SDL_Rect* rect) {
        SDL_Surface* image = IMG_Load("src/SDL_material/o.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_RenderCopy(renderer, texture, NULL,rect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(texture);
    }
    PlayerO() {
        win = false;
        
        moves = {};
        val = -1;
    }
};

#endif // PLAYER_O_H