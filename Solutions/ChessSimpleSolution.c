#include <stdlib.h>
#include <assert.h>

/*
    Check out ChessProperSolution if you want a solution that covers both
    properly.  This one is just a bit easier to understand
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
int checkLeft(int player, int startX, int y, int size,
              int chessBoard[size][size]) {
    for (int i = startX - 1; i >= 0; i--) {
        if (player * chessBoard[i][y] < 0) {
            return 1;
        } else if (chessBoard[i][y] != NO_PIECE) {
            return 0;
        }
    }
    return 0;
}

// Checks if there is any piece to the right
// noting that pieces block the path
int checkRight(int player, int startX, int y, int size,
               int chessBoard[size][size]) {
    for (int i = startX + 1; i < size; i++) {
        if (player * chessBoard[i][y] < 0) {
            return 1;
        } else if (chessBoard[i][y] != NO_PIECE) {
            return 0;
        }
    }
    return 0;
}

// Checks if there is any piece down
// noting that pieces block the path
int checkDown(int player, int x, int startY, int size,
              int chessBoard[size][size]) {
    for (int i = startY - 1; i >= 0; i--) {
        if (player * chessBoard[x][i] < 0) {
            return 1;
        } else if (chessBoard[x][i] != NO_PIECE) {
            return 0;
        }
    }
    return 0;
}

// Checks if there is any piece up
// noting that pieces block the path
int checkUp(int player, int x, int startY, int size,
            int chessBoard[size][size]) {
    for (int i = startY + 1; i < size; i++) {
        if (player * chessBoard[x][i] < 0) {
            return 1;
        } else if (chessBoard[x][i] != NO_PIECE) {
            return 0;
        }
    }
    return 0;
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
int checkDiagonalAntiClockwise(int player, int startX, int startY, int size,
                  int chessBoard[size][size]) {
    int count = 0;
    for (int i = startX - 1, j = startY + 1; i >= 0 && j < size; i--, j++) {
        if (player * chessBoard[i][j] < 0) {
            count += 1;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    for (int i = startX + 1, j = startY - 1; i < size && j >= 0; i++, j--) {
        if (player * chessBoard[i][j] < 0) {
            count += 1;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    return count;
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
int checkDiagonalClockwise(int player, int startX, int startY, int size,
                           int chessBoard[size][size]) {
    int count = 0;
    for (int i = startX + 1, j = startY + 1; i < size && j < size; i++, j++) {
        if (player * chessBoard[i][j] < 0) {
            count += 1;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    for (int i = startX - 1, j = startY - 1; i >= 0 && j >= 0; i--, j--) {
        if (player * chessBoard[i][j] < 0) {
            count += 1;
            break;
        } else if (chessBoard[i][j] != NO_PIECE) {
            break;
        }
    }
    return count;
}

// Checks if there is any piece in a given position
int checkPosition(int player, int x, int y, int size, int board[size][size]) {
    if (x < size && x >= 0 && y < size && y >= 0 && board[x][y] * player < 0) {
        return 1;
    } else {
        return 0;
    }
}

// checks the weird knight movement (no pieces can block it)
int checkKnightMovement(int player, int startX, int startY, int size,
                        int board[size][size]) {
    int count = 0;
    count += checkPosition(player, startX + 2, startY + 1, size, board);
    count += checkPosition(player, startX + 2, startY - 1, size, board);
    count += checkPosition(player, startX - 2, startY + 1, size, board);
    count += checkPosition(player, startX - 2, startY - 1, size, board);

    count += checkPosition(player, startX + 1, startY + 2, size, board);
    count += checkPosition(player, startX - 1, startY + 2, size, board);
    count += checkPosition(player, startX + 1, startY - 2, size, board);
    count += checkPosition(player, startX - 1, startY - 2, size, board);
    return count;
}

// sees how many pieces a given piece can take
int piecesCanTake(int piece, int player, int x, int y, int size, int chessBoard[size][size]) {
    int piece_white = piece * player;
    int count = 0;
    if (piece_white == WHITE_PAWN) {
        int new_y = y + -1 * player;
        if (new_y >= 0 && new_y < size) {
            // check out of bounds for our pawn
            if (x > 0 && chessBoard[x - 1][new_y] * player < 0) {
                count++;
            }
            if (x < size - 1 && chessBoard[x + 1][new_y] * player < 0) {
                count++;
            }
        }
    } else if (piece_white == WHITE_ROOK) {
        // move left
        count += checkLeft(player, x, y, size, chessBoard);
        count += checkRight(player, x, y, size, chessBoard);
        count += checkUp(player, x, y, size, chessBoard);
        count += checkDown(player, x, y, size, chessBoard);
    } else if (piece_white == WHITE_BISHOP) {
        count += checkDiagonalClockwise(player, x, y, size, chessBoard);
        count += checkDiagonalAntiClockwise(player, x, y, size, chessBoard);
    } else if (piece_white == WHITE_KING) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                count += checkPosition(player, x + i, y + j, size, chessBoard);
            }
        }
    } else if (piece_white == WHITE_KNIGHT) {
        count += checkKnightMovement(player, x, y, size, chessBoard);
    } else if (piece_white == WHITE_QUEEN) {
        count += checkLeft(player, x, y, size, chessBoard);
        count += checkRight(player, x, y, size, chessBoard);
        count += checkUp(player, x, y, size, chessBoard);
        count += checkDown(player, x, y, size, chessBoard);
        count += checkDiagonalClockwise(player, x, y, size, chessBoard);
        count += checkDiagonalAntiClockwise(player, x, y, size, chessBoard);
    }
    return count;
}

// counts up non unique moves
int countMoves(int size, int chessBoard[size][size], int player) {
    int count = 0;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            // if player == -1 then it multiplied by any
            // negative player piece > 0
            if (player * chessBoard[x][y] > 0) {
                // there is a piece here so find all the pieces it can take
                count += piecesCanTake(chessBoard[x][y], player, x, y, size,
                                       chessBoard);
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
    return 0;
}
