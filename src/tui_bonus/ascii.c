{
    char *digit0[] = {
    " ┏┓ ",
    " ┃┃ ",
    " ┗┛ "
};

char *digit1[] = {
    " ┓ ",
    " ┃ ",
    " ┻ "
};

char *digit2[] = {
    " ┏┓ ",
    " ┏┛ ",
    " ┗━ "
};

char *digit3[] = {
    " ┏┓ ",
    "  ┫ ",
    " ┗┛ "
};

char *digit4[] = {
    " ┳┓ ",
    " ┃┃ ",
    " ┗┛ ",
    "    "
};

char *digit5[] = {
    " ┏━ ",
    " ┃┏ ",
    " ┗┛ ",
    "    "
};

char *digit6[] = {
    " ┏━ ",
    " ┃┏ ",
    " ┻┛ ",
    "    "
};

char *digit7[] = {
    " ┏┓ ",
    "  ┃ ",
    "  ┛ ",
    "    "
};

char *digit8[] = {
    " ┏┓ ",
    " ┃━┃",
    " ┗┛ ",
    "    "
};

char *digit9[] = {
    " ┏┓ ",
    " ┃┃ ",
    " ┗┫ ",
    "    "
};

}

{
    #include <stdio.h>

char *digit0[] = {
    "╔══╗",
    "║  ║",
    "║  ║",
    "╚══╝"
};

char *digit1[] = {
    "═╗",
    " ║",
    " ║",
    " ║"
};

char *digit2[] = {
    "╔══╗",
    "   ║",
    "╔══╝",
    "╚══╝"
};

char *digit3[] = {
    "╔══╗",
    "   ║",
    "   ║",
    "╚══╝"
};

char *digit4[] = {
    "║   ║",
    "║═══║",
    "    ║",
    "    ║"
};

char *digit5[] = {
    "╔══╗",
    "║   ",
    "╚══╗",
    "═══╝"
};

char *digit6[] = {
    "╔══╗",
    "║   ",
    "║══╗",
    "╚══╝"
};

char *digit7[] = {
    "╔══╗",
    "   ║",
    "   ║",
    "   ║"
};

char *digit8[] = {
    "╔═══╗",
    "║   ║",
    "║═══║",
    "╚═══╝"
};

char *digit9[] = {
    "╔═══╗",
    "║   ║",
    "╚═══╗",
    "    ║"
};

char **digits[] = {digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9};

void print_digit(int digit) {
    if (digit >= 0 && digit <= 9) {
        for (int i = 0; i < 4; i++) {
            printf("%s\n", digits[digit][i]);
        }
    } else {
        printf("Invalid digit\n");
    }
}

int main() {
    // Example: Print digit 3
    print_digit(3);
    
    return 0;
}

/* 
    ::  __   ___    ____    _  _     _____     __    ______    ___     ___     ___  
    :: /_ | |__ \  |___ \  | || |   | ____|   / /   |____  |  / _ \   / _ \   / _ \ 
    ::  | |    ) |   __) | | || |_  | |__    / /_       / /  | (_) | | (_) | | | | |
    ::  | |   / /   |__ <  |__   _| |___ \  | '_ \     / /    > _ <   \__, | | | | |
    ::  | |  / /_   ___) |    | |    ___) | | (_) |   / /    | (_) |    / /  | |_| |
    ::  |_| |____| |____/     |_|   |____/   \___/   /_/      \___/    /_/    \___/  
*/