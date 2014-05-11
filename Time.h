#include <iostream>
#include <math.h>
using namespace std;

class Time{
	public:
	int hours;
	int minutes;
	int seconds;
	
	Time(const Time& o){
		hours = o.hours;
		minutes = o.minutes;
		seconds = o.seconds;
	}
	
	Time(int h, int m, int s): hours(h), minutes(m), seconds(s){	
	}	
	
	void add(const Time& h){
		hours += h.hours;
		minutes += h.minutes;
		seconds += h.seconds;
		
		if(seconds > 59){
			minutes += seconds/60;
			seconds %=60;
		}
		if(minutes > 59){
			hours += minutes/60;
			minutes %=60;
		}
	}
		
	int getHours(){return hours;}
	int getMinutes(){return minutes;}
	int getSeconds(){return seconds;}
	void getAngles(float &h, float &m, float &s){


		if(seconds >= 0 && seconds <= 15){
			s = (15 - seconds)*M_PI/30;
		}
		else if(seconds >= 45 && seconds < 60){
			s = (60 - seconds)*M_PI/30 + M_PI/2;
		}
		else if(seconds > 15 && seconds < 45){
			s = (seconds - 15) * -M_PI/30;
		}
	
	
		if(minutes >= 0 && minutes <= 15){
			m = (15 - minutes)*M_PI/30;
		}
		else if(minutes >= 45 && minutes < 60){
			m = (60 - minutes)*M_PI/30 + M_PI/2;
		}
		else if(minutes > 15 && minutes < 45){
			m = (minutes - 15) * -M_PI/30;
		}		

		double h_temp = hours + (minutes + 0.0)/60;
	
		if(h_temp > 12)
			h_temp /= 12;	
		if(h_temp >= 0 && h_temp <= 3){
			h = (3 - h_temp)*M_PI/6;
		}
		else if(h_temp >= 9 && h_temp < 12){
			h = (12 - h_temp)*M_PI/6 + M_PI/2;
		}
		else if(h_temp > 3 && h_temp < 9){
			h = (h_temp - 3) * -M_PI/6;
		}
	}
    	void getHourCoords(float &x, float&y){
		float a;
		float b;
		float c;
		getAngles(a,b,c);
		x = cos(a);
		y = sin(a);			
	}
    	void getMinuteCoords(float &x, float&y){
		float a;
		float b;
		float c;
		getAngles(a,b,c);
		x = cos(b);
		y = sin(b);				
	}
    	void getSecondsCoords(float &x, float&y){	
		float a;
		float b;
		float c;
		getAngles(a,b,c);
		x = cos(c);
		y = sin(c);			
	}
};
