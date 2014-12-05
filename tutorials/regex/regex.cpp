#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int x = 0, y = 0;
string regexPattern;
string replacePattern;
regex r;
bool valid = false;
string words[10] = {"apple", "apex", "air", "annoy", "aardvark", "apply", "bot", "brains", "crayon", "master"};
vector<string> lines;

void keyAction( int ch )
{
    switch (ch)
    {
        case KEY_BACKSPACE:
            if (y == 0 && x > 0 && regexPattern.length() >= x)
            {
                regexPattern.erase(regexPattern.begin()+x-1);
                x--;
            }
            if (y == 1 && x > 0 && replacePattern.length() >= x)
            {
                replacePattern.erase(replacePattern.begin()+x-1);
                x--;
            } 
            break;
            case KEY_LEFT:
            if (x>0)
                x--;
            break;
        case KEY_RIGHT:
            if (y == 0 && x < regexPattern.length())
                x++;
            if (y == 1 && x < replacePattern.length())
                x++;
            break;
        case KEY_UP:
            y = 0;
            if (x > regexPattern.length())
                x = regexPattern.length();
            break;
        case KEY_DOWN:
            y = 1;
            if (x > replacePattern.length())
                x = replacePattern.length();
            break;
        default:
            if (ch >= 32 && ch < 128)
            {
                if (y == 0)
                    regexPattern.insert(regexPattern.begin()+x, ch);
                else
                    replacePattern.insert(replacePattern.begin()+x, ch);
                x++;
            }
    }
}

void drawScreen()
{
    clear();
    addstr(regexPattern.c_str());
    addstr("\n");
    addstr(replacePattern.c_str());
    addstr("\n");
    addstr("\n");
    try
    {
        r.assign(regexPattern.c_str(), regex::basic);
        valid = true;
    }
    catch (regex_error &e)
    {
        addstr("Invalid regex!");
        valid = false;
    }
    addstr("\n");
    addstr("\n");
    for (int i = 0; i < lines.size(); i++)
    {
        int color = 1;
        if (!valid)
        {
            addstr(lines[i].c_str());
            addstr("\n");
            continue;
        }
        smatch m;
        string s= lines[i];
        auto words_begin = sregex_iterator(s.begin(), s.end(), r);
        auto words_end = sregex_iterator();

        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_BLACK, COLOR_BLUE);

        for (sregex_iterator j = words_begin; j != words_end; j++)
        {
            m = *j;
            addstr(m.prefix().str().c_str());
            
            attron(COLOR_PAIR(color+1));
            addstr(m.str().c_str());
            attroff(COLOR_PAIR(color+1));
            
            color = 1 - color;
        }
        if (words_begin == words_end)
            addstr(s.c_str());
        else
            addstr(m.suffix().str().c_str());
        addstr("     ");
        if (replacePattern.length() != 0)
            addstr(regex_replace(s,r,replacePattern).c_str());
        addstr("\n");
        
    }
    move(y, x);
}

void getFile(string s)
{
    ifstream infile(s);
    for (string line; getline(infile, line);) 
    {
        lines.push_back(line);
    }
}

int main ()
{
    int ch=0;
    getFile("test1");
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    drawScreen();
    while(ch!= 'q')
    {
        ch = getch();
        keyAction(ch);
        drawScreen();
    }
    endwin();
    printf("end\n");
    return 0;
}
