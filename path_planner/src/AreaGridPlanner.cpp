#include "AreaGridPlanner.h"
#include <cmath>
#include <algorithm>

AreaGridPlanner::AreaGridPlanner(const std::vector<Point>& polygon,
                                 double spacing,
                                 double angle_deg)
    : _polygon(polygon)
    , _spacing(spacing)
    , _angleDeg(angle_deg)
{
}

static double rad(double deg) { return deg * M_PI / 180.0; }

Point AreaGridPlanner::rotatePoint(const Point& pt, const Point& origin, double angle_rad) const
{
    double s = std::sin(angle_rad);
    double c = std::cos(angle_rad);
    Point p;
    double x = pt.x - origin.x;
    double y = pt.y - origin.y;
    p.x = origin.x + x * c - y * s;
    p.y = origin.y + x * s + y * c;
    return p;
}

bool AreaGridPlanner::lineIntersect(const Point& p1, const Point& p2,
                                    const Point& q1, const Point& q2,
                                    Point& result) const
{
    double s1_x = p2.x - p1.x;
    double s1_y = p2.y - p1.y;
    double s2_x = q2.x - q1.x;
    double s2_y = q2.y - q1.y;
    double denom = (-s2_x * s1_y + s1_x * s2_y);
    if (std::abs(denom) < 1e-6) {
        return false;
    }
    double s = (-s1_y * (p1.x - q1.x) + s1_x * (p1.y - q1.y)) / denom;
    double t = ( s2_x * (p1.y - q1.y) - s2_y * (p1.x - q1.x)) / denom;
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        result.x = p1.x + (t * s1_x);
        result.y = p1.y + (t * s1_y);
        return true;
    }
    return false;
}

std::vector<std::pair<Point, Point>> AreaGridPlanner::generate()
{
    std::vector<std::pair<Point, Point>> transects;
    if (_polygon.size() < 3) {
        return transects;
    }

    // bounding rect
    double minx = _polygon[0].x, maxx = _polygon[0].x;
    double miny = _polygon[0].y, maxy = _polygon[0].y;
    for (const Point& p : _polygon) {
        minx = std::min(minx, p.x);
        maxx = std::max(maxx, p.x);
        miny = std::min(miny, p.y);
        maxy = std::max(maxy, p.y);
    }
    Point center{ (minx + maxx) / 2.0, (miny + maxy) / 2.0 };
    double length = std::max(maxx - minx, maxy - miny) + 2.0 * _spacing;
    double half = length / 2.0;

    // generate parallel lines
    for (double x = center.x - half; x <= center.x + half; x += _spacing) {
        Point start{ x, center.y - half };
        Point end{ x, center.y + half };
        start = rotatePoint(start, center, rad(_angleDeg));
        end = rotatePoint(end, center, rad(_angleDeg));

        // intersect with polygon
        std::vector<Point> intersections;
        for (size_t i = 0; i < _polygon.size(); ++i) {
            Point a = _polygon[i];
            Point b = _polygon[(i + 1) % _polygon.size()];
            Point inter;
            if (lineIntersect(start, end, a, b, inter)) {
                intersections.push_back(inter);
            }
        }
        if (intersections.size() >= 2) {
            // choose two farthest points
            Point p1 = intersections[0];
            Point p2 = intersections[1];
            double maxDist = (p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y);
            for (size_t i=0;i<intersections.size();++i) {
                for (size_t j=i+1;j<intersections.size();++j) {
                    double d = (intersections[j].x-intersections[i].x)*(intersections[j].x-intersections[i].x)+
                               (intersections[j].y-intersections[i].y)*(intersections[j].y-intersections[i].y);
                    if (d > maxDist) {
                        maxDist = d;
                        p1 = intersections[i];
                        p2 = intersections[j];
                    }
                }
            }
            transects.push_back({p1,p2});
        }
    }

    // lawnmower pattern
    for (size_t i=0;i<transects.size();++i) {
        if (i % 2 == 1) {
            std::swap(transects[i].first, transects[i].second);
        }
    }
    return transects;
}
