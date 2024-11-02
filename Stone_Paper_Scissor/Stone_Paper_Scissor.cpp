#include <iostream>
#include <cstdlib>
#include<string>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice ComputerChoice;
	enGameChoice PlayerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResult
{
	short RoundNumbers = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int from, int to)
{
	// to Get Choice Computer
	int Random = rand() % (to - from + 1) + from;
	return Random;
}

int HowManyRound()
{
	int Round = 0;
	do
	{
		cout << "Enter Number Round Want to Play [1 to 10]? ";
		cin >> Round;

	} while (Round < 1 || Round > 10);

	return Round;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player" ,"Computer", "No Winner" };

	return arrWinnerName[Winner - 1];
}

enWinner WhoWinnerRound(stRoundInfo RoundInfo)
{

	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{

	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;

}

string choiceName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone" ,"Paper", "Scissors" };

	return arrGameChoice[Choice - 1];
}

void SetWinnerScreanColor(enWinner Winner)
{
	switch (Winner)
	{
		case enWinner::Player:
		{
			system("color 2F"); // turn screen to Green 
			break;
		}
		case enWinner::Computer:
		{
			system("color 4F");// turn screen to Red 
			cout << "\a";
			break;
		}
		case enWinner::Draw:
		{
			system("color 6F");// turn screen to Yellow 
			break;
		}

	}

}

void printRoundResult(stRoundInfo RonudInfo)
{
	cout << "------------------Round [" << RonudInfo.RoundNumber << "]-------------------\n";
	cout << "PLayer Choice   : "  << choiceName(RonudInfo.PlayerChoice) << endl;
	cout << "Computer Choice : "  << choiceName(RonudInfo.ComputerChoice) << endl;
	cout << "Round Winner    : [" << RonudInfo.WinnerName << "]\n";
	cout << "----------------------------------------------\n";

	SetWinnerScreanColor(RonudInfo.Winner);
}

enWinner WhoWinnerGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else if (PlayerWinTimes < ComputerWinTimes)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}

stGameResult FillGameResult(int RoundNumber, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;
	GameResult.RoundNumbers = RoundNumber;
	GameResult.PlayerWinTimes = PlayerWinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWinnerGame(PlayerWinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);
	return GameResult;
}

