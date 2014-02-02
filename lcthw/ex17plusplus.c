#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
  int id;
  int set;
  char *name;
  char *email;
};

struct Database {
  int max_rows;
  int max_data;
  struct Address *rows;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close();
struct Connection *conn;

void die(const char *message)
{
  Database_close();
  if(errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

int string_size()
{
  return conn->db->max_data * sizeof(char);
}

int rows_size()
{
  int address_size = sizeof(int) * 2 + string_size() * 2;

  return address_size * conn->db->max_rows;
}

void Database_load()
{
  int rc = fread(&conn->db->max_rows, sizeof(int), 1 , conn->file);
  if(rc != 1) die("Failed to load database.");
  rc = fread(&conn->db->max_data, sizeof(int), 1 , conn->file);
  if(rc != 1) die("Failed to load database.");

  conn->db->rows = malloc(rows_size());
  int i;
  for(i = 0; i < conn->db->max_rows; i++) {
    struct Address *addr = &conn->db->rows[i];

    rc = fread(&addr->id, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to load database.");

    rc = fread(&addr->set, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to load database.");

    int str_size = string_size();
    addr->name = malloc(str_size);
    addr->email = malloc(str_size);

    rc = fread(addr->name, str_size, 1, conn->file);
    if(rc != 1) die("Failed to load database.");

    rc = fread(addr->email, str_size, 1, conn->file);
    if(rc != 1) die("Failed to load database.");
  }
}

void Database_open(const char *filename, char mode)
{
  conn = malloc(sizeof(struct Connection));
  if(!conn) die("Memory error");

  conn->db = malloc(sizeof(struct Database));
  if(!conn->db) die("Memory error");

  if(mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn -> file = fopen(filename, "r+");

    if(conn->file) {
      Database_load();
    }
  }

  if(!conn->file) die("Failed to open file");
}

void Database_close()
{
  if(conn) {
    if(conn->file) fclose(conn->file);
    if(conn->db) free(conn->db);
    free(conn);
  }
}

void Database_write()
{
  rewind(conn->file);

  int rc = fwrite(&conn->db->max_rows, sizeof(int), 1 , conn->file);
  if(rc != 1) die("Failed to write database.");
  rc = fwrite(&conn->db->max_data, sizeof(int), 1 , conn->file);
  if(rc != 1) die("Failed to write database.");

  int i;
  for(i = 0; i < conn->db->max_rows; i++) {
    struct Address *addr = &conn->db->rows[i];

    rc = fwrite(&addr->id, sizeof(int), 1 , conn->file);
    if(rc != 1) die("Failed to write database.");

    rc = fwrite(&addr->set, sizeof(int), 1 , conn->file);
    if(rc != 1) die("Failed to write database.");

    rc = fwrite(addr->name, conn->db->max_data * sizeof(char), 1 ,
        conn->file);
    if(rc != 1) die("Failed to write database.");

    rc = fwrite(addr->email, conn->db->max_data * sizeof(char), 1 ,
        conn->file);
    if(rc != 1) die("Failed to write database.");
  }

  rc = fflush(conn->file);
  if(rc == -1) die("Failed to flush database.");
}

void Database_create(int max_rows, int max_data)
{
  int i = 0;

  conn->db->max_rows = max_rows;
  conn->db->max_data = max_data;
  int rows = rows_size();

  conn->db->rows = malloc(rows);
  for(i = 0; i < max_rows; i++) {
    // make a prototype to initialize it
    struct Address addr = {.id = i, .set = 0};
    addr.name = malloc(string_size());
    addr.email = malloc(string_size());
    // then just assign it
    conn->db->rows[i] = addr;
  }
}

void Database_set(int id, const char *name, const char *email)
{
  int max_data = conn->db->max_data;
  struct Address *addr = &conn->db->rows[id];
  if(addr->set) die("Already set, delete it first");

  addr->set = 1;
  addr->name = malloc(string_size());
  addr->email = malloc(string_size());

  // WARNING: Bug, read "How to Break IT" and fix this
  char *res = strncpy(addr->name, name, max_data);
  addr->name[max_data - 1] = '\0';
  // demonstrate the strncpy bug
  if(!res) die("Name copy failed");

  res = strncpy(addr->email, email, max_data);
  addr->name[max_data - 1] = '\0';
  if(!res) die("Email copy failed");
}

void Database_get(int id)
{
  struct Address *addr = &conn->db->rows[id];

  if(addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set");
  }
}

void Database_delete(int id)
{
  struct Address addr = {.id = id, .set = 0};
  addr.name = malloc(string_size());
  addr.email = malloc(string_size());
  conn->db->rows[id] = addr;
}

void Database_list()
{
  int i = 0;
  struct Database *db = conn->db;

  for(i = 0; i < db->max_rows; i++) {
    struct Address *cur = &db->rows[i];

    if(cur->set) {
      Address_print(cur);
    }
  }
}

void Database_find(const char *search_term)
{
  int i = 0;
  struct Database *db = conn->db;

  for(i = 0; i < db->max_rows; i++) {
    struct Address *cur = &db->rows[i];

    if(strcmp(cur->name, search_term) == 0) {
      Address_print(cur);
      return;
    }
  }
  printf("Name not found: %s\n", search_term);
}

int main(int argc, char *argv[])
{
  if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

  char *filename = argv[1];
  char action = argv[2][0];
  Database_open(filename, action);
  int id = 0;

  if(argc > 3) id = atoi(argv[3]);
  if(id >= conn->db->max_rows && action != 'c') {
    die("There's not that many records.");
  }

  switch(action) {
    case 'c':
      if(argc != 5) die("USAGE: ex17 <dbfile> c <max_rows> <max_data>");
      int max_rows = atoi(argv[3]);
      int max_data = atoi(argv[4]);

      Database_create(max_rows, max_data);
      Database_write();
      break;

    case 'g':
      if(argc != 4) die("Need an id to get");

      Database_get(id);
      break;

    case 's':
      if(argc != 6) die("Need an id");

      Database_set(id, argv[4], argv[5]);
      Database_write();
      break;

    case 'd':
      if(argc != 4) die("Need an id to delete");

      Database_delete(id);
      Database_write();
      break;

    case 'f':
      if(argc != 4) die("Need a search term to find");
      Database_find(argv[3]);
      break;

    case 'l':
      Database_list();
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close();

  return 0;
}

