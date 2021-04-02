#include "file.h"
#include "time_lapse.h"

int find_in_file(char name[STR_MAX], int data, int *temp_cmp)
{
    FILE *f = fopen(name, "r");
    int rc = 1;
    int temp_value;
    int position = 0;

    while (!feof(f))
    {
        position++;

        rc = fscanf(f, "%d", &temp_value);

        if (rc != TRUE)
        {
            break;
        }

        *temp_cmp += 1;

        if (temp_value == data)
        {
            fclose(f);
            return position;
        }
    }

    fclose(f);

    return -1;
}

void delete_in_file(char name[STR_MAX], int data, int *temp_cmp, uint64_t *time)
{
    int position;
    int arr[N_MAX];
    int n = 0;
    int rc;
    int temp_value;

    FILE *f = fopen(name, "r");

    uint64_t start = ticks();
    position = find_in_file(name, data, temp_cmp);

    if (position == -1)
    {
        uint64_t stop = ticks();
        *time = stop - start;
    }

    while (!feof(f))
    {
        rc = fscanf(f, "%d", &temp_value);
        if (rc != TRUE)
        {
            break;
        }
        arr[n] = temp_value;
        n++;
    }

    fclose(f);

    if (position != -1)
        *temp_cmp = position;
    else
    {
        *temp_cmp = n;
        return;
    }

    f = fopen(name, "w");

    for (int i = 0; i < n; i++)
        fprintf(f, "%d ", arr[i]);

    fclose(f);

    uint64_t stop = ticks();
    *time = stop - start;
}