enGameChoice ReadPlayerChoice()
{
	short playerChoice = 1;
	do
	{
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?: ";
		cin >> playerChoice;

	} while (playerChoice < 1 || playerChoice > 3);

	return (enGameChoice)playerChoice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

stGameResult PlayGame(short HowManyRound)
{
	stRoundInfo RoundInfo;

	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	
	for (short i = 1; i <= HowManyRound; i++)
	{
		cout << "\nRound [" << i << "] begins:\n";
		RoundInfo.RoundNumber = i;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinnerRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
		{
			PlayerWinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}

		printRoundResult(RoundInfo);
	}

	return FillGameResult(HowManyRound, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void showGameOverScreen()
{
	cout << "\t\t\t_____________________________________________________________\n";
	cout << "\t\t\t\t\t +++ G a m e  O v e r  +++\n";
	cout << "\t\t\t_____________________________________________________________\n\n";
}

void ShowFinalGameScreen(stGameResult GameResult)
{
	cout << "\t\t\t____________________[Game Results ]__________________________\n";
	cout << "\t\t\tGame Rounds        : " << GameResult.RoundNumbers << endl;
	cout << "\t\t\tPlayer Won Times   : " << GameResult.PlayerWinTimes << endl;
	cout << "\t\t\tComputer Won Times : " << GameResult.ComputerWinTimes << endl;
	cout << "\t\t\tDraw Times         : " << GameResult.DrawTimes << endl;
	cout << "\t\t\tFinal Winner       : " << GameResult.WinnerName << endl;
	cout << "\t\t\t_____________________________________________________________\n";

	SetWinnerScreanColor(GameResult.GameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StratGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(HowManyRound());
		showGameOverScreen();
		ShowFinalGameScreen(GameResult);

		cout << "\t\t\tDo you Want play Again? Y/N ?: ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StratGame();

	cin.get();
}













/*
//////////////////// M Y  S O L V E /////////////////////////
#include <iostream>
#include<string>
#include <cstdlib>
#include<Windows.h>
using namespace std;
enum enPLaying  { Stone = 1 , Paper = 2, Scissor = 3 };
struct StWhoWin
{
	int CounterPlayer1 = 0;
	int CounterComputer = 0;
	int CounterDraw = 0;
};
int HowManyRounds()
{
	int number = 0;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> number;

	} while (!(number >= 1 && number <= 10));

	return number;
}
int RandomComputerChoice(int from , int to)
{
	int random = rand() % (to - from + 1) + from;
	return random;
}
int ComputerChoice()
{
	int computerPlay = RandomComputerChoice(1, 3);

	return computerPlay;
}
void PLayingFromComputerOrUser()
{	

	StWhoWin Winner;
	int NumberRound = HowManyRounds();
	int Player;
	int Computer;
	for (int i = 1; i <= NumberRound; i++)
	{
		Computer = ComputerChoice();
		cout << "Round [" << i << "] begins..:)\n\n";
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?: ";
		cin >> Player;
		if (Player == Computer && enPLaying::Stone)
		{
			system("color 6f");
			Winner.CounterDraw++;
			cout << "______________Round["<<i<<"]______________\n";
			cout << "Player1 Choice : " << "Stone\n";
			cout << "Computer choice: " << "Stone\n";
			cout << "Round Winner   : " << "[NO Winner]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == Computer && enPLaying::Paper)
		{
			system("color 6f");
			Winner.CounterDraw++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Paper\n";
			cout << "Computer choice: " << "Paper\n";
			cout << "Round Winner   : " << "[NO Winner]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == Computer && enPLaying::Scissor)
		{
			system("color 6f");
			Winner.CounterDraw++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Scissor\n";
			cout << "Computer choice: " << "Scissor\n";
			cout << "Round Winner   : " << "[NO Winner]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player==enPLaying::Paper &&Computer == enPLaying::Stone)
		{
			system("color 2f");
			cout << "\a";
			Winner.CounterPlayer1++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Paper\n";
			cout << "Computer choice: " << "Stone\n";
			cout << "Round Winner   : " << "[PLayer1]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == enPLaying::Scissor && Computer == enPLaying::Paper)
		{
			system("color 2f");
			cout << "\a";
			Winner.CounterPlayer1++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Scissor\n";
			cout << "Computer choice: " << "Paper\n";
			cout << "Round Winner   : " << "[PLayer1]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == enPLaying::Stone && Computer == enPLaying::Scissor)
		{
			system("color 2f");
			cout << "\a";
			Winner.CounterPlayer1++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Stone\n";
			cout << "Computer choice: " << "Scissor\n";
			cout << "Round Winner   : " << "[PLayer1]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == enPLaying::Stone && Computer == enPLaying::Paper)
		{
			system("color 4f");
			Winner.CounterComputer++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Stone\n";
			cout << "Computer choice: " << "Paper\n";
			cout << "Round Winner   : " << "[Computer]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == enPLaying::Paper && Computer == enPLaying::Scissor)
		{
			system("color 4f");
			Winner.CounterComputer++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Paper\n";
			cout << "Computer choice: " << "Scissor\n";
			cout << "Round Winner   : " << "[Computer]\n";
			cout << "____________________________________\n\n";
		}
		else if (Player == enPLaying::Scissor && Computer == enPLaying::Stone)
		{
			system("color 4f");
			Winner.CounterComputer++;
			cout << "______________Round[" << i << "]______________\n";
			cout << "Player1 Choice : " << "Scissor\n";
			cout << "Computer choice: " << "Stone\n";
			cout << "Round Winner   : " << "[Computer]\n";
			cout << "____________________________________\n\n";
		}
		else
		{
			break;
		}
	}

	//--------------------------------------------

	string FinalWinner = WhoWinPlay();

	cout << "\t\t\t_____________________________________________________________\n";
	cout << "\t\t\t\t\t +++ G a m e  O v e r  +++\n";
	cout << "\t\t\t_____________________________________________________________\n\n";
	cout << "\t\t\t____________________[Game Results ]__________________________\n";
	cout << "\t\t\tGame Rounds        : " << NumberRound << endl;
	cout << "\t\t\tPlayer Won Times   : " << Winner.CounterPlayer1 << endl;
	cout << "\t\t\tComputer Won Times : " << Winner.CounterComputer << endl;
	cout << "\t\t\tDraw Times         : " << Winner.CounterDraw << endl;
	cout << "\t\t\tFinal Winner       : " << FinalWinner << endl;
	cout << "\t\t\t_____________________________________________________________\n\n";
}
string WhoWinPlay()
{
	StWhoWin Winner;
	
	if (Winner.CounterComputer < Winner.CounterPlayer1)
	{
		Sleep(400);
		system("color 2f");

		return "Player1";
	}
	else if (Winner.CounterComputer > Winner.CounterPlayer1)
	{
		Sleep(400);
		system("color 4f");
		
		return "Computer";
	}
	else if (Winner.CounterComputer == Winner.CounterPlayer1)
	{
		Sleep(400);
		system("color 6f");

		return "No Winner";
	}
}
void StatrGame()
{
	char Choice;
	do
	{
		PLayingFromComputerOrUser();
		cout << "\t\t\tDo you Want to Play again? Y/N?  ";
		cin >> Choice;
		
		if (Choice == 'y' || Choice == 'Y')
		{
			system("cls");
			system("color 0f");
		}
		else
		{
			return;
		}
	} while (Choice == 'Y' || Choice == 'y');
}
int main()
{

	srand((unsigned)time(NULL));

	StatrGame();
   

	cin.get();
	return 0;
}
*/
