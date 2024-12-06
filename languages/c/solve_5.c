#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Rule {
  int before;
  int after;
} Rule;

const char *filepath =
    "/home/marcus/Documents/coding/advent-of-code/2024/inputs/5_test.txt";

bool isOrderCorrect() {
  printf("isOrderCorrect() not implemented\n");
  return false;
}
int getMiddle() {
  printf("getMiddle() not implemented\n");
  return 0;
}

int main() {
  FILE *file = fopen(filepath, "r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return 1; // Exit if the file cannot be opened
  }
  char *line = NULL;
  size_t len = 0;
  unsigned int array_index = 0;

  Rule rules[1600];
  int line_index = 0;
  int rule_index = 0;
  char num_buf[3];
  num_buf[2] = '\0';

  // Read the file line by line
  while (getline(&line, &len, file) != -1) {
    line_index++;
    if (line[0] == '\n' || line[0] == '\0') {
      break;
    }
    num_buf[0] = line[0];
    num_buf[1] = line[1];
    int before = atoi(num_buf);
    num_buf[0] = line[3];
    num_buf[1] = line[4];
    int after = atoi(num_buf);
    struct Rule rule = {before, after};
    rules[rule_index] = rule;
    rule_index++;
  }
  for (int i = 0; i < rule_index; i++) {
    Rule rule = rules[i];
    printf("%i|%i\n", rule.before, rule.after);
  }
  int sum = 0;
  while (getline(&line, &len, file) != -1) {
    if (isOrderCorrect()) {
      sum += getMiddle();
    };
  }
  printf("Answer: %i", sum);

  fclose(file); // Close the file when done
  free(line);

  return 0;
}
