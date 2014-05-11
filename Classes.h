#include <iostream>
#include <algorithm>
#include <vector>
#include "glut_window.h"
#include <math.h>
#include "Movement.h"
using namespace std;

class Square{
	private:
		int val;
		float centerX;
		float centerY;
		float r;
		float g;
		float b;
	public:
		Square(){
			val = 2;
			r = .5;
			b = .5;
			g = .5;
		}
		Square(float x, float y){
			centerX = x;
			centerY = y;
		}
		void draw(){
			glColor3f(1,1,1);
			glBegin(GL_POLYGON);
			glVertex2d(centerX - 0.25, centerY + 0.25);
			glVertex2d(centerX + 0.25, centerY + 0.25);
			glVertex2d(centerX + 0.25, centerY - 0.25);
			glVertex2d(centerX - 0.25, centerY -0.25);
			glEnd();
		}
		void move(int m){
			switch (m){
			case UP:
			centerY = 0.75;
			break;
			case DOWN:
			centerY = -0.75;
			break;
			case LEFT:
			centerX = -0.75;
			break;
			case RIGHT:
			centerX = 0.75;
			break;
			}
		}
};
class Field{
	private:
	Square container[4][4];		
	public:
	Field(){}
};
