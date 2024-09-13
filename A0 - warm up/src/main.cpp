#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string RESPONSE_SEPARATOR = "----------";

struct Time {
    int h;
    int m;
};

struct Train {
    std::string name;
    std::string source;
    std::string destination;
    Time departure;
    int remainingCapacity;
};

struct UserRequest {
    std::string source;
    std::string destination;
    Time earliestDeparture;
    int requiredCapacity;
};

Time parseTime(const std::string& time) {
    Time t;
    t.h = std::stoi(time.substr(0, 2));
    t.m = std::stoi(time.substr(3, 2));
    return t;
}

std::string formatTime(const Time& time) {
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << time.h << ":" << std::setw(2) << std::setfill('0') << time.m;
    return ss.str();
}

bool departsBefore(const Train& train, const Time& time) {
    return train.departure.h < time.h || (train.departure.h == time.h && train.departure.m < time.m);
}

std::vector<Train> readTrainData(int n) {
    std::vector<Train> trains;
    for (int i = 0; i < n; ++i) {
        std::string name, source, destination, departure;
        int remainingCapacity;
        std::cin >> name >> source >> destination >> departure >> remainingCapacity;
        trains.push_back({name, source, destination, parseTime(departure), remainingCapacity});
    }
    return trains;
}

std::vector<Train> findMatchingTrains(const std::vector<Train>& trains, const UserRequest& request) {
    std::vector<Train> matchingTrains;
    for (const Train& train : trains) {
        if (train.source == request.source && train.destination == request.destination &&
            !departsBefore(train, request.earliestDeparture) && train.remainingCapacity >= request.requiredCapacity) {
            matchingTrains.push_back(train);
        }
    }
    return matchingTrains;
}

void printMatchingTrains(const std::vector<Train>& trains) {
    if (trains.empty()) {
        abort(); // this should never happen
    }
    else {
        for (const Train& train : trains) {
            std::cout << train.name << " "
                      << formatTime(train.departure) << " "
                      << train.remainingCapacity << std::endl;
        }
    }
    std::cout << RESPONSE_SEPARATOR << std::endl;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Train> trains = readTrainData(n);
    for (int i = 0; i < m; ++i) {
        std::string source, destination, earliestDeparture;
        int requiredCapacity;
        std::cin >> source >> destination >> earliestDeparture >> requiredCapacity;
        UserRequest request = {source, destination, parseTime(earliestDeparture), requiredCapacity};
        std::vector<Train> matchingTrains = findMatchingTrains(trains, request);
        printMatchingTrains(matchingTrains);
    }
    return 0;
}
