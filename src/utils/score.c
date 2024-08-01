#include "../inc/tui_bonus.h"

int	read_best_score(void)
{
	int	fbest = open(FBEST, O_RDONLY);
	if (fbest < 0)
		return (-1);
	char	score_text[17];
	int		score_val;
	int		bytes_read = -1;
	bytes_read = read(fbest, score_text, 16);
	if (bytes_read < 0)
		return (-1);
	score_text[bytes_read] = 0;
	score_val = ft_atoi(score_text);
	close(fbest);
	return (score_val);
}

void	save_best_score(int best)
{
	int	fbest = open(FBEST, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fbest < 0)
		return ;
	char	*bscore_str = ft_itoa(best);
	if (!bscore_str)
		return ;
	write(fbest, bscore_str, ft_strlen(bscore_str));
	ft_free_ptr(bscore_str);
}
