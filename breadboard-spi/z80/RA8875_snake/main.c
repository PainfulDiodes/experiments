// snake
// classic snake game for BeanZee over VT100 terminal
// built with z88dk
// tested on BeanBoard v1, BeanZee v1 and Marvin v1.2.1-beanzee / v1.2.1-beanboard

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ra8875.h"
#include "../libc/marvin.h"

// function prototypes
void splash(void);
void splashDot(int,int);
bool splashBox(int,int,int,int);
void delay(unsigned long);
void setCell(int,int,char);
void drawSnake(void);
void setupGame(void);
void dropFruit(void);
bool isWithinSnake(int,int);
void printScore(void);
void gameLoop(void);
void move(void);
void gameOver(void);
void clearScreen(void);
void setCursor(int,int);
void setCursorHome(void);
void hideCursor(void);
void showCursor(void);
void tft_print(char*);
void drawFrame(void);

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define X_MAX_CELL 80
#define Y_MAX_CELL 23
#define X_START_CELL 40
#define Y_START_CELL 12

#define LEFT_KEY 'z'
#define RIGHT_KEY 'x'

// snake is held in 2 arrays for coordinates. First element is the head of the snake. 
#define MAX_LENGTH 100
int x_cell_pos[MAX_LENGTH+1];
int y_cell_pos[MAX_LENGTH+1];

bool alive;
int seed,length,score,motion,fruit_x,fruit_y;

#define MOTION_NONE  0
#define MOTION_UP    1
#define MOTION_DOWN  2
#define MOTION_LEFT  3
#define MOTION_RIGHT 4

int main()
{
  tft_setup();
  
  char k;
  clearScreen();
  hideCursor();
  splash();

  while(true) {
        setupGame();
        while(alive) gameLoop();
        gameOver();
        while(true) {
            k=marvin_readchar();
            if(k=='q') {
                clearScreen();
                showCursor();
                setCursorHome();
                return;
            }
            if(k=='p') {
                break;
            }
        }
    }

}

void gameOver() {
    clearScreen();
    drawSnake();
    printScore();
    setCursor(20,10);
    tft_print("Game Over");
    setCursor(20,12);
    tft_print("Press q to quit");
    setCursor(20,13);
    tft_print("or p to play again");
}

void splash() {
    printf("\nSnake!\n");
    printf("z=left x=right\n");
    seed=0;
    setCursor(35,13);
    tft_print("Snake!");
    setCursor(28,16);
    tft_print("Press any key to start");
    setCursor(28,18);
    tft_print("z and x to change direction");
    setCursorHome();
    for(int r=0; r<12; r++) {
        if(splashBox(1+r,SCREEN_WIDTH-r,1+r,SCREEN_HEIGHT-r)) break;
    }
    setCursor(35,13);
    tft_print("Snake!");
    srand(seed);
}

bool splashBox(int x1, int x2, int y1, int y2) {
    for(int x=x1; x<=x2; x++) {
        splashDot(x,y1); 
        if(marvin_readchar()!=0) return true;
    }
    for(int y=y1; y<=y2; y++) {
        splashDot(x2,y);
        if(marvin_readchar()!=0) return true;
    }
    for(int x=x2; x>=x1; x--) {
        splashDot(x,y2);
        if(marvin_readchar()!=0) return true;
    }
    for(int y=y2; y>=y1; y--) {
        splashDot(x1,y);
        if(marvin_readchar()!=0) return true;
    }
    return false;
}

void drawFrame() {
    for(int y=0; y<=SCREEN_HEIGHT-1; y++) setCell(SCREEN_WIDTH,y,'|');
    for(int x=SCREEN_WIDTH; x>=0; x--) setCell(x,SCREEN_HEIGHT-1,'-');
}

void splashDot(int x, int y) {
    setCell(x,y,'*');
    delay(3);
    seed++;
}

void setupGame() {
    score = 0;
    length = 5;
    motion = MOTION_RIGHT;
    alive = true;
    
    for(int i=0; i<=length; i++) // use <= as the position after the length is used to clean up the prior position of the snake
    {
      x_cell_pos[i] = X_START_CELL-i;
      y_cell_pos[i] = Y_START_CELL;
    }
    
    clearScreen();    
    drawFrame();
    drawSnake();
    dropFruit();
    printScore();
}

