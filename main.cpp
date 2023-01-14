#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include "string.h"
#include <sstream>

using namespace std;

int Priority(string c)
{
    if (c[0] == '+' || c[0] == '-')
        return 1;
    else if (c[0] == '*' || c[0] == '/')
        return 2;
    else return 0;
}

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

vector <string> delSpecialChar(string text, char del = ' ')
{
    vector <string> arrResult;
    text = removeSpaces(text);
    string result = "";
    for(int i = 0; i < text.length(); i++)
    {
        if( 
            (text[i] == '-' || text[i] =='+') && 
            (i+1) < text.length() && 
            (text[i+1] >= '0' && text[i+1] <= '9') &&
            (i-1) >= 0 &&
            Priority(&text[i-1])
        )
        {
            result += text[i];
        }
        else if(text[i] >= '0' && text[i] <= '9')
        {
            result += text[i];
        }
        else
        {
            if(result != "")
            {
                arrResult.push_back(result);
            }
            string s;
            s.push_back(text[i]);
            arrResult.push_back(s);
            result = "";
        }
    }
    if(result != "") arrResult.push_back(result);
    return arrResult;
}

bool isNum(string text)
{
    if(atoi(text.c_str()) == 0)
    {
        if(text[0] == '0')
        {
            return true;
        }
    }
    else if(atoi(text.c_str()) != 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool isValidExpression(vector <string> text)
{
    vector <string> operand;
    vector <string> operation;
    stack <string> bracket;
    for(int i = 0; i < text.size(); i++)
    {
        if(isNum(text[i])) operand.push_back(text[i]);
        else if(Priority(text[i]) != 0) operation.push_back(text[i]);
        else if(text[i] == "(") 
        {
            bracket.push(text[i]);
        }
        else if(text[i] == ")")
        {
            if(bracket.empty()) return false;
            else
            {
                bracket.pop();
            }
        }
        else
        {
            return false;
        }
    }
    if(operand.size() - 1 != operation.size()) return false;
    return (bracket.empty()) ? true : false;
}

string polishNotation(string text)
{
    vector <string> output;
    vector <string> input;
    stack <string> S;
    stack <string> S1;
    input = delSpecialChar(text);
    if(isValidExpression(input))
    {
        for(int i = 0; i < input.size(); i++)
        {
            if(isNum(input[i]))
            {
                output.push_back(input[i]);
            }
            else if(Priority(input[i]) != 0)
            {
                if(!S.empty())
                {
                    string op = S.top();
                    if(Priority(input[i]) <= Priority(op) && Priority(op) != 0)
                    {
                        output.push_back(op);
                        S.pop();
                        S.push(input[i]);
                    }
                    else
                    {
                        S.push(input[i]);
                    }
                }
                else S.push(input[i]);
            }
            else if(input[i][0] == '('){
                S.push(input[i]);
            }
            else if(input[i][0] == ')') 
            {
                string ch = S.top();
                while(ch[0] != '(')
                {
                    output.push_back(ch);
                    S.pop();
                    ch = S.top();
                }
                S.pop();
            }
        }
        while(!S.empty())
        {
            string ch = S.top();
            output.push_back(ch);
            S.pop();
        }
    
        for(int i = 0; i < output.size(); i++)
        {
            if(isNum(output[i])) S1.push(output[i]);
            else
            {
                float a = atof(S1.top().c_str());
                S1.pop();
                float b = atof(S1.top().c_str());
                S1.pop();
                if(output[i][0] == '+') 
                {
                    float r = (float)a+b;
                    string sttr;
                    stringstream ss;
                    ss << r;
                    ss >> sttr;
                    S1.push(sttr);
                }
                else if (output[i][0] == '-')
                {
                    float r = (float)b-a;
                    string sttr;
                    stringstream ss;
                    ss << r;
                    ss >> sttr;
                    S1.push(sttr);
                }
                else if (output[i][0] == '*')
                {
                    float r = (float)a*b;
                    string sttr;
                    stringstream ss;
                    ss << r;
                    ss >> sttr;
                    S1.push(sttr);
                }
                else if (output[i][0] == '/')
                {
                    if(a == 0) return "You can not divide by zero in your expression";
                    float r = (float)b/a;
                    string sttr;
                    stringstream ss;
                    ss << r;
                    ss >> sttr;
                    S1.push(sttr);
                };
            }
        }
        return S1.top();
    }
    else
    {
        return "The expression is invalid";
    }
}

int main()
{
    string text = " ((10 * (6 / ((9 + 3) * -11))) + 17) + 5";
    cout << polishNotation(text);
    return 0;
}