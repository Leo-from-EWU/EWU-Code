// Algorithms: Sorting Algorithm, Greedy Allocation, Prim's Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ZONES 20

int total_zones = 16;
int availablePower = 0;

void greedyPowerAllocation(int autoRun);

struct Zone {
  char name[50];
  int hospitals;
  int schools;
  int industries;
  int banks;
  int govt_offices;
  int population;
  int power_required;
  int status;
  int score;
  int rank;
};

struct Zone zones[MAX_ZONES] = {{"Mirpur", 2, 3, 4, 2, 1, 9, 40, 0, 0, 0},
                                {"Tejgaon", 3, 2, 8, 3, 2, 6, 55, 0, 0, 0},
                                {"Dhanmondi", 6, 5, 2, 4, 3, 7, 35, 0, 0, 0},
                                {"Gulshan", 4, 3, 5, 7, 5, 5, 45, 0, 0, 0},
                                {"Old Dhaka", 5, 6, 6, 3, 2, 10, 60, 0, 0, 0},
                                {"Uttara", 3, 7, 3, 3, 2, 8, 50, 0, 0, 0},
                                {"Mohammadpur", 3, 5, 3, 2, 1, 8, 30, 0, 0, 0},
                                {"Motijheel", 4, 2, 6, 9, 7, 6, 65, 0, 0, 0},
                                {"Banani", 2, 4, 3, 6, 4, 4, 35, 0, 0, 0},
                                {"Badda", 1, 3, 5, 2, 1, 7, 40, 0, 0, 0},
                                {"Khilgaon", 2, 5, 4, 3, 2, 8, 45, 0, 0, 0},
                                {"Rampura", 1, 4, 3, 2, 1, 7, 35, 0, 0, 0},
                                {"Shyamoli", 3, 4, 2, 3, 2, 6, 30, 0, 0, 0},
                                {"Farmgate", 4, 5, 3, 5, 6, 5, 45, 0, 0, 0},
                                {"Bashundhara", 3, 6, 2, 8, 1, 5, 50, 0, 0, 0},
                                {"Moghbazar", 2, 3, 4, 4, 3, 6, 40, 0, 0, 0}};


