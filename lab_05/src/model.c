#define __USE_MINGW_ANSI_STDIO 1

#include "model.h"

double random_double(double bottom, double top)
{
    double range = top - bottom;
    double div = RAND_MAX / range;

    return bottom + (rand() / div);
}

double tick(double request_time[COUNT], double end)
{
    double min = end;

    for (size_t i = 0; i < COUNT; i++)
        if (request_time[i] < min)
            min = request_time[i];

    return min;
}

double calculate_time(times_t queue, size_t requests_num)
{
    double d1 = queue.in_time_t1[1] + queue.in_time_t1[0];
    double d2 = queue.oper_time_t1[1] + queue.oper_time_t1[0];
    double max = d1;
    double res;

    if (d2 > max)
        max = d2;

    res = requests_num * max / 2;

    return res;
}

int model_list_queue(queue_list_t *q_1, queue_list_t *q_2)
{
    FILE *f_out;

    f_out = fopen("txt/address.txt", "w");

    double request_time[COUNT] = {0};
    double req_on_time[COUNT] = {0};
    size_t req_processed[COUNT] = {0};
    size_t req_processed_all = 0;
    size_t req_generated_all = 0;

    double oper_end_time = 0;
    double curr_time = 0;
    double last_time = 0;

    times_t t;

    init_times(&t);

    request_time[0] = random_double(t.in_time_t1[0], t.in_time_t1[1]);
    request_time[1] = random_double(t.in_time_t2[0], t.in_time_t2[1]);

    while (req_processed[0] < NUM_T1)
    {
        //printf("oper_end_time = %lf, curr_time = %lf\n", oper_end_time, curr_time);
        //printf("%zu\n", req_processed[0]);
        // Добавление новых заявок
        if (curr_time >= request_time[0])
        {
            request_t r = {req_generated_all++};
            push_queue_list(&r, q_1);
            request_time[0] = curr_time + random_double(t.in_time_t1[0], t.in_time_t1[1]);
            fprintf(f_out, "Add: %p\n", &(q_1->tail->data.address));
        }
        if (curr_time >= request_time[1])
        {
            request_t r = {req_generated_all++};
            push_queue_list(&r, q_2);
            request_time[1] = curr_time + random_double(t.in_time_t2[0], t.in_time_t2[1]);
            fprintf(f_out, "Add: %p\n", &(q_2->tail->data.address));
        }

        // Обработка одной заявки
        if (curr_time >= oper_end_time)
        {
            //printf("curr_time >= oper_end_time ");
            queue_list_t *cur_q = q_1;
            int cur_queue_num = 1;
            if (is_empty_queue_list(cur_q))
            {
                cur_queue_num++;
                cur_q = q_2;
            }

            if (is_empty_queue_list(cur_q))
            {
                curr_time = request_time[0];
                if (curr_time > request_time[1])
                    curr_time = request_time[1];
                //curr_time = tick(request_time, request_time[0] + request_time[1]);
                continue;
            }

            request_t r;
            pop_queue_list(cur_q, &r);
            if (cur_queue_num == 1)
                req_processed[0] += 1;
            else
                req_processed[1] += 1;

            req_processed_all += 1;

            fprintf(f_out, "Del: %p\n", &(r.address));

            if (cur_queue_num == 1)
                oper_end_time = curr_time + random_double(t.oper_time_t1[0], t.oper_time_t1[1]);
            else
                oper_end_time = curr_time + random_double(t.oper_time_t2[0], t.oper_time_t2[1]);

            if (cur_queue_num == 1 && req_processed[0] % 100 == 0)
            {
                printf("Обработано: ");
                size_t sum = 0;
                for (size_t i = 0; i < COUNT; i++)
                {
                    printf("%zu + ", req_processed[i]);
                    sum += req_processed[i];
                }
                printf("\b\b= %zu (из %zu вошедших)\n", sum, req_generated_all);

                printf("Текущая длина очередей:\n");
                printf("- заявок 1 типа: %zu\n", q_1->cur_len);
                printf("- заявок 2 типа: %zu\n", q_2->cur_len);

                printf("Средняя длина очередей:\n");
                printf("- заявок 1 типа: %lf\n", req_on_time[0] / curr_time);
                printf("- заявок 2 типа: %lf\n", req_on_time[1] / curr_time);

                printf("Поступило заявок: %zu\n", req_generated_all);
                printf("Прошло времени: %lf е.в.\n", curr_time);
                printf("————————————————————————————\n");
            }
        }

        double diff = curr_time - last_time;

        req_on_time[0] += q_1->cur_len * diff;
        req_on_time[1] += q_2->cur_len * diff;

        last_time = curr_time;
        curr_time = tick(request_time, oper_end_time);
    }

    double expect_time = calculate_time(t, NUM_T1);

    double perc_pogr = fabs((1 - curr_time / expect_time)) * 100;

    printf("Обработано:\n");
    size_t sum = 0;
    for (size_t i = 0; i < COUNT; i++)
    {
        printf("- заявок %zu типа: %zu\n", i + 1, req_processed[i]);
        sum += req_processed[i];
    }

    printf("Всего обработано: %zu \n", sum);
    printf("Поступило заявок: %zu \n", req_generated_all);

    printf("Рассчитатаное время работы:   %lf \n", expect_time);
    printf("Смоделированной время работы: %lf \n", curr_time);
    printf("Погрешность: %lf%% \n", perc_pogr);

    fclose(f_out);

    return EXIT_SUCCESS;
}

