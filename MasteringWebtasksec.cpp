#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct Speed{
    int sx; int sy; int sz;
};

typedef struct Speed Sp;

struct Car{
    string make;
    string model;
    int year;
    Sp speed;
    int x;
    int y;
    int z;
};

void accelerate(Car* car, int ix, int iy, int iz) {
    car->speed.sx += ix;
    car->speed.sy += iy;
    car->speed.sz += iz;
}

void brake(Car* car, int dx, int dy, int dz) {
    car->speed.sx -= dx;
    car->speed.sy -= dy;
    car->speed.sz -= dz;
}

void move(Car* car) {
    car->x += car->speed.sx;
    car->y += car->speed.sy;
    car->z += car->speed.sz;
}

bool detect_collision(Car* car1, Car* car2) {
    double distance = sqrt(pow((car1->x - car2->x), 2) + pow((car1->y - car2->y), 2) + pow((car1->z - car2->z), 2));
    if (distance <= 0) { // assuming collision distance of 0 units
        return true;
    } else {
        return false;
    }
}

double time_to_collision(Car* car1, Car* car2) {
    double speedcar1 = pow(pow((car1->speed.sx), 2) + pow((car1->speed.sy), 2) + pow((car1->speed.sz), 2), (1.0/3));
    double speedcar2 = pow(pow((car2->speed.sx), 2) + pow((car2->speed.sy), 2) + pow((car2->speed.sz), 2), (1.0/3));
    double relative_speed = fabs(speedcar1 - speedcar2);
    double distance = sqrt(pow((car1->x - car2->x), 2) + pow((car1->y - car2->y), 2) + pow((car1->z - car2->z), 2));
    if (relative_speed == 0) {
        return INFINITY; // cars are moving at the same speed
    } else {
        double time = distance / relative_speed;
        return time;
    }
}

int main() {
    int spx1, spy1, spz1, spx2, spy2, spz2, x1, y1, z1, x2, y2, z2; 
    int ix, iy, iz, dx, dy, dz;
    
    cout << "Enter speed with co-ordinates of car1: ";
    cin >> spx1 >> spy1 >> spz1;
    
    cout << "Enter co-ordinates of car1: ";
    cin >> x1 >> y1 >> z1;

    cout << "Enter speed with co-ordinates of car2: ";
    cin >> spx2 >> spy2 >> spz2;
    
    cout << "Enter co-ordinates of car2: ";
    cin >> x2 >> y2 >> z2;

    Sp sp1; 
    sp1.sx = spx1; sp1.sy = spy1; sp1.sz = spz1; 
    Sp sp2; 
    sp2.sx = spx2; sp2.sy = spy2; sp2.sz;
       
    Car car1 = {"Hyundai","Verna" ,2020, sp1, x1, y1, z1};
    Car car2 = {"Kia", "Seltos", 2021, sp2, x2, y2, z2};
    

    int p = 0;
    char q;
    printf("Which car do you want to accelerate or brake?");
    scanf("%d", &p);
    if (p == 'A') {
        printf("Press A if you want to accelerate, B if you want to brake.");
        scanf(" %c", &q);
        if (q == 'A') {
            int ix, iy, iz;
            printf("Enter acceleration with 3 components: ");
            scanf("%d %d %d", &ix, &iy, &iz);
            accelerate(&car1, ix, iy, iz);
        } else {
            int dx, dy, dz;
            printf("Enter braking with 3 components: ");
            scanf("%d %d %d", &dx, &dy, &dz);
            brake(&car1, dx, dy, dz);
        }
    } else {
        printf("Press A if you want to accelerate, B if you want to brake.");
        scanf(" %c", &q);
        if (q == 'A') {
            int ix, iy, iz;
            printf("Enter acceleration with 3 components: ");
            scanf("%d %d %d", &ix, &iy, &iz);
            accelerate(&car2, ix, iy, iz);
        } else {
            int dx, dy, dz;
            printf("Enter braking with 3 components: ");
            scanf("%d %d %d", &dx, &dy, &dz);
            brake(&car2, dx, dy, dz);
        }
    }
    double time_to_collision1 = time_to_collision(&car1, &car2);
    move(&car1);
    move(&car2);

    if (detect_collision(&car1, &car2)) {
        printf("Cars will not collide.\n");
        return 0;
    } else {
        printf("Cars will collide.\n");
    }
    printf("Time to collision: %lf", time_to_collision1);

    return 0;
}

