#ifndef AREA_GRID_PLANNER_H
#define AREA_GRID_PLANNER_H

#include <vector>
#include <utility>
#include "Point.h"

class AreaGridPlanner {
public:
    AreaGridPlanner(const std::vector<Point>& polygon,
                    double spacing,
                    double angle_deg);

    std::vector<std::pair<Point, Point>> generate();

private:
    Point rotatePoint(const Point& pt, const Point& origin, double angle_rad) const;
    bool lineIntersect(const Point& p1, const Point& p2,
                       const Point& q1, const Point& q2,
                       Point& result) const;

    std::vector<Point> _polygon;
    double _spacing;
    double _angleDeg;
};

#endif // AREA_GRID_PLANNER_H
