#ifndef __JUG_H__
#define __JUG_H__
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Vertex
{
  public:
    string name;
    list<pair<int, int>> neighbors;
    Vertex(string name) : name(name) { }
    ~Vertex() { }
};

class Jug
{
  private:
    int Ca;
    int Cb;
    int N;
    int cfA; // fill A
    int cfB; // fill B
    int ceA; // empty A
    int ceB; // empty B
    int cpAB; // pour A to B
    int cpBA; // pour B to A
    vector<Vertex> graph;
  public:
    // Constructor
    Jug(int, int, int, int, int, int, int, int, int);
    ~Jug();
    Jug(const Jug&) = delete;
    Jug operator=(const Jug&) = delete;
    int solve(string&);
  private:
    bool checkInput() const; 
    bool checkTargetNum(const list<pair<int, int>>& ); 
    int String(vector<int>&, string&) const;
    int calculateCost(vector<int> steps);
    vector<int> attempt(); 
    int applyStep(int&, int&, const int&); 
    vector<int> traverse(int,vector<int>,list<std::pair<int, int>>); 
    bool checkCircular(int, int, list<pair<int, int>>); 
};

#endif