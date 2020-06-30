#include <bits/stdc++.h>

using namespace std;

#define WIN 500
#define	DRAW 0
#define LOSS -500
#define AI 'O'
#define Player 'X'
#define empty '-'

void game_state(int state)
{
	if (WIN == state)
        cout <<"WIN"<< endl;
	else if (DRAW == state)
        cout <<"DRAW"<< endl;
	else if (LOSS == state)
        cout <<"LOSS"<< endl;
}

// 3ROW + 3COL + 2DIAG
vector<vector<pair<int, int> > > winning_states;

void print_board(char board[3][3])
{
	cout<<"\n ";
	cout<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<"\n";
	cout<<"------------"<<"\n ";
	cout<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<"\n";
	cout<<"------------"<<"\n ";
	cout<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<"\n";
}

// Find free spaces
vector<pair<int, int> > get_legal_moves(char board[3][3])
{
	vector<pair<int, int> > legal_moves;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]!=AI && board[i][j]!=Player)
			{
				legal_moves.push_back(make_pair(i, j));
			}
		}
	}
	return legal_moves;
}

bool occupied(char board[3][3], pair<int, int> pos)
{
	vector<pair<int, int> > legal_moves=get_legal_moves(board);
	for (int i=0;i<legal_moves.size();i++)
	{
		if(pos.first==legal_moves[i].first && pos.second==legal_moves[i].second)
			return false;
	}
	return true;
}

// Get all positions occupied by given player
vector<pair<int, int> > get_occupied_positions(char board[3][3], char marker)
{
	vector<pair<int, int> > occupied_positions;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if (marker == board[i][j])
			{
				occupied_positions.push_back(make_pair(i, j));
			}
		}
	}
	return occupied_positions;
}

bool filled(char board[3][3])
{
	vector<pair<int, int> > legal_moves = get_legal_moves(board);
	if (legal_moves.size()==0)
		return true;
	else
		return false;
}

bool is_won(vector<pair<int, int> > occupied_positions)
{
	bool game_won;
	for (int i = 0; i < winning_states.size(); i++)
	{
		game_won = true;
		vector<pair<int, int> > curr_win_state = winning_states[i];
		for (int j = 0; j < 3; j++)
		{
			if (find(occupied_positions.begin(), occupied_positions.end(), curr_win_state[j]) == occupied_positions.end())
			{
				game_won = false;
				break;
			}
		}
		if (game_won)
			break;
	}
	return game_won;
}

char get_opponent(char marker)
{
	char opponent;
	if (marker == Player)
		opponent = AI;
	else
		opponent = Player;
	return opponent;
}

// Check if someone has won or lost
int get_board_state(char board[3][3], char marker)
{
	char opponent=get_opponent(marker);
	vector<pair<int, int> > occupied_positions=get_occupied_positions(board, marker);
	bool won=is_won(occupied_positions);
	if (won)
	{
		return WIN;
	}
	occupied_positions=get_occupied_positions(board, opponent);
	bool lost=is_won(occupied_positions);
	if (lost)
	{
		return LOSS;
	}
	bool full=filled(board);
	if (full)
	{
		return DRAW;
	}
	return DRAW;
}

// Minimax with alpha beta pruning
pair<int, pair<int, int> > minimax(char board[3][3], char marker, int alpha, int beta, int depth)
{
	pair<int, int> best_move = make_pair(-1, -1);
	int best_score = (marker == AI) ? LOSS : WIN;
    // If terminal (leaf) return best
	if (filled(board) || DRAW != get_board_state(board, AI))
	{
		best_score = get_board_state(board, AI);
		return make_pair(best_score, best_move);
	}

	vector<pair<int, int> > legal_moves = get_legal_moves(board);
	for (int i = 0; i < legal_moves.size(); i++)
	{
		pair<int, int> curr_move = legal_moves[i];
		board[curr_move.first][curr_move.second]=marker;
		// Maximizer
		if (marker==AI)
		{
			int score=minimax(board, Player, alpha, beta, depth+1).first;
			if (best_score<score)
			{
				best_score=score - depth * 10; //Decrease with depth because winning earlier is better
				best_move=curr_move;
                //check for pruning
				alpha = max(alpha, best_score);
				board[curr_move.first][curr_move.second] = empty;
				if (beta <= alpha)
					break;
			}
		}
		// Minimizer
		else
		{
			int score = minimax(board, AI, alpha, beta, depth+1).first;
			if (best_score > score)
			{
				best_score = score + depth * 10; //Decrease with depth because winning earlier is better
				best_move = curr_move;
				//check for pruning
				beta = min(beta, best_score);
				board[curr_move.first][curr_move.second] = empty;
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		board[curr_move.first][curr_move.second] = empty;//Undo the move
	}
	return make_pair(best_score, best_move);
}

bool game_over(char board[3][3])
{
	if (filled(board))
		return true;
	if (DRAW != get_board_state(board, AI))
		return true;
	return false;
}

int main()
{
    vector<pair <int, int> >v;
    //ROWS
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            v.clear();
            for(int k=0;k<3;k++)
            {
                v.push_back(make_pair(j, k));
            }
            winning_states.push_back(v);
        }
    }
    //COLUMNS
    for(int i=3;i<6;i++)
    {
        for(int j=0;j<3;j++)
        {
            v.clear();
            for(int k=0;k<3;k++)
            {
                v.push_back(make_pair(k, j));
            }
            winning_states.push_back(v);
        }
    }
    //DIAGONAL
    v.clear();
    for(int i=0;i<3;i++)
        v.push_back(make_pair(i, i));
    winning_states.push_back(v);
    //ANTI-DIAGONAL
    v.clear();
    for(int i=0;i<3;i++)
        v.push_back(make_pair(i, (2-i)));
    winning_states.push_back(v);

	char board[3][3]={" "};
	cout<<"$$$$$ Tic Tac Toe AI $$$$$"<<"\n";
	cout<<"Player = X\t AI = O"<<"\n";
    int choice;
    cout<<"1.Player Starts \n2.AI starts \nEnter Choice : ";
    cin>>choice;
    if(choice==2)
    {
        pair<int, pair<int, int> > ai_move = minimax(board, AI, LOSS, WIN, 0);
		board[ai_move.second.first][ai_move.second.second]=AI;
        print_board(board);
    }
    else
        print_board(board);

	while (!game_over(board))
	{
		int row, col;
		cout<<"Choose Row: ";
		cin>>row;
		cout<<"Choose Col: ";
		cin>>col;
		row--;
		col--;
		cout<<"\n";
		if (occupied(board, make_pair(row, col)))
		{
			cout<<"The position ("<<(row+1)<<", "<<(col+1)<<") is occupied. Try again..."<<"\n";
			continue;
		}
		else
		{
			board[row][col]=Player;
		}
		pair<int, pair<int, int> > ai_move = minimax(board, AI, LOSS, WIN, 0);
		board[ai_move.second.first][ai_move.second.second]=AI;
		print_board(board);
	}
	cout<<"GAME OVER"<<"\n";
	int player_state = get_board_state(board, Player);
	cout<<"PLAYER ";
	game_state(player_state);
	return 0;
}
