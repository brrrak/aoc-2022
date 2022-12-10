#include <stdio.h>

const int CRT_LENGTH = 40;
void draw(int cycle_count, int x) {
    int pos = cycle_count - 1;
    if (pos % CRT_LENGTH >= x - 1 && pos % CRT_LENGTH <= x + 1) {
        printf("#");
    } else {
        printf(".");
    }
    if (cycle_count % CRT_LENGTH == 0)
        printf("\n");
}

int check_signal(int cycle_count, int x) {
    return (cycle_count % 40 == 20) ? x * cycle_count : 0;
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    int cycle_count = 0, x = 1, signal_strength = 0;

    while (!feof(fp)) {
        char buf[5];
        int num, inp_read = fscanf(fp, "%s %d", buf, &num);
        if (inp_read < 1) continue;
        if (inp_read < 2) {
            cycle_count++;
            draw(cycle_count, x);
            signal_strength += check_signal(cycle_count, x);
            continue;
        }

        for (int i = 0; i < 2; i++) {
            cycle_count++;
            draw(cycle_count, x);
            signal_strength += check_signal(cycle_count, x);
            if (i == 1) x += num;
        }
    }
    fclose(fp);
    printf("Part 1 Answer: %d\n", signal_strength);

    return 0;
}
