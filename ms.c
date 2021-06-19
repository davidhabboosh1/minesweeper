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
	
	for (int i = 0; i < LEN(realBoard); i ++) {
		if (i < width) {
			topNull = true;
		}
		if (i % width == 0) {
			leftNull = true;
		}
		if (i >= LEN(realBoard) - width) {
			bottomNull = true;
		}
		if (i % width == width - 1) {
			rightNull = true;
		}

		if (topNull) {
			realBoard[i].top = NULL;
		}
		else {
			realBoard[i].top = &(realBoard[i - width]);
		}
		if (leftNull) {
			realBoard[i].left = NULL;
		}
		else {
			realBoard[i].left = &(realBoard[i - 1]);
		}
		if (rightNull) {
			realBoard[i].right = NULL;
		}
		else {
			realBoard[i].right = &(realBoard[i + 1]);
		}
		if (bottomNull) {
			realBoard[i].bottom = NULL;
		}
		else {
			realBoard[i].bottom = &(realBoard[i + width]);
		}
		if (topNull && leftNull) {
			realBoard[i].topLeft = NULL;
		}
		else {
			realBoard[i].topLeft = &(realBoard[i - width - 1]);
		}
		if (topNull && rightNull) {
			realBoard[i].topRight = NULL;
		}
		else {
			realBoard[i].topRight = &(realBoard[i - width + 1]);
		}
		if (bottomNull && leftNull) {
			realBoard[i].bottomLeft = NULL;
		}
		else {
			realBoard[i].bottomLeft = &(realBoard[i + width - 1]);
		}
		if (bottomNull && rightNull) {
			realBoard[i].bottomRight = NULL;
		}
		else {
			realBoard[i].bottomRight = &(realBoard[i + width + 1]);
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

int surroundingBombs(int x, int y, struct node *playingBoard) {
	int surrounding = 0;
	struct node selected;
	
	if (selected.topLeft->val == 'B') {
		surrounding ++;
	}
	if (selected.top->val == 'B') {
		surrounding ++;
	}
	if (selected.topRight->val == 'B') {
		surrounding ++;
	}
	if (selected.left->val == 'B') {
		surrounding ++;
	}
	if (selected.right->val == 'B') {
		surrounding ++;
	}
	if (selected.bottomLeft->val == 'B') {
		surrounding ++;
	}
	if (selected.bottom->val == 'B') {
		surrounding ++;
	}
	if (selected.bottomRight->val == 'B') {
		surrounding ++;
	}

	return surrounding;
}

void play(int width, int height, int bombs, struct node *realBoard, struct node *playingBoard) {
	int state = 0; // 0 = playing, 1 = won, 2 = lost
	int totalClear = LEN(playingBoard) - bombs;

	printf("The length of the board is: %d", sizeof(playingBoard[0]));
	int cleared = 0;
	int x;
	int y;

	while (state == 0) {
		printBoard(width, height, playingBoard);
		bool set = false;
		
		while (set == false) {
			printf("Where would you like to move? (x, y): ");
			scanf("%d, %d", &x, &y);
			
			if (x < width && y < height) {
				set = true;
			}
		}

		if (realBoard[x + y * width].val == 'B') {
			playingBoard[x + y * height].val = 'B';
			state = 2;
		}
		else {
			playingBoard[x + y * height].val = '0' + surroundingBombs(x, y, playingBoard);
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