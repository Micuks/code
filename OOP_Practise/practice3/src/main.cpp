#include "Shape.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Circle.h"

using namespace std;

void generateRectangle();
void generateCube();
void generateCircle();

int main() {
    generateRectangle();
    cout << endl;
    generateCube();
    cout << endl;
    generateCircle();
    cout << endl;
}

void generateRectangle() {
    double l, w;
    cout << "Enter the length and witdh of the rectangle.\n";
    cin >> l >> w;
    Rectangle rec(l, w);
    cout << "The area of the rectangle with length of " << l << " and width of " << w << " is " << rec.calculateArea() << endl;
}

void generateCube() {
    double l;
    cout << "Enter the length of the cube.\n";
    cin >> l;
    Cube cube(l);
    cout << "The area of the cube with length of " << l << " is " << cube.calculateArea() << endl;
}

void generateCircle() {
    double r;
    cout << "Enter the radius of the round.\n";
    cin >> r;
    Circle cir(r);
    cout << "The area of the Circle with radius of " << r << " is " << cir.calculateArea() << endl;
}
