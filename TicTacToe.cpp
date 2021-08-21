#include <iostream>
#include <fstream>

using namespace std;

// Check if any row is filled with the same character.
bool check_row(char a[][3], bool players[], char playerz[])
{
    // Iterating over all rows.
    for (int i = 0; i < 3; i++)
    {
        // Assume there is a row filled with the same character.
        bool line = true;
        // Looking for different characters or an empty cell in the i-th row.
        for (int j = 0; j < 2; j++)
            if (a[i][j] != a[i][j + 1] || a[i][j] == ' ' || a[i][j + 1] == ' ')
            {
                line = false;
                break;
            }
        // The case that there is a row filled with the same character.
        if (line)
        {
            // Determining the winner.
            if (a[i][0] == playerz[0])
                players[0] = true;
            else
                players[1] = true;
            // Ending the game.
            return true;
        }
    }
    // Resuming the game.
    return false;
}

// Check if any column is filled with the same character.
bool check_column(char a[][3], bool players[], char playerz[])
{
    // Iterating over all columns.
    for (int j = 0; j < 3; j++)
    {
        // Assume there is a column filled with the same character.
        bool line = true;
        // Looking for different characters or an empty cell in the j-th column.
        for (int i = 0; i < 2; i++)
            if (a[i][j] != a[i + 1][j] || a[i][j] == ' ' || a[i + 1][j] == ' ')
            {
                line = false;
                break;
            }
        // The case that there is a column filled with the same character.
        if (line)
        {
            // Determining the winner.
            if (a[0][j] == playerz[0])
                players[0] = true;
            else
                players[1] = true;
            // Ending the game.
            return true;
        }
    }
    // Resuming the game.
    return false;
}

// Check if the main diagonal is filled with the same character.
bool check_main_diagonal(char a[][3], bool players[], char playerz[])
{
    // Assume the main diagonal filled with the same character.
    bool line = true;
    // Looking for different characters or an empty cell in the main diagonal.
    for (int i = 0; i < 2; i++)
        if (a[i][i] != a[i + 1][i + 1] || a[i][i] == ' ' || a[i + 1][i + 1] == ' ')
        {
            line = false;
            break;
        }
    // The case that main diagonal filled with the same character.
    if (line)
    {
        // Determining the winner.
        if (a[0][0] == playerz[0])
            players[0] = true;
        else
            players[1] = true;
    }
    // Ending or resuming the game depends on the line value.
    return line;
}

// Check if the antidiagonal is filled with the same character.
bool check_antidiagonal(char a[][3], bool players[], char playerz[])
{
    // Assume the antidiagonal filled with the same character.
    bool line = true;
    // Looking for different characters or an empty cell in the antidiagonal.
    for (int i = 0; i < 2; i++)
        if (a[i][2 - i] != a[i + 1][1 - i] || a[i][2 - i] == ' ' || a[i + 1][1 - i] == ' ')
        {
            line = false;
            break;
        }
    // The case that antidiagonal filled with the same character.
    if (line)
    {
        // Determining the winner.
        if (a[0][2] == playerz[0])
            players[0] = true;
        else
            players[1] = true;
    }
    // Ending or resuming the game depends on the line value.
    return line;
}

// Check if any cell is empty or not.
bool check_fill(char a[][3])
{
    // Assume there is no empty cell.
    bool fill = true;
    // Iterating over all cells, looking for empty cell.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            if (a[i][j] == ' ')
            {
                fill = false;
                break;
            }
        // Don't check the remaining cells if any empty cell is found.
        if (!fill)
            break;
    }
    // Ending or resuming the game depends on the fill value.
    return fill;
}

