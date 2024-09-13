#include <iostream>
#include <string>
#include <vector>

const int ROOT = 0;
const int ROOT_FATHER = -2;
const int NOT_FOUND = 1;
const int NO_CHILD_YET = -1;

const std::string LEAF = "|__";
const std::string OPEN_ANCESTOR = "|  ";
const std::string CLOSE_ANCESTOR = "   ";

struct Node {
    std::string name;
    std::vector<int> children;
    int number;
    int father;
    int lastChild;
    bool isOpen;
};

int findIndex(std::vector<Node>& nodes, int number) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].number == number) {
            return i;
        }
    }
    return NOT_FOUND;
}

bool goToRoot(std::vector<Node>& nodes, int number, std::string& createdLine, int maxDepth, int currDepth) {
    int thisNodeFather = nodes[findIndex(nodes, number)].father;
    if (thisNodeFather == ROOT) {
        return true;
    }
    else if (currDepth >= maxDepth) {
        return false;
    }
    int thisNodeGrandFather = nodes[findIndex(nodes, thisNodeFather)].father;
    if (nodes[findIndex(nodes, thisNodeGrandFather)].isOpen) {
        createdLine.insert(0, OPEN_ANCESTOR);
    }
    else {
        createdLine.insert(0, CLOSE_ANCESTOR);
    }
    return goToRoot(nodes, nodes[findIndex(nodes, number)].father, createdLine, maxDepth, currDepth + 1);
}

void checkParentClose(std::vector<Node>& nodes, int number) {
    int fatherNumber = nodes[findIndex(nodes, number)].father;
    if (nodes[findIndex(nodes, fatherNumber)].lastChild == number) {
        nodes[findIndex(nodes, fatherNumber)].isOpen = false;
    }
}

void printLine(std::vector<Node>& nodes, int number, int maxDepth) {
    std::string line = "";
    if (goToRoot(nodes, number, line, maxDepth, 1) == false) {
        return;
    }
    line += LEAF + nodes[findIndex(nodes, number)].name + "\n";
    std::cout << line;
    checkParentClose(nodes, number);
}

void draw(std::vector<Node>& nodes, int number, int maxDepth) {
    if (number != ROOT) {
        printLine(nodes, number, maxDepth);
    }
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].father == number) {
            draw(nodes, nodes[i].number, maxDepth);
        }
    }
}

void findChildNodes(std::vector<Node>& nodes) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].father != ROOT_FATHER) {
            int fatherIndex = findIndex(nodes, nodes[i].father);
            nodes[fatherIndex].children.push_back(nodes[i].number);
            if (nodes[fatherIndex].lastChild < nodes[i].number) {
                nodes[fatherIndex].lastChild = nodes[i].number;
            }
        }
    }
}

std::vector<Node> readInput(int inputLines) {
    std::vector<Node> result;
    Node root{.number = ROOT,
              .father = ROOT_FATHER,
              .lastChild = NO_CHILD_YET,
              .isOpen = true};
    result.push_back(root);
    for (int i = 0; i < inputLines; i++) {
        std::string name;
        int fatherNumber;
        std::cin >> name >> fatherNumber;
        Node node{.name = name,
                  .number = i + 1,
                  .father = fatherNumber,
                  .lastChild = NO_CHILD_YET,
                  .isOpen = true};
        result.push_back(node);
    }
    findChildNodes(result);
    return result;
}

int main() {
    int inputLines, maxDepth;
    std::cin >> inputLines >> maxDepth;
    std::vector<Node> nodes = readInput(inputLines);
    draw(nodes, ROOT, maxDepth);
}
