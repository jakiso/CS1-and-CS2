#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SneakyRooks.h"

int toDigit(char c)
{
  c = tolower(c);

  if (c >= '0' && c <= '9')
  {
    return c - '0';
  }

  else if (c >= 'a' && c <= 'z')
  {
    // Return a value from 1-26 based
    return c - 'a' + 1;
  }

}

int Horner(char *str, int base, int length)
{
  int i, result = 0;

  for (i = 0; i < length; i++)
  {
    // A replacement for the pow function
    // to help with runtime
    result *= base;
    result += toDigit(str[i]);
  }

  return result;
}

// Checks if any rooks "kill" any other rooks by being in same
// row or column. If no murder happens return 1. Else return 1.
int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
  // Create Chessboard
  int *col = calloc(boardSize, sizeof(int));
  int *row = calloc(boardSize, sizeof(int));
  Coordinate temp;
  int i;

  // Check if there are rooks to place
  if(numRooks == 0)
  {
    // free board
    free(col);
    free(row);
    // Since there are no rooks technically they
    // are safe
    return 1;
  }

  for(i = 0; i < numRooks; i++)
  {
    // Obtain row and column coordinates for each rook string
    parseCoordinateString(rookStrings[i], &temp);
    // Adds a rook on its assigned row and column
    row[temp.row - 1] += 1;
    col[temp.col - 1] += 1;

    // Checks if there is a previous rook already
    // on new rook's row and column
    if(row[temp.row - 1] > 1)
    {
      // Free the board
      free(col);
      free(row);
      // If there is a previous rook on its row,
      // the new rook is not safe
      return 0;
    }

    if(col[temp.col - 1] > 1)
    {
      free(col);
      free(row);
      // If there is a previous rook on its column,
      // the new rook is not safe
      return 0;
    }

  }
  free(col);
  free(row);
  // If each rook has a unique row and
  // column, all rooks are safe
  return 1;
}

// Sets rookCoordinate.col and rookCoordinate.row based off
// of rookstring
void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
  int length = strlen(rookString);
  char *col;
  char *row;
  int i = 0;
  int parseC = 0;
  int parseR = 0;

  // Checks if string is valid length
  if(length == 0)
  {
    return;
  }

  // Allocate memory for row and column string
  row = calloc(length, sizeof(char));
  col = calloc(length, sizeof(char));

  for(i = 0; i < length; i++)
  {

    if(rookString[i] >= 'a' && rookString[i] <= 'z')
    {
      // Sets column string
      col[parseC] = rookString[i];
      parseC++;
    }

    if(rookString[i] >= '0' && rookString[i] <= '9')
    {
      // Sets row string
      row[parseR] = rookString[i];
      parseR++;
    }

  }

  // Calculates the numerical representation of
  // column
  rookCoordinate->col = Horner(col, 26, parseC);
  // Changes row string from char to a integer
  rookCoordinate->row = Horner(row, 10, parseR);
  // Free strings
  free(row);
  free(col);
}