// Cleaning the game board.
void clean_board(char a[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            a[i][j] = ' ';
}

// Printing the game board.
void print_board(char a[][3])
{
    cout << "+---+---+---+\n";
    for (int i = 0; i < 3; i++)
    {
        cout << '|';
        for (int j = 0; j < 3; j++)
            cout << ' ' << a[i][j] << ' ' << '|';
        cout << "\n+---+---+---+\n";
    }
}

// Making one step forward in the game.
bool play(char a[][3], int i, int j, bool turn, char playerz[])
{
    // The case that chosen row or column is out of range.
    if (i > 2 || j > 2 || i < 0 || j < 0)
    {
        cout << "Your chosen position is out of range.\n";
        return false;
    }
    // The case that chosen cell is empty.
    if (a[i][j] == ' ')
    {
        // Filling the chosen cell with proper character.
        if (turn)
            a[i][j] = playerz[0];
        else
            a[i][j] = playerz[1];
        return true;
    }
    // The case that chosen cell is filled.
    cout << "Your chosen position is filled with a character.\n";
    return false;
}

int main()
{

    char board_matrix[3][3]; // The matrix of the game board.
    bool players[2];         // The array that determines which player has won.
    char playerz[2];         // The character of each player.
    char command;            // Input command.

again:
    // No one has won yet, so initialize the array with false values.
    players[0] = false;
    players[1] = false;
    // Cleaning the board.
    clean_board(board_matrix);
    // Requesting for the input command from the user.
    cout << "Press 'p' to to start or press 'r' to show record or press 'q' to quit: ";
    cin >> command;

    // The case that user wants to play.
    if (command == 'p')
        goto start;
    else
    {
        // The case that user wants to quit the game.
        if (command == 'q')
            return 0;
        else
        {
            // The case that user wants to see the records.
            if (command == 'r')
            {
                // Open the records file.
                ifstream f("Records.txt");

                // Checking the existance of the records file.
                if (f.is_open())
                    // Print the previous records.
                    cout << f.rdbuf() << "\n";
                else // The case that no record exist.
                    cout << "There is no record.\n";
                // Closing the records file.
                f.close();
                goto again; // Going to the request section.
            }
            else // The case input command is invalid.
            {
                cout << "Wrong Code!"
                     << "\n";
                goto again; // Going to the request section.
            }
        }
    }
start: // Starting the game.

    // Requesting for the character of first player.
    cout << "Player 1 - Choose x or o to play: ";
    cin >> playerz[0]; // The character of first player.

    // Checking the correctness of first player.
    if (playerz[0] != 'o' && playerz[0] != 'x')
    {
        cout << "Wrong Character!\n";
        goto start;
    }

    // Set the character of the other player.
    if (playerz[0] == 'x')
        playerz[1] = 'o';
    else
        playerz[1] = 'x';

    bool turn = true; // Determine the turn in the game.
    int i, j;         // The chosen row and column from the player.

    while (true)
    {
        // Printing the game board in each step.
        print_board(board_matrix);
        while (true)
        {
            // Requesting for the row and column from the player.
            if (turn)
                cout << "Player 1 - ";
            else
                cout << "Player 2 - ";
            cout << "Choose Row:     ";
            cin >> i; // Assign the row.
            if (turn)
                cout << "Player 1 - ";
            else
                cout << "Player 2 - ";
            cout << "Choose Column:  ";
            cin >> j; // Assign the column.

            // Play the game with chosen cell and check...
            // if it is a valid move or not.
            if (play(board_matrix, i, j, turn, playerz))
            {
                // Reversing the turn.
                if (turn)
                    turn = false;
                else
                    turn = true;
                break;
            }
        }
        // Looking for the end of the game by checking the columns.
        if (check_column(board_matrix, players, playerz))
            break;
        // Looking for the end of the game by checking the rows.
        if (check_row(board_matrix, players, playerz))
            break;
        // Looking for the end of the game by checking the main diagonal.
        if (check_main_diagonal(board_matrix, players, playerz))
            break;
        // Looking for the end of the game by checking the antidiagonal.
        if (check_antidiagonal(board_matrix, players, playerz))
            break;
        // Looking fot the draw by checking all cells.
        if (check_fill(board_matrix))
            break;
    }

    FILE *R2;                       // File pointer.
    R2 = fopen("Records.txt", "a"); // Opening the record file
    print_board(board_matrix);      // // Printing the final game board.

    // The case that first player has won the game.
    if (players[0])
    {
        // Printing the result.
        cout << "+---------------------------------+\n"
             << "| Player1 (win) - (lose) Player 2 |\n"
             << "+---------------------------------+\n\n";
        // Recording the result.
        fprintf(R2, "\n%s", "+---------------------------------+");
        fprintf(R2, "\n%s", "| Player1 (win) - (lose) Player 2 |");
        fprintf(R2, "\n%s", "+---------------------------------+");
        fprintf(R2, "\n");
    }

    // The case that second player has won the game.
    else if (players[1])
    {
        // Printing the result.
        cout << "+----------------------------------+\n"
             << "| Player 1 (lose) - (win) Player 2 |\n"
             << "+----------------------------------+\n\n";
        // Recording the result.
        fprintf(R2, "\n%s", "+----------------------------------+");
        fprintf(R2, "\n%s", "| Player 1 (lose) - (win) Player 2 |");
        fprintf(R2, "\n%s", "+----------------------------------+");
        fprintf(R2, "\n");
    }

    // The case that the game is tied.
    else
    {
        // Printing the result.
        cout << "+---------------------------------+\n"
             << "| Player 1 (win) - (win) Player 2 |\n"
             << "+---------------------------------+\n\n";
        // Recording the result.
        fprintf(R2, "\n%s", "+---------------------------------+");
        fprintf(R2, "\n%s", "| Player 1 (win) - (win) Player 2 |");
        fprintf(R2, "\n%s", "+---------------------------------+");
        fprintf(R2, "\n");
    }

    // Closing the records file.
    fclose(R2);
    // Going to the request section.
    goto again;
}
