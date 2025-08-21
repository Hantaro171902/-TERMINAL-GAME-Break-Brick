#include <iostream>
#include "ball.hpp"
#include "game.hpp"

using namespace std;

Ball::Ball() : x(0), y(0), speed(1), dir(1) {}

void draw() {
	map[y][x] = 5;
}

void Ball::move() {
    if (dir == 0 && !collision(x - speed, y - speed)) {
        x -= speed;
        y -= speed;
    } else if (dir == 1 && !collision(x + speed, y - speed)) {
        x += speed;
        y -= speed;
    } else if (dir == 2 && !collision(x - speed, y + speed)) {
        x -= speed;
        y += speed;
    } else if (dir == 3 && !collision(x + speed, y + speed)) {
        x += speed;
        y += speed;
    }
}

bool Ball::collision(int fx, int fy) {
    if (map[fy][fx] == 8) {
        decre_life = true;
        x = screenWidth / 2 - 1;
        y = screenHeight - screenHeight / 7 - 3;
        dir = 4;
        life--;
    } else if (map[fy][fx] != 0 || map[y][fx] != 0 || map[fy][x] != 0 || 
               map[fy][fx] == 2 || map[y][fx] == 2 || map[fy][x] == 2) {
        
        if(map[fy][fx] == 2) heart[fy-2][fx-6] = '.';
		if(map[y][fx] == 2) heart[y-2][fx-6] = '.';
		if(map[fy][x] == 2) heart[fy-2][x-6] = '.';
		
		if(map[y][fx] != 0) bounce(fx,y);
		else if(map[fy][x] != 0) bounce(x,fy);
		else if(map[fy][fx] != 0) bounce(fx,fy);

        return true;
    }

    return false;
}

void Ball::bounce(int fx, int fy) {
    if(dir == 0){
		if(fx < x) dir = 1;
		else if(fy < y) dir = 2;
		else if(fx < x && fy < y) dir = 0;
	}else if(dir == 1){
		if(fx > x) dir = 0;
		else if(fy < y) dir = 3;
		else if(fx > x && fy < y) dir = 1;
	}else if(dir == 2){
		if(fx < x) dir = 3;
		else if(fy > y) dir = 0;
		else if(fx < x && fy > y) dir = 2;
	}else if(dir == 3){
		if(fx > x) dir = 2;
		else if(fy > y) dir = 1;
		else if(fx > x && fy > y) dir = 3;
	}
}
