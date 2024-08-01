#include <ncurses.h>


void print_digit(WINDOW *win, int y, int x, int digit)
{
    switch (digit) 
    {
        case 0:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x, ACS_VLINE);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x, ACS_VLINE);
            mvwaddch(win, y + 2, x + 2, ACS_VLINE);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            break;
        case 1:
            mvwaddch(win, y, x + 2, ACS_VLINE);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x + 2, ACS_VLINE);
            mvwaddch(win, y + 3, x + 2, ACS_VLINE);
            break;
        case 2:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 2, x, ACS_LLCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_LRCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            break;
        case 3:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x, ACS_ULCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            break;
        case 4:
            mvwaddch(win, y, x, ACS_VLINE);
            mvwaddch(win, y, x + 2, ACS_VLINE);
            mvwaddch(win, y + 1, x, ACS_VLINE);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x, ACS_LTEE);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_PLUS);
            mvwaddch(win, y + 3, x + 2, ACS_VLINE);
            break;
        case 5:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x, ACS_LLCORNER);
            mvwaddch(win, y + 2, x, ACS_ULCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            break;
        case 6:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x, ACS_LLCORNER);
            mvwaddch(win, y + 2, x, ACS_ULCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            mvwaddch(win, y + 2, x, ACS_VLINE);
            mvwaddch(win, y + 2, x + 2, ACS_VLINE);
            break;
        case 7:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x + 2, ACS_VLINE);
            mvwaddch(win, y + 3, x + 2, ACS_VLINE);
            break;
        case 8:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x, ACS_VLINE);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x, ACS_ULCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            break;
        case 9:
            mvwaddch(win, y, x, ACS_ULCORNER);
            mvwaddch(win, y, x + 1, ACS_HLINE);
            mvwaddch(win, y, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 1, x, ACS_VLINE);
            mvwaddch(win, y + 1, x + 2, ACS_VLINE);
            mvwaddch(win, y + 2, x, ACS_ULCORNER);
            mvwaddch(win, y + 2, x + 1, ACS_HLINE);
            mvwaddch(win, y + 2, x + 2, ACS_URCORNER);
            mvwaddch(win, y + 3, x, ACS_LLCORNER);
            mvwaddch(win, y + 3, x + 1, ACS_HLINE);
            mvwaddch(win, y + 3, x + 2, ACS_LRCORNER);
            mvwaddch(win, y + 2, x + 2, ACS_VLINE);
            break;
        default:
            break;
    }
}

/**
#define DIGIT_0 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_VLINE ACS_ULCORNER ACS_URCORNER ACS_VLINE ACS_LLCORNER ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_1 ACS_VLINE ACS_VLINE ACS_VLINE ACS_VLINE ACS_VLINE
#define DIGIT_2 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_HLINE ACS_LRCORNER ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_3 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_HLINE ACS_LRCORNER ACS_HLINE ACS_HLINE ACS_URCORNER
#define DIGIT_4 ACS_ULCORNER ACS_HLINE ACS_URCORNER ACS_VLINE ACS_ULCORNER ACS_URCORNER ACS_LRCORNER ACS_LLCORNER ACS_HLINE ACS_URCORNER
#define DIGIT_5 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_LLCORNER ACS_HLINE ACS_ULCORNER ACS_URCORNER ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_6 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_LLCORNER ACS_VLINE ACS_ULCORNER ACS_URCORNER ACS_VLINE ACS_LLCORNER ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_7 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_HLINE ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_8 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_VLINE ACS_ULCORNER ACS_URCORNER ACS_VLINE ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_LRCORNER
#define DIGIT_9 ACS_ULCORNER ACS_HLINE ACS_HLINE ACS_URCORNER ACS_VLINE ACS_ULCORNER ACS_URCORNER ACS_HLINE ACS_LRCORNER

 */