#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


int isJumping = 0;  
int jumpHeight = 0;
int obstaclePosition = 70;
int score = 0;

void clearScreen() {
     printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

void drawAkshay() {
    printf("\033[%d;%dH", 10 - jumpHeight, 10); // Move cursor to dyno position
    printf("^   ^ ");
    printf("\033[%d;%dH", 11 - jumpHeight, 10);
    printf("  !");
    printf("\033[%d;%dH", 12 - jumpHeight, 10);
    printf("I___I");
    printf("\033[%d;%dH", 13 - jumpHeight, 10);
    printf("AKSHAY");
} 

void drawObstacle() {
    printf("\033[%d;%dH", 13, obstaclePosition); // Move cursor to obstacle position
    printf("CLASS");
}

void clearObstacle() {
    printf("\033[%d;%dH", 13, obstaclePosition); // Move cursor to obstacle position
    printf("    ");
}

int checkCollision() {
  return (obstaclePosition >= 10 && obstaclePosition <= 15 && jumpHeight == 0);
}

void updateGame() {
    if (isJumping) {
        jumpHeight++;
        if (jumpHeight >= 6) { // Slow down the akshay's descent
            isJumping = 0;
        }
    } else if (jumpHeight > 0) {
        jumpHeight--;
    } else {
        // Akshay is on the ground; allow jumping again
        if (_kbhit()) {
            char input = _getch();
            if (input == ' ') {
                isJumping = 1;
            }
        }
    }

    clearObstacle();
    obstaclePosition -= 2; // Make the obstacle move faster

    if (obstaclePosition <= 0) {
        obstaclePosition = 80; //  value based on terminal width
        score++;
    }

    if (checkCollision()) {
        restartGame();
    }
}

void restartGame() {
  clearScreen();
  printf("HE SKIPPED %d LECTURES DEFAULTER OP \n\n", score);
  printf("Press any key to restart...");
  _getch();

  // Reset game state
  isJumping = 0;
  jumpHeight = 0;
  obstaclePosition = 80;
  score = 0;
}

int main() {
    srand(time(NULL));

    while (1) {
        updateGame();
        clearScreen();
        drawAkshay();
        drawObstacle();

        printf("\nScore: %d", score);
        fflush(stdout);

        usleep(75000); // Sleep for 75,000 microseconds (0.075 second) for faster obstacle movement
        //nanosleep is now used as its deprecated due to precision and accuracy
    }

    return 0;
}
