#include <GL/glut.h>
#include <GL/gl.h>
#include "game.h"
#include <ctime>
#include <stdio.h>
#include<stdlib.h>
#include <iostream>
int gridX, gridY;

int snake_length = 5;

bool food = true;

int foodX, foodY;

int posx[60] = { 20, 20, 20, 20, 20 }, posy[60] = { 20, 20, 20, 20, 20 };

short sDirection = RIGHT;

extern bool GameOver;

extern int score;

extern int skin;

void initGrid(int x, int y) {
	gridX = x;
	gridY = y;
}
void unit(int, int);
void drawGrid() {
	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++)
			unit(x, y);
	}
}

void unit(int x, int y) {
	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
		glLineWidth(1.0);
		glColor3f(1.0, 0.0, 0.0);
	} else {
		glLineWidth(1.0);
		glColor3f(1.0, 1.0, 1.0);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();

}

void drawFood() {
	glColor3f(1.0, 1.0, 0.0);
	if (food) {
		random(foodX, foodY);
	}
	food = false;
	glRectd(foodX, foodY, foodX + 1, foodY + 1);
}

void drawSnake() {
	for (int i = snake_length - 1; i > 0; i--) {
		posx[i] = posx[i - 1];
		posy[i] = posy[i - 1];
	}

	if (sDirection == UP)
		posy[0]++;
	else if (sDirection == DOWN)
		posy[0]--;
	else if (sDirection == RIGHT)
		posx[0]++;
	else if (sDirection == LEFT)
		posx[0]--;
	for (int i = 0; i < snake_length; i++) {
		if (skin == 0) {
			if (i == 0)
				glColor3f(1.0, 0.0, 1.0);
			else
				glColor3f(0.0, 1.0, 0.0);
		}
		if (skin == 1) {
			if (i == 0)
				glColor3f(1.0, 0.0, 0.0);
			else
				glColor3f(0.0, 0.0, 1.0);
		}
		if (skin == 2) {
			if (i == 0)
				glColor3f(0.0, 1.0, 1.0);
			else
				glColor3f(1.0, 0.0, 0.0);
		}

		glRectd(posx[i], posy[i], posx[i] + 1, posy[i] + 1);
	}

	if (posx[0] == 0 || posy[0] == 0 || posx[0] == gridX + 1
			|| posy[0] == gridY + 1) {
		GameOver = true;
	}

	if (posx[0] == foodX && posy[0] == foodY) {
		score++;
		snake_length++;
		food = true;
	}

	for (int i = snake_length - 1; i > 0; i--)
		if (posx[0] == posx[i] && posy[0] == posy[i]) {
			GameOver = true;
		}

}

void random(int &x, int &y) {
	int _maxX = gridX - 2, _min = 1, _maxY = gridY - 2;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);

}
