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
   


// This code is a simple implementation of a game where a Akshay jumps over obstacles. The game runs in a loop, updating the game state, clearing the screen, drawing the Akshay and obstacle, and displaying the score. The game uses a sleep function to control the speed of the obstacles.

// Here's a breakdown of the code:

// 1 #include <stdio.h>: This line includes the standard input/output library, which is necessary for input and output operations in C.

// 2 #include <stdlib.h>: This line includes the standard library, which provides function  srand() and rand() for seeding the random number generator.

//3  #include <time.h>: This line includes the time library, which is used to seed the random number generator with the current time.

//4 #include <conio.h> It is a header file used in c and cpp and it includes inbuilt functions like getch(), clrscr() and _kbhit()

// 1. `srand(time(NULL));` - This line initializes the random number generator with the current time. This ensures that the random numbers generated will be different each time the program is run.

// 2. `while (1) { ... }` - This is the main game loop. The loop continues indefinitely until the program is terminated.

// 3. `updateGame();` - This function updates the game state, such as the Akshay's position and the obstacle's position.

// 4. `clearScreen();` - This function clears the screen, preparing it for the next frame of the game.

// 5. `drawAkshay();` - This function draws the Akshay on the screen.

// 6. `drawObstacle();` - This function draws the obstacle on the screen.

// 7. `printf("\nScore: %d", score);` - This line prints the current score to the screen.

// 8. `fflush(stdout);` - This line ensures that the output buffer is flushed, so the score is displayed immediately.

// 9. `usleep(75000);` - This line causes the program to sleep for 75,000 microseconds (0.075 seconds). This is used to control the speed of the obstacles. A smaller value would make the obstacles move faster, while a larger value would make them move slower.

// 10. clearObstacle() : This function clears the obstacle at the specified position.

// 11. checkCollision() : This function checks if the Akshay has collided with an obstacle.

// 12. restartGame() : This function is called when the player dies. It resets the game state to its initial values and then prints a message to the player asking them to press any key to restart.

//13. main() : This is the main game loop. It calls the updateGame() function to update the game state, and then clears the screen and draws the Akshay and the obstacle at their respective positions. Finally, it prints the score and sleeps for 75,000 microseconds before repeating the loop.

// In summary, this code is a simple implementation of a game where a Akshay jumps over Class. The game loop continuously updates the game state, clears the screen, draws the person and obstacle, and displays the score. The speed of the obstacles is controlled by the sleep function.


// 1. `fflush(stdout)`:

// - `fflush(stdout)` is a function used to flush the output buffer of the standard output stream (`stdout`).
// - When you write data to the `stdout` stream, it is typically stored in a buffer instead of being immediately written to the screen. This is because writing to the screen is a relatively slow operation, and buffering the data allows the program to write larger chunks of data at once, which can improve performance.
// - However, in some cases, it is important for the program to ensure that the data in the buffer is actually written to the screen before continuing. This is where `fflush(stdout)` comes in. When `fflush(stdout)` is called, it forces the `stdout` stream to write any buffered data to the screen immediately.
// - It's important to note that `fflush(stdout)` should only be used with output streams that are open for writing. Using `fflush` with an input stream or a stream that has been closed can result in undefined behavior.

// 2. `printf()`:

// - `printf()` is a function used to write formatted data to the standard output stream (`stdout`).
// - The `printf()` function takes a format string as its first argument, followed by a variable number of additional arguments. The format string specifies how the additional arguments should be formatted and written to the output stream.
// - Unlike `fflush(stdout)`, `printf()` does not automatically flush the output buffer. This means that the data written by `printf()` may not be immediately visible on the screen, even if the output buffer is full.
// - If you want to ensure that the data written by `printf()` is immediately visible on the screen, you can either call `fflush(stdout)` after calling `printf()`, or you can use the `'\n'` character in the format string to insert a newline character at the end of the output. This will cause the output buffer to be flushed automatically.


