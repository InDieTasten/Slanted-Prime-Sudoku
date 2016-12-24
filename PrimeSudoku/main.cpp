#include <iostream>
#include <algorithm>
#include <vector>


bool isPatternValid(std::vector<short> board, std::vector<size_t> pattern)
{
	std::vector<short> counts(10);

	for (auto position : pattern)
	{
		if (board[position] != -1)
		{
			counts[board[position]]++;

			if (counts[board[position]] > 2)
			{
				// if we have a determinated value more than twice, the pattern is to be claimed invalid
				return false;
			}
		}
	}

	return true;
}

std::vector<size_t> invertPattern(std::vector<size_t> pattern)
{
	std::vector<size_t> invertedPattern;
	for (size_t i = 0; i < 40; i++)
	{
		if (std::find(pattern.begin(), pattern.end(), i) == pattern.end())
		{
			invertedPattern.push_back(i);
		}
	}
	return invertedPattern;
}

bool check_primes(std::vector<short> board)
{
	std::vector<size_t> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	std::vector<std::pair<size_t, size_t>> cells
	{
		std::make_pair(0, 1),
			std::make_pair(2, 3),
			std::make_pair(4, 5),
			std::make_pair(6, 7),
			std::make_pair(9, 8),
			std::make_pair(11, 10),
			std::make_pair(13, 12),
			std::make_pair(15, 14)
	};

	for (auto pair : cells)
	{
		short first = board[pair.first];
		short second = board[pair.second];

		if (first != -1 && second != -1)
		{
			short value = first * 10 + second;

			if (std::find(primes.begin(), primes.end(), value) == primes.end())
			{
				// not a prime
				return false;
			}
		}
	}

	return true;
}

std::vector<std::vector<size_t>> patterns;

void initializePatterns()
{
	patterns.push_back(std::vector<size_t> { 0, 1, 10, 11, 12, 13, 14, 15, 16, 19, 20, 25, 26, 27, 28, 33, 34, 35, 36, 39 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
	patterns.push_back(std::vector<size_t> { 0, 1, 2, 3, 4, 5, 14, 15, 16, 17, 20, 21, 22, 27, 28, 29, 30, 35, 36, 37 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
	patterns.push_back(std::vector<size_t> { 16, 15, 14, 26, 27, 35, 28, 36, 37, 38, 39, 34, 32, 31, 30, 22, 23, 6, 7, 18 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
	patterns.push_back(std::vector<size_t> { 19, 12, 13, 33, 34, 26, 27, 35, 17, 4, 5, 29, 30, 22, 23, 31, 36, 37, 38, 39 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
	patterns.push_back(std::vector<size_t> { 16, 0, 1, 35, 28, 20, 21, 29, 18, 8, 9, 31, 32, 24, 25, 33, 36, 37, 38, 39 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
	patterns.push_back(std::vector<size_t> { 2, 3, 20, 21, 17, 28, 29, 36, 37, 30, 34, 39, 38, 19, 33, 32, 24, 25, 10, 11 });
	patterns.push_back(invertPattern(patterns[patterns.size() - 1]));
}

bool check_patterns(std::vector<short> board)
{
	for (auto pattern : patterns)
	{
		if (!isPatternValid(board, pattern))
		{
			return false;
		}
	}
	return true;
}

bool check_all(std::vector<short> board)
{
	return check_primes(board)
		&& check_patterns(board);
}

size_t guesses = 0;
std::vector<std::vector<short>> solutions;

void printBoard(std::vector<short> board)
{
	std::cout << "Solution #" << solutions.size() << ": ";
	for (size_t i = 0; i < board.size(); i++)
	{
		std::cout << board[i] << "|";
	}
	std::cout << std::endl;
}

bool optimisticGuess(std::vector<short> board)
{
	guesses++;

	// check, if everythings filled
	auto missing = std::find(board.begin(), board.end(), -1);
	if (missing == board.end())
	{
		solutions.push_back(board);
		printBoard(board);

		return true;
	}
	else
	{
		size_t currentCell = missing - board.begin();

		// take guesses for allowed digits
		for (short guess = 0; guess < 10; guess++)
		{
			board[currentCell] = guess;
			if (check_all(board))
			{
				optimisticGuess(board);
			}
		}
		return false;
	}
}

int main()
{
	initializePatterns();

	std::vector<short> globalBoard(40, -1);
	globalBoard[36] = 0;
	globalBoard[11] = 2;
	globalBoard[33] = 3;
	globalBoard[39] = 5;
	globalBoard[25] = 6;
	globalBoard[26] = 6;
	globalBoard[29] = 7;

	std::cout << "Starting game!" << std::endl;

	if (!check_all(globalBoard))
	{
		std::cout << "Invalid board to begin with!!! :C" << std::endl;
	}

	if (!optimisticGuess(globalBoard))
	{
		std::cout << "No solution found" << std::endl;
	}

	getchar();
	return EXIT_SUCCESS;
}
