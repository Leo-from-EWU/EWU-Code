#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ZONES 10
#define STACK_SIZE 10
#define WAIT_SIZE 10
#define LOG_SIZE 20

int total_size = 8;

struct LogEntry {
  char message[100];
};

struct Zone {
  char name[50];
  int hospitals;
  int schools;
  int industries;
  int banks;
  int govt_offices;
  int population;
  int status;
  int score;
  int rank;
};

struct Zone zones[MAX_ZONES] = {{"Mirpur", 2, 3, 4, 2, 1, 9, 0, 0, 0},
                                {"Tejgaon", 3, 2, 8, 3, 2, 6, 0, 0, 0},
                                {"Dhanmondi", 6, 5, 2, 4, 3, 7, 0, 0, 0},
                                {"Gulshan", 4, 3, 5, 7, 5, 5, 0, 0, 0},
                                {"Old Dhaka", 5, 6, 6, 3, 2, 10, 0, 0, 0},
                                {"Uttara", 3, 7, 3, 3, 2, 8, 0, 0, 0},
                                {"Mohammadpur", 3, 5, 3, 2, 1, 8, 0, 0, 0},
                                {"Motijheel", 4, 2, 6, 9, 7, 6, 0, 0, 0}};

struct Zone stack[STACK_SIZE];
struct Zone waitingList[WAIT_SIZE];
struct LogEntry logs[LOG_SIZE];

int top = -1;
int waitCount = 0;
int logCount = 0;

// isEmpty: returns 1 (true) if there is nothing in the stack.
int isEmpty() {
  if (top == -1)
    return 1;
  else
    return 0;
}

// isFull: returns 1 (true) if the stack has reached its max size.
int isFull() {
  if (top == 8 - 1)
    return 1;
  else
    return 0;
}

// push: adds a zone onto the top of the stack.
void push(struct Zone z) {
  if (isFull() == 0) {
    top = top + 1;
    stack[top] = z;
  }
}

// pop: removes and returns the zone from the top of the stack.
struct Zone pop() {
  struct Zone item;
  if (isEmpty() == 0) {
    item = stack[top];
    top = top - 1;
  }
  return item;
}

// restack: CLEARS the stack and refills it with the top 3 unpowered zones.
void restack() {
  int count;
  int temp_indices[3];

  top = -1;
  count = 0;
  int i = 0;

  while (count < 3 && i < total_size) {
    if (zones[i].status != 1) {
      temp_indices[count] = i;
      count = count + 1;
    }
    i = i + 1;
  }

  for (int i = count - 1; i >= 0; i--) {
    push(zones[temp_indices[i]]);
  }
}

// addToWaiting: saves a zone into the waitingList[] array.
void addToWaiting(struct Zone z) {
  if (waitCount < WAIT_SIZE) {
    waitingList[waitCount] = z;
    waitCount = waitCount + 1;
  }
}

// addLog: saves a text message into the logs[] array.
void addLog(char *msg) {
  if (logCount < LOG_SIZE) {
    strcpy(logs[logCount].message, msg);
    logCount = logCount + 1;
  }
}

// calculateScore: computes the priority score for one zone using its data.
void calculateScore(struct Zone *z) {
  z->score = (z->hospitals * 9) + (z->schools * 5) + (z->industries * 6) +
             (z->banks * 4) + (z->govt_offices * 3) + (z->population * 4);

  if (z->status == 2) {
    z->score = z->score + 100;
  }
}

// calculateAllScores: loops through every zone and calls calculateScore on it.
void calculateAllScores() {
  for (int i = 0; i < total_size; i++)
    calculateScore(&zones[i]);
}

