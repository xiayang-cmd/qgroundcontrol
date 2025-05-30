#include "CorridorStripPlanner.h"
#include <cmath>
#include <algorithm>

CorridorStripPlanner::CorridorStripPlanner(const std::vector<Point>& polyline,
                                           double width,
                                           double spacing)
    : _polyline(polyline)
    , _width(width)
    , _spacing(spacing)
{
}

Point CorridorStripPlanner::offsetPoint(const Point& p1, const Point& p2, double offset) const
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double len = std::sqrt(dx*dx + dy*dy);
    if (len == 0) {
        return p1;
    }
    double nx = -dy / len;
    double ny = dx / len;
    Point result{ p1.x + nx * offset, p1.y + ny * offset };
    return result;
}

std::vector<std::vector<Point>> CorridorStripPlanner::generate()
{
    std::vector<std::vector<Point>> transects;
    if (_polyline.size() < 2) {
        return transects;
    }

    int count = std::max(1, static_cast<int>(std::floor(_width / _spacing)));
    double half = _width / 2.0;
    double startOffset = count == 1 ? 0.0 : -half + _spacing / 2.0;

    for (int i=0;i<count;i++) {
        double offset = startOffset + i * _spacing;
        std::vector<Point> transect;
        for (size_t j=0;j<_polyline.size();++j) {
            if (j+1 < _polyline.size()) {
                transect.push_back(offsetPoint(_polyline[j], _polyline[j+1], offset));
            } else {
                // last point use previous segment direction
                transect.push_back(offsetPoint(_polyline[j-1], _polyline[j], offset));
            }
        }
        transects.push_back(transect);
    }

    // lawnmower pattern
    for (size_t i=0;i<transects.size();++i) {
        if (i % 2 == 1) {
            std::reverse(transects[i].begin(), transects[i].end());
        }
    }

    return transects;
}
