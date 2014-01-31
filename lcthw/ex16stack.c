#include <stdio.h>
#include <assert.h> // gives assert function
#include <stdlib.h> // gives us the malloc function
#include <string.h> // gives us string duplication

struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
  struct Person who;

  who.name = strdup(name); // strdup is used to duplicate string it mallocs memory and assigns the string to it
  who.age = age;
  who.height = height;
  who.weight = weight;

  return who;
}

void Person_destroy(struct Person who) // all stucts must be destroyed to avoid memory leaks
{
  free(who.name);
}

void Person_print(struct Person who)
{
  printf("Name: %s\n", who.name);
  printf("\tAge: %d\n", who.age);
  printf("\tHeight: %d\n", who.height);
  printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
  // make two people stuctures
  struct Person joe = Person_create("Joe Alex", 32, 64, 140);

  struct Person frank = Person_create("Frank Black", 30, 72, 180);

  // print them out and where they are in memory
  printf("Joe is at memory location %p:\n", &joe);
  Person_print(joe);

  printf("Frank is at memory location %p:\n", &frank);
  Person_print(frank);

  // make everyone age 20 years and print them again
  joe.age += 20;
  joe.height -= 2;
  joe.weight += 40;
  Person_print(joe);

  frank.age += 20;
  frank.weight += 20;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}

