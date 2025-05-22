#include "screen.h"
#include <numeric>
#include <cmath>

struct vec3{
    float x, y, z;
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
        {200, 200, 200},
        {400, 200, 200},
        {400, 400, 200},
        {200, 200, 400},
        {200, 400, 400},
        {400, 200, 400},
        {400, 400, 400},
        {200, 400, 200}
    };
    

    while(true){
        screen.show();
        screen.input();
    }

    return 0;
}