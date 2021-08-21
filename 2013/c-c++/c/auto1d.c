#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BITS_PER_RULE 3
#define MARGIN 2

static const int NUM_OF_RULES = (2 << BITS_PER_RULE);
static const int BITS_IN_INT = sizeof(int) * 8;

void parseRule(const int rule, int *rules) {
 int mask = 1, i = 0;
 for(i = 0; i < NUM_OF_RULES; ++i) {
  rules[i] = (rule & mask) ? 1 : 0;
  printf("Rule# %d, Result: %d\n", i, rules[i]);
  mask <<= 1;
 }
}

void parsePositions(const char *positions, const int length, int *row) {
 int i, j, mask;
 for(i = 0, j = 0; i < length; ++i) {
  if(i == 0) {
   row[j] = 0;
   mask = 2;
  } else if(((i + 1) % BITS_IN_INT) == 0) {
   row[++j] = 0;
   mask = 1;
  }
  if(positions[i] != ' '/* && positions[i] != '\0'*/) {
   row[j] |= mask;
  }
  mask <<= 1;
  printf("%c", positions[i]);
 }
 if(((i + 1) % BITS_IN_INT) == 0) {
   row[++j] = 0;
 }
 printf("%c", '\n'); 
}

void printRow(int *prev_row, int *next_row, const int * const rules, const int num_of_positions) {
 int i, j, shift, part, ri, mask;
 const int RULE_MASK = NUM_OF_RULES - 1;
 for(i = 0, j = 0; i < num_of_positions; ++i) {
  if(i == 0) {
   next_row[j] = 0;
   shift = 0;
   mask = 2;
  } 
  shift = (i % BITS_IN_INT);
  ri = (prev_row[j] >> shift) & RULE_MASK;
  if((part = (BITS_IN_INT - shift)) < BITS_PER_RULE) {
   if(part == 1) {
    next_row[++j] = 0;
    mask = 1;
   }
   ri |= ((prev_row[j] & RULE_MASK) << part);
  }
  if(rules[ri] != 0) {
   printf("%c", 'o'); 
   next_row[j] |= mask; 
  } else {
   printf("%c", ' '); 
  }
  mask <<= 1;
 }
 printf("%c", '\n'); 
 if(part == 2) {
  next_row[++j] = 0;
 }
}

int printRows(int *prev_row, int *next_row, const int * const rules, 
 const int num_of_positions, const int chunks, const int limit) {
 int i, j, d;
 for(i = 1; i <= limit; ++i) {
  printRow(prev_row, next_row, rules, num_of_positions);
  d = 0;
  for(j = 0; j < chunks; ++j) {
   if(d = (prev_row[j] != next_row[j])) {
    prev_row[j] = next_row[j];
   }
  }
  if(!d) {
   break;
  }
 }
 return ((d) ? limit : i) + 1;
}

int auto1d(int rule, char *positions, int limit) {
 int rules[NUM_OF_RULES], num_of_positions = strlen(positions), 
  chunks = (num_of_positions + MARGIN) / (sizeof(int) * NUM_OF_RULES) + 1,
  *prev_row, *next_row, rows;
 prev_row = (int *)malloc(chunks);
 next_row = (int *)malloc(chunks);
 parseRule(rule, rules);
 printf("num_of_positions = %d, number of chunks = %d\n", num_of_positions, chunks);
 parsePositions(positions, num_of_positions, prev_row);
 rows = printRows(prev_row, next_row, rules, num_of_positions, chunks, limit);
 free(prev_row);
 free(next_row);
 return rows;
}

void runRule(const int rule, const int limit) {
  printf("#### Begin rule %d ####\n", rule);
  printf("printed %d rows\n", auto1d(rule, "          o          ", limit));
  printf("#### End rule %d ####\n", rule);
}

int main(int argc, char **argv) {
 enum { APP_NAME, RULE, LIMIT };
 int rule, limit;
 if(argc != 3) {
  printf("Usage: %s <rule, e.g. 18, 204> <limit of additional rows, e.g. 20>\n", argv[APP_NAME]);
  runRule(18, 20);
  runRule(204, 20);
 } else {
  sscanf(argv[RULE], "%d", &rule);
  sscanf(argv[LIMIT], "%d", &limit);
  runRule(rule, limit); 
 }
 return 0;
}
