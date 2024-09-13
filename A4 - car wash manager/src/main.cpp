#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Time;
class Stage;
class Car;
class Worker;
class CarWash;

//======================================================================================================

struct Time {
    int day;
    int hour;
    Time(int day, int hour) : day(day), hour(hour) {}
    bool isBefore(Time other) {
        if (day < other.day)
            return false;
        else if (other.day < this->day)
            return true;
        return this->hour > other.hour;
    }
    string toStr() {
        stringstream str;
        str << day << ' ';
        if (hour < 10)
            str << '0';
        str << hour << ":00";
        return str.str();
    }
    void increase() {
        hour++;
        if (hour >= 24) {
            day++;
            hour -= 24;
        }
    }
};

class Worker {
public:
    Worker(int id, int stage_id, int from, int to_time, int reward, int time_to_finish, const Time* global_time) : id(id), stage_id(stage_id), from(from), to_time(to_time), reward(reward), time_to_finish(time_to_finish), remaining_hours_on_one_car(0), current_car_id(0), total_reward(0), busy(false), global_time(global_time) {
    }

#ifdef FRIENDLY_MAIN
    friend int main(int argc, char* argv[]);
#endif

    bool isAvailable() {
        if (global_time->hour < from)
            return false;
        else if (busy)
            return false;
        if ((*this->global_time).hour + time_to_finish > to_time)
            return false;
        return true;
    }

    bool isPresent() {
        return global_time->hour >= from && global_time->hour <= to_time;
    }

    bool hasMessage() { return this->message != ""; }
    string flushMessage() {
        string temp = message;
        this->message = "";
        return temp;
    }
    string Data() { return "Worker " + to_string(id); }
    int getId() const { return id; }
    int getTimeToFinish() const { return time_to_finish; }
    int getStageId() const { return this->stage_id; }
    int getTotalReward() { return this->total_reward; }
    int getCurrentWorkingCar() { return this->current_car_id; }

    void passOneHour() {
        if (busy && --remaining_hours_on_one_car == 0) {
            busy = false;
            this->current_car_id = 0;
            total_reward += reward;
        }
        if (global_time->hour == from) {
            message = "Entered";
        }
        if (global_time->hour == to_time) {
            message = "Left";
        }
    }

    void GetAssigned(int carId) {
        this->busy = true;
        this->remaining_hours_on_one_car = this->time_to_finish;
        this->current_car_id = carId;
    }

private:
    int id;
    int stage_id;
    int from;
    int to_time;
    int reward;
    int time_to_finish;

    int remaining_hours_on_one_car;
    int current_car_id;
    int total_reward;

    bool busy;
    string message;

    const Time* const global_time;
};

class Stage {
public:
    Stage(int id, int price) : id(id), price(price), washed_count(0) {}
    bool isAvailable() {
        for (Worker* w : stage_workers) {
            if (w->isAvailable())
                return true;
        }
        return false;
    }

#ifdef FRIENDLY_MAIN
    friend int main(int argc, char* argv[]);
#endif

    int getId() const { return id; }
    int getPrice() const { return price; }
    int getWashedCount() const { return this->washed_count; }

    int calc_income() const {
        int income = washed_count * price;
        for (auto w : stage_workers) {
            income += w->getTotalReward();
        }
        return income;
    }

    void addWorker(Worker* w) { this->stage_workers.push_back(w); }

    Worker* findSuitableWorker() {
        vector<Worker*> temp;
        for (Worker* w : this->stage_workers) {
            if (w->isAvailable())
                temp.push_back(w);
        }
        if (temp.size() == 0)
            return nullptr;
        sort(temp.begin(), temp.end(), [](Worker* a, Worker* b) { return a->getId() < b->getId(); });
        sort(temp.begin(), temp.end(), [](Worker* a, Worker* b) { return a->getTimeToFinish() < b->getTimeToFinish(); });
        return temp[0];
    }

    void addWashed() { this->washed_count++; }

private:
    int id;
    int price;
    vector<Worker*> stage_workers;
    int washed_count;
};

class Car {
public:
    Car(int id, Time arrival_time, vector<Stage*> stages) : id(id), remaining_stages(stages), current_stage(stages[0]), remaining_stage_time(0), state(State::Staged), arrival_time(arrival_time), finished_stage(true) {
    }

    enum class State {
        Queue = 0,
        Staged = 1,
        Done = 2,
    };

