#include <cstdio>
#include <iostream>
#include <string>

#include "communication/base_router.hpp"
#include "communication/command_line_interface.hpp"
#include "communication/utgram_console_responder.hpp"
#include "communication/utgram_router.hpp"
#include "data_loader/data_loader.hpp"
#include "system_core/utgram.hpp"

using namespace std;

const int MINIMUM_NUMBER_OF_ARGUMENTS = 4;

// Gonna keep these functions for further tests
void printMajor(Major* x) {
    cout << x->getId() << "- " << x->getName() << endl;
}

void printCourse(Course* x) {
    cout << x->getId() << "- " << x->getName() << endl;
    cout << "Valid Majors for course:" << endl;
    for (auto y : x->getValidMajors()) {
        cout << '\t';
        printMajor(y);
    }
    cout << endl;
}

void printMember(Member* x) {
    cout << x->getId() << "- " << x->getName() << endl;
}

int main(int argc, char* argv[]) {
    if (argc < MINIMUM_NUMBER_OF_ARGUMENTS + 1) {
        cerr << "At least " << MINIMUM_NUMBER_OF_ARGUMENTS
             << " arguments should be passed to the executable.";
        return 1;
    }

    string majorsPath = argv[1];
    string studentsPath = argv[2];
    string coursesPath = argv[3];
    string teachersPath = argv[4];

    DataLoader loader =
        DataLoader(majorsPath, coursesPath, studentsPath, teachersPath);
    Utgram* utgram = new Utgram(loader);
    UtgramBaseResponder* responder = new UtgramConsoleResponder(utgram);
    BaseRouter* router = new UtgramRouter(responder);
    CommandLineInterface* cli = new CommandLineInterface(router, responder);

#ifdef DEBUG

    cout << "Majors:" << endl;
    for (auto x : loader.loadMajors()) {
        printMajor(x);
    }

    cout << endl
         << "Courses:" << endl;
    for (auto x : loader.loadCourses(loader.loadMajors())) {
        printCourse(x);
    }

    cout << endl
         << "Members:" << endl;
    for (auto x : loader.loadAllMembers(loader.loadMajors())) {
        printMember(x);
    }

#endif // DEBUG

    cli->start();

    return 0;
}
