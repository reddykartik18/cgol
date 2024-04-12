#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#define WIDTH 1800
#define HEIGHT 900
#define BLOCK 10
#define FPS 60

#define ROWS (HEIGHT/BLOCK)
#define COLS (WIDTH/BLOCK)
#define SIZE (ROWS * COLS)
#define N 8

typedef struct {
  unsigned char is_alive: 1;
  unsigned char neighbors: 4;
} Grid;

typedef struct {
  signed char x;
  signed char y;
} Point;

void update_neighbors(Grid grid[SIZE]) {
  Point neighbors[N] = {
    { -1, -1 },
    { 0, -1 },
    { 1, -1 },
    { -1, 0 },
    { 1, 0 },
    { -1, 1 },
    { 0, 1 },
    { 1, 1 }
  };
  for (size_t index = 0; index < SIZE; ++index) {
    grid[index].neighbors = 0;
  }
  Point point;
  Point pos;
  unsigned short index;
  for (size_t i = 0; i < SIZE; ++i) {
    if (grid[i].is_alive == 1) {
      point.x = (i % COLS);
      point.y = (i / COLS);
      for (size_t j = 0; j < N; ++j) {
        pos.x = (((point.x + neighbors[j].x) % COLS) + COLS) % COLS;
        pos.y = (((point.y + neighbors[j].y) % ROWS) + ROWS) % ROWS;
        index = (pos.y * COLS) + pos.x;
        grid[index].neighbors += 1;
      }
    }
  }
}

void gen(Grid grid[SIZE]) {
  for (size_t index = 0; index < SIZE; ++index) {
    switch (grid[index].is_alive) {
      case 1:
        if (!((grid[index].neighbors == 2) || (grid[index].neighbors == 3))) {
          grid[index].is_alive = 0;
        }
        break;
      case 0:
        if (grid[index].neighbors == 3) {
          grid[index].is_alive = 1;
        }
        break;
    }
  }
  update_neighbors(grid);
}

void load_file(
    const char *restrict filename,
    Grid grid[SIZE]
    ) {
  FILE *file;
  if ((file = fopen(filename, "r")) == NULL)
    exit(1);
  unsigned char ch; 
  char n;
  for (size_t index = 0; index < SIZE; ++index) {
    if ((((n = fscanf(file, " %c", &ch)) == EOF) && (n == 0)) || (n != 1)) {
      fclose(file);
      exit(1);
    }
    grid[index].is_alive = ch;
  }  
  update_neighbors(grid);
  fclose(file);
}

void print_grid(Grid grid[SIZE]) {
  //puts("Cells: ");
  for (size_t y = 0; y < ROWS; ++y) {
    for (size_t x = 0; x < COLS; ++x) {
      printf("%d", grid[y*COLS + x].is_alive);
    }
    printf("\n");
  }
  //printf("\033[%dA", ROWS);
  //printf("\033[%dD", COLS);
  //puts("");
  ////puts("Neighbors: ");
  //for (size_t y = 0; y < ROWS; ++y) {
  //   for (size_t x = 0; x < COLS; ++x) {
  //     printf("%d", grid[y*COLS + x].neighbors);
  //   }
  //   printf("\n");
  // }
  printf("\033[%dA", ROWS);
  printf("\033[%dD", COLS);
}

#endif
