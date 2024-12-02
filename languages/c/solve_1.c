#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(unsigned int (*array)[1024], int length) {
  bool sorted = false;
  while (!sorted) {
    bool in_order = true;
    for (int i = 0; i < length - 1; i++) {
      int val = (*array)[i];
      int next = (*array)[i + 1];
      if (val > next) {
        in_order = false;
        (*array)[i] = next;
        (*array)[i + 1] = val;
      }
    }
    if (in_order) {
      sorted = true;
    }
  }
}



int main() {
  FILE *file =
      fopen("/home/marcus/Documents/coding/advent-of-code/2024/inputs/1.txt",
            "r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return 1; // Exit if the file cannot be opened
  }
  char *line = NULL;
  size_t len = 0;
  unsigned int array_index = 0;

  unsigned int list_one[1024];
  unsigned int list_two[1024];

  // Read the file line by line
  while (getline(&line, &len, file) != -1) {
    char num_string_one[6];
    char num_string_two[6];
    for (int i = 0; i < 5; i++) {
      num_string_one[i] = line[i];
      num_string_two[i] = line[i + 8];
    }
    num_string_one[5] = '\0';
    num_string_two[5] = '\0';
    list_one[array_index] = atoi(num_string_one);
    list_two[array_index] = atoi(num_string_two);
    array_index += 1;
  }

  fclose(file); // Close the file when done
  free(line);

  bubble_sort(&list_one, array_index);
  bubble_sort(&list_two, array_index);

  int diff = 0;
  for (int i = 0; i < array_index; i++) {
    int entry_list_one = list_one[i];
    int entry_list_two = list_two[i];
    diff += abs(entry_list_one - entry_list_two);
  }

  printf("Part One: %d\n", diff);

  int frequency_arr[100000] = {0};
  for (int i = 0; i < array_index; i++) {
      frequency_arr[list_two[i]]++;
  }

  int similarity = 0;

  for (int i = 0; i < array_index; i++) {
      int val = list_one[i];
      similarity += val * frequency_arr[val];
  }

  printf("Part Two: %d\n", similarity);
  return 0;
}
