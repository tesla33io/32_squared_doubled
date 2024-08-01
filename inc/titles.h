
#ifndef TITLES_H
# define TITLES_H

# include <wchar.h>
# include <ncurses.h>

typedef enum
{
    TITLE_SMALL,
    TITLE_BIG,
    TITLE_SIZE,
} e_titleType;

typedef struct s_title {
    e_titleType type;
    wchar_t **titleText;
} t_title;

extern wchar_t *titleBigLines[];
extern wchar_t *titleSmallLines[];
extern t_title titles[];
void    displayGameTitle(WINDOW *win, e_titleType type, int maxWidth, int y_pading);


#endif // TITLES_H

/**
 * 

--   _,  _, . ,  _,  ,   _, . , ._, ._, __,  _, 
--  '_) |.| |_| (_) /|  '_) |_| |_  (_   /  (_) 
--  /_. |_|   | (_) .|. ._)   | ._) (_) /     | 
--                                              


--  __  _     _    __     __ _  __ _ 
--   _)/ \\|_|(_)/| __)|_||_ |_   /(_|
--  /__\_/  |(_) | __)  |__)|_) /  _|



                                         
 .:::.:    .::          .::       .:     
.:    .: .::  .::     . .::    .::  .::  
    .::.::     .::   .: .::   .::     .: 
  .::  .::      .::.::  .::     .:: .:   
.::     .::    .::.:::: .: .::.::     .::
.:::::::  .:::          .::     .::::    
                                         


 */
