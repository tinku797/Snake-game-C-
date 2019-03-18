#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;
// Map size
const int height = 20;
const int width = 20;

int score = 0;

// Snake (x,y) coordinates
int snakeHeadX;
int snakeHeadY;

// Arrays for x and y coordinates of snake tail parts respectively
int tailX[40];
int tailY[40];

int tailLength = 0;

int prevX[40];
int prevY[40];

// Food (x,y) coordinates
int foodX;
int foodY;
bool gameOver;

enum edirection {STOP=0,LEFT=1,RIGHT=2,UP=3,DOWN=4};
edirection dir;

void drawBoard()
{  
     system("cls");
     // First wall
   for(int i=0;i<width+2;i++)
   {
           cout<<"#";
   }
   
   cout<<endl;
   
   
   
   for(int j=0;j<height;j++)
   {
           cout<<"#";
           
           for(int i=0;i<width;i++)
           {
                   if(i==snakeHeadX&&j==snakeHeadY)
                   {
                        cout<<"0";
                   
                   }
                   else if(i==foodX&&j==foodY)
                   {
                        cout<<"*";
                   }
                   else
                   {      bool print = false;
                          for(int k = 0;k<tailLength;k++)
                          {
                                  if(tailX[k] == i&&tailY[k]==j)
                                  {
                                             print = true;
                                              cout<<"o";
                                  }
                          }
                          if(!print)
                          {cout<<" ";} 
                   }
                         
           }
           
           cout<<"#"; 
           
           cout<<endl;     
   }
   // Last wall
   for(int i=0;i<width+2;i++)
   {
           cout<<"#";
   }    
   cout<<endl; 
      
   // Prints score
   cout<<"score: "<<score<<endl<<endl;
   
   // Prints controls
   cout<<"CONTROLS:-"<<endl;
   cout<<"W - move up"<<endl;
   cout<<"A - move left"<<endl;
   cout<<"D - move right"<<endl;
   cout<<"S - move down";
                 
}
// Detects collision with the wall 
void collision()
{
     if(snakeHeadX<0)
     {
             snakeHeadX = 19;
     }
     if(snakeHeadX>19)
     {
             snakeHeadX = 0;
     }
     if(snakeHeadY>19)
     {
             snakeHeadY = 0;
     }
     if(snakeHeadY<0)
     {
             snakeHeadY = 19;
     }
     // Detects if the snake ate itself
     else
     {
         for(int z = 0;z<tailLength;z++)
         {
                 if(snakeHeadX == tailX[z] && snakeHeadY == tailY[z])
                     {
                               gameOver = true;
                     }
         }     
     }
     
}     


// moves the snakeHead
void movement()
{    
     // Stores snakeHead coordinates in variables before snakeHead movement
     prevX[0] = snakeHeadX;
     prevY[0] = snakeHeadY;
     // Stores coordinates of all the parts of the snake from 2nd tail part i.e. overall 3rd part of the whole snake
     for(int i = 1;i<tailLength;i++)
     {
          prevX[i] = tailX[i-1];
          prevY[i] = tailY[i-1];  
     }
     
     
     if(_kbhit())
     {     // When a key is pressed the direction of snakeHead is changed
           switch(_getch())
           {
                   
                   case 'a':
                        dir = LEFT;
                        break;
                   case 'd':
                        dir = RIGHT;
                        break;
                   case 'w':
                        dir = UP;
                        break;
                   case 's':
                        dir = DOWN;
                        break;
                   default:
                        break;
                   
           }
     }
     // When direction is changed, snakeHead moves continously in that direction
     switch(dir)
     {
            case LEFT:
                 snakeHeadX--;
                 break;
            case RIGHT:
                 snakeHeadX++;
                 break;
            case UP:
                 snakeHeadY--;
                 break;
            case DOWN:
                 snakeHeadY++;
                 break;
            default:
                 break;
     }
     
     // Assigns the tail parts their new coordinates
     for(int i = 0;i<tailLength;i++)
     {
          tailX[i] = prevX[i];
          tailY[i] = prevY[i];   
     }
     
    
}

int main()
{   
    gameOver = false;
    dir = STOP;
    // Initial position of snakeHead
    snakeHeadX = width/2;
    snakeHeadY = height/2;
    
    // Randomly generates (x,y) coordinates of food
    foodX = rand() % width;
    foodY = rand() % height;
     
    
     
     
         // While loop to update game frames
        while(!gameOver)
        {  
            drawBoard();
            
            // If snake eats food generate food again and score variable increments by 10 points
            if(snakeHeadX==foodX&&snakeHeadY==foodY)
            {
                   score += 10;
                   tailLength++;
                   foodX = rand() % width;
                   foodY = rand() % height;                                      
            }       
            movement();
            collision();
            
            Sleep(30);
        }
  
  return 0;
}

