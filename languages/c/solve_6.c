#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 130
#define HEIGHT 130

const char *filepath =
    "/home/marcus/Documents/coding/advent-of-code/2024/inputs/6.txt";

typedef struct Point {
  int col_index;
  int row_index;
} Point;

typedef enum Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
} Direction;

typedef enum PositionType { EMPTY, OBSTACLE, OUT_OF_BOUNDS } PositionType;

typedef struct PointDirection {
  Point point;
  Direction direction;
} PointDirection;

typedef PositionType PositionType2dArray[HEIGHT][WIDTH];
typedef Point ObstacleArray[HEIGHT * WIDTH];

typedef struct MapInfo {
  Point *obstacles;
  int obstacle_count;
  int map_width;
  int map_height;
  PointDirection guard;
} MapInfo;

Point get_next_position(Point point, Direction direction) {
  switch (direction) {
  case UP:
    return (Point){point.col_index, point.row_index - 1};
  case RIGHT:
    return (Point){point.col_index + 1, point.row_index};
  case DOWN:
    return (Point){point.col_index, point.row_index + 1};
  case LEFT:
    return (Point){point.col_index - 1, point.row_index};
    break;
  }
}
void print_point(Point point) {
  printf("row_index: %i, col_index: %i\n", point.row_index, point.col_index);
}

PositionType get_position_type(Point point, Point *obstacles,
                               int obstacle_count) {
  if (point.row_index < 0 || point.col_index < 0 || point.row_index >= WIDTH ||
      point.col_index >= HEIGHT) {
    return OUT_OF_BOUNDS;
  }
  for (int i = 0; i < obstacle_count; i++) {
    Point obstacle = obstacles[i];
    if (obstacle.row_index == point.row_index &&
        obstacle.col_index == point.col_index) {
      return OBSTACLE;
    }
  }
  return EMPTY;
}

Direction get_next_direction(Direction dir) {
  switch (dir) {
  case UP:
    return RIGHT;
  case RIGHT:
    return DOWN;
  case DOWN:
    return LEFT;
  case LEFT:
    return UP;
  }
}

MapInfo get_map_info(FILE *file, ObstacleArray obstacles) {
  char *line = NULL;
  size_t len = 0;
  unsigned int row_index = 0;

  int line_index = 0;
  int rule_index = 0;
  int col_index = 0;
  int obstacle_index = 0;
  Point guard_position;
  Direction guard_direction = UP;
  char ch;

  while ((ch = fgetc(file)) != EOF) {
    switch (ch) {
    case '.':
      col_index++;
      break;
    case '#':
      obstacles[obstacle_index] = (Point){col_index, row_index};
      obstacle_index++;
      col_index++;
      break;
    case '^':
      guard_position = (Point){col_index, row_index};
      col_index++;
      break;
    case '\n':
      row_index++;
      col_index = 0;
      break;
    }
  }
  PointDirection guard = {.point = guard_position, .direction = UP};
  MapInfo mapInfo = {.guard = guard,
                     .map_width = WIDTH,
                     .map_height = HEIGHT,
                     .obstacles = obstacles,
                     .obstacle_count = obstacle_index};
  return mapInfo;
}

int answer_part_one(MapInfo mapInfo) {
  Direction guard_direction = mapInfo.guard.direction;
  Point guard_position = mapInfo.guard.point;

  bool visited_map[HEIGHT][WIDTH];
  memset(visited_map, 0,
         sizeof(visited_map)); // Set all elements to `false` (0)

  visited_map[guard_position.col_index][guard_position.row_index] = true;

  while (true) {
    Point next_position = get_next_position(guard_position, guard_direction);
    PositionType position_type = get_position_type(
        next_position, mapInfo.obstacles, mapInfo.obstacle_count);

    bool should_exit = false;
    switch (position_type) {
    case EMPTY:
      guard_position = next_position;
      visited_map[next_position.col_index][next_position.row_index] = true;
      break;
    case OBSTACLE:
      guard_direction = get_next_direction(guard_direction);
      break;
    case OUT_OF_BOUNDS:
      should_exit = true;
      break;
    }
    if (should_exit) {
      break;
    }
  }

  // find answer;
  int answer = 0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (visited_map[y][x]) {
        answer++;
      }
    }
  }
  return answer;
}
PointDirection create_point_direction(int col_index, int row_index,
                                      Direction dir) {
  Point point = {col_index, row_index};
  return (PointDirection){.point = point, .direction = dir};
}