    void passOneHour() {
        if (state == State::Staged)
            remaining_stage_time--;
        if (state == State::Staged && remaining_stage_time == 0) {
            this->finished_stage = true;
        }
        if (finished_stage && remaining_stages.size() == 0 && state != State::Done) {
            state = State::Done;
            message = "Stage " + to_string(this->current_stage->getId()) + " -> Done";
            this->current_stage->addWashed();
        }
    }

    State getState() { return this->state; }
    bool isReadyToMove() {
        return (finished_stage && state != State::Done);
    }

    Stage* getNextStage() {
        if (remaining_stages.size() == 0)
            return nullptr;
        return remaining_stages[0];
    }
    Stage* getCurrentStage() { return this->current_stage; }

    void goToNextStage(State st, int stage_time, Time arrivalTime) {
        if (this->current_stage == this->remaining_stages[0] && this->state == State::Staged) {
            stringstream strstm;
            strstm << "Arrived -> ";
            strstm << (st == State::Queue ? "Queue " : "Stage ");
            strstm << remaining_stages[0]->getId();
            message = strstm.str();
        }
        else {
            this->message = generateMessage(this->state, st, this->current_stage->getId(),
                                            this->state == State::Queue ? this->current_stage->getId() : this->remaining_stages[0]->getId());
        }
        if (this->state == State::Staged) {
            if (this->current_stage != remaining_stages[0])
                this->current_stage->addWashed();
            this->current_stage = remaining_stages[0];

            this->remaining_stages.erase(remaining_stages.begin());
            this->finished_stage = false;
        }
        this->state = st;
        this->remaining_stage_time = stage_time;
        this->arrival_time = arrivalTime;
        this->finished_stage = false;
    }

#ifdef FRIENDLY_MAIN
    friend int main(int argc, char* argv[]);
#endif

    bool hasMessage() { return this->message != ""; }
    string flushMessage() {
        string temp = message;
        this->message = "";
        return temp;
    }
    string Data() { return "Car " + to_string(id); }

    int getId() const { return this->id; }
    Time getArrivalTime() { return this->arrival_time; }

private:
    int id;
    vector<Stage*> remaining_stages;
    Stage* current_stage;
    int remaining_stage_time;
    State state;
    Time arrival_time;

    bool finished_stage;

    string message;
    string data;

    string generateMessage(State from_state, State to_state, int from_id, int to_id) {
        stringstream str;
        str << ((from_state == State::Staged) ? "Stage " : "Queue ");
        str << from_id << " -> ";
        str << ((to_state == State::Staged) ? "Stage " : "Queue ");
        str << to_id;
        return str.str();
    }
};

//======================================================================================================

class CarWash {
public:
    CarWash(Time* t) : global_time(t), car_index(1) {}
    ~CarWash() {
        for (Car* c : cars)
            delete c;
        for (Stage* s : stages)
            delete s;
        for (Worker* w : workers)
            delete w;
    }

#ifdef FRIENDLY_MAIN
    friend int main(int argc, char* argv[]);
#endif

    void addStage(int id, int price) { this->stages.push_back(new Stage(id, price)); }
    void addWorker(int id, int stage_id, int from, int to_time, int reward, int time_to_finish, const Time* time) {
        Worker* temp = new Worker(id, stage_id, from, to_time, reward, time_to_finish, time);
        workers.push_back(temp);
        for (Stage* s : stages) {
            if (stage_id == s->getId()) {
                s->addWorker(temp);
                return;
            }
        }
    }

    void AssignCars() {
        sort(cars.begin(), cars.end(), [](Car* a, Car* b) { return a->getId() < b->getId(); });
        sort(cars.begin(), cars.end(), [](Car* a, Car* b) { return a->getArrivalTime().isBefore(b->getArrivalTime()); });
        for (Stage* s : stages) {
            for (Car* c : cars) {
                if (c->getCurrentStage() == s && c->getState() == Car::State::Queue && s->isAvailable()) {
                    Worker* w = s->findSuitableWorker();
                    c->goToNextStage(Car::State::Staged, w->getTimeToFinish(), *global_time);
                    w->GetAssigned(c->getId());
                }
            }
            for (Car* c : cars) {
                if (c->isReadyToMove() && c->getNextStage() == s) {
                    if (s->isAvailable()) {
                        Worker* w = s->findSuitableWorker();
                        c->goToNextStage(Car::State::Staged, w->getTimeToFinish(), *global_time);
                        w->GetAssigned(c->getId());
                    }
                    else {
                        c->goToNextStage(Car::State::Queue, 0, *global_time);
                    }
                }
            }
        }
    }

