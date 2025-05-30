#include "AreaGridPlanner.h"
#include "CorridorStripPlanner.h"
#include <fstream>
#include <cassert>
#include <filesystem>

int main() {
    std::filesystem::create_directories("output");
    // Area grid test
    std::vector<Point> polygon = {{0,0},{100,0},{100,50},{0,50}};
    AreaGridPlanner areaPlanner(polygon, 20.0, 0.0);
    auto transects = areaPlanner.generate();
    assert(!transects.empty());
    std::ofstream areaFile("output/area_transects.txt");
    for (const auto& seg : transects) {
        areaFile << seg.first.x << " " << seg.first.y << " "
                 << seg.second.x << " " << seg.second.y << "\n";
    }
    areaFile.close();

    // Corridor strip test
    std::vector<Point> polyline = {{0,0},{100,0}};
    CorridorStripPlanner stripPlanner(polyline, 40.0, 20.0);
    auto strips = stripPlanner.generate();
    assert(!strips.empty());
    std::ofstream stripFile("output/corridor_transects.txt");
    for (const auto& line : strips) {
        for (size_t i=0;i<line.size();++i) {
            stripFile << line[i].x << " " << line[i].y;
            if (i+1 < line.size()) stripFile << ","; // delim between points
        }
        stripFile << "\n";
    }
    stripFile.close();
    return 0;
}
