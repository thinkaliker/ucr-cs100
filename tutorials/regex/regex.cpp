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
string hint;
string prompt;


vector<string> lines;
vector<vector<string>> coloredLines;
vector<string> replaced;
vector<vector<string>> captures;

bool extended = false;
bool global = false;
bool replaceMode = false;
bool finished = false;

void mouseAction(int mx, int my)
{
    if (my == 2)
    {
        if (mx < 18)
            extended = !extended;
        else if (mx > 22 && mx < 36)
            global = !global;
        else if (mx > 38 && mx < 57)
            replaceMode = !replaceMode;
    }
    else if (my == 0)
    {
        y = 0;
        x = mx-16;
        if (mx-16 > regexPattern.length())
            x = regexPattern.length();
    }
    else if (my == 1)
    {
        y = 1;
        x = mx-16;
        if (mx-16 > replacePattern.length())
            x = replacePattern.length();
    }
}

void keyAction( int ch )
{
    switch (ch)
    {
        case KEY_MOUSE:
            MEVENT event;
            getmouse(&event);
            mouseAction(event.x,event.y);
            break;
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
    move(0,0);
    addstr("Regex Pattern: ");
    move(0,16);
    addstr(regexPattern.c_str());
    move(1,0);
    addstr("Replace With:  ");
    move(1,16);
    addstr(replacePattern.c_str());
    move(2,0);
    addstr("Extended Regex [ ]    Global Tag [ ]    Replace Mode [ ]");
    
    if (extended)
        mvaddch(2,16,'X');
    if (global)
        mvaddch(2,34,'X');
    if (replaceMode)
        mvaddch(2,54,'X');
    

    move(3,0);
    addstr(hint.c_str());
    for (int i = 0; i < lines.size(); i++)
    {
        int color = 1;

        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_BLACK, COLOR_BLUE);
        
        move(5+i,0);    
        for (int j = 0; j < coloredLines[i].size(); j++)
        {
            if (j%2!=0)
            {
                color = 1 - color;
                attron(COLOR_PAIR(color+1));
            }
            addstr(coloredLines[i][j].c_str()); 
            if (j%2!=0)
                attroff(COLOR_PAIR(color+1));
        }
        move(5+i, 50); 
        if (replaceMode)
        {
            addstr(replaced[i].c_str());
        }
    }
    move(y, x+16);
}

void performRegex()
{
    replaced.clear();
    hint = "";
    bool valid = true;
    regex r;
    try
    {  
        if (extended)
        {
            r.assign(regexPattern.c_str(), regex::extended);
        }
        else
        {
            if (regexPattern.back() != '\\')
                r.assign(regexPattern.c_str(), regex::basic);
            else
                valid = false;
        }
    }
    catch (regex_error &e)
    {
        valid = false;
    }
    if (!valid)
        hint = "Invalid regex!";

    for (int i = 0; i < lines.size(); i++)
    {
        coloredLines[i].clear();
        if (!valid)
        {
            replaced.push_back("");
            coloredLines[i].push_back(lines[i]);
            continue;
        }
        smatch m;
        string s= lines[i];
        auto words_begin = sregex_iterator(s.begin(), s.end(), r);
        auto words_end = sregex_iterator();

        for (sregex_iterator j = words_begin; j != words_end; j++)
        {
            m = *j;
            coloredLines[i].push_back(m.prefix().str());
            coloredLines[i].push_back(m.str());
            if (!global)
                break;
        }
        if (words_begin == words_end)
            coloredLines[i].push_back(s);
        else
            coloredLines[i].push_back(m.suffix().str());

        replaced.push_back(regex_replace(s,r,replacePattern));
    }
}

void getFile(string s)
{
    ifstream infile(s);
    for (string line; getline(infile, line);) 
    {
        lines.push_back(line);
        coloredLines.push_back(vector<string>());
    }
}

void initCurses()
{
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();
    mousemask(BUTTON1_PRESSED, NULL);
    keypad(stdscr, TRUE);
}


int main ()
{
    int ch = 0;
    getFile("test1");
    initCurses();
    while(ch!= 'q')
    {
        keyAction(ch);
        performRegex();
        drawScreen();
        ch = getch();
    }
    endwin();
    printf("end\n");
    return 0;
}
