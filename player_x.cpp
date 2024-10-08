#ifndef PLAYER_X_H
#define PLAYER_X_H
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
class PlayerX {
public:
    bool win;
    std::vector<std::vector<int>> moves;
    int val;
    void set_move(int row, int col) {
        std::vector<int> move_address;
        move_address.push_back(row);
        move_address.push_back(col);
        moves.push_back(move_address);
        
    }
    void set_win(bool w) {
        win = w;
    }
    void render(SDL_Renderer* renderer, SDL_Rect* rect) {
        SDL_Surface* image = IMG_Load("src/SDL_material/x.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_RenderCopy(renderer, texture, NULL,rect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(texture);
    }
    PlayerX() {
        win = false;
        
        moves = {};
        val = 1;
    }
};
#endif // PLAYER_X_H