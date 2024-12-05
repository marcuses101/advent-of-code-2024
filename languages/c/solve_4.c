#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
  int row;
  int col;
} Point;

const int ROW_COUNT = 140;
const int COL_COUNT = 140;
const char *filepath = "/home/marcus/Documents/coding/advent-of-code/2024/inputs/4.txt";

enum Directions {
  TOP,
  TOP_RIGHT,
  RIGHT,
  BOTTOM_RIGHT,
  BOTTOM,
  BOTTOM_LEFT,
  LEFT,
  TOP_LEFT
};

Point get_next_point(Point point, enum Directions direction) {
  struct Point result = point;
  switch (direction) {
  case TOP:
    result.col--;
    break;
  case TOP_RIGHT:
    result.col--;
    result.row++;
    break;
  case RIGHT:
    result.row++;
    break;
  case BOTTOM_RIGHT:
    result.col++;
    result.row++;
    break;
  case BOTTOM:
    result.col++;
    break;
  case BOTTOM_LEFT:
    result.col++;
    result.row--;
    break;
  case LEFT:
    result.row--;
    break;
  case TOP_LEFT:
    result.col--;
    result.row--;
    break;
  }
  return result;
}

int count_xmas_part_one(char arr[ROW_COUNT][COL_COUNT], struct Point start) {
  enum Directions directions[8] = {TOP,    TOP_RIGHT,   RIGHT, BOTTOM_RIGHT,
                                   BOTTOM, BOTTOM_LEFT, LEFT,  TOP_LEFT};
  char expected_chars[3] = {'M', 'A', 'S'};
  int count = 0;
  for (int direction_index = 0; direction_index < 8; direction_index++) {
    struct Point current_point = start;
    enum Directions current_direction = directions[direction_index];
    bool isValid = true;
    for (int char_index = 0; char_index < 3; char_index++) {
      char expected_char = expected_chars[char_index];
      current_point = get_next_point(current_point, current_direction);
      // check neg
      if (current_point.row < 0 || current_point.col < 0 ||
          current_point.row >= ROW_COUNT || current_point.col >= COL_COUNT) {
        isValid = false;
        break;
      }
      char actual_char = arr[current_point.row][current_point.col];
      if (expected_char != actual_char) {
        isValid = false;
        break;
      }
    }
    if (isValid) {
      count++;
    }
  }
  return count;
}

int count_xmas_part_two(char arr[ROW_COUNT][COL_COUNT], struct Point start) {
  if (start.row <= 0 || start.col <= 0 || start.row >= ROW_COUNT - 1 ||
      start.col >= COL_COUNT - 1) {
    return 0;
  }
  Point top_left_point = get_next_point(start, TOP_LEFT);
  char top_left = arr[top_left_point.row][top_left_point.col];

  Point top_right_point = get_next_point(start, TOP_RIGHT);
  char top_right = arr[top_right_point.row][top_right_point.col];

  Point bottom_left_point = get_next_point(start, BOTTOM_LEFT);
  char bottom_left = arr[bottom_left_point.row][bottom_left_point.col];

  Point bottom_right_point = get_next_point(start, BOTTOM_RIGHT);
  char bottom_right = arr[bottom_right_point.row][bottom_right_point.col];

  switch (top_left) {
  case 'M':
    if (bottom_right != 'S') {
      return 0;
    }
    break;

  case 'S':
    if (bottom_right != 'M') {
      return 0;
    }
    break;
  default:
    return 0;
  }
  switch (top_right) {
  case 'M':
    if (bottom_left != 'S') {
      return 0;
    }
    break;

  case 'S':
    if (bottom_left != 'M') {
      return 0;
    }
    break;
  default:
    return 0;
  }
  return 1;
}

int part_one(char arr[ROW_COUNT][COL_COUNT]) {
  int xmas_count = 0;
  for (int row = 0; row < ROW_COUNT; row++) {
    for (int col = 0; col < COL_COUNT; col++) {
      char current_char = arr[row][col];
      if (current_char == 'X') {
        struct Point point = {row, col};
        xmas_count += count_xmas_part_one(arr, point);
      }
    }
  }
  return xmas_count;
}

int part_two(char arr[ROW_COUNT][COL_COUNT]) {
  int xmas_count = 0;
  for (int row = 0; row < ROW_COUNT; row++) {
    for (int col = 0; col < COL_COUNT; col++) {
      char current_char = arr[row][col];
      if (current_char == 'A') {
        struct Point point = {row, col};
        xmas_count += count_xmas_part_two(arr, point);
      }
    }
  }
  return xmas_count;
}

int main() {
  FILE *file =
      fopen(filepath,"r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return 1; // Exit if the file cannot be opened
  }

  char array[ROW_COUNT][COL_COUNT];

  char ch;
  int row = 0;
  int col = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      row++;
      col = 0;
      continue;
    }
    array[row][col] = ch;
    col++;
  }

  printf("Part One Xmas count: %i\n", part_one(array));
  printf("Part Two Xmas count: %i\n", part_two(array));
  return 0;
}