    vector<Stage*> getStages(vector<int> stage_ids, bool& flag) {
        vector<Stage*> res;
        flag = true;
        for (int st_id : stage_ids) {
            auto temp = find_if(stages.begin(), stages.end(), [st_id](Stage* st) { return st->getId() == st_id; });
            if (temp != stages.end())
                res.push_back(*temp);
            else {
                flag = false;
                return vector<Stage*>();
            }
        }
        return res;
    }

    void addCar(vector<int> stageIndexes) {
        bool flag;
        Car* temp = new Car(car_index++, *global_time, getStages(stageIndexes, flag));
        if (flag)
            this->cars.push_back(temp);
        else {
            warning = "NOT FOUND";
        }
    }

    string getMessages() {
        sort(cars.begin(), cars.end(), [](Car* a, Car* b) { return a->getId() < b->getId(); });
        sort(workers.begin(), workers.end(), [](Worker* a, Worker* b) { return a->getId() < b->getId(); });
        stringstream str;
        for (Worker* w : workers) {
            if (w->hasMessage()) {
                str << global_time->toStr() << ' ' << w->Data() << ": " << w->flushMessage() << endl;
            }
        }
        for (Car* c : cars) {
            if (c->hasMessage()) {
                str << global_time->toStr() << ' ' << c->Data() << ": " << c->flushMessage() << endl;
            }
        }

        return str.str();
    }

    void PassOneHour() {
        global_time->increase();
        for (Worker* w : workers)
            w->passOneHour();
        for (Car* c : cars)
            c->passOneHour();

        AssignCars();
    }

    string getStageStatus(int stage_id) {
        auto temp = find_if(stages.begin(), stages.end(), [stage_id](Stage* st) { return st->getId() == stage_id; });
        if (temp == stages.end()) {
            this->warning = "NOT FOUND";
            return "";
        }
        stringstream str;
        str << "Number of present workers: " << number_of_present_workers(stage_id) << endl;
        str << "Number of washed cars: " << number_of_washed_cars(*temp) << endl;
        str << "Number of cars in queue: " << number_of_cars_in_queue(*temp) << endl;
        str << "Number of cars being washed: " << number_of_cars_being_washed(*temp) << endl;
        str << "income: " << income(*temp) << endl;
        return str.str();
    }

    string getWorkerStatus(int worker_id) {
        auto temp = find_if(workers.begin(), workers.end(), [worker_id](Worker* st) { return st->getId() == worker_id; });
        if (temp == workers.end()) {
            warning = "NOT FOUND";
            return "";
        }
        Worker* w = *temp;
        if (!w->isPresent())
            return "Off Duty";
        if (w->isAvailable())
            return "Idle";
        return "Working: " + to_string(w->getCurrentWorkingCar());
    }

    string getWorkerSalary(int worker_id) {
        auto temp = find_if(workers.begin(), workers.end(), [worker_id](Worker* st) { return st->getId() == worker_id; });
        if (temp == workers.end()) {
            warning = "NOT FOUND";
            return "";
        }
        return to_string((*temp)->getTotalReward());
    }

    string getCarStatus(int car_id) {
        auto temp = find_if(cars.begin(), cars.end(), [car_id](Car* st) { return st->getId() == car_id; });
        if (temp == cars.end()) {
            warning = "NOT FOUND";
            return "";
        }

        Car* c = *temp;
        switch (c->getState()) {
        case Car::State::Done: {
            return "Done";
            break;
        }
        case Car::State::Queue: {
            return "In line: " + to_string(c->getCurrentStage()->getId());
            break;
        }
        case Car::State::Staged: {
            return "Washing: " + to_string(c->getCurrentStage()->getId());
            break;
        }
        default: {
            return "";
            break;
        }
        }
    }

    string flushWarning() {
        string temp = this->warning;
        this->warning = "";
        return temp;
    }
    bool hasWarning() {
        return this->warning != "";
    }

private:
    vector<Car*> cars;
    vector<Stage*> stages;
    vector<Worker*> workers;

    Time* const global_time;
    int car_index;

    string warning;

