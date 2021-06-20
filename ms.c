// TODO: Add flag system
// TODO: Add clearing multiple blocks at once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN(ARR) (sizeof(ARR) / sizeof(ARR[0]))

struct node {
	char val;
	struct node *topLeft;
	struct node *top;
	struct node *topRight;
	struct node *left;
	struct node *right;
	struct node *bottomLeft;
	struct node *bottom;
	struct node *bottomRight;
};

void setup(int width, int height, struct node *realBoard, struct node *playingBoard) {
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < height; j ++) {
			realBoard[i + j * width].val = 'C';
			playingBoard[i + j * width].val = 'U';
		}
	}
}

void placeBombs(int width, int height, int bombs, struct node *realBoard) {
	for (int i = 0; i < bombs; i ++) {
		bool placedBomb = false;
		while (!placedBomb) {
			int x = rand() % width;
			int y = rand() % height;
			if (realBoard[x + y * width].val == 'C') {
				realBoard[x + y * width].val = 'B';
				placedBomb = true;
			}
		}
	}
}

void connectNodes(int width, int height, struct node *realBoard) {
	bool topNull;
	bool leftNull;
	bool rightNull;
	bool bottomNull;

	for (int i = 0; i < width * height; i ++) {
		topNull = false;
		leftNull = false;
		bottomNull = false;
		rightNull = false;
		
		if (i < width) {
			topNull = true;
		}
		if (i % width == 0) {
			leftNull = true;
		}
		if (i >= width * height - width) {
			bottomNull = true;
		}
		if (i % width == width - 1) {
			rightNull = true;
		}

		if (!topNull) {
			realBoard[i].top = &(realBoard[i - width]);
		}
		else {
			realBoard[i].top = NULL;
		}
		if (!leftNull) {
			realBoard[i].left = &(realBoard[i - 1]);
		}
		else {
			realBoard[i].left = NULL;
		}
		if (!rightNull) {
			realBoard[i].right = &(realBoard[i + 1]);
		}
		else {
			realBoard[i].right = NULL;
		}
		if (!bottomNull) {
			realBoard[i].bottom = &(realBoard[i + width]);
		}
		else {
			realBoard[i].bottom = NULL;
		}
		if (!topNull && !leftNull) {
			realBoard[i].topLeft = &(realBoard[i - width - 1]);
		}
		else {
			realBoard[i].topLeft = NULL;
		}
		if (!topNull && !rightNull) {
			realBoard[i].topRight = &(realBoard[i - width + 1]);
		}
		else {
			realBoard[i].topRight = NULL;
		}
		if (!bottomNull && !leftNull) {
			realBoard[i].bottomLeft = &(realBoard[i + width - 1]);
		}
		else {
			realBoard[i].bottomLeft = NULL;
		}
		if (!bottomNull && !rightNull) {
			realBoard[i].bottomRight = &(realBoard[i + width + 1]);
		}
		else {
			realBoard[i].bottomRight = NULL;
		}
	}
}

void printBoard (int width, int height, struct node *playingBoard) {
	for (int j = 0; j < height; j ++) {
		for (int i = 0; i < width; i ++) {
			printf("%c ", playingBoard[i + j * width].val);
		}
		printf("\n");
	}
	printf("\n");
}

int surroundingBombs(int x, int y, int width, struct node *realBoard) {
	int surrounding = 0;
	struct node selected = realBoard[x + y * width];

	if (selected.topLeft && selected.topLeft->val == 'B') {
		surrounding ++;
	}
	if (selected.top && selected.top->val == 'B') {
		surrounding ++;
	}
	if (selected.topRight && selected.topRight->val == 'B') {
		surrounding ++;
	}
	if (selected.left && selected.left->val == 'B') {
		surrounding ++;
	}
	if (selected.right && selected.right->val == 'B') {
		surrounding ++;
	}
	if (selected.bottomLeft && selected.bottomLeft->val == 'B') {
		surrounding ++;
	}
	if (selected.bottom && selected.bottom->val == 'B') {
		surrounding ++;
	}
	if (selected.bottomRight && selected.bottomRight->val == 'B') {
		surrounding ++;
	}

	return surrounding;
}

void play(int width, int height, int bombs, struct node *realBoard, struct node *playingBoard) {
	int state = 0; // 0 = playing, 1 = won, 2 = lost
	int totalClear = width * height - bombs;
	int cleared = 0;
	int x;
	int y;

	while (state == 0) {
		printBoard(width, height, playingBoard);
		bool set = false;

		while (set == false) {
			printf("Where would you like to move? (x, y): ");
			scanf("%d, %d", &x, &y);

			if (x < width && y < height && x >= 0 && y >= 0 && playingBoard[x + y * width].val == 'U') {
				set = true;
			}
		}

		if (realBoard[x + y * width].val == 'B') {
			playingBoard[x + y * width].val = 'B';
			state = 2;
		}
		else {
			playingBoard[x + y * width].val = '0' + surroundingBombs(x, y, width, realBoard);
			cleared ++;
		}

		if (cleared == totalClear) {
			state = 1;
		}
	}

	printBoard(width, height, playingBoard);
	printBoard(width, height, realBoard);
	if (state == 1) {
		printf("YOU WON!\n");
	}
	else {
		printf("YOU LOST!\n");
	}
}

int main() {
    int width;
    int height;
    printf("How many squares wide should the board be?\n");
    scanf("%d", &width);
    printf("How many squares tall should the board be?\n");
    scanf("%d", &height);

	int totalBlocks = width * height;
    int maxBombs = 1 > ((width - 1) * (height - 1)) ? 1 : ((width - 1) * (height - 1));
    srand(time(NULL));
    int bombs = rand() % maxBombs + 1;

    struct node playingBoard[totalBlocks]; // Starts with all unflipped
	struct node realBoard[totalBlocks]; // Starts with all clear

	setup(width, height, realBoard, playingBoard);
	placeBombs(width, height, bombs, realBoard);
	connectNodes(width, height, realBoard);
	play(width, height, bombs, realBoard, playingBoard);
}