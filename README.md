# TicTacToe-AI

An unbeatable computer TicTacToe player implemented using the minimax algorithm along with alpha-beta pruning.

2 players: the maximizer and the minimizer
Maximizer tries to get the highest value possible
Minimizer tries to give the lowest possible value
Alpha-Beta pruning is used to reduce and cutoff some of the branches of the game decision tree that we don't need to evaluate.

Alpha-Minimum value the maximizing player will have to take
Beta-Maximum value the minimizing player will have to give
Alpha starts at negative infinity
Beta starts at positive infinity

Cut happens when beta<=alpha
Beta is only updated during Min player's move and Alpha is only updated during Max player's move.
