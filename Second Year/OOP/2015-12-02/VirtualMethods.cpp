/*
Cesitli sekillerin ifade edilebilmesi icin Shape isimnde bir temel sinifi ve Line, Triangle, ve Rectangle isimlerinde
turetilmis siniflari tasarlayiniz. Hersinif bir siniflara ait olmayan tek bir goster() fonksiyonu kullanarak ilgili
sinifin kendisine ait verilerin degerlerini ekrana yazdirsin
*/
#include <iostream>
using namespace std;

class Point{
public :
    int x,y;
    Point(int, int);
    friend ostream& operator<<(ostream& , const Point &);
};
ostream& operator<<(ostream& os, const Point & obj){
    os<<"("<<obj.x<<","<<obj.y<<")";
    return os;
}
Point::Point(int a=0,int b=0){
    x=a;
    y=b;
}

class Shape{
    Point p1;
public:
    Shape(Point);
    virtual void print();
};
void Shape::print(){
    cout<<"Shape print Function:"<<endl;
    cout<<p1;
}
Shape::Shape(Point p){
    p1 = p;
}
class Line:public Shape{
    Point p2;
public:
    Line(Point, Point);
    void print();
};
Line::Line(Point p1, Point p2):Shape(p1){
    this->p2=p2;
}
void Line::print(){
    cout<<"Line print Funcion:"<<endl;
    Shape::print();
    cout<<"\t"<<p2<<endl;
}

class Triangle:public Shape{
    Point p2,p3;
public:
    Triangle(Point,Point,Point);
    void print();

};
Triangle::Triangle(Point p1, Point p2, Point p3):Shape(p1){
    this->p2=p3;
    this->p3=p3;
}
void Triangle::print(){
    cout<<"Triangle print Funcion:"<<endl;
    Shape::print();
    cout<<"\t"<<p2<<"\t"<<p3<<endl;
}

void goster (Shape* objPtr){
    objPtr->print();
}

class Rectangle:public Shape{
    Point p2, p3, p4;
public:
    Rectangle (Point, Point, Point, Point);
    void print();
};
Rectangle::Rectangle(Point p1,Point p2, Point p3, Point p4):Shape(p1){
    this->p2=p2;
    this->p3=p3;
    this->p4=p4;
}
void Rectangle::print(){
    Shape::print();
    cout<<"\t"<<p2<<"\t"<<p3<<"\t"<<p4;
}
int main()
{
    Point p1(1,1),p2(2,2),p3(3,3),p4(4,4);
    Line* l  = new Line (p2,p3);
    Triangle* t  = new Triangle(p1,p2,p3);
    Rectangle* r  = new Rectangle(p1,p2,p3,p4);
	int option;
	cin>>option;
	if(option == 1)
		goster(l);
	else if (option == 2)
		goster(t);
	else
		goster(r);

    return 0;
}
