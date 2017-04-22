#include "expression.h"
#include <stack>


Logic Expression::calc(ArgsMap args)
{
    stack<Logic> vals;
    string valNameNow;
    for (auto chr : m_suffix)
    {
        switch (chr)
        {
        case '&':
        {
            Logic o1 = vals.top();
            vals.pop();
            Logic o2 = vals.top();
            vals.pop();
            vals.push(o1&&o2);
            break;
        }
        case '|':
        {
            Logic o1 = vals.top();
            vals.pop();
            Logic o2 = vals.top();
            vals.pop();
            vals.push(o1 || o2);
            break;
        }
        case '!':
        {
            Logic o = vals.top();
            vals.pop();
            vals.push(!o);
            break;
        }
        case ' ':
        {
            if (valNameNow=="") continue;
            if (args.find(valNameNow) == args.cend()) vals.push(Logic::Unknown);
            else vals.push(args[valNameNow]);
            valNameNow = "";
            break;
        }
        default:
        {
            valNameNow += chr;
        }
        }
    }
    if(vals.size() != 1) throw StatementError::CalcError;
    return vals.top();
}

set<string> Expression::getVars()
{
    set<string> ret;
    stack<bool> vals;
    string valNameNow;
    for (auto chr : m_suffix)
    {
        switch (chr)
        {
        case '&':
        case '|':
        case '!':
        case ' ':
            if (valNameNow == "") continue;
            ret.insert(valNameNow);
            valNameNow = "";
            break;
        default:
            valNameNow += chr;
        }
    }
    return ret;
}

string Expression::toInfix(string postfix)
{
    auto getPriority = [](char chr)
    {
        switch (chr)
        {
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        }
        return 0;
    };
    string ret = "";
    stack<char> opers;
    string valNameNow;
    for (auto chr : postfix)
    {
        switch (chr)
        {
        case '(':
            if (valNameNow != "")
            {
                ret += valNameNow + " ";
                valNameNow = "";
            }
            opers.push(chr);
            break;
        case ')':
        {
            if (valNameNow != "")
            {
                ret += valNameNow + " ";
                valNameNow = "";
            }
            while (opers.top() !='(')
            {
                if (opers.empty()) throw StatementError::BadStatement;
                ret += opers.top();
                opers.pop();
            }
            opers.pop(); //pop '('
            break;
        }
        case '&':
        case '|':
        case '!':
        {
            if (valNameNow != "")
            {
                ret += valNameNow + " ";
                valNameNow = "";
            }
            while (!opers.empty() && getPriority(opers.top()) >= getPriority(chr))
            {
                ret += opers.top();
                opers.pop();
            }
            opers.push(chr);
            break;
        }
        default:
            valNameNow += chr;
        }
    }
    if(valNameNow!="") ret += valNameNow + " ";
    while (!opers.empty())
    {
        ret += opers.top();
        opers.pop();
    }
    return ret;
}
