#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
class Button {
public:
    // Image,renderer, rect, color
    SDL_Surface* image;
    SDL_Rect rect;
    int x, y;
    int counter = 0;

    // Draw button
    void draw(SDL_Renderer* renderer) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->image);
        SDL_RenderCopy(renderer, texture, NULL, &this->rect);
        SDL_FreeSurface(this->image);
        SDL_DestroyTexture(texture);

    }
    bool handleClicked(SDL_Event event) {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            return (mouseX >= this->x && mouseX <= this->x + this->rect.w && mouseY >= this->y && mouseY <= this->y + this->rect.h);
        } else {
            return false;
        }
    }
    // Constructor
    Button(std::string image_url, int x, int y,int dim_x, int dim_y) {
        // Load image
        this->image = IMG_Load(image_url.c_str());
        // Set rect dimensions
        this->rect = { x, y, dim_x, dim_y };
        // Set x and y position
        this->x = x;
        this->y = y;
    }
};
