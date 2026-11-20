#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName;
};


int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}


enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}


string ChoiceName(enGameChoice Choice)
{
    string arrChoices[3] = { "Stone", "Paper", "Scissors" };

    return arrChoices[Choice - 1];
}


string WinnerName(enWinner Winner)
{
    string arrWinner[3] = { "Player", "Computer", "Draw" };

    return arrWinner[Winner - 1];
}


enGameChoice ReadPlayerChoice()
{
    short Choice;

    do
    {
        cout << "\nYour Choice: [1] Stone [2] Paper [3] Scissors? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}


short ReadHowManyRounds()
{
    short Rounds;

    do
    {
        cout << "\nHow Many Rounds Do You Want To Play? ";
        cin >> Rounds;

    } while (Rounds < 1);

    return Rounds;
}


enWinner WhoWonRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:

        return (RoundInfo.ComputerChoice == enGameChoice::Paper)
            ? enWinner::Computer : enWinner::Player;

    case enGameChoice::Paper:

        return (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            ? enWinner::Computer : enWinner::Player;

    case enGameChoice::Scissors:

        return (RoundInfo.ComputerChoice == enGameChoice::Stone)
            ? enWinner::Computer : enWinner::Player;
    }

    return enWinner::Draw;
}


enWinner WhoWonGame(short PlayerWins, short ComputerWins)
{
    if (PlayerWins > ComputerWins)
        return enWinner::Player;

    else if (ComputerWins > PlayerWins)
        return enWinner::Computer;

    else
        return enWinner::Draw;
}


void SetScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;

    case enWinner::Draw:
        system("color 6F");
        break;
    }
}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n";

    cout << "\nPlayer Choice   : " << ChoiceName(RoundInfo.PlayerChoice);

    cout << "\nComputer Choice : " << ChoiceName(RoundInfo.ComputerChoice);

    cout << "\nRound Winner    : " << RoundInfo.WinnerName;

    cout << "\n_________________________________________\n";
}


stRoundInfo PlayOneRound(short RoundNumber)
{
    stRoundInfo RoundInfo;

    RoundInfo.RoundNumber = RoundNumber;

    RoundInfo.PlayerChoice = ReadPlayerChoice();

    RoundInfo.ComputerChoice = GetComputerChoice();

    RoundInfo.Winner = WhoWonRound(RoundInfo);

    RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

    PrintRoundResults(RoundInfo);

    SetScreenColor(RoundInfo.Winner);

    system("pause");

    return RoundInfo;
}


void PrintGameResults(stGameResults GameResults)
{
    cout << "\n\n";
    cout << "\t\t_________________________________________\n";
    cout << "\t\t\t       +++ GAME OVER +++\n";
    cout << "\t\t_________________________________________\n";

    cout << "\n\t\tGame Rounds        : " << GameResults.GameRounds;

    cout << "\n\t\tPlayer Win Times   : " << GameResults.PlayerWinTimes;

    cout << "\n\t\tComputer Win Times : " << GameResults.ComputerWinTimes;

    cout << "\n\t\tDraw Times         : " << GameResults.DrawTimes;

    cout << "\n\t\tFinal Winner       : " << GameResults.WinnerName;

    cout << "\n\t\t_________________________________________\n\n";
}


stGameResults PlayGame(short HowManyRounds)
{
    stGameResults GameResults;

    GameResults.GameRounds = HowManyRounds;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        system("color 07");

        cout << "\n\nRound [" << GameRound << "] begins:\n";

        stRoundInfo RoundInfo = PlayOneRound(GameRound);

        if (RoundInfo.Winner == enWinner::Player)
            GameResults.PlayerWinTimes++;

        else if (RoundInfo.Winner == enWinner::Computer)
            GameResults.ComputerWinTimes++;

        else
            GameResults.DrawTimes++;
    }

    GameResults.GameWinner = WhoWonGame(
        GameResults.PlayerWinTimes,
        GameResults.ComputerWinTimes
    );

    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    system("color 07");

    PrintGameResults(GameResults);

    return GameResults;
}


void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");
        system("color 07");

        short HowManyRounds = ReadHowManyRounds();

        PlayGame(HowManyRounds);

        cout << "\nDo You Want To Play Again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

    system("color 07");

    cout << "\nThanks For Playing!\n";
}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
