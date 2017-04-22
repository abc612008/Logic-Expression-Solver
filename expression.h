#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include "logic.h"
using namespace std;
enum class StatementError
{
    CalcError, BadStatement
};
class Expression
{
public:
    using ArgsMap = unordered_map<string, Logic>;
    Expression(string expression, bool isPostfix = false) :m_suffix(isPostfix?expression:toInfix(expression)) {}

    Logic calc(ArgsMap args);
    set<string> getVars();

private:
    static string toInfix(string suffix);
    string m_suffix;
};
