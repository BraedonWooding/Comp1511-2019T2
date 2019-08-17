/*
 * ====================================================================
 *
 *       Filename:  knight_moves.c
 *
 *    Description:  Move a knight around a chessboard
 *
 *        Version:  1.0
 *        Created:  08/08/19 13:37:40
 *       Revision:  none
 *       Compiler:  dcc
 *
 *         Author:  Braedon Wooding, b.wooding@unsw.edu.au
 *   Organization:  UNSW
 *
 * ===================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE (8)

// prints out a given path of a given length
void printPath(int path[][2], int length);

// find all the paths that a knight can move given a max move count
// prints out the paths to stdout and returns the number printed
int findMoves(int path[][2], int length, int maxMoves, int endX, int endY);

int main(int argc, char *argv[]) {
    // note: we are offsetting to 1 because our coordinates start
    //       at A1 instead of A0 so this way we can convert them
    //       into (0, 0) and (7, 7) instead of (0, 1) and (7, 8)
    int startX = argv[1][0] - 'a';
    int startY = argv[1][1] - '1';
    int endX = argv[2][0] - 'a';
    int endY = argv[2][1] - '1';

    int i = 1;
    int stop = 0;
    // loop forever
    while (!stop) {
        // this is just a way to allocate the path
        // you could also write it like
        // `int path[i][2];` without any problems
        // I just don't like VLAs
        int (*path)[2] = malloc(sizeof(int) * i * 2);
        path[0][0] = startX;
        path[0][1] = startY;
        stop = findMoves(path, 1, i, endX, endY) > 0;
        free(path);
        i++;
    }
}

int findMoves(int path[][2], int length, int maxMoves, int endX, int endY) {
    if (length == maxMoves) {
        return 0;
    }

    int deltaX[] = { -2, -2, -1, -1,  1,  1,  2,  2 };
    int deltaY[] = { -1,  1, -2,  2, -2,  2, -1,  1 };

    int i = 0;
    int paths = 0;

    while (i < 8) {
        int nextX = path[length - 1][0] + deltaX[i];
        int nextY = path[length - 1][1] + deltaY[i];
        if (nextX >= 0 && nextX < SIZE && nextY >= 0 && nextY < SIZE) {
            path[length][0] = nextX;
            path[length][1] = nextY;
            if (nextX == endX && nextY == endY) {
                // early exit, if we found the end
                // then there won't be any more paths
                // from this point that will be shorter
                assert(length + 1 == maxMoves);
                printPath(path, length + 1);
                paths++;
                return paths;
            } else {
                paths += findMoves(path, length + 1, maxMoves, endX, endY);
            }
        }
        i++;
    }
    return paths;
}

void printPath(int path[][2], int length) {
    int i = 0;
    while (i < length) {
        printf("%c%c ", path[i][0] + 'a', path[i][1] + '1');
        i++;
    }
    putchar('\n');
}
