#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

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

void connectNodes(int width, int height, struct node *realBoard, struct node *playingBoard) {
	bool top;
	bool left;
	bool right;
	bool bottom;

	for (int i = 0; i < width * height; i ++) {
		realBoard[i].top = NULL;
		playingBoard[i].top = NULL;
		realBoard[i].left = NULL;
		playingBoard[i].left = NULL;
		realBoard[i].right = NULL;
		playingBoard[i].right = NULL;
		realBoard[i].bottom = NULL;
		playingBoard[i].bottom = NULL;
		realBoard[i].topLeft = NULL;
		playingBoard[i].topLeft = NULL;
		realBoard[i].topRight = NULL;
		playingBoard[i].topRight = NULL;
		realBoard[i].bottomLeft = NULL;
		playingBoard[i].bottomLeft = NULL;
		realBoard[i].bottomRight = NULL;
		playingBoard[i].bottomRight = NULL;
	}

	for (int i = 0; i < width * height; i ++) {
		top = true;
		left = true;
		bottom = true;
		right = true;
		
		if (i < width) {
			top = false;
		}
		if (i % width == 0) {
			left = false;
		}
		if (i >= width * height - width) {
			bottom = false;
		}
		if (i % width == width - 1) {
			right = false;
		}

		if (top) {
			realBoard[i].top = &(realBoard[i - width]);
			playingBoard[i].top = &(playingBoard[i - width]);
		}
		if (left) {
			realBoard[i].left = &(realBoard[i - 1]);
			playingBoard[i].left = &(playingBoard[i - 1]);
		}
		if (right) {
			realBoard[i].right = &(realBoard[i + 1]);
			playingBoard[i].right = &(playingBoard[i + 1]);
		}
		if (bottom) {
			realBoard[i].bottom = &(realBoard[i + width]);
			playingBoard[i].bottom = &(playingBoard[i + width]);
		}
		if (top && left) {
			realBoard[i].topLeft = &(realBoard[i - width - 1]);
			playingBoard[i].topLeft = &(playingBoard[i - width - 1]);
		}
		if (top && right) {
			realBoard[i].topRight = &(realBoard[i - width + 1]);
			playingBoard[i].topRight = &(playingBoard[i - width + 1]);
		}
		if (bottom && left) {
			realBoard[i].bottomLeft = &(realBoard[i + width - 1]);
			playingBoard[i].bottomLeft = &(playingBoard[i + width - 1]);
		}
		if (bottom && right) {
			realBoard[i].bottomRight = &(realBoard[i + width + 1]);
			playingBoard[i].bottomRight = &(playingBoard[i + width + 1]);
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

char surroundingBombs(int x, int y, int width, struct node *realBoard) {
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

	return surrounding + '0';
}

void move(int x, int y, int width, int *cleared, struct node *realBoard, struct node *playingBoard) {
	if (playingBoard[x + y * width].val == 'U') {
		playingBoard[x + y * width].val = surroundingBombs(x, y, width, realBoard);
		(*cleared) ++;

		if (playingBoard[x + y * width].val == '0') {
			if (playingBoard[x + y * width].top) {
				move(x, y - 1, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].topLeft) {
				move(x - 1, y - 1, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].topRight) {
				move(x + 1, y - 1, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].left) {
				move(x - 1, y, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].right) {
				move(x + 1, y, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].bottom) {
				move(x, y + 1, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].bottomLeft) {
				move(x - 1, y + 1, width, cleared, realBoard, playingBoard);
			}
			if (playingBoard[x + y * width].bottomRight) {
				move(x + 1, y + 1, width, cleared, realBoard, playingBoard);
			}
		}
	}
}

int main() {
	int width = 0;
	int height = 0;

	while (width < 1 || height < 1 || width * height == 1) {
		printf("Enter the dimensions of the board. The board must be larger than 1 block.\n");
		printf("How many squares wide should the board be?\n");
		scanf("%d", &width);
		printf("How many squares tall should the board be?\n");
		scanf("%d", &height);
		printf("\n");
	}

	int totalBlocks = width * height;
	int maxBombs = 1 > ((width - 1) * (height - 1)) ? 1 : ((width - 1) * (height - 1));
	srand(time(NULL));
	int bombs = rand() % maxBombs + 1;

	struct node playingBoard[totalBlocks]; // Starts with all unflipped
	struct node realBoard[totalBlocks]; // Starts with all clear

	setup(width, height, realBoard, playingBoard);
	placeBombs(width, height, bombs, realBoard);
	connectNodes(width, height, realBoard, playingBoard);
	
	int state = 0; // 0 = playing, 1 = won, 2 = lost
	int totalClear = width * height - bombs;
	int cleared = 0;
	int x;
	int y;
	int flag; // true places/removes a flag, false clears the block

	while (state == 0) {
		printBoard(width, height, playingBoard);
		bool set = false;

		while (set == false) {
			printf("Where would you like to move? (x, y): ");
			scanf("%d, %d", &x, &y);

			if (x < width && y < height && x >= 0 && y >= 0 && (playingBoard[x + y * width].val == 'U' || playingBoard[x + y * width].val == 'F')) {
				set = true;
			}
		}

		printf("Would you like to place/remove a flag? (0 for no, 1 for yes): ");
		scanf("%d", &flag);

		if (flag) {
			if (playingBoard[x + y * width].val == 'U') {
				playingBoard[x + y * width].val = 'F';
			}
			else {
				playingBoard[x + y * width].val = 'U';
			}
		}
		else if (realBoard[x + y * width].val == 'B') {
			playingBoard[x + y * width].val = 'B';
			state = 2;
		}
		else {
			move(x, y, width, &cleared, realBoard, playingBoard);
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
