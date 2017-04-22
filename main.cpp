#include <iostream>
#include <string>
#include <set>
#include "solver.h"

inline std::ostream& operator << (std::ostream& os, Logic rhs)
{
    if (rhs == Logic::True) os << "True";
    else if (rhs == Logic::False) os << "False";
    else if (rhs == Logic::Unknown) os << "Any";
    return os;
}

int main()
{
    while (true)
    {
        cout << "Input expression: ";
        string str;
        cin >> str;
        if (str == "EXIT") break;
        try
        {
            auto solution = SATSolver(Expression(str));
            if (solution.getResults().empty())
            {
                cout << "Cannot solve!" << endl;
                continue;
            }
            auto varnames = solution.getVarnames();
            for (auto& res : solution.getResults())
            {
                for (auto& vn : varnames)
                    cout << vn << ":" << res[vn] << "\t";
                cout << endl;
            }
        }
        catch (StatementError err)
        {
            if (err == StatementError::BadStatement) cout << "Error: BadStatement"<<endl;
            if (err == StatementError::CalcError) cout << "Error: CalcError" << endl;
        }
    }
}