// Scoresorting: sorts the zones[] array from highest score to lowest.
void Scoresorting() {
  struct Zone temp;
  for (int i = 0; i < total_size - 1; i++) {
    for (int j = 0; j < total_size - 1 - i; j++) {
      if (zones[j].score < zones[j + 1].score) {
        temp = zones[j];
        zones[j] = zones[j + 1];
        zones[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < total_size; i++) {
    zones[i].rank = i + 1;
  }
}

// showmenu: prints the main menu.
void showmenu() {
  printf("\n=====================================================\n");
  printf("     DHAKA EMERGENCY POWER DISTRIBUTION SYSTEM\n");
  printf("=====================================================\n");
  printf("  [1] View all zones ranked by priority\n");
  printf("  [2] View top 3 zones (Stack)\n");
  printf("  [3] View powered zones (Waiting List)\n");
  printf("  [4] Give power to top zone\n");
  printf("  [5] Declare EMERGENCY\n");
  printf("  [6] Add/Remove facilities\n");
  printf("  [7] Reset zone power status\n");
  printf("  [8] View activity log\n");
  printf("  [9] Exit\n");
  printf("=====================================================\n");
  printf("Enter choice: ");
}

// viewALlrank: shows the full details of every zone.
void viewALlrank() {
  for (int i = 0; i < total_size; i++) {
    printf("\n============================\n");
    printf("   ZONE: %s\n", zones[i].name);
    printf("============================\n");

    printf(" Rank         : %d\n", zones[i].rank);
    printf(" Score        : %d\n", zones[i].score);
    printf(" Hospitals    : %d\n", zones[i].hospitals);
    printf(" Schools      : %d\n", zones[i].schools);
    printf(" Industries   : %d\n", zones[i].industries);

    if (zones[i].status == 1)
      printf(" Status       : POWERED\n");
    else if (zones[i].status == 2)
      printf(" Status       : EMERGENCY\n");
    else
      printf(" Status       : WAITING\n");

    printf("----------------------------\n");
  }
}

// viewTop3: shows the top 3 zones currently in the stack.
void viewTop3() {
  struct Zone temp[STACK_SIZE];
  int count = 0;
  int rank = 1;

  while (isEmpty() == 0) {
    temp[count] = pop();
    printf("  Rank %d: %s (Score: %d)\n", rank, temp[count].name,
           temp[count].score);
    count = count + 1;
    rank = rank + 1;
  }

  for (int i = count - 1; i >= 0; i--)
    push(temp[i]);
}

// viewWaitingList: shows all zones that have previously received power.
void viewWaitingList() {
  printf("\n--- POWERED ZONES (WAITING LIST) ---\n");

  if (waitCount == 0) {
    printf("No zones have received power yet.\n");
    return;
  }

  printf("--------------------------------------------\n");
  for (int i = 0; i < waitCount; i++) {
    printf("Zone: %s\n", waitingList[i].name);
    printf("  - Priority Score: %d\n", waitingList[i].score);
    printf("--------------------------------------------\n");
  }
}

// givepower: gives electricity to the top zone in the stack.
void givepower() {
  struct Zone power;

  if (isEmpty() == 1) {
    printf("The Stack is empty\n");
    return;
  }
  printf("\n--- BEFORE POWER ROTATION ---\n");
  viewALlrank();
  power = pop();

  for (int i = 0; i < total_size; i++) {
    if (strcmp(zones[i].name, power.name) == 0) {
      zones[i].status = 1;
      break;
    }
  }
  addToWaiting(power);

  calculateAllScores();
  Scoresorting();
  restack();

  printf("\n[LOG] %s received power - Score: %d\n", power.name, power.score);

  char msg[100];
  snprintf(msg, sizeof(msg), "%s received power", power.name);
  addLog(msg);

  printf("\n>> %s has been powered!\n", power.name);
  if (isEmpty() == 0) {
    printf(">> %s is now Rank 1.\n", stack[top].name);
  }

  printf("\n--- AFTER POWER ROTATION ---\n");
  viewALlrank();
}

// declareEmergency: gives a MANUAL OVERRIDE to any zone.
void declareEmergency() {
  int choice;

  printf("\n--- DECLARE EMERGENCY ---\n");
  for (int i = 0; i < total_size; i++) {
    printf("[%d] %s (Rank %d)\n", i + 1, zones[i].name, zones[i].rank);
  }

  printf("Select zone number: ");
  scanf(" %d", &choice);

  if (choice < 1 || choice > total_size) {
    printf("Invalid choice!\n");
    return;
  }

  int idx = choice - 1;
  zones[idx].status = 2;

  printf("\n[LOG] EMERGENCY declared in %s\n", zones[idx].name);

  char msg[100];
  snprintf(msg, sizeof(msg), "EMERGENCY: %s", zones[idx].name);
  addLog(msg);

  calculateAllScores();
  Scoresorting();
  restack();

  printf("\nEMERGENCY DECLARED: %s is now Rank 1!\n", zones[0].name);
}

// resetPower: removes the POWERED status from a zone.
void resetPower() {
  int choice;
  int found;

  printf("\n--- RESET ZONE POWER STATUS ---\n");

  found = 0;
  for (int i = 0; i < total_size; i++) {
    if (zones[i].status == 1) {
      printf("[%d] %s (Rank %d)\n", i + 1, zones[i].name, zones[i].rank);
      found = 1;
    }
  }

  if (found == 0) {
    printf("No zones are currently powered.\n");
    return;
  }

  printf("Select zone number to reset: ");
  scanf(" %d", &choice);

  if (choice < 1 || choice > total_size) {
    printf("Invalid choice!\n");
    return;
  }

  int idx = choice - 1;

  if (zones[idx].status != 1) {
    printf("That zone is not currently powered!\n");
    return;
  }

  zones[idx].status = 0;

  calculateAllScores();
  Scoresorting();
  restack();

  printf("\n[LOG] %s has been reset to WAITING\n", zones[idx].name);
  printf(">> %s is now back in the priority queue.\n", zones[idx].name);

  char msg[100];
  snprintf(msg, sizeof(msg), "Reset %s to waiting", zones[idx].name);
  addLog(msg);
}

// manageFacilities: lets the user add or remove a facility.
void manageFacilities() {
  int choice, action, fac;
  int old_score, old_rank;
  printf("\n--- MANAGE FACILITIES ---\n");
  for (int i = 0; i < total_size; i++) {
    printf("Rank: [%d] [%s]===  Score: %d  \n", zones[i].rank, zones[i].name,
           zones[i].score);
  }

  printf("Select zone number: ");
  scanf(" %d", &choice);

  if (choice < 1 || choice > total_size) {
    printf("Invalid choice!\n");
    return;
  }

  int idx = choice - 1;
  old_score = zones[idx].score;
  old_rank = zones[idx].rank;

  printf("\n============================================\n");
  printf("  ZONE: %s\n", zones[idx].name);
  printf("============================================\n");
  printf("  Hospitals    : %d\n", zones[idx].hospitals);
  printf("  Schools      : %d\n", zones[idx].schools);
  printf("  Industries   : %d\n", zones[idx].industries);
  printf("  Banks        : %d\n", zones[idx].banks);
  printf("  Govt Offices : %d\n", zones[idx].govt_offices);
  printf("  Score        : %d\n", zones[idx].score);
  printf("  Rank         : %d\n", zones[idx].rank);
  printf("============================================\n");
  printf("[1] Add a facility\n");
  printf("[2] Remove a facility\n");
  printf("[3] Go back\n");
  printf("Select: ");
  scanf(" %d", &action);

  if (action == 3)
    return;
  if (action != 1 && action != 2) {
    printf("Invalid choice!\n");
    return;
  }

  printf(
      "\n[1] Hospital  [2] School  [3] Industry  [4] Bank  [5] Govt Office\n");
  printf("Select facility: ");
  scanf(" %d", &fac);

  if (fac < 1 || fac > 5) {
    printf("Invalid choice!\n");
    return;
  }

  if (action == 1) {
    if (fac == 1)
      zones[idx].hospitals = zones[idx].hospitals + 1;
    else if (fac == 2)
      zones[idx].schools = zones[idx].schools + 1;
    else if (fac == 3)
      zones[idx].industries = zones[idx].industries + 1;
    else if (fac == 4)
      zones[idx].banks = zones[idx].banks + 1;
    else
      zones[idx].govt_offices = zones[idx].govt_offices + 1;
    printf("\nFacility added to %s!\n", zones[idx].name);
  } else {
    if (fac == 1) {
      if (zones[idx].hospitals == 0) {
        printf("No hospitals to remove!\n");
        return;
      }
      zones[idx].hospitals = zones[idx].hospitals - 1;
    } else if (fac == 2) {
      if (zones[idx].schools == 0) {
        printf("No schools to remove!\n");
        return;
      }
      zones[idx].schools = zones[idx].schools - 1;
    } else if (fac == 3) {
      if (zones[idx].industries == 0) {
        printf("No industries to remove!\n");
        return;
      }
      zones[idx].industries = zones[idx].industries - 1;
    } else if (fac == 4) {
      if (zones[idx].banks == 0) {
        printf("No banks to remove!\n");
        return;
      }
      zones[idx].banks = zones[idx].banks - 1;
    } else {
      if (zones[idx].govt_offices == 0) {
        printf("No govt offices to remove!\n");
        return;
      }
      zones[idx].govt_offices = zones[idx].govt_offices - 1;
    }
    printf("\nFacility removed from %s!\n", zones[idx].name);
  }

  calculateAllScores();
  Scoresorting();
  restack();
  printf("Old Score: %d  ->  New Score: %d\n", old_score, zones[idx].score);
  printf("Old Rank : %d  ->  New Rank : %d\n", old_rank, zones[idx].rank);

  printf("\n[LOG] Facilities updated for %s | Score: %d -> %d\n",
         zones[idx].name, old_score, zones[idx].score);

  char msg[100];
  snprintf(msg, sizeof(msg), "Updated facilities in %s", zones[idx].name);
  addLog(msg);
}

// viewLog: displays all recorded activity in order.
void viewLog() {
  printf("\n--- ACTIVITY LOG ---\n");

  if (logCount == 0) {
    printf("No activity recorded yet.\n");
    return;
  }

  for (int i = 0; i < logCount; i++) {
    printf("[%d] %s\n", i + 1, logs[i].message);
  }
}

// main: program entry point.
int main() {
  int choice = 0;
  calculateAllScores();
  Scoresorting();
  restack();

  while (choice != 9) {
    showmenu();
    scanf("%d", &choice);

    if (choice == 1)
      viewALlrank();
    else if (choice == 2)
      viewTop3();
    else if (choice == 3)
      viewWaitingList();
    else if (choice == 4)
      givepower();
    else if (choice == 5)
      declareEmergency();
    else if (choice == 6)
      manageFacilities();
    else if (choice == 7)
      resetPower();
    else if (choice == 8)
      viewLog();
    else if (choice == 9)
      printf("\nGoodbye!\n\n");
    else
      printf("Invalid choice! Try again.\n");
  }
}