int model_array_queue(queue_array_t *q_1, queue_array_t *q_2)
{
    double request_time[COUNT] = {0};
    double req_on_time[COUNT] = {0};
    size_t req_processed[COUNT] = {0};
    size_t req_processed_all = 0;
    size_t req_generated_all = 0;

    double oper_end_time = 0;
    double curr_time = 0;
    double last_time = 0;

    times_t t;

    init_times(&t);

    request_time[0] = random_double(t.in_time_t1[0], t.in_time_t1[1]);
    request_time[1] = random_double(t.in_time_t2[0], t.in_time_t2[1]);

    while (req_processed[0] < NUM_T1)
    {
        // Добавление новых заявок
        if (curr_time >= request_time[0])
        {
            request_t r = {req_generated_all++};
            push_queue_array(q_1, &r);
            request_time[0] = curr_time + random_double(t.in_time_t1[0], t.in_time_t1[1]);
        }
        else if (curr_time >= request_time[1])
        {
            request_t r = {req_generated_all++};
            push_queue_array(q_2, &r);
            request_time[1] = curr_time + random_double(t.in_time_t2[0], t.in_time_t2[1]);
        }

        // Обработка одной заявки
        if (curr_time >= oper_end_time)
        {
            queue_array_t *cur_q = q_1;
            int cur_queue_num = 1;
            if (is_empty_queue_array(cur_q))
            {
                cur_queue_num = 2;
                cur_q = q_2;
            }

            if (is_empty_queue_array(cur_q))
            {
                curr_time = request_time[0];
                if (curr_time > request_time[1])
                    curr_time = request_time[1];
                //curr_time = tick(request_time, request_time[0] + request_time[1]);
                continue;
            }

            request_t r;
            pop_queue_array(cur_q, &r);
            //printf("q_1 cur len = %zu\n", q_1->cur_len);
            //printf("q_2 cur len = %zu\n", q_2->cur_len);

            if (cur_queue_num == 1)
                req_processed[0] += 1;
            else
                req_processed[1] += 1;

            req_processed_all += 1;

            if (cur_queue_num == 1)
                oper_end_time = curr_time + random_double(t.oper_time_t1[0], t.oper_time_t1[1]);
            else
                oper_end_time = curr_time + random_double(t.oper_time_t2[0], t.oper_time_t2[1]);

            if (cur_queue_num == 1 && req_processed[0] % 100 == 0)
            {
                printf("Обработано: ");
                size_t sum = 0;
                for (size_t i = 0; i < COUNT; i++)
                {
                    printf("%zu + ", req_processed[i]);
                    sum += req_processed[i];
                }
                printf("\b\b= %zu (из %zu вошедших)\n", sum, req_generated_all);

                printf("Текущая длина очередей:\n");
                printf("- заявок 1 типа: %zu\n", q_1->cur_len);
                printf("- заявок 2 типа: %zu\n", req_generated_all - sum);

                printf("Средняя длина очередей:\n");
                printf("- заявок 1 типа: %lf\n", req_on_time[0] / curr_time);
                printf("- заявок 2 типа: %lf\n", req_on_time[1] / curr_time);

                printf("Поступило заявок: %zu\n", req_generated_all);
                printf("Прошло времени: %lf е.в.\n", curr_time);
                printf("————————————————————————————\n");
            }
        }

        double diff = curr_time - last_time;

        req_on_time[0] += q_1->cur_len * diff;
        req_on_time[1] += q_2->cur_len * diff;

        last_time = curr_time;
        curr_time = tick(request_time, oper_end_time);
    }

    double expect_time = calculate_time(t, NUM_T1);

    double perc_pogr = fabs((1 - curr_time / expect_time)) * 100;

    printf("Обработано:\n");
    size_t sum = req_processed[0] + req_processed[1];

    printf("- заявок 1 типа: %zu\n", req_processed[0]);
    printf("- заявок 2 типа: %zu\n", req_processed[1]);

    printf("Всего обработано: %zu \n", sum);
    printf("Поступило заявок: %zu \n", req_generated_all);

    printf("Рассчитатаное время работы:   %lf \n", expect_time);
    printf("Смоделированной время работы: %lf \n", curr_time);
    printf("Погрешность: %lf%% \n", perc_pogr);

    return EXIT_SUCCESS;
}
