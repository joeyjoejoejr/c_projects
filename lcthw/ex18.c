#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);
typedef int *(*sort_alg) (int *a, int b, compare_cb cmp);

int *quick_sort(int *numbers, int count, compare_cb cmp)
{
  int *target = malloc(count * sizeof(int));
  int *lower = malloc(count * sizeof(int));
  int *higher = malloc(count * sizeof(int));
  int *pivots = malloc(count * sizeof(int));
  int lower_count = 0;
  int higher_count = 0;
  int pivot_count = 0;
  int pivot = 0;
  int i = 0;
  if(!target) die("Memmory error.");
  memcpy(target, numbers, count * sizeof(int));

  //if count is 0 or 1 return the array
  if(count == 1 || count == 0) return target;
  //else pick a pivot
  pivot = target[0];
  //split into two lists one higher than the pivot and one lower
  for(i = 0; i < count; i++) {
    if(cmp(target[i], pivot) < 0) {
      lower[lower_count] = target[i];
      lower_count += 1;
    } else if(cmp(target[i], pivot) > 0) {
      higher[higher_count] = target[i];
      higher_count += 1;
    } else {
      pivots[pivot_count] = target[i];
      pivot_count += 1;
    }
  }

  int *lower_sorted = quick_sort(lower, lower_count, cmp);
  int *higher_sorted = quick_sort(higher, higher_count, cmp);
  int lower_size = lower_count * sizeof(int);
  memcpy(target, lower_sorted, lower_size);
  memcpy(&target[lower_count], pivots, pivot_count * sizeof(int));
  memcpy(&target[lower_count + pivot_count], higher_sorted, higher_count * sizeof(int));

  free(lower_sorted);
  free(higher_sorted);
  free(lower);
  free(higher);
  free(pivots);

  return target;
}

/*
 * A classic bubble sort function that uses compare_cb to do the sorting
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i = 0;
  int j = 0;
  int *target = malloc(count * sizeof(int));

  if(!target) die("Memmory error.");

  memcpy(target, numbers, count * sizeof(int));

  for(i = 0; i < count; i++) {
    for(j = 0; j < count - 1; j++) {
      if(cmp(target[j], target[j + 1]) > 0) {
        temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }

  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

// Used to test that we are doing the sort correctly by sorting and printing  it
// out.
void test_sorting(int *numbers, int count, sort_alg sort, compare_cb cmp)
{
  int i = 0;
  int *sorted = sort(numbers, count, cmp);

  if(!sorted) die("Failed to sort.");

  for(i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);
}

int main(int argc, char *argv[])
{
  if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  if(!numbers) die("Memmory error.");

  for(i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  puts("Using Bubble Sort:");
  test_sorting(numbers, count, bubble_sort, sorted_order);
  test_sorting(numbers, count, bubble_sort, reverse_order);
  test_sorting(numbers, count, bubble_sort, strange_order);

  puts("Using Quicksort:");
  test_sorting(numbers, count, quick_sort, sorted_order);
  test_sorting(numbers, count, quick_sort, reverse_order);
  test_sorting(numbers, count, quick_sort, strange_order);

  free(numbers);

  return 0;
}
