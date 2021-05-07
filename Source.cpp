#include <iostream>
#include<string>
using namespace std;


 struct Point{
    float x, y;
};

class Line{
public:
    //ky*y = kx * x + m
    float kx, m;
    bool ky;
    Point point1, point2;

    void create(Point point1, Point point2) {
        this->point1 = point1;
        this->point2 = point2;

        if (point1.x == point2.x){
            ky = false;
            kx = 1;
            m = -point1.x;
        }
        else {
            ky = true;
            kx = (point1.y - point2.y) / (point1.x - point2.x);
            m = (point1.y + point2.y)/2 - kx * (point1.x + point2.x)/2 ;
        }
    }
    //проверка принадлежности отрезку(если точка изначально там лежит)
    bool check_belong(Point a){
        if ((a.x - point1.x) * (a.x - point2.x) <= 0  && (a.y - point1.y) * (a.y - point2.y) <= 0) return true;
        else return false;
    }


    float getY(float x){
        return x * kx + m;
    }
 
};

Point getXY(float x, Line line) {
    Point cross;
    cross.x = x;
    cross.y = line.getY(cross.x);

    return cross; 
}

//проверка пересечени€ отрезков
bool crossing_lines(Line line1, Line line2){

    if (line1.ky == true and line2.ky == true){

        if (line1.kx != line2.kx){
            Point cross = getXY((line2.m - line1.m) / (line1.kx - line2.kx), line1);

            if (line1.check_belong(cross) && line2.check_belong(cross)) return true;
            else return false;
        }
        
        else if (line1.m == line2.m) {
            if (line1.check_belong(line2.point1) || line1.check_belong(line2.point2)) 
                return true;
            else return false;
        }
        else return false;
    }


    else if (line1.ky == false && line2.ky != false) {
        Point cross = getXY(-line1.m / line1.kx, line2);
 
        if (line1.check_belong(cross) and line2.check_belong(cross)) return true;
        else return false;
    }

    else if (line1.ky != false && line2.ky == false)  {
        Point cross = getXY(-line2.m / line2.kx, line1);

        if (line1.check_belong(cross) && line2.check_belong(cross)) return 1;
        else return false;
    }

    else {
        if (line1.m / line1.kx == line2.m / line2.kx)  {
            if (line1.check_belong(line2.point1) || line1.check_belong(line2.point2)) 
                return true;
            else return false;
        }
        else return false;
    }
}

class Triangle{
public:
    Line line[3];
    void create(){
        Point point[3];
        for (short i = 0; i < 3; i++) {   
            cin >> point[i].x >> point[i].y;
        }
        line[0].create(point[0], point[1]);
        line[1].create(point[1], point[2]);
        line[2].create(point[2], point[0]);
    }
};


float findDistance(float x1, float y1, float x2, float y2) {
    return sqrt((x1-x2)* (x1 - x2) + (y1 - y2)* (y1 - y2));
}

class Square {
public:
    Line line[4];
    void create() {
        Point point[4];
        cout << "¬ведите координаты квадрата: " << endl;
        for (int i = 0; i < 4; i++)  {
            cin >> point[i].x >> point[i].y;
        }

        float side = findDistance(point[0].x, point[0].y, point[1].x, point[1].y);
        for (short i = 0; i < 4; i++) {
            for (short j = i+1; j < 4; j++)  {
                if (findDistance(point[i].x, point[i].y, point[j].x, point[j].y) < side)
                    side = findDistance(point[i].x, point[i].y, point[j].x, point[j].y);
            }
        }
  
        for (short i = 0; i < 3; i++) {
            if (findDistance(point[i].x, point[i].y, point[i + 1].x, point[i + 1].y) > side) {
                if (i == 0) {
                    Point tmp = point[2];
                    point[2] = point[i + 1];
                    point[i + 1] = tmp;
                }
                if (i == 1) {
                    Point tmp = point[3];
                    point[3] = point[i + 1];
                    point[i + 1] = tmp;
                }

                if (i == 2) {
                    Point tmp = point[0];
                    point[0] = point[i + 1];
                    point[i + 1] = tmp;
                }
          }
 
        }

        //0 0
        //0 50
        //50 50
        //50 0

        line[0].create(point[0], point[1]); 
        line[1].create(point[1], point[2]);
        line[2].create(point[2], point[3]);
        line[3].create(point[3], point[0]);
    }
};

bool cross_t_s(Triangle triangle, Square square){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (crossing_lines(triangle.line[i], square.line[j])) return true;
        }
    }
    return 0;
}

class Mnogougolnik {
    int* coords;

    Mnogougolnik() {
        short n; 
        cin >> ; 
        coords = new int[n];
    }
};


int main(){
    setlocale(LC_ALL, "Rus");
    unsigned int n, count = 0;
    cout << "¬ведите n: ";
    cin >> n;
    Triangle* trgl = new Triangle[n];

    for (int i = 0; i < n; i++) {
        cout << "¬ведите координаты точек " << (i + 1) << " треугольника: " << endl;
        trgl[i].create();
    }

    Square kvadr;
    kvadr.create();
    for (int i = 0; i  < n; i++)  {
        count += cross_t_s(trgl[i], kvadr);
    }
    cout << endl;
    cout << count;

    return 0;
}