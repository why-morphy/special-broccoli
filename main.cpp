#include "screen.h"
#include <numeric>
#include <cmath>


const int s = 2;



struct vec3{
    float x, y, z;
};

struct connection{
    int a, b;
};


void rotate(vec3& point, float x = 1, float y = 1, float z = 1 ){
    float rad = 0;

    rad = x;
    point.y = std::cos(rad)*point.y - std::sin(rad)*point.z;
    point.z = std::sin(rad)*point.y + std::cos(rad)*point.z;

    rad = y;
    point.x = std::cos(rad)*point.x + std::sin(rad)*point.z;
    point.z = -std::sin(rad)*point.x + std::cos(rad)*point.z;

    rad = z;
    point.x = std::cos(rad)*point.x - std::sin(rad)*point.y;
    point.y = std::sin(rad)*point.x + std::cos(rad)*point.y;
}

void line(Screen& screen, float x1, float y1, float x2, float y2){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx*dx + dy*dy);
    float angle = std::atan2(dy, dx);

    for(float i = 0; i < length; i++){
        screen.pixel(x1 + cos(angle)*i, y1 +sin(angle)*i);
    }
}

int main(int argv, char** args){

    Screen screen;

    //particles effect
    // for(int i = 0; i < 100; i++){
    //     screen.pixel(rand()%640, rand()%480);
    // }

    std::vector<vec3> points {
        {s*100, s*100, s*100},
        {s*200, s*100, s*100},
        {s*200, s*200, s*100},
        {s*100, s*200, s*100},
        {s*100, s*100, s*200},
        {s*200, s*100, s*200},
        {s*200, s*200, s*200},
        {s*100, s*200, s*200}
    };

    std::vector<connection> connections {
       {0,4},
       {1,5},
       {2,6},
       {3,7},

       {0,1},
       {1,2},
       {2,3},
       {3,0},

       {4,5},
       {5,6},
       {6,7},
       {7,4}

    };
    
    //Declaration of the centeroid and the follow-ups
    vec3 c{25,25,25};
    for(auto& point : points){
        c.x += point.x;
        c.y += point.y;
        c.z += point.z;
    }

    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();

    //Rotation
    while(true){
        for(auto& point : points){
            point.x -= c.x;
            point.y -= c.y;
            point.z -= c.z;
            rotate(point, 0.01, 0.01, 0.01);
            point.x += c.x;
            point.y += c.y;
            point.z += c.z;
        }
        for(auto& point : points){
            screen.pixel(point.x, point.y);
        }

        for(auto& connection : connections){
            line(screen, points[connection.a].x, points[connection.a].y, points[connection.b].x, points[connection.b].y);
        }
        screen.show();
        screen.clear();
        screen.input();
        SDL_Delay(10);
    }

    return 0;
}