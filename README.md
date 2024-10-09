# Tic-tac-toe
The basic Tic-tac-toe game with SDL2 and C++ but at the moment there are many unfinished features.
# Note and issues
- Only **PvP function** active. PvE function will be developed soon.
- There is **no algorithms** for 3x3 map now, you can't play at this map.
- The back button not working right now.
- The function for reponsive screen only active on Window operating system. So when you use another operating system please change variable **SCREEN_WIDTH** and **SCREEN_HEIGHT**.
- Config of this folder give you able to run without **Makefile** so when you change something in code just save then run main.cpp
- Some algorithms in this project just run without optimized, change it if you can :>>
# Dependencies
You need **SDL2**, **SDL_image**, **SDL_ttf** library to compile this program. In window everything will setup for you but in another operating system please install and set path for those librarys
# Usage
- In Window run main.cpp on project source
- If another operating system
  ```
  $make
  $./main
  ```
