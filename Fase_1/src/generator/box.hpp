#ifndef BOX_HPP
#define BOX_HPP

#include "../utils/figure.hpp"

class Box : public Figure {
public:
    Box(int length, int grid);

    ~Box();

    int length;
    int grid;

    virtual void generate_points() override;
};

#endif // BOX_HPP
