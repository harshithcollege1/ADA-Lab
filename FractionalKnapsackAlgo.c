#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure for an item
struct Item {
    int weight;
    int value;
    float ratio;
};

// Function to sort items by value/weight ratio (descending)
void sort(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                struct Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

int main() {
    clock_t start_t, end_t;
    double total_t;

    int n;
    float capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];

    srand(time(0));

    printf("Generated items (value, weight):\n");
    for (int i = 0; i < n; i++) {
        items[i].value = rand() % 50 + 1;
        items[i].weight = rand() % 10 + 1;
        items[i].ratio = (float)items[i].value / items[i].weight;

        printf("%d: %d, %d\n", i + 1, items[i].value, items[i].weight);
    }

    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);

    sort(items, n);

    float totalValue = 0.0;

    start_t = clock();
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].ratio * capacity;
            break;
        }
    }
    end_t = clock();

    printf("Maximum value = %.2f\n", totalValue);
    total_t = (end_t - start_t)/CLOCKS_PER_SEC;
    printf("\nTime taken: %f", total_t);

    return 0;
}
