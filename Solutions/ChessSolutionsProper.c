#include <stdlib.h>
#include <assert.h>

/*
    This solution is more complex but solves both problems in a nicer way.

    Taken is just an array that records how many times that given piece can
    be taken.
    
    For example for;
        WHITE_QUEEN NO_PIECE
        BLACK_ROOK  BLACK_PAWN
    The WHITE_PLAYER taken array would look like;
             0        0
             1        1
    And the BLACK_PLAYER taken array would look like;
             2        0
             0        0
*/

#define NO_PIECE        (0)
#define WHITE_PAWN      (1)
#define BLACK_PAWN      (-1)
#define WHITE_ROOK      (2)
#define BLACK_ROOK      (-2)
#define WHITE_BISHOP    (3)
#define BLACK_BISHOP    (-3)
#define WHITE_KING      (4)
#define BLACK_KING      (-4)
#define WHITE_KNIGHT    (5)
#define BLACK_KNIGHT    (-5)
#define WHITE_QUEEN     (6)
#define BLACK_QUEEN     (-6)

#define WHITE_PLAYER    (1)
#define BLACK_PLAYER    (-1)

// Checks if there is any piece to the left
// noting that pieces block the path
void checkLeft(int player, int startX, int y, int size,
              int chessBoard[size][size], int taken[size][size]) {
    for (int i = startX - 1; i >= 0; i--) {
        if (player * chessBoard[i][y] < 0) {
            taken[i][y]++;
            break;
        } else if (chessBoard[i][y] != NO_PIECE) {
            break;
        }
    }
}

// Checks if there is any piece to the right
// noting that pieces block the path
void checkRight(int player, int startX, int y, int size,
               int chessBoard[size][size], int taken[size][size]) {
    for (int i = startX + 1; i < size; i++) {
        if (player * chessBoard[i][y] < 0) {
            taken[i][y]++;
            break;
        } else if (chessBoard[i][y] != NO_PIECE) {
            break;
        }
    }
}

// Checks if there is any piece down
// noting that pieces block the path
void checkDown(int player, int x, int startY, int size,
              int chessBoard[size][size], int taken[size][size]) {
    for (int i = startY - 1; i >= 0; i--) {
        if (player * chessBoard[x][i] < 0) {
            taken[x][i]++;
            break;
        } else if (chessBoard[x][i] != NO_PIECE) {
            break;
        }
    }
}

// Checks if there is any piece down
// noting that pieces block the path
void checkUp(int player, int x, int startY, int size,
            int chessBoard[size][size], int taken[size][size]) {
    for (int i = startY + 1; i < size; i++) {
        if (player * chessBoard[x][i] < 0) {
            taken[x][i]++;
            break;
        } else if (chessBoard[x][i] != NO_PIECE) {
            break;
        }
    }
}

/*
    That is going top left and bottom right
    i..e
    \
     \
    noting that pieces block the path
    There may be a piece in the top left part and bottom right so max of 2
    min of 0.
*/
void checkDiagonalAntiClockwise(int player, int startX, int startY, int size,
                  int chessBoard[size][size], int taken[size][size]) {
    for (int i = startX - 1, j = startY + 1; i >= 0 && j < size; i--, j++) {
        if (player * chessBoard[i][j] < 0) {
            taken[i][j]++;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    for (int i = startX + 1, j = startY - 1; i < size && j >= 0; i++, j--) {
        if (player * chessBoard[i][j] < 0) {
            taken[i][j]++;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
}

/*
    That is going top right and bottom left
    i.e.
     /
    /
    noting that pieces block the path
    There may be a piece in the top right part and bottom left so max of 2
    min of 0.
*/
void checkDiagonalClockwise(int player, int startX, int startY, int size,
                           int chessBoard[size][size], int taken[size][size]) {
    for (int i = startX + 1, j = startY + 1; i < size && j < size; i++, j++) {
        if (player * chessBoard[i][j] < 0) {
            taken[i][j]++;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    for (int i = startX - 1, j = startY - 1; i >= 0 && j >= 0; i--, j--) {
        if (player * chessBoard[i][j] < 0) {
            taken[i][j]++;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
}

// Checks if there is any piece in a given position
void checkPosition(int player, int x, int y, int size, int board[size][size],
                  int taken[size][size]) {
    if (x < size && x >= 0 && y < size && y >= 0 && board[x][y] * player < 0) {
        taken[x][y]++;
    }
}

// checks the weird knight movement (no pieces can block it)
void checkKnightMovement(int player, int startX, int startY, int size,
                        int board[size][size], int taken[size][size]) {
    checkPosition(player, startX + 2, startY + 1, size, board, taken);
    checkPosition(player, startX + 2, startY - 1, size, board, taken);
    checkPosition(player, startX - 2, startY + 1, size, board, taken);
    checkPosition(player, startX - 2, startY - 1, size, board, taken);

    checkPosition(player, startX + 1, startY + 2, size, board, taken);
    checkPosition(player, startX - 1, startY + 2, size, board, taken);
    checkPosition(player, startX + 1, startY - 2, size, board, taken);
    checkPosition(player, startX - 1, startY - 2, size, board, taken);
}

// builds up the taken array for a given piece
void piecesCanTake(int piece, int player, int x, int y, int size,
                  int chessBoard[size][size], int taken[size][size]) {
    int piece_white = piece * player;
    if (piece_white == WHITE_PAWN) {
        int new_y = y + -1 * player;
        if (new_y >= 0 && new_y < size) {
            // check out of bounds for our pawn
            if (x > 0 && chessBoard[x - 1][new_y] * player < 0) {
                taken[x - 1][new_y]++;
            }
            if (x < size - 1 && chessBoard[x + 1][new_y] * player < 0) {
                taken[x + 1][new_y]++;
            }
        }
    } else if (piece_white == WHITE_ROOK) {
        // move left
        checkLeft(player, x, y, size, chessBoard, taken);
        checkRight(player, x, y, size, chessBoard, taken);
        checkUp(player, x, y, size, chessBoard, taken);
        checkDown(player, x, y, size, chessBoard, taken);
    } else if (piece_white == WHITE_BISHOP) {
        checkDiagonalClockwise(player, x, y, size, chessBoard, taken);
        checkDiagonalAntiClockwise(player, x, y, size, chessBoard, taken);
    } else if (piece_white == WHITE_KING) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                checkPosition(player, x + i, y + j, size, chessBoard, taken);
            }
        }
    } else if (piece_white == WHITE_KNIGHT) {
        checkKnightMovement(player, x, y, size, chessBoard, taken);
    } else if (piece_white == WHITE_QUEEN) {
        checkLeft(player, x, y, size, chessBoard, taken);
        checkRight(player, x, y, size, chessBoard, taken);
        checkUp(player, x, y, size, chessBoard, taken);
        checkDown(player, x, y, size, chessBoard, taken);
        checkDiagonalClockwise(player, x, y, size, chessBoard, taken);
        checkDiagonalAntiClockwise(player, x, y, size, chessBoard, taken);
    }
}

int countMoves(int size, int chessBoard[size][size], int player) {
    int count = 0;
    // easiest way is just to use VLA's here (but I'm still cranky about it!)
    // you can do it using malloc but its a little more tricky to get it happy
    int taken[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            taken[i][j] = 0;
        }
    }

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            // if player == -1 then it multiplied by any
            // negative player piece > 0
            if (player * chessBoard[x][y] > 0) {
                // there is a piece here so find all the pieces it can take
                piecesCanTake(chessBoard[x][y], player, x, y, size,
                                       chessBoard, taken);
            }
        }
    }

    // count up sum of array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            count += taken[i][j];
        }
    }
    return count;
}