void gameLoop() {

    unsigned int k = marvin_readchar();
    if(k!=0)
    {     
      switch (motion) {
        case MOTION_LEFT:
          if(k==LEFT_KEY) motion=MOTION_DOWN;
          else if(k==RIGHT_KEY) motion=MOTION_UP;
          break;
        case MOTION_RIGHT:
          if(k==LEFT_KEY) motion=MOTION_UP;
          else if(k==RIGHT_KEY) motion=MOTION_DOWN;
          break;
        case MOTION_UP:
          if(k==LEFT_KEY) motion=MOTION_LEFT;
          else if(k==RIGHT_KEY) motion=MOTION_RIGHT;
          break;
        case MOTION_DOWN:
          if(k==LEFT_KEY) motion=MOTION_RIGHT;
          else if(k==RIGHT_KEY) motion=MOTION_LEFT;
          break;
        default:
          break;
      }  
    }
  
    if(alive) {
        delay(1000);
        move();
    }  
}

  void move() {
    if(motion == MOTION_NONE) return;

    int new_x = x_cell_pos[0];
    int new_y = y_cell_pos[0];
  
    switch (motion) {
      case MOTION_LEFT:
       new_x--;
        break;
      case MOTION_RIGHT:
        new_x++;
        break;
      case MOTION_UP:
        new_y--;
        break;
      case MOTION_DOWN:
        new_y++;
        break;
      default:
        break;
    }
  
    // check for crossed snake or boundary collision
    if(isWithinSnake(new_x, new_y) || new_x < 0 || new_x > X_MAX_CELL-1 || new_y < 0 || new_y > Y_MAX_CELL-1)
    { // crashed
      motion = MOTION_NONE;
      alive = false;
      drawSnake();
      return;
    }
  
      // stack push
    for(int i = length; i > 0; i--) {
      x_cell_pos[i] = x_cell_pos[i-1];
      y_cell_pos[i] = y_cell_pos[i-1];
    }
  
    // add new position to top
    x_cell_pos[0] = new_x;
    y_cell_pos[0] = new_y;
  
    // eaten fruit?
    if(new_x==fruit_x && new_y==fruit_y) {
      length++;
      printScore();
      score++;
      printScore();
      dropFruit();
    }
  
    drawSnake();
  
}

void setCell(int x, int y, char c) {
    setCursor(x,y);
    tft_putchar(c);
}

void drawSnake() {
    int c = 1;
    for(int i=0; i<length; i++) {
        if(i==0) setCell(x_cell_pos[i],y_cell_pos[i], alive ? '#' : '&');         //head
        else if(c==1) setCell(x_cell_pos[i],y_cell_pos[i], alive ? '*' : '.');    //stripe
        else setCell(x_cell_pos[i],y_cell_pos[i],alive ? '*' : '.');              //alt-stripe
        c=-c;
    }
    setCell(x_cell_pos[length],y_cell_pos[length],' ');  
}

void dropFruit() {
    while(true) {
      fruit_x = (rand() % (X_MAX_CELL-2))+2;
      fruit_y = (rand() % (Y_MAX_CELL-2))+2;
      if(!isWithinSnake(fruit_x, fruit_y)) {
        setCell(fruit_x,fruit_y,'+');
        return;
      }
    }
  }
  
bool isWithinSnake(int x, int y) {
    for(int i = 0; i < length; i++) {
        if(x == x_cell_pos[i] && y == y_cell_pos[i]) {
            return true;
        }
    }
    return false;
}

void printScore() {
    setCursor(35, 24);
    char buf[16];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    tft_print(buf);
}

void delay(unsigned long d) {
    for(unsigned long l=0; l<d; l++) {
        //
    }
}

void clearScreen() {
    tft_clear_screen();
    delay(1000);
}

void setCursor(int x, int y) {
    tft_cursor_x(x*8);
    tft_cursor_y(y*16);
}

void setCursorHome() {
    tft_cursor_x(0);
    tft_cursor_y(0);
}

void hideCursor() {
    tft_cursor_off();
}

void showCursor() {
    tft_cursor_on();
}

void tft_print(char* s) {
    while(*s) {
        tft_putchar(*s++);
    }
}
