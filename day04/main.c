#include <stdio.h>

int main() {
    int contained_count = 0, overlap_count = 0;

    FILE *fp = fopen("input.txt", "r");
    while (!feof(fp)) {
        int s1 = 0, e1 = 0, s2 = 0, e2 = 0;
        if (fscanf(fp, "%d-%d,%d-%d", &s1, &e1, &s2, &e2) < 4) {
            continue;
        }

        // check if one contains the other
        if ((s1 >= s2 && e1 <= e2) || (s2 >= s1 && e2 <= e1)) {
            ++contained_count;
        }

        // check if there is an overlap
        if ((s1 <= s2 && s2 <= e1) || (s2 <= s1 && s1 <= e2)) {
            ++overlap_count;
        }
    }

    printf("Part 1 Answer: %d\n", contained_count);
    printf("Part 2 Answer: %d\n", overlap_count);

    return 0;
}