int countUniqueMoves(int size, int chessBoard[size][size], int player) {
    int count = 0;
    // easiest way is just to use VLA's here (but I'm still cranky about it!)
    // you can do it using malloc but its a little more tricky
    int taken[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            taken[i][j] = 0;
        }
    }

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            // if player == -1 then it multiplied by any
            // negative player piece > 0
            if (player * chessBoard[x][y] > 0) {
                // there is a piece here so find all the pieces it can take
                piecesCanTake(chessBoard[x][y], player, x, y, size,
                                       chessBoard, taken);
            }
        }
    }

    // count up only when > 0 this will ensure no piece is taken twice
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (taken[i][j] > 0) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    /*
        For example in the 2x2 board (note: 0, 0 is bottom left; 1, 1 is top right)

        WHITE_QUEEN NO_PIECE
        BLACK_ROOK  BLACK_PAWN

        The white player has 2 pieces they can take (rook or pawn using queen) so you would return 2 for both moves and unique moves
        The black player can take the queen with either the black rook or with the pawn (presume the black starts on the 'bottom' side) so you would also return 2 moves but only 1 unique move.
    */

    int a[2][2] = { {BLACK_ROOK, WHITE_QUEEN}, {BLACK_PAWN, NO_PIECE} };
    assert(countMoves(2, a, WHITE_PLAYER) == 2);
    assert(countMoves(2, a, BLACK_PLAYER) == 2);
    assert(countUniqueMoves(2, a, WHITE_PLAYER) == 2);
    assert(countUniqueMoves(2, a, BLACK_PLAYER) == 1);

    /*
        WHITE_PAWN(1)   WHITE_PAWN(2)   BLACK_ROOK    WHITE_KING
        BLACK_PAWN(1)   BLACK_PAWN(2)   BLACK_KNIGHT  NO_PIECE
        NO_PIECE        WHITE_BISHOP    NO_PIECE      NO_PIECE
        WHITE_ROOK      WHITE_KNIGHT    WHITE_QUEEN   BLACK_KING

        White can take a total of 5 pieces with 13 total moves;
        - black pawn(1) with white pawn(2), white_rook, white_knight, white_bishop
        - black pawn(2) with white pawn(1)
        - black_rook with white_king
        - black_knight with white_bishop, white_queen, white_king, white_pawn(2), white_knight
        - black_king with white_queen and white_bishop
        Black can take a total of 5 pieces with 7 total moves;
        - white pawn(1) with black pawn(2) and black knight
        - white pawn(2) with black rook, black pawn(1)
        - white king with black_rook
        - white queen with black king
        - white knight with black knight
    */
    int b[4][4] = { {WHITE_ROOK, NO_PIECE, BLACK_PAWN, WHITE_PAWN},
                    {WHITE_KNIGHT, WHITE_BISHOP, BLACK_PAWN, WHITE_PAWN},
                    {WHITE_QUEEN, NO_PIECE, BLACK_KNIGHT, BLACK_ROOK},
                    {BLACK_KING, NO_PIECE, NO_PIECE, WHITE_KING} };
    assert(countMoves(4, b, WHITE_PLAYER) == 12);
    assert(countMoves(4, b, BLACK_PLAYER) == 7);
    assert(countUniqueMoves(4, b, WHITE_PLAYER) == 5);
    assert(countUniqueMoves(4, b, BLACK_PLAYER) == 5);
    return 0;
}
