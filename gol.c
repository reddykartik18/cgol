#include <stdlib.h>
//#include <unistd.h>
#include "raylib.h"
#include "gol.h"

int main(void) {
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(WIDTH, HEIGHT, "Conway\'s Game of Life");
  SetTargetFPS(FPS);
  Grid *grid = (Grid *)calloc(SIZE, sizeof(Grid));
  if (grid == NULL)
    return 1;
  load_file("grid.txt", grid);
  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);
      unsigned char x, y;
      for (size_t index = 0; index < SIZE; ++index) {
        x = (index % COLS);
        y = (index / COLS);
        DrawRectangle(x*BLOCK, y*BLOCK, BLOCK, BLOCK, grid[index].is_alive ? WHITE : BLACK);
      }
      for (size_t y = 1; y < ROWS; ++y) {
        DrawLine(0, y*BLOCK, WIDTH, y*BLOCK, GRAY);
      }

      for (size_t x = 1; x < COLS; ++x) {
        DrawLine(x*BLOCK, 0, x*BLOCK, HEIGHT, GRAY);
      }

    EndDrawing();
    gen(grid);
    //sleep(1);
  }
  CloseWindow(); 
  return 0;
}



