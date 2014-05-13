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
	float size;
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
        Square(float x, float y, float size){
            val = 0;
            centerX = x;
            centerY = y;
		this -> size = size;
            r = 0;
            g = 0;
            b = 0;
        }
        void draw(){
		if(val > 0){
            renderString();
            glColor3f(1,1,1);
            glBegin(GL_POLYGON);
		float offset = (size/2 - 0.04*size/2);
            glVertex2d(centerX - offset, centerY + offset);
            glVertex2d(centerX + offset, centerY + offset);
            glVertex2d(centerX + offset, centerY - offset);
            glVertex2d(centerX - offset, centerY - offset);
            glEnd();
		}
        }
        void renderString() {
            char buffer[256];
            sprintf(buffer,"%d", val);
            glColor3f(0, 0, 0); 
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
        void setVal(int val){
		this->val = val;
	}
        bool equals(Square s){
            return (this->val == s.getVal());
        }
	bool operator ==(Square &s){
		return (this->val == s.getVal());
	}
	void print(){
		cout << "X: " << centerX << " Y: " << centerY << endl;
	}
};

class Field{

    private:
	int size;
    	vector<vector<Square*> > container;
    public:
	Field(){
		size = 0;
		container.clear();
	}
	Field(int n){
		size = n;
	}
	void initialize(){
		for(int i = 0; i < size; i++){
			vector<Square*> temp;
			container.push_back(temp);
			for(int j = 0; j < size; j++){
				container[i].push_back(new Square(-1.+1./size + 2./size*j, 
				1. - 1./size - 2./size*i, 2./size));
			}	
		}
		cout << "SDLFJKSDLFJ " << endl;
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				container[i][j] -> print();
		createSquare();	
	}
     bool createSquare () {
        int number = 0;
        //Checks for an empty square
        bool empty = false;
	srand(time(NULL));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (container[i][j] -> getVal() == 0) {
                    empty = true;    
                }
            }
        }
        //Gets a random number, either 2 or size
        if (empty == true) {
            while (number != 2 && number != size) {
                number = (rand() % 3) + 2;
            }
            
            //Sets the value to a random square
            while (empty == true) {
                int a = (rand() % size);
                int b = (rand() % size);
                if (container[a][b] -> getVal() == 0) { //makes sure the spot is empty
                    container[a][b] -> setVal(number);
		return true;
                }
            }
        }
        return false;
    }
    bool checkSquare(int i , int j){
        int v_i = i;
        int h_j = j;
        for(int k = 0; i < size; i++){
            if(*(container[i][j]) == *(container[k][j]) && k != i){
                return true;
            }
            if(*(container[i][j]) == *(container[i][k]) && k != j){
                return true;
            }
        }
    }   
    bool checkMoveAvail(){
        bool anyMove = false;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
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
		for(int i = 0; i < size; i ++)
			for(int j = 0; j < size; j++)
				container[i][j] -> draw();
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

