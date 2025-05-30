#ifndef CORRIDOR_STRIP_PLANNER_H
#define CORRIDOR_STRIP_PLANNER_H

#include <vector>
#include <utility>
#include "Point.h"

class CorridorStripPlanner {
public:
    CorridorStripPlanner(const std::vector<Point>& polyline,
                         double width,
                         double spacing);

    std::vector<std::vector<Point>> generate();

private:
    Point offsetPoint(const Point& p1, const Point& p2, double offset) const;

    std::vector<Point> _polyline;
    double _width;
    double _spacing;
};

#endif // CORRIDOR_STRIP_PLANNER_H