int powerGrid[16][16] = {
    {0, 10, 0, 0, 0, 12, 8, 0, 0, 0, 0, 0, 5, 0, 0, 0},
    {10, 0, 7, 14, 0, 0, 0, 11, 0, 0, 0, 0, 0, 6, 0, 8},
    {0, 7, 0, 0, 9, 0, 6, 0, 0, 0, 0, 0, 4, 0, 0, 0},
    {0, 14, 0, 0, 0, 15, 0, 13, 5, 7, 0, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 0, 0, 10, 0, 0, 11, 0, 0, 0, 0, 0},
    {12, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0},
    {8, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
    {0, 11, 0, 13, 10, 0, 0, 0, 0, 0, 8, 12, 0, 0, 0, 7},
    {0, 0, 0, 5, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 10, 0},
    {0, 0, 0, 7, 0, 0, 0, 0, 6, 0, 0, 5, 0, 0, 8, 0},
    {0, 0, 0, 0, 11, 0, 0, 8, 0, 0, 0, 4, 0, 0, 0, 6},
    {0, 0, 0, 0, 0, 0, 0, 12, 0, 5, 4, 0, 0, 0, 0, 5},
    {5, 0, 4, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 7, 0, 0},
    {0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 4},
    {0, 0, 0, 0, 0, 18, 0, 0, 10, 8, 0, 0, 0, 0, 0, 0},
    {0, 8, 0, 0, 0, 0, 0, 7, 0, 0, 6, 5, 0, 4, 0, 0}
};

//Sorting the priority

void calculateScore(struct Zone *z) {
  z->score = (z->hospitals * 10) + (z->schools * 6) + (z->industries * 5) +
             (z->banks * 4) + (z->govt_offices * 3) + (z->population * 4);

  if (z->status == 2) {
    z->score = z->score + 100;
  }
}

void calculateAllScores() {
  for (int i = 0; i < total_zones; i++)
    calculateScore(&zones[i]);
}

void Scoresorting() {
  struct Zone temp;
  for (int i = 0; i < total_zones - 1; i++) {
    for (int j = 0; j < total_zones - 1 - i; j++) {
      if (zones[j].score < zones[j + 1].score) {
        temp = zones[j];
        zones[j] = zones[j + 1];
        zones[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < total_zones; i++) {
    zones[i].rank = i + 1;
  }
}

void showmenu() {
  printf("\n");
  printf("-------- {-.-} -------- (-.-) -------- -..- ---------- [-...-] -----");
  printf("\n");
  printf("\n");
  printf("     DHAKA EMERGENCY POWER DISTRIBUTION SYSTEM\n");
  printf("=====================================================\n");
  printf("  [1] View All Zones Ranked by Priority\n");
  printf("  [2] View Powered Zones\n");
  printf("  [3] Distribute Power (Greedy)\n");
  printf("  [4] Add/Remove Facilities\n");
  printf("  [5] Reset Zone Power Status\n");
  printf("  [6] Minimum Cost Power Grid (Prim's)\n");
  printf("  [7] Exit\n");
  printf("=====================================================\n");
  printf("Enter choice: ");
}

void viewALlrank() {
  
  printf("\n");
  printf("------------------------------------------------------------------------------\n");
  printf("%-5s %-15s %-6s %-5s %-7s %-6s %-5s %-5s %-6s %s\n", 
         "Rank", "Zone", "Score", "Hosp", "School", "Indus", "Bank", "Govt", "Power", "Status");
  printf("------------------------------------------------------------------------------\n");

  for (int i = 0; i < total_zones; i++) {
    char status[12]; // Pow,eme,waiti string number..
    
    if (zones[i].status == 1)
      strcpy(status, "POWERED");
    else if (zones[i].status == 2)
      strcpy(status, "EMERGENCY");
    else
      strcpy(status, "WAITING");

    printf("%-5d %-15s %-6d %-5d %-7d %-6d %-5d %-5d %-6d %s\n",
        zones[i].rank, zones[i].name, zones[i].score, zones[i].hospitals,
        zones[i].schools, zones[i].industries, zones[i].banks,
        zones[i].govt_offices, zones[i].power_required, status);
  }
  printf("------------------------------------------------------------------------------\n");
}

void viewPoweredZones() {
  printf("\n--- POWERED ZONES ---\n");
  int found = 0;
  printf("--------------------------------------------\n");
  for (int i = 0; i < total_zones; i++) {
    if (zones[i].status == 1) {
      printf("Zone: %s\n", zones[i].name);
      printf("  - Priority Score: %d\n", zones[i].score);
      printf("  - Power Allocated: %d MW\n", zones[i].power_required);
      printf("--------------------------------------------\n");
      found = 1;
    }
  }

  if (found == 0) {
    printf("No zones are currently powered.\n");
  }
}

void resetPower() {
  int choice;
  int found=0;

  printf("\n--- RESET ZONE POWER STATUS ---\n");

  
  for (int i = 0; i < total_zones; i++) {
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

  if (choice < 1 || choice > total_zones) {
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

  printf("\n>> %s has been reset to WAITING\n", zones[idx].name);
}

void manageFacilities() {
  int choice, action, facility;
  int old_score, old_rank;
  printf("\n--- MANAGE FACILITIES ---\n");
  for (int i = 0; i < total_zones; i++) {
    printf("Rank: [%d] [%s]===  Score: %d  \n", zones[i].rank, zones[i].name,
           zones[i].score);
  }

  printf("Select zone number: ");
  scanf(" %d", &choice);

  if (choice < 1 || choice > total_zones) {
    printf("Invalid choice.... Give correct one!!!!!\n");
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
  if (action < 1 || action > 2 ) {
    printf("Invalid choice\n");
    return;
  }

  printf(
      "\n[1] Hospital  [2] School  [3] Industry  [4] Bank  [5] Govt Office\n");
  printf("Select facility: ");
  scanf(" %d", &facility);

  if (facility < 1 || facility > 5) {
    printf("Invalid choice!\n");
    return;
  }

  if (action == 1) {
    if (facility == 1)
      zones[idx].hospitals = zones[idx].hospitals + 1;
    else if (facility == 2)
      zones[idx].schools = zones[idx].schools + 1;
    else if (facility == 3)
      zones[idx].industries = zones[idx].industries + 1;
    else if (facility == 4)
      zones[idx].banks = zones[idx].banks + 1;
    else
      zones[idx].govt_offices = zones[idx].govt_offices + 1;
    printf("\nFacility added to %s!\n", zones[idx].name);
  } else {
    if (facility == 1) {
      if (zones[idx].hospitals == 0) {
        printf("No hospitals to remove!\n");
      } else {
        zones[idx].hospitals = zones[idx].hospitals - 1;
        printf("\nFacility removed from %s!\n", zones[idx].name);
      }
    } else if (facility == 2) {
      if (zones[idx].schools == 0) {
        printf("No schools to remove!\n");
      } else {
        zones[idx].schools = zones[idx].schools - 1;
        printf("\nFacility removed from %s!\n", zones[idx].name);
      }
    } else if (facility == 3) {
      if (zones[idx].industries == 0) {
        printf("No industries to remove!\n");
      } else {
        zones[idx].industries = zones[idx].industries - 1;
        printf("\nFacility removed from %s!\n", zones[idx].name);
      }
    } else if (facility == 4) {
      if (zones[idx].banks == 0) {
        printf("No banks to remove!\n");
      } else {
        zones[idx].banks = zones[idx].banks - 1;
        printf("\nFacility removed from %s!\n", zones[idx].name);
      }
    } else {
      if (zones[idx].govt_offices == 0) {
        printf("No govt offices to remove!\n");
      } else {
        zones[idx].govt_offices = zones[idx].govt_offices - 1;
        printf("\nFacility removed from %s!\n", zones[idx].name);
      }
    }
  }

  calculateAllScores(); // again calculate
  Scoresorting(); // again sorting
  printf("Old Score: %d  ->  New Score: %d\n", old_score, zones[idx].score);
  printf("Old Rank : %d  ->  New Rank : %d\n", old_rank, zones[idx].rank);

  if (availablePower > 0) {
    printf("\n Facilities changed. Recalculating  power ""allocation with %d MW...\n",availablePower);
    greedyPowerAllocation(1);
  }
}

// Greedy

void greedyPowerAllocation(int autoRun) {
  int capacity;

  if (autoRun == 0) {
    printf("\n--- DISTRIBUTE POWER (Strict Priority / Greedy) ---\n");
    printf("Enter available power capacity (MW): ");
    scanf(" %d", &capacity);

    if (capacity <= 0) {
      printf("Invalid capacity!\n");
      return;
    }
    availablePower = capacity;
  } else {
    capacity = availablePower;
  }

  for (int i = 0; i < total_zones; i++) {
    zones[i].status = 0;
  }

  int total_weight = 0;
  int total_value = 0;
  //int powered_count = 0;

  printf("\n-- ZONES NOW POWERED --\n");
  
  for (int i = 0; i < total_zones; i++) {
    if (capacity >= zones[i].power_required) {
      zones[i].status = 1;
      capacity = capacity - zones[i].power_required;
      total_weight = total_weight + zones[i].power_required;
      total_value = total_value + zones[i].score;
      //powered_count++;
      
      printf("  >> %s is now POWERED  (Power: %d MW, Score: %d)\n",
             zones[i].name, zones[i].power_required, zones[i].score);
    }
  }

  printf("\n  Total power used : %d MW\n", total_weight);
  printf("  Total score      : %d\n", total_value);
}


void primsMinimumGrid() {
  int key[20];
  int tree[20];
  int parent[20];
  int total = 0;
  int total_all_cables = 0;

  for (int i = 0; i < total_zones; i++) {
    for (int j = i + 1; j < total_zones; j++) {
      if (powerGrid[i][j] != 0) {
        total_all_cables = total_all_cables + powerGrid[i][j];
      }
    }
  }

  printf("\n--- MINIMUM COST POWER GRID (Prim's) ---\n");
  printf("Zones: ");
  for (int i = 0; i < total_zones; i++) {
    printf("%d=%s  ", i, zones[i].name);
  }
  printf("\n");

  for (int i = 0; i < total_zones; i++) {
    key[i] = 999;
    tree[i] = 0;
    parent[i] = -1;
  }
  key[0] = 0;

  for (int i = 0; i < total_zones - 1; i++) {
    int u = -1, min = 999;
    for (int v = 0; v < total_zones; v++) {
      if (tree[v] == 0 && key[v] < min) {
        min = key[v];
        u = v;
      }
    }
    if (u == -1) {
      printf("No Spanning Tree\n");
      return;
    }

    tree[u] = 1;

    for (int v = 0; v < total_zones; v++) {
      if (powerGrid[u][v] != 0 && tree[v] == 0 && powerGrid[u][v] < key[v]) {
        key[v] = powerGrid[u][v];
        parent[v] = u;
      }
    }
  }

  printf("\nZone\t\t\tCost\tConnected To\n");
  printf("------------------------------------------------\n");

  for (int i = 0; i < total_zones; i++) {
    if (parent[i] == -1)
      printf("%-15s\t\t%d\t\tROOT\n", zones[i].name, key[i]);
    else
      printf("%-15s\t\t%d\t\t%s\n", zones[i].name, key[i], zones[parent[i]].name);
    total = total + key[i];
  }

  printf("\n--- COST ANALYSIS ---\n");
  printf("Cost of laying ALL possible cables : %d crore BDT\n",
         total_all_cables);
  printf("Cost of optimal Prim's MST network : %d crore BDT\n", total);
  printf("Total money SAVED by the algorithm : %d crore BDT\n",
         total_all_cables - total);
}


int main() {
  int choice = 0;
  calculateAllScores();
  Scoresorting();

  while (choice != 7) {
    showmenu();
    scanf("%d", &choice);

    if (choice == 1)
      viewALlrank();
    else if (choice == 2)
      viewPoweredZones();
    else if (choice == 3)
      greedyPowerAllocation(0);
    else if (choice == 4)
      manageFacilities();
    else if (choice == 5)
      resetPower();
    else if (choice == 6)
      primsMinimumGrid();
    else if (choice == 7)
      printf("\nGoodbye!\n\n");
    else
      printf("Invalid choice! Try again.\n");
  }
}

