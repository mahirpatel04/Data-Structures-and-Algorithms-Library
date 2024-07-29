#include "Jug.h"
#include <iostream>
using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA){
    // Pushback the Vertices into the graph
    graph.push_back(Vertex("cfA"));
    graph.push_back(Vertex("cfB"));
    graph.push_back(Vertex("ceA"));
    graph.push_back(Vertex("ceB"));
    graph.push_back(Vertex("cpAB"));
    graph.push_back(Vertex("cpBA"));
    // Set the neighbors for the 6 vertexes
    graph[0].neighbors = {{1, cfB}, {4, cpAB}};
    graph[1].neighbors = {{0, cfA}, {5, cpBA}};
    graph[2].neighbors = {{1, cfB}, {3, ceB}, {5, cpBA}};
    graph[3].neighbors = {{0, cfA}, {2, ceA}, {4, cpAB}};
    graph[4].neighbors = {{0, cfA}, {3, ceB}, {5, cpBA}};
    graph[5].neighbors = {{0, cfA}, {1, cfB}, {2, ceA}, {3, ceB}, {4, cpAB}};
}

Jug::~Jug() {}

int Jug::solve(string& solution) {
    // Check if input is bad and return -1 if it is
    if (!checkInput()) {
        solution= "";
        return -1;
    }
    // Attempt a path
    vector<int> path = attempt();
    // If path is not empty then create the string and return 1
    if (!path.empty()){
        String(path, solution);
        return 1;
    }
    // Otherwise return 0 with empty solution
    solution= "";
    return 0;
}


bool Jug::checkInput() const{
    // Check is all the weightages are valid
    return (cfB >= 0 && cpAB >= 0 && cpBA >= 0 && ceA >= 0 && ceB >= 0 && N >= 0 && cfA >= 0) && (Ca > 0 && Ca <= Cb) && (N <= Cb && Cb <= 1000);
}

bool Jug::checkTargetNum(const list<pair<int, int>>& route) {
    // Make sure that the amounts are good
    int jugA = route.back().first;
    int jugB = route.back().second;
    return (jugA == 0) && (jugB == N);
}


int Jug::String(vector<int>& steps, string& solution) const{
    string result;
    int totalCost = 0;
    for (const int& step : steps) {
        // For all the steps add to the result
        switch (step) {
            case 0:
                totalCost += cfA;
                result += "fill A\n";
                break;
            case 1:
                totalCost += cfB;
                result += "fill B\n";
                break;
            case 2:
                totalCost += ceA;
                result += "empty A\n";
                break;
            case 3:
                totalCost += ceB;
                result += "empty B\n";
                break;
            case 4:
                totalCost += cpAB;
                result += "pour A B\n";
                break;
            case 5:
                totalCost += cpBA;
                result += "pour B A\n";
                break;
            default:
                break;
        }
    }
    // The solution is the result with the addition of string success and the total cost
    result = result + "success " + to_string(totalCost);
    solution = result;
    return totalCost;
}

int Jug::calculateCost(vector<int>steps) {
    // Initialize totalCost to be 0
    int totalCost = 0;
    int size = steps.size();
    // For every step, add the corresponding weightage to total cost
    for (int i = 0; i < size; ++i) {
        int step = steps[i];
        if (step == 0) {
            totalCost =totalCost + cfA;
        }
        else if (step == 1) {
            totalCost =totalCost + cfB;
        }
        else if (step == 2) {
            totalCost =totalCost + ceA;
        }
        else if (step == 3) {
            totalCost =totalCost + ceB;
        }
        else if (step == 4) {
            totalCost =totalCost + cpAB;
        }
        else if (step == 5) {
            totalCost =totalCost + cpBA;
        }
    }
    return totalCost;
}

vector<int> Jug::attempt() {
    // Create two route lists and vector of steps
    list<pair<int, int>> aRoute;
    list<pair<int, int>> bRoute;
    vector<int> aSteps;
    vector<int> bSteps;
    aRoute.push_back(pair<int, int>(0, 0));
    bRoute.push_back(pair<int, int>(0, 0));
    // Traverse through both ways and get the corresponding steps
    aSteps = traverse(0, aSteps, aRoute);
    bSteps = traverse(1, bSteps, bRoute);
    // If both steps are empty return empty vector of empty steps
    if (aSteps.empty() && bSteps.empty())  {
        vector<int> emptySteps;
        return emptySteps; 
    }
    // If either is empty then return the one that is not empty
    else if (aSteps.empty() || bSteps.empty()) {
        if (aSteps.empty()) return bSteps;
        else return aSteps;
    }
    // Return the route that has LESSER cost (the main part of Djikstra's)
    else {
        int aTotalCost = calculateCost(aSteps);
        int bTotalCost = calculateCost(bSteps);
        if (aTotalCost < bTotalCost) return aSteps; 
        else return bSteps; 
    }
}

int Jug::applyStep(int& amountforA, int& amountforB, const int& stepIndex) {
    // For each set the corresponding specific values for weightages/amount
    if (graph.at(stepIndex).name== "ceB") {
        amountforB = 0;
    }
    else if (graph.at(stepIndex).name == "ceA") {
        amountforA = 0;
    }
    else if (graph.at(stepIndex).name == "cpBA") {
        amountforA =amountforA+ amountforB;
        amountforB = 0;
        if (amountforA > Ca) {
            amountforB = amountforA - Ca;
            amountforA = Ca;
        }
    }
    
    else if (graph.at(stepIndex).name == "cfA") {
        amountforA = Ca;
    }
    else if (graph.at(stepIndex).name== "cpAB") {
        amountforB += amountforA;
        amountforA = 0;
        if (amountforB > Cb) {
            amountforA = amountforB - Cb;
            amountforB = Cb;
        }
    }
    // Return the same index
    return stepIndex;
}

vector<int> Jug::traverse(int stepIndex, vector<int> steps, list<pair<int, int>> route) {
    // Create the vector which will hold the best possible steps
    vector<int> bestSteps;
    int amountforA;
    int amountforB;
    int stepTaken;

    if (checkTargetNum(route)) return steps;
    // Iterate through the neighbors and check the different routes
    for (const auto& neighbor : graph.at(stepIndex).neighbors) {
        amountforA = route.back().first;
        amountforB = route.back().second;
        stepTaken = applyStep(amountforA, amountforB, neighbor.first);
        // If it isn't circular then push back another step and get the best step possible
        if (!checkCircular(amountforA, amountforB, route)) {
            steps.push_back(stepTaken);
            route.push_back(pair<int, int>(amountforA, amountforB));
            vector<int> currentSteps = traverse(stepTaken, steps, route);
            if (bestSteps.empty() || calculateCost(currentSteps) < calculateCost(bestSteps)) {
                bestSteps = currentSteps;
            }
            // Pop the last step and route
            steps.pop_back();
            route.pop_back();
        }
    }
    // Return the best step
    return bestSteps;
}

bool Jug::checkCircular(int amountforA, int amountforB, list<pair<int, int>> route) {
    // Iterate through the routes and if the amounts are the same then we have a cycle so return true
    for (unsigned int i = 0; i < route.size(); i++) {
        list<pair<int, int>>::iterator it = next(route.begin(), i);
        if (it->first == amountforA && it->second == amountforB) {
            return true;
        }
    }
    // Otherwise just return false
    return false;
}
