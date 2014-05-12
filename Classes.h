#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "glut_window.h"
#include <math.h>   
#include <time.h>
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
            val = 0;
            r = 0;
            b = 0;
            g = 0;
        }
        Square(float x, float y){
            val = 0;
            centerX = x;
            centerY = y;
            r = 0;
            g = 0;
            b = 0;
        }
        Square(int v, float x, float y){
            val = v;
            centerX = x;
            centerY = y;
        }
        void draw(){
		if(val > 0){
            renderString();
            glColor3f(1,1,1);
            glBegin(GL_POLYGON);
            glVertex2d(centerX - 0.25, centerY + 0.25);
            glVertex2d(centerX + 0.25, centerY + 0.25);
            glVertex2d(centerX + 0.25, centerY - 0.25);
            glVertex2d(centerX - 0.25, centerY -0.25);
            glEnd();
		}
        }
        void renderString() {
            char buffer[256];
            sprintf(buffer,"%d", val);
            glColor3f(0, 1, 1); 
            glRasterPos2f(centerX, centerY);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(buffer));
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
        int getVal(){
            return val;
        }
        
        bool equals(Square s){
            return (this->val == s.getVal());
        }
	bool operator ==(Square &s){
		return (this->val == s.getVal());
	}
};

class Field{

    private:
    Square container[4][4];
    public:
    Field(){}
    void initialize(){
	// to initialize the field, add one randomly generated square.
   	srand(time(NULL));
	int x = rand()%4;
	int y = rand()%4;
	container[y][x] = Square(2,y*0.25,x*0.25);
	}
    bool createSquare () {
        srand(time(NULL));
   	return 0;
	}
    bool checkSquare(int i , int j){
        int v_i = i;
        int h_j = j;
        for(int k = 0; i < 4; i++){
            if(container[i][j] == (container[k][j]) && k != i){
                return true;
            }
            if(container[i][j] == (container[i][k]) && k != j){
                return true;
            }
        }
    }   
    bool checkMoveAvail(){
        bool anyMove = false;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(checkSquare(i,j)) {
                    anyMove = true;
                }
            }    
        }
        if (anyMove == false && createSquare() == false) {
            endGame();
        }
    }
    void endGame(){}
	void draw(){
		for(int i = 0; i < 4; i ++)
			for(int j = 0; j < 4; j++)
				container[i][j].draw();
	}
	void move(int input){
		switch(input){
		case UP:
		break;
		case RIGHT:
		break;
		case DOWN:
		break;
		case LEFT:
		break;

		}
	}  
};