bool contains_point_direction(PointDirection path[WIDTH * HEIGHT * 4],
                              int path_count, PointDirection point_direction) {
  for (int i = 0; i < path_count; i++) {
    PointDirection current_path_direction = path[i];
    if (current_path_direction.point.row_index ==
            point_direction.point.row_index &&
        current_path_direction.point.col_index ==
            point_direction.point.col_index &&
        current_path_direction.direction == point_direction.direction) {
      return true;
    }
  }
  return false;
}

bool does_path_loop(MapInfo mapInfo) {
  PointDirection path[WIDTH * HEIGHT * 4];
  int path_entry_count = 0;
  Direction guard_direction = mapInfo.guard.direction;
  Point guard_position = mapInfo.guard.point;

  while (true) {
    Point next_position = get_next_position(guard_position, guard_direction);
    PositionType position_type = get_position_type(
        next_position, mapInfo.obstacles, mapInfo.obstacle_count);
    bool should_exit = false;
    switch (position_type) {
    case EMPTY:
      guard_position = next_position;
      PointDirection point_direction = create_point_direction(
          guard_position.col_index, guard_position.row_index, guard_direction);

      if (contains_point_direction(path, path_entry_count, point_direction)) {
        return true;
      }
      path[path_entry_count] = point_direction;
      path_entry_count++;
      break;
    case OBSTACLE:
      guard_direction = get_next_direction(guard_direction);
      break;
    case OUT_OF_BOUNDS:
      should_exit = true;
      break;
    }
    if (should_exit) {
      break;
    }
  }
  return false;
}

int answer_part_two(MapInfo mapInfo) {
  Direction guard_direction = mapInfo.guard.direction;
  Point guard_position = mapInfo.guard.point;

  bool visited_map[HEIGHT][WIDTH];
  memset(visited_map, 0,
         sizeof(visited_map)); // Set all elements to `false` (0)

  while (true) {
    Point next_position = get_next_position(guard_position, guard_direction);
    PositionType position_type = get_position_type(
        next_position, mapInfo.obstacles, mapInfo.obstacle_count);

    bool should_exit = false;
    switch (position_type) {
    case EMPTY:
      guard_position = next_position;
      visited_map[next_position.col_index][next_position.row_index] = true;
      break;
    case OBSTACLE:
      guard_direction = get_next_direction(guard_direction);
      break;
    case OUT_OF_BOUNDS:
      should_exit = true;
      break;
    }
    if (should_exit) {
      break;
    }
  }

  Point possible_obstacles[WIDTH * HEIGHT];
  int possible_obstacle_count = 0;

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (visited_map[y][x]) {
        possible_obstacles[possible_obstacle_count] = (Point){y, x};
        possible_obstacle_count++;
      }
    }
  }

  int newObstacleIndex = mapInfo.obstacle_count;
  mapInfo.obstacle_count++;

  int answer = 0;
  for (int possible_obstacle_index;
       possible_obstacle_index < possible_obstacle_count;
       possible_obstacle_index++) {
    Point obstacle = possible_obstacles[possible_obstacle_index];
    mapInfo.obstacles[newObstacleIndex] = obstacle;
    if (does_path_loop(mapInfo)) {
      answer++;
    }
  }
  return answer;
}

int main() {
  FILE *file = fopen(filepath, "r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return 1; // Exit if the file cannot be opened
  }

  Point obstacles[WIDTH * HEIGHT];
  MapInfo map_info = get_map_info(file, obstacles);
  printf("Answer Part 1: %i\n", answer_part_one(map_info));
  printf("Answer Part 2: %i\n", answer_part_two(map_info));
  printf("Complete");

  return 0;
}
