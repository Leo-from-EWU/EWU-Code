#include <stdio.h>
#include <stdlib.h>

struct knapsack
{
    int item;
    int weight;
    int benefit;
    // int value;                 // BUG: ratio benefit/weight is fractional -> int truncates it
    float value;                  // FIX: float keeps the decimals of the ratio
};

int main()
{
    int total_weight = 10;
    int small_weight = 0;

    int tracker_weight;
    int profit_tracker;
    // int benefit_tracker = 0;   // BUG: total profit can be fractional (when a part of an item is taken)
    float benefit_tracker = 0;    // FIX: float so the partial-item profit is kept
    int item_tracker;
    int selected_index;           // FIX (NEW): remember WHICH item we picked, so we remove it by index
    int remaining_weight;

    struct knapsack arr[] = {
        {1, 4, 12, 0},
        {2, 8, 32, 0},
        {3, 2, 40, 0},
        {4, 6, 30, 0},
        {5, 1, 50, 0},

    };

    for (int i = 0; i < 5; i++)
    {
        // arr[i].value = arr[i].benefit / arr[i].weight;       // BUG: integer division
        arr[i].value = (float)arr[i].benefit / arr[i].weight;   // FIX: cast -> real ratio
        // printf("%d\n", arr[i].value);                        // BUG: %d on a float
        printf("Item %d ratio (benefit/weight) = %.2f\n", arr[i].item, arr[i].value);
    }

    // while (small_weight <= total_weight)     // BUG: <= keeps looping after the jar is already full
    while (small_weight < total_weight)         // FIX: stop once the jar is full
    {
        // int highest_value = 0;               // BUG: ratio is a float now, compare as float
        float highest_value = 0;                // FIX: highest ratio found this round
        selected_index = -1;                    // FIX: -1 means "nothing selected yet"
        for (int i = 0; i < 5; i++)
        {
            if (arr[i].value != 0)
            {

                if (arr[i].value > highest_value)
                {
                    highest_value = arr[i].value;    // biggest ratio so far
                    tracker_weight = arr[i].weight;
                    profit_tracker = arr[i].benefit;
                    item_tracker = arr[i].item;
                    selected_index = i;              // FIX: record the chosen item's index
                }
            }
        }

        if (selected_index == -1)   // FIX: no items left -> stop
            break; // best case for stopping the loop when alrady filled.

        remaining_weight = total_weight - small_weight;   // space left in the jar

        // if ( (tracker_weight + small_weight) > total_weight)   // OLD: capped the weight ...
        //     tracker_weight = total_weight - small_weight;
        // small_weight = tracker_weight + small_weight;
        // benefit_tracker = profit_tracker + benefit_tracker;    // BUG: ... but still added the FULL profit
        if (tracker_weight <= remaining_weight)                   // FIX: whole item fits
        {
            small_weight = small_weight + tracker_weight;
            benefit_tracker = benefit_tracker + profit_tracker;
            printf("Item :%d fully taken  -> weight used : %d, profit: %d, remaining jar: %d\n",
                   item_tracker, tracker_weight, profit_tracker, (total_weight - small_weight));
        }
        else                                                      // FIX: only a fraction fits
        {
            float fraction_profit = profit_tracker * ((float)remaining_weight / tracker_weight);
            benefit_tracker = benefit_tracker + fraction_profit;
            printf("Item :%d partly taken -> weight used : %d of %d, profit: %.2f, remaining jar: 0\n",
                   item_tracker, remaining_weight, tracker_weight, fraction_profit);
            small_weight = total_weight;                          // jar is now full
        }

        // for (int i = 0; i < 5; i++)                  // BUG: removing by matching value deletes
        // {                                            //      EVERY item that shares the same ratio
        //     if (arr[i].value == highest_value)
        //     {
        //         arr[i].benefit = 0;
        //         arr[i].value = 0;
        //         arr[i].weight = 0;
        //     }
        // }
        arr[selected_index].benefit = 0;                // FIX: remove only the picked item, by index
        arr[selected_index].value = 0;
        arr[selected_index].weight = 0;
    }

    printf("\nTotal profit = %.2f\n", benefit_tracker); // FIX: print the total profit at the end
    return 0;
}
