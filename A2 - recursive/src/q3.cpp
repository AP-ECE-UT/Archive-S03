#include <iostream>
#include <utility>
#include <vector>

typedef std::pair<int, int> Station;

const int NEXT_STATION_TIME = 1;
const int CHANGE_LINE_TIME = 2;

const int INVALID = -1;
const int NON_INTERSECTION = -1;
const int FORWARD = 1;
const int BACKWARD = -1;
const int BOTHWAYS = 0;

struct Inputs {
    Station src;
    Station dst;
    std::vector<std::vector<int>> stations;
};

bool isVisited(Station station, std::vector<Station>& visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == station)
            return true;
    }
    return false;
}

int bestTime(std::vector<int> times) {
    int min = INVALID;
    for (int i = 0; i < times.size(); i++) {
        if (min == INVALID || times[i] < min)
            min = times[i];
    }
    return min;
}

int findIntersection(int lineId, std::vector<int> line) {
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == lineId)
            return i;
    }
    return INVALID;
}

int timeToGo(Station src, Station dst, std::vector<std::vector<int>>& stations, std::vector<Station> visited, int direction = BOTHWAYS) {
    if (src == dst)
        return 0;

    if (src.second < 0 || src.second >= stations[src.first].size())
        return INVALID;

    if (isVisited(src, visited))
        return INVALID;

    std::vector<int> times;
    visited.push_back(src);

    if (direction == FORWARD || direction == BOTHWAYS) {
        int t = timeToGo(Station(src.first, src.second + FORWARD), dst, stations, visited, FORWARD);
        if (t != INVALID)
            times.push_back(NEXT_STATION_TIME + t);
    }

    if (direction == BACKWARD || direction == BOTHWAYS) {
        int t = timeToGo(Station(src.first, src.second + BACKWARD), dst, stations, visited, BACKWARD);
        if (t != INVALID)
            times.push_back(NEXT_STATION_TIME + t);
    }

    int stationCode = stations[src.first][src.second];
    if (stationCode != NON_INTERSECTION) {
        Station stationInOtherLine = Station(stationCode, findIntersection(src.first, stations[stationCode]));
        int t = timeToGo(stationInOtherLine, dst, stations, visited, BOTHWAYS);
        if (t != INVALID)
            times.push_back(CHANGE_LINE_TIME + t);
    }

    return bestTime(times);
}

Inputs zeroIndexify(Inputs inputs) {
    inputs.src.first = inputs.src.first - 1;
    inputs.src.second = inputs.src.second - 1;
    inputs.dst.first = inputs.dst.first - 1;
    inputs.dst.second = inputs.dst.second - 1;
    for (int i = 0; i < inputs.stations.size(); i++) {
        for (int j = 0; j < inputs.stations[i].size(); j++)
            inputs.stations[i][j] = inputs.stations[i][j] - 1;
    }
    return inputs;
}

Inputs getInput(std::istream& inputStream) {
    Inputs result;

    int subwayLinesCount;
    inputStream >> subwayLinesCount;
    while (subwayLinesCount--) {
        int subwayStaionCount;
        inputStream >> subwayStaionCount;
        std::vector<int> lineStations;
        while (subwayStaionCount--) {
            int stationCode;
            inputStream >> stationCode;
            lineStations.push_back(stationCode);
        }
        result.stations.push_back(lineStations);
    }
    inputStream >> result.src.first >> result.src.second >> result.dst.first >> result.dst.second;
    result = zeroIndexify(result);
    return result;
}

int main() {
    Inputs inputs = getInput(std::cin);
    std::cout << timeToGo(inputs.src, inputs.dst, inputs.stations, std::vector<Station>{});
    return 0;
}