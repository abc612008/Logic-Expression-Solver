#pragma once
#include "expression.h"
#include <vector>
#include <set>
using namespace std;

class SATSolver
{
public:
    SATSolver(Expression exp)
    {
        auto vars=exp.getVars();
        for (auto& var : vars) varnames.push_back(var);
        _solve(exp, Expression::ArgsMap(), 0);
    };
    vector<Expression::ArgsMap> getResults() const
    {
        return results;
    }
    vector<string> getVarnames() const
    {
        return varnames;
    }

private:
    vector<Expression::ArgsMap> results;
    vector<string> varnames;

    void __solve(Expression exp, Expression::ArgsMap args, int depth)
    {
        switch (exp.calc(args))
        {
        case Logic::Unknown:
            _solve(exp, args, depth + 1);
            break;
        case Logic::True:
            results.push_back(args);
            break;
        }
    }

    void _solve(Expression exp, Expression::ArgsMap args, int depth)
    {
        string key = varnames[depth];
        args[key] = Logic::True;
        __solve(exp, args, depth);
        args[key] = Logic::False;
        __solve(exp, args, depth);
    }
};