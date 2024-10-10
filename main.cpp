#include <GL/gl.h>
#include<GL/glut.h>
#include "game.h"
#include <stdio.h>
#include<iostream>

#define COLUMNS 40
#define ROWS 40

int FPS = 10;

int skin = 0;

extern short sDirection;

extern int snake_length;

bool GameOver = false;

void time_callback(int);

void display_callback();

void keyboard_callback(int, int, int);

void drawStrings(const char*, float, float, void*);

void display();

void mouse_callback(int, int, int, int);

void mouse_exit(int, int, int, int);

int score = 0;


struct testing{
	int ok = 9;

	int ok1=1;

	int test = 0;

	int test1 = 0;
}m;


void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMNS, ROWS);
}

int i = 0;

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake");
	glutDisplayFunc(display);
	glutMouseFunc(mouse_callback);

	glutMainLoop();

	skin = 0;
	return 0;
}

void drawStrings(const char *str, float x, float y, void *font) {
	glRasterPos2f(x, y);
	while (*str) {
		glutBitmapCharacter(font, *str);
		str++;
	}
}

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	if (GameOver) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.0, 0.0);
		drawStrings("Game Over", 15.0, 25.0, GLUT_BITMAP_TIMES_ROMAN_24);
		char scoreStr[60];
		sprintf(scoreStr, "Score: %d", score);
		drawStrings(scoreStr, 16.0, 20.0, GLUT_BITMAP_TIMES_ROMAN_24);
		glPopMatrix();
		glutMouseFunc(mouse_exit);
		FPS = 10;
		m.ok = 9;
		if(m.ok1==1)
		{
		FILE *f;
		FILE *fs;
		f = fopen("Logs.txt", "a");
		fs = fopen("LogNum.txt", "r");
		fscanf(fs, "%d", &i);
		fprintf(f, "LOGS %d\nSkin: %d\nScor: %d\nLungime: %d\n\n", i++, skin, score,
				snake_length);
		fclose(fs);
		fs = fopen("LogNum.txt", "w");
		fprintf(fs, "%d", i);
		fclose(fs);
		fclose(f);}
		m.ok1=0;
	}
	if (score >= MAX) {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 0.0);
		drawStrings("You WON!", 15.0, 25.0, GLUT_BITMAP_TIMES_ROMAN_24);
		glPopMatrix();
		glutMouseFunc(mouse_exit);
		FPS = 10;
		m.ok = 9;

	}
	glutSwapBuffers();
}

void time_callback(int) {
	glutPostRedisplay();
	if (score > m.ok && score % 10 == 0) {
		FPS += 2;
		m.ok += 10;
	}
	glutTimerFunc(1000 / FPS, time_callback, 0);
}

void keyboard_callback(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP:
		if (sDirection != DOWN)
			sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP)
			sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT)
			sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT)
			sDirection = LEFT;
		break;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	drawStrings("Snake", -0.1, 0.5, font);
	drawStrings("Click to start", -0.2, 0.3, font);
	drawStrings("BattlePass", -0.2, -0.6, font);
	glutSwapBuffers();
}

void mouse_callback(int button, int state, int x, int y) {

	if (state == GLUT_DOWN && (x >= 100 && x <= 400) && (y >= 1 && y <= 200)) {
		glViewport(0, 0, 500, 500);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glutDisplayFunc(display_callback);
		glutSpecialFunc(keyboard_callback);

		init();

		glutTimerFunc(0, time_callback, 0);
	}

	if (state == GLUT_DOWN && (x >= 200 && x <= 400)
			&& (y >= 300 && y <= 400)) {
		if (m.test1 == 0) {
			m.test = 1;
			m.test1 = 1;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 0.0);
		void *font = GLUT_BITMAP_TIMES_ROMAN_24;
		drawStrings("Start Game", -0.2, 0.6, font);

		printf("%d %d\n", x, y);

		drawStrings("Skin 1", -0.1, -0.3, font);
		drawStrings("Skin 2", -0.1, -0.6, font);
		if (m.test == 0) {
			if (state == GLUT_DOWN && (x >= 100 && x <= 400)) {
				if (y >= 150 && y <= 350)
					skin = 1;
				if (y >= 360 && y <= 500)
					skin = 2;
			}
		} else {
			m.test = 0;
		}

		printf("%d %d\n", x, y);

		printf("%d\n", skin);

		glutSwapBuffers();
	}

}

void mouse_exit(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		exit(0);
}
