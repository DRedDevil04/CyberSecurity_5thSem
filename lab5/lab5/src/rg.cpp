#include <iostream>
#include <vector>

using namespace std;

class Employee {
public:
    int salary;
    vector<int> subordinates;

    Employee(int sal) : salary(sal) {}
};

void dfs(int u, const vector<Employee>& employees, vector<bool>& visited, vector<int>& result,
         long long& totalSalary, int& totalCount) {
    visited[u] = true;
    totalSalary += employees[u].salary;
    totalCount++;

    long long subordinateSalary = 0;
    int subordinateCount = 0;

    for (int v : employees[u].subordinates) {
        if (!visited[v]) {
            long long subSal = 0;
            int subCnt = 0;
            dfs(v, employees, visited, result, subSal, subCnt);
            subordinateSalary += subSal;
            subordinateCount += subCnt;
        }
    }

    if (subordinateCount > 0) {
        double averageSubordinateSalary = (double)subordinateSalary / subordinateCount;
        if (employees[u].salary < averageSubordinateSalary) {
            result.push_back(u);
        }
    }
}

vector<int> findManagersWithLowerSalary(const vector<Employee>& employees) {
    vector<int> result;
    vector<bool> visited(employees.size(), false);

    for (int i = 0; i < employees.size(); i++) {
        if (!visited[i]) {
            long long totalSalary = 0;
            int totalCount = 0;
            dfs(i, employees, visited, result, totalSalary, totalCount);
        }
    }

    return result;
}

int main() {
    // Example usage:

    // Create employees
    Employee e0(100);
    Employee e1(90);
    Employee e2(120);
    Employee e3(80);
    Employee e4(70);

    // Define subordinates
    e0.subordinates = {1, 2};  // Employee 0 has subordinates 1 and 2
    e1.subordinates = {3};     // Employee 1 has subordinate 3
    e2.subordinates = {4};     // Employee 2 has subordinate 4

    // Create the employee list
    vector<Employee> employees = {e0, e1, e2, e3, e4};

    // Find managers with a lower salary than the average of their subordinates
    vector<int> result = findManagersWithLowerSalary(employees);

    // Print results
    for (int manager : result) {
        cout << "Manager with lower salary: Employee " << manager << endl;
    }

    return 0;
}
