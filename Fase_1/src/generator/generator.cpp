#include "sphere.hpp"
#include "plane.hpp"
#include "box.hpp"
#include "cone.hpp"

#include "../utils/figure.hpp"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main(int argc, char *argv[]){
    if (argc >= 5){
        Figure* figure;
        const char *file_path;

        if (strcmp(argv[1], "plane") == 0) {
            int length = atoi(argv[2]), divisions = atoi(argv[3]); 
            file_path = argv[4];

            figure = new Plane(length, divisions);
        }
        else if (strcmp(argv[1], "box") == 0) {
            int length = atoi(argv[2]), divisions = atoi(argv[3]);
            file_path = argv[4];

            figure = new Box(length, divisions);
        }
        else if (strcmp(argv[1], "sphere") == 0) {
            int radius = atoi(argv[2]), slices = atoi(argv[3]), stacks = atoi(argv[4]);
            file_path = argv[5];

            figure = new Sphere(radius, slices, stacks); 
        }
        else if (strcmp(argv[1], "cone") == 0) {
            int radius = atoi(argv[2]), height = atoi(argv[3]), slices = atoi(argv[4]), stacks = atoi(argv[5]);
            file_path = argv[6];

            figure = new Cone(radius, height, slices, stacks);
        }
        else {
            printf("Invalid\n");
            return 1;
        }

        figure->generate_points();
        figure->to_file(file_path);

        delete figure;
    }
    else{
        printf("Invalid number of arguments.\n");
        return 1;
    }
    return 0;
}
