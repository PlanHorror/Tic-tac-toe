#include <iostream>
#include <string>
#include <vector>
#include "wtypes.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <limits>
#include "game.cpp"
#include "button.cpp"
#include "image.cpp"
//Screen dimension constants just for windows if you want to run it on another OS you should change it
const HWND SCREEN_WIDTH_DEVICE = GetDesktopWindow();
RECT desktop;
const int a = GetWindowRect(SCREEN_WIDTH_DEVICE, &desktop);
const int  SCREEN_HEIGHT = desktop.bottom*8/9,SCREEN_WIDTH = SCREEN_HEIGHT*789/622;
// Screen dimension constants just for windows if you want to run it on another OS you should change it
typedef enum {
    FIRST_INTERFACE,
    SECOND_INTERFACE,
    THIRD_INTERFACE
} Interface;
Interface current_interface;
// Render png image like a button

void drawFirstInterface(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, Button pvE, Button pvP, Image tictactoe) {
    //Draw a screen with rgba(58, 41, 41, 0.57)      
    SDL_SetRenderDrawColor(renderer, 58, 41, 41, 0);
    SDL_RenderClear(renderer);
    // Draw buttons
    try
    {
        pvE.draw(renderer);
        pvP.draw(renderer);
        
        tictactoe.draw(renderer);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    // Draw image
    current_interface = FIRST_INTERFACE;}

void drawSecondInterface(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, Button map3, Button map5, Button map7, Button map9, Button map11, Button map13, Button back, Image tictactoe) {
    //Draw a screen with rgba(58, 41, 41, 0.57)
    SDL_SetRenderDrawColor(renderer, 58, 41, 41, 0.57);
    SDL_RenderClear(renderer);
    // Draw buttons
    map3.draw(renderer);
    map5.draw(renderer);
    map7.draw(renderer);
    map9.draw(renderer);
    map11.draw(renderer);
    map13.draw(renderer);
    back.draw(renderer);    
    // Draw image
    tictactoe.draw(renderer);
    current_interface = SECOND_INTERFACE;
}
void drawThirdInterface(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT,int cell, int rc, Board board,Button back1) {
    //Draw a screen with rgba(58, 41, 41, 0.57)
    SDL_SetRenderDrawColor(renderer, 58, 41, 41, 0.57);
    SDL_RenderClear(renderer);
    board.render_board(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    back1.draw(renderer);
    current_interface = THIRD_INTERFACE;
}
void gameRun(Game game, Board board, PlayerX player_x, PlayerO player_o, SDL_Renderer* renderer) {
    while (game.is_started && !game.is_finished) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT) {
            game.is_finished = true;
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && current_interface == THIRD_INTERFACE)
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            for (int i = 0; i < board.rc; i++) {
                for (int j = 0; j < board.rc; j++) {
                    if (board.board[i][j].handleClick(event)&& board.board[i][j].is_blank) {
                        if (game.turn % 2 == 0) {
                            player_x.set_move(i, j);
                            player_x.render(renderer, &board.board[i][j].rect);
                            SDL_RenderPresent(renderer);
                            board.set_cell_value(i, j, player_x.val);
                            game.moves.push_back({i, j});
                            board.make_move(i, j, player_x.val);
                            game.turn++;
                            board.print_board();
                            game.end(board);
                        } else {
                            player_o.set_move(i, j);
                            player_o.render(renderer, &board.board[i][j].rect);
                            SDL_RenderPresent(renderer);
                            board.set_cell_value(i, j, player_o.val);
                            game.moves.push_back({i, j});
                            board.make_move(i, j, player_o.val);
                            game.turn++;
                            board.print_board();
                            game.end(board);
                        }
                    }
                }
            }
        }
        
    }
    if (game.w_l_or_d) {
        if (game.winner == 1) {
            std::cout << "Player X wins!" << std::endl;
            SDL_Surface* image = IMG_Load("src/SDL_material/xw.png");
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
            SDL_Rect rect = {SCREEN_WIDTH*274/789, SCREEN_HEIGHT*27/622, SCREEN_WIDTH*242/789, SCREEN_HEIGHT*48/622};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_FreeSurface(image);
            SDL_DestroyTexture(texture);
            SDL_RenderPresent(renderer);
        } else {
            std::cout << "Player O wins!" << std::endl;
            SDL_Surface* image = IMG_Load("src/SDL_material/ow.png");
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
            SDL_Rect rect = {SCREEN_WIDTH*274/789, SCREEN_HEIGHT*27/622, SCREEN_WIDTH*242/789, SCREEN_HEIGHT*48/622};
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_FreeSurface(image);
            SDL_DestroyTexture(texture);
            SDL_RenderPresent(renderer);
        }
    } else {
        SDL_Surface* image = IMG_Load("src/SDL_material/draw.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_Rect rect = {SCREEN_WIDTH*343/789, SCREEN_HEIGHT*27/622, SCREEN_WIDTH*103/789, SCREEN_HEIGHT*48/622};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(image);
        SDL_DestroyTexture(texture);
        SDL_RenderPresent(renderer);
        std::cout << "Draw!" << std::endl;
    };
}
int main( int argc, char* args[] )
{
    bool renderThird = false;
    //The window we'll be rendering to 
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    // Render 
    SDL_Renderer* renderer = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }  else
    {
        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        //Initialize SDL_image
        if( IMG_Init(IMG_INIT_PNG) == -1)
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }
        //Load font
        TTF_Font* font = TTF_OpenFont("src/Roboto/Roboto-Regular.ttf", 20);
        //Button
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_INPUT_FOCUS );
        Button pvE = Button("src/SDL_material/PvE.png", (SCREEN_WIDTH * 338/789) , (SCREEN_HEIGHT*337/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button pvP = Button("src/SDL_material/PvP.png", (SCREEN_WIDTH * 338/789) , (SCREEN_HEIGHT*290/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map3 = Button("src/SDL_material/3x3.png", (SCREEN_WIDTH * 275/789) , (SCREEN_HEIGHT*290/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map5 = Button("src/SDL_material/5x5.png", (SCREEN_WIDTH * 275/789) , (SCREEN_HEIGHT*346/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map7 = Button("src/SDL_material/7x7.png", (SCREEN_WIDTH * 275/789) , (SCREEN_HEIGHT*396/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map9 = Button("src/SDL_material/9x9.png", (SCREEN_WIDTH * 411/789) , (SCREEN_HEIGHT*290/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map11 = Button("src/SDL_material/11x11.png", (SCREEN_WIDTH * 411/789) , (SCREEN_HEIGHT*346/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button map13 = Button("src/SDL_material/13x13.png", (SCREEN_WIDTH * 411/789) , (SCREEN_HEIGHT*396/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button back = Button("src/SDL_material/back.png", (SCREEN_WIDTH * 343/789) , (SCREEN_HEIGHT*452/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        Button back1 = Button("src/SDL_material/back1.png", (SCREEN_WIDTH * 343/789) , (SCREEN_HEIGHT*548/622), (SCREEN_WIDTH * 103/789), (SCREEN_HEIGHT*29/622));
        //Image
        Image tictactoe = Image("src/SDL_material/Tic-Tac-Toe.png", (SCREEN_WIDTH * 271/789) , (SCREEN_HEIGHT*212/622), (SCREEN_WIDTH * 237/789), (SCREEN_HEIGHT*32/622));
        Image tictactoe1 = Image("src/SDL_material/Tic-Tac-Toe1.png", (SCREEN_WIDTH * 271/789) , (SCREEN_HEIGHT*212/622), (SCREEN_WIDTH * 237/789), (SCREEN_HEIGHT*32/622));
        //Create renderer for window
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else
        {
            //Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            } else {
                // Render first interface
                drawFirstInterface(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, pvE, pvP, tictactoe);
                //Update the surface
                SDL_RenderPresent(renderer);

            }
            
            //Hack to get window to stay up
            SDL_Event e;  bool quit = false; 
            int cell,rc;
            while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ){quit = true;}else{
                // Handle button click
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    if((pvE.handleClicked(e)||pvP.handleClicked(e))&&current_interface == FIRST_INTERFACE) {
                        // Render second interface
                        drawSecondInterface(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, map3, map5, map7, map9, map11, map13,back, tictactoe1);
                        //Update the surface
                        SDL_RenderPresent(renderer);
                        continue;
                    }
                    if (map3.handleClicked(e))
                    {
                        cell = 9;
                        rc = 3;
                        renderThird = true;
                    }
                    if (map5.handleClicked(e))
                    {
                        cell = 25;
                        rc = 5;
                        renderThird = true;
                    }
                    if (map7.handleClicked(e))
                    {
                        cell = 49;
                        rc = 7;
                        renderThird = true;
                    }
                    if (map9.handleClicked(e))
                    {
                        cell = 81;
                        rc = 9;
                        renderThird = true;
                    }
                    if (map11.handleClicked(e))
                    {
                        cell = 121;
                        rc = 11;
                        renderThird = true;
                    }
                    if (map13.handleClicked(e))
                    {
                        cell = 169;
                        rc = 13;
                        renderThird = true;
                    }
                    // Render third interface
                    if (renderThird && current_interface == SECOND_INTERFACE)
                    {
                        Game game = Game(rc);
                        Board board = Board(rc, SCREEN_WIDTH, SCREEN_HEIGHT);
                        PlayerX player_x;
                        PlayerO player_o;
                        drawThirdInterface(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, cell, rc, board, back1);
                        //Update the surface
                        SDL_RenderPresent(renderer);
                        gameRun(game, board, player_x, player_o, renderer);
                        
                    }
                    
                    
                }
            } } }
        }
    }
    //Wait two seconds
    SDL_Delay( 2000 );
   //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}