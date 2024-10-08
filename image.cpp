#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
class Image {
public:
    // Image,renderer, rect, color
    SDL_Surface* image;
    SDL_Rect rect;
    SDL_Color color;
    int x, y;

    // Draw button
    void draw(SDL_Renderer* renderer) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->image);
        // Set blend mode
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderer, texture, NULL, &this->rect);
        SDL_FreeSurface(this->image);
        SDL_DestroyTexture(texture);

    }
    // Constructor
    Image(std::string image_url, int x, int y,int dim_x, int dim_y) {
        // Load image
        this->image = IMG_Load(image_url.c_str());
        // Set rect dimensions
        this->rect = { x, y, dim_x, dim_y };
        // Set x and y position
        this->x = x;
        this->y = y;
    }
};
