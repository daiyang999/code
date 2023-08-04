#pragma once
#include"circle.h"

void circle::setcenter(point center1) {
	center = center1;
}
point circle::getcenter() {
	return center;
}
void circle::setr(int r1) {
	r = r1;
}
int circle::getr() {
	return r;
}
