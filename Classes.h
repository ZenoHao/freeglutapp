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
	Square(const Square&s){
		this -> val = s.val;
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
            char * buffer = new char[256];
            sprintf(buffer,"%d", val);
            glColor3f(0, 0, 0); 
            glRasterPos2f(centerX-(0.005*sizeof(buffer)/sizeof(buffer[0])), centerY);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>(buffer));
        	delete buffer;
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
	bool operator ==(int &val){
		return (this -> val == val);
	}
	void print(){
	}
};

class Field{

    private:
	int size;
    	vector<vector<Square*> > container;
	vector<vector<Square*> > buffer;
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
			buffer.push_back(temp);
			container.push_back(temp);
			for(int j = 0; j < size; j++){
				container[i].push_back(new Square(-1.+1./size + 2./size*j, 
				1. - 1./size - 2./size*i, 2./size));
				buffer[i].push_back(new Square(-1.+1./size + 2./size*j, 
				1. - 1./size - 2./size*i, 2./size));
			}	
		}
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
	return anyMove;
        if (anyMove == false && createSquare() == false) {
            endGame();
        }
    }
    void endGame(){
		cout << "YOU ARE BAD " << endl;		
	}
	void draw(){
		for(int i = 0; i < size; i ++)
			for(int j = 0; j < size; j++)
				container[i][j] -> draw();
	}
	void merge(int input){
		switch(input){
		case UP:
		for(int i = 0; i < size; i++){// for each col	
			for(int j = 0; j < size - 1; j++){ // for each row in the col
				if(container[j][i] -> getVal() == container[j + 1][i] -> getVal()){
					container[j][i] -> setVal((container[j][i] -> getVal())*2);
					container[j + 1][i] -> setVal(0);
					j++;
				}
			}	
		}
		break;
		case RIGHT:
		for(int i = 0; i < size; i++){// for each col	
			for(int j = size - 1; j > 0; j--){ // for each row in the col
				if(container[i][j]-> getVal() == container[i][j - 1] -> getVal()){
					container[i][j] -> setVal(container[i][j] -> getVal()*2);
					container[i][j - 1] -> setVal(0);
					j--;
				}
			}	
		}
		break;
		case DOWN:
		for(int i = 0; i < size; i++){// for each col	
			for(int j = size - 1; j > 0; j--){ // for each row in the col
				if(container[j][i]-> getVal() == container[j - 1][i] -> getVal()){
					container[j][i] -> setVal(container[j][i] -> getVal()*2);
					container[j - 1][i] -> setVal(0);
					j--;
				}
			}	
		}
		break;
		case LEFT:
		for(int i = 0; i < size; i++){// for each col	
			for(int j = 0; j < size - 1; j++){ // for each row in the col
				if(container[i][j] -> getVal() == container[i][j + 1] ->getVal()){
					container[i][j] -> setVal(container[i][j] -> getVal()*2);
					container[i][j+1] -> setVal(0);
					j++;
				}
			}	
		}
		break;
		}
	}
	void compact(int input){
		bool avail = true;
		//int i = 0;
		//int j = 0;
		//int k = 0;
		switch(input){
		case UP:
		for(int i = 0; i < size; i++){// for each col	
				for(int j = 0; j < size - 1; j++){ // for each row in the col
					avail = false; 
					for(int m = j; m < size; m++){
						if(container[m][i] -> getVal() != 0)
							avail = true;
					}
					while(avail && container[j][i] -> getVal() == 0){
						// if there is one val that is not equal to 0 in teh rest of column
						for(int k = j; k < size - 1; k ++){
						container[k][i] -> setVal(container[k + 1][i] -> getVal());
						container[k + 1][i] -> setVal(0);
						}	
					}
				}	
			}
		break;
		case RIGHT:
		for(int i = 0; i < size; i++){// for each col	
				for(int j = size - 1; j >= 0; j--){ // for each row in the col
					avail = false; 
					for(int m = j; m >= 0; m--){
						if(container[i][m] -> getVal() != 0)
							avail = true;
					}
					while(avail && container[i][j] -> getVal() == 0){
						// if there is one val that is not equal to 0 in teh rest of column
						for(int k = j; k > 0; k--){
						container[i][k] -> setVal(container[i][k - 1] -> getVal());
						container[i][k - 1] -> setVal(0);
						}	
					}
				}	
			}
		break;
		case DOWN:
		for(int i = 0; i < size; i++){// for each col	
				for(int j = size - 1; j >= 0; j--){ // for each row in the col
					avail = false; 
					for(int m = j; m >= 0; m--){
						if(container[m][i] -> getVal() != 0)
							avail = true;
					}
					while(avail && container[j][i] -> getVal() == 0){
						// if there is one val that is not equal to 0 in teh rest of column
						for(int k = j; k > 0; k --){
						container[k][i] -> setVal(container[k - 1][i] -> getVal());
						container[k - 1][i] -> setVal(0);
						}	
					}
				}	
			}
		break;
		case LEFT:
		for(int i = 0; i < size; i++){// for each col	
			for(int j = 0; j < size - 1; j++){ // for each row in the col
				avail = false; 
				for(int m = j; m < size; m++){
					if(container[i][m] -> getVal() != 0)
						avail = true;
				}
				while(avail && container[i][j] -> getVal() == 0){
					// if there is one val that is not equal to 0 in teh rest of column
					for(int k = j; k < size - 1; k ++){
					container[i][k] -> setVal(container[i][k + 1] -> getVal());
					container[i][k+1] -> setVal(0);
					}	
				}
			}	
		}
		break;
		}
	}
	void move(int input){
		bool diff = false;
		for(int i = 0; i < size; i++){
			for(int j = 0; j< size; j++){
				buffer[i][j] -> setVal(container[i][j] -> getVal());
			}
		}
		compact(input);
		merge(input);
		compact(input);
		for(int i = 0; i < size; i++){
			for(int j = 0; j< size; j++){
				if(buffer[i][j] -> getVal() != container[i][j] -> getVal()){
					diff = true;
					break;
				}
			}
			if(diff)
				break;
		}
		if(diff)
		createSquare();
		checkMoveAvail();
	}  
};

