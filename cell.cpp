#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
class Cell {
public:
    int cell_index;
    int cell_value;
    bool is_blank;
    int cell_address[2];
    SDL_Rect rect;
    SDL_Surface* image;
    void set_cell_address(int row, int col) {
        cell_address[0] = row;
        cell_address[1] = col;
    }
    void set_cell_value(int index, int value) {
        cell_index = index;
        cell_value = value;
    }
    void render_cell(SDL_Renderer* renderer, int x, int y, int w, int h) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->image);
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(texture);
    }
    bool handleClick(SDL_Event event){
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            return (mouseX >= this->rect.x && mouseX <= this->rect.x + this->rect.w && mouseY >= this->rect.y && mouseY <= this->rect.y + this->rect.h);
        } else {
            return false;
        }
    }
    Cell( int index, int row, int col, std::string image_url,int x, int y,int w, int h) {
        image = IMG_Load(image_url.c_str());
        is_blank = true;
        cell_index = index;
        cell_value = 0;
        set_cell_address(row, col);
        rect = {x, y, w, h};
    }
};