    int number_of_present_workers(int stage_id) {
        int res = 0;
        for (Worker* w : workers) {
            if (w->getStageId() == stage_id && w->isPresent())
                res++;
        }
        return res;
    }
    int number_of_washed_cars(const Stage* stage) {
        return stage->getWashedCount();
    }
    int number_of_cars_in_queue(const Stage* stage) {
        int res = 0;
        for (Car* c : cars) {
            if (c->getState() == Car::State::Queue && c->getCurrentStage() == stage)
                res++;
        }
        return res;
    }
    int number_of_cars_being_washed(const Stage* stage) {
        int res = 0;
        for (Car* c : cars) {
            if (c->getState() == Car::State::Staged && c->getCurrentStage() == stage)
                res++;
        }
        return res;
    }

    int income(const Stage* stage) {
        return stage->calc_income();
    }
};

//======================================================================================================

class IOHandle {
private:
    vector<string> breakStringIntoVector(string str, char sep) {
        vector<string> res;
        string temp;
        for (int i = 0; i < (int)str.size(); i++) {
            if (str[i] == sep) {
                res.push_back(temp);
                temp = "";
            }
            else
                temp += str[i];
        }
        if (temp != "")
            res.push_back(temp);
        return res;
    }

public:
    string processCommand(string command, CarWash& carwash) {
        vector<string> arguments = breakStringIntoVector(command, ' ');
        if (arguments.size() == 0)
            return "";
        command = arguments[0];
        arguments.erase(arguments.begin());

        if (command == "pass_time") {
            stringstream str;
            for (int i = 0; i < stoi(arguments[0]); i++) {
                carwash.PassOneHour();
                str << carwash.getMessages();
            }
            return str.str();
        }
        else if (command == "car_arrival") {
            vector<int> stg;
            for_each(arguments.begin(), arguments.end(), [&stg](string s) { stg.push_back(stoi(s)); });
            carwash.addCar(stg);
            if (!carwash.hasWarning()) {
                carwash.AssignCars();
                return carwash.getMessages();
            }
            else {
                return carwash.flushWarning() + "\n";
            }
        }
        else if (command == "get_stage_status") {
            string s = carwash.getStageStatus(stoi(arguments[0]));
            if (carwash.hasWarning())
                return carwash.flushWarning() + "\n";
            return s;
        }
        else if (command == "get_worker_status") {
            string s = carwash.getWorkerStatus(stoi(arguments[0]));
            if (carwash.hasWarning())
                return carwash.flushWarning() + "\n";
            return s + "\n";
        }
        else if (command == "get_worker_salary") {
            string s = carwash.getWorkerSalary(stoi(arguments[0]));
            if (carwash.hasWarning())
                return carwash.flushWarning() + "\n";
            return s + "\n";
        }
        else if (command == "get_car_status") {
            string s = carwash.getCarStatus(stoi(arguments[0]));
            if (carwash.hasWarning())
                return carwash.flushWarning() + "\n";
            return s + "\n";
        }
        else {
            return "COMMAND NOT FOUND\n";
        }
    }

    void LoadCSV(char* stages, char* workers, CarWash& carwash, const Time* t) {
        ifstream stage_file(stages), worker_file(workers);
        string temp;
        getline(stage_file, temp);

        while (getline(stage_file, temp)) {
            vector<int> args;
            vector<string> args_str = breakStringIntoVector(temp, ',');
            for_each(args_str.begin(), args_str.end(), [&args](string s) { args.push_back(stoi(s)); });
            carwash.addStage(args[0], args[1]);
        }
        getline(worker_file, temp);

        while (getline(worker_file, temp)) {
            vector<int> args;
            vector<string> args_str = breakStringIntoVector(temp, ',');
            for_each(args_str.begin(), args_str.end(), [&args](string s) { args.push_back(stoi(s)); });
            carwash.addWorker(args[0], args[1], args[2], args[3], args[4], args[5], t);
        }

        stage_file.close();
        worker_file.close();
    }
};

int main(int argc, char* argv[]) {
    Time t(1, 0);
    CarWash carwash(&t);
    string command;
    IOHandle iohdl;
    //    iohdl.LoadCSV("stages.csv", "workers.csv", carwash, &t);
    iohdl.LoadCSV(argv[1], argv[2], carwash, &t);
    while (getline(cin, command)) {
        cout << iohdl.processCommand(command, carwash);
    }
}
