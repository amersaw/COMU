//Nesne Dizilerini Başlatma
#include<iostream>

using namespace std;
class Point{
    int x,y;
public:
    Point(int x, int y = 0){
        this->x = x;
        this->y = y;
    }
    void print(){
        cout<<"x="<<x<<", y="<<y<<endl;
    }

};
int main(){

    Point array[] = {
                            {10},  // Burda tek bir Argument ile yeni bir point nesne olusturduk
                            {23,7},// Burda iki Argument ile yeni point nesnesi olusturduk
                            Point(83,1) // Burda Point class'in ismi yazarak ve 2 argument göndererek yeni nesne oluşturduk
                    };


    Point *z = new Point(2,49);

    array[0].print();
    array[1].print();
    array[2].print();
    return 0;
}
