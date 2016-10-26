#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#define MEMORY_SIZE 32768
using namespace std;
unsigned char memory[MEMORY_SIZE];
char program[128000];
map<int, int> brackets;
int program_pos = 0;

bool isValidChar(const char& ch)
{
    return ch == '[' || ch == ']' || ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '.' || ch == ',';
}

void read_program()
{
    string line;
    getline(cin, line);
    while (line != "end")
    {
        for (auto& ch : line)
        {
            if (ch == '%')
                break;
            if (!isValidChar(ch))
                continue;
            program[program_pos] = ch;
            ++program_pos;
        }
        getline(cin, line);
    }
}

bool check_program()
{
    auto balance = 0;
    for (auto i = 0; i < program_pos; ++i)
    {
        if (program[i] == '[')
            ++balance;
        if (program[i] == ']')
            --balance;
        if (balance < 0)
            break;
    }
    return balance == 0;
}

void prepare_these_brackets()
{
    stack<int> opening_brackets;
    for (auto i = 0; i<program_pos; ++i)
    {
        if (program[i] == '[')
            opening_brackets.push(i);
        if (program[i] == ']')
        {
            auto o = opening_brackets.top();
            opening_brackets.pop();
            brackets[o] = i;
            brackets[i] = o;
        }
    }
}

void process_program()
{
    auto pointer = 0;
    for (auto pos = 0; pos<program_pos; ++pos)
    {
        auto command = program[pos];
        switch (command)
        {
        case '>':
            pointer = (pointer + 1) % (MEMORY_SIZE + 1);
            break;
        case '<':
            pointer = pointer == 0 ? MEMORY_SIZE : pointer - 1;
            break;
        case '+':
            ++memory[pointer];
            break;
        case '-':
            --memory[pointer];
            break;
        case '[':
            if (memory[pointer] == 0)
                pos = brackets[pos] - 1;
            break;
        case ']':
            if (memory[pointer] != 0)
                pos = brackets[pos] - 1;
            break;
        case ',':
            cin >> memory[pointer];
            break;
        default:
            cout << memory[pointer];
            break;
        }
    }
}

int main()
{
    while(true)
    {
        program_pos = 0;
        brackets.clear();
        memset(&memory, 0, MEMORY_SIZE);
        read_program();
        if (check_program())
        {
            prepare_these_brackets();
            process_program();
            cout << endl;
        }
        else
            cout << "COMPILE ERROR" << endl;
    }
}
