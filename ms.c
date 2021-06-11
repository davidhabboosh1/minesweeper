#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN(ARR) (sizeof(ARR) / sizeof(ARR[0]))

void setup() {
        int width;
        int height;
        printf("How many squares wide should the board be?\n");
        scanf("%d", &width);
        printf("How many squares tall should the board be?\n");
        scanf("%d", &height);

        int maxBombs = (width - 1) * (height - 1);
        srand(time(NULL));
        int bombs = rand() % maxBombs + 1;

        char realBoard[height][width]; // U=Unflipped, F=Flag, C=Clear, B=Bomb
        char playingBoard[height][width]; // Starts with all unflipped

        for (int i = 0; i < LEN(realBoard); i ++) {
                for (int j = 0; j < LEN(realBoard[0]); j ++) {
                        realBoard[i][j] = 'C';
                        playingBoard[i][j] = 'U';
                }
        }

	for (int i = 0; i < bombs; i ++) {
		bool placedBomb = false;
		while (!placedBomb) {
			int x = rand() % width;
			int y = rand() % height;
			if (realBoard[y][x] == 'C') {
				realBoard[y][x] = 'B';
				placedBomb = true;
			}
		}
	}

	for (int i = 0; i < LEN(realBoard); i ++) {
		for (int j = 0; j < LEN(realBoard[0]); j ++) {
			printf("%c ", realBoard[i][j]);
		}
		printf("\n");
	}
}


int main() {
	setup();
	return 0;
}
