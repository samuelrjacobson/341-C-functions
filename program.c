#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
/* compute pi using first n terms of infinite sum */
double compute_pi(int n)
{
    double sum = 0.0;
    double denom = 1.0;
    int i;
    double val;
    for (i = 1; i <= n; i++)
    {
        val = 4.0 / denom ; /* calculate value of term i */
        if (i % 2 == 0) val *= -1.0; /* flip sign for every other term */
        sum += val; /* add value to sum */
        denom += 2; /* increment denominator for next term */
    }
    return sum;
}
/* compute square root of x */
double compute_sqrt(double x)
{
    double last = 1.0;
    double next;
    int i;
    for (i = 0; i < 10; i++) /* repeatedly approximate closer */
    {
        next = 0.5 * (last + x / last);
        last = next;
    }
    return next; /* return approximation of sqrt(x) */
}
/* determine whether n is prime*/
int is_prime(int n)
{
    int prime = TRUE;
    int i;
    for (i = 2; i <= n / 2; i++) /* check each number 2 to n */
    {
        if (n % i == 0) /* if it's a factor of n, prime = false */
        {
            prime = FALSE;
            break;
        }
    }
    return prime; /* return true/false (prime or not) */
}
/* display all prime numbers less than or equal to n */
void display_primes(int n)
{
    int i;
    for (i = 2; i <= n; i++)
    {
        if (is_prime(i)) printf("%d\n", i); /* print if prime */
    }
}
/* receive test scores and display summary data */
void process_scores( )
{
    char name[20];
    int score;
    int min;
    char min_name[20];
    int max;
    char max_name[20];
    double avg = 0;
    int count_students = 0;

    while (1)
    {
        printf("Enter a name and score: ");
        scanf("%s", name);

        if (name[0] == 'q' || name[0] == 'Q') break; /* quit when user inputs q */

        scanf("%d", &score);

        /* set variables in first iteration */
        if (count_students == 0)
        {
            strcpy(min_name, name);
            strcpy(max_name, name);
            min = score;
            max = score;
        }
        else
        {
            if (score < min) /* Find minimum score */
            {
                min = score;
                strcpy(min_name, name);
            }
            if (score > max) /* Find maximum score */
            {
                max = score;
                strcpy(max_name, name);
            }
        }
        avg += score; /* calculate average */
        count_students++;
    }
    avg /= count_students;

    /* display summary data */
    printf("Average: %f\nMinimum: %d\nMaximum: %d\n", avg, min, max);
    printf("Student with lowest score: %s\n", min_name);
    printf("Student with highest score: %s\n", max_name);
}
/* calculate tax amount */
double compute_tax(int income, char *status, char state)
{
    double tax_rate;
    /* calculate base rate (instate) */
    if (state == 'i' || state == 'I' || state == 'o' || state == 'O')
    {
        if (*status == 's' || *status == 'S') /* Single */
        {
            if (income < 40000) tax_rate = 0.30; /* Income */
            else tax_rate = 0.35;
        }
        else if (*status == 'm' || *status == 'M') /* Married */
        {
            if (income < 60000) tax_rate = 0.20; /* Income */
            else tax_rate = 0.25;
        } 
    }
    /* adjust for out-of-state */
    if (state == 'o' || state == 'O')
    {
        tax_rate -= .03;
    }
    return tax_rate;
}
/* perform quadratric formula given coefficients */
int quadratic(double a, double b, double c, double *solution1, double *solution2)
{
    double discriminant = b*b - 4 * a * c; /* calculate discriminant */
    if (discriminant < 0){ /* check whether there are solutions */
        *solution1 = -1.0;
        *solution2 = -1.0;
        return FALSE;
    }
    else /* calculate two solutions */
    {
        *solution1 = (-b + sqrt(discriminant)) / (2 * a);
        *solution2 = (-b - sqrt(discriminant)) / (2 * a);
        return TRUE;
    }
}
/* calculate sum of squares from 1 to n */
int sum_squares(int n)
{
    if (n < 2) return 1;
    return n * n + sum_squares(n - 1); /* recursive call with n - 1 */
}
/* count characters, blanks and lines in a file */
void file_count(char *file, int *characters, int *blanks, int *lines)
{
    FILE *fp = fopen(file, "r"); /* open file for reading */
    char ch;
    *characters = 0;
    *blanks = 0;
    *lines = 0;

    /* read characters until break upon EOF */
    while(1)
    {
        ch = getc(fp);
        (*characters)++; /* incremement character counter for each character */

        if (isspace(ch))
        {
            (*blanks)++; /* increment blank counter for each blank */
        }
        if (ch == '\n' || ch == EOF)
        {
            (*lines)++; /* increment line counter for each line */
        }
        if (ch == EOF) break; /* end when end of file is reached */
    }
    fclose(fp);
}
/* read student information from file, sort and output to file */
void file_sort(char *infile, char *outfile)
{
    FILE *in = fopen(infile, "r"); /* open file for reading */
    int m;
    fscanf(in, "%d", &m); /* get number of students */
    
    /* dynamically allocate arrays for data */
    int *id = (int *) malloc(m * sizeof (int));
    char *grade = (char *) malloc(m * sizeof (char));
    double *gpa = (double *) malloc(m * sizeof (double));

    /* read values to arrays */
    int i;
    for (i = 0; i < m; i++)
    {
        fscanf(in, "%d", id + i); /* add value to id array */
        char ch = ' ';
        while (isspace(ch)) /* discard whitespace */
        {
            ch = getc(in);
        }
        grade[i] = ch; /* add value to grade array */
        fscanf(in, "%lf", gpa + i); /* add value to gpa array */
    }

    /* insertion sort by id */
    for (i = 1; i < m; i++)
    {
        int id_to_sort = id[i];
        char grade_to_sort = grade[i];
        double gpa_to_sort = gpa[i];

        int j;
        for(j = i - 1; j >= 0; j--)
        {
           if(id[j] < id_to_sort) break;
           id[j + 1] = id[j];
           grade[j + 1] = grade[j];
           gpa[j + 1] = gpa[j];
        }
        id[j + 1] = id_to_sort;
        grade[j + 1] = grade_to_sort;
        gpa[j + 1] = gpa_to_sort;
    }

    FILE *out = fopen(outfile, "w"); /* write info to output file */
    for(i = 0; i < m; i++)
    {
        fprintf(out, "%d %c %lf\n", id[i], grade[i], gpa[i]);
    }
    free(id);
    free(grade);
    free(gpa);

    fclose(in);
    fclose(out);
}
/* read student information from file, print average gpa,
    print names of students whose gpa is no more than 3.0,
    print all data in ascending order by id */
void file_student(char *infile)
{
    /* open file for reading */
    FILE *fp = fopen(infile, "r");
    int student_count;
    fscanf(fp, "%d", &student_count); /* get number of students */
    
    /* declare student structure */
    struct student {
        char name[20];
        int id;
        int age;
        double gpa;
    };

    /* dynamically create array of student structures*/
    struct student *students = (struct student *) malloc(student_count * sizeof (struct student));

    /* read student information into array */
    double avg_gpa;
    int i;
    for (i = 0; i < student_count; i++)
    {
        fscanf(fp, "%s%d%d%lf", students[i].name, &(students[i].id), &(students[i].age), &(students[i].gpa));
        avg_gpa += students[i].gpa; /* add up gpa values while reading */
    }

    /* find and print average gpa */
    avg_gpa /= (double) student_count;
    printf("Average GPA: %lf\n", avg_gpa);
    
    /* print names of students with GPA 3.0 or below */
    for (i = 0; i < student_count; i++) {
        if (students[i].gpa <= 3.0)
            printf("%s has a GPA equal or under 3.0\n", students[i].name);
    }

    /* insertion Sort by id */
    for (int i = 1; i < student_count; i++) {
        char name_to_sort[20];
        strcpy(name_to_sort, students[i].name);
        int id_to_sort = students[i].id;
        int age_to_sort = students[i].age;
        double gpa_to_sort = students[i].gpa;

        int j;
        for(j = i - 1; j >= 0; j--) {
            if(students[j].id < id_to_sort) break;
            strcpy(students[j + 1].name, students[j].name);
            students[j + 1].id = students[j].id;
            students[j + 1].age = students[j].age;
            students[j + 1].gpa = students[j].gpa;
        }
        strcpy(students[j + 1].name, name_to_sort);
        students[j + 1].id = id_to_sort;
        students[j + 1].age = age_to_sort;
        students[j + 1].gpa = gpa_to_sort;
    }
    /* print student data in ascending order by id */
    for (int i = 0; i < student_count; i++) {
        printf("%s %d %d %lf\n", students[i].name, students[i].id, students[i].age, students[i].gpa);
    }

    free(students);
    fclose(fp);
}
/* menu for user to access options */
int main()
{
    while (1) /* let user execute multiple options until terminating program */
    {
        /* display menu */
        printf("\nSelect an option:\n1-computing pi\n2-computing square root\n");
        printf("3-displaying primes\n4-processing grades\n5-computing tax\n");
        printf("6-solving quadratic\n7-computing sum squares\n8-counting file\n");
        printf("9-sorting file\n10-student file\n11-quit\n");

        /* get option number from user */
        int option;
        scanf("%d", &option);

        /* execute corresponding option based on user selection */
        if (option == 1) /* pi calculation */
        {
            printf("Enter an integer to use as the number of terms in the infinite sum calculation: ");
            int n;
            scanf("%d", &n);
            double pi = compute_pi(n);
            printf("Pi is approximately equal to %lf\n", pi);
        }
        else if (option == 2) /* sqrt calculation */
        {
            printf("Enter a number to find out its square root: ");
            double x;
            scanf("%lf", &x);
            double root = compute_sqrt(x);
            printf("The square root of %lf is %lf\n", x, root);
        }
        else if (option == 3) /* prime numbers */
        {
            printf("Enter a number to see all prime numbers less than or equal to it: ");
            int n;
            scanf("%d", &n);
            display_primes(n);
        }
        else if (option == 4) /* process grades */
        {
            process_scores();
        }
        else if (option == 5) /* tax computation */
        {
            int income;
            printf("Enter income: ");
            scanf("%d", &income);
            char status[7];
            printf("Enter married/single status: ");
            scanf("%s", status);
            char state;
            printf("Enter i for instate or o for out-of-state: ");
            scanf(" %c", &state);
            double tax_amount = compute_tax(income, status, state);
            printf("Your tax amount is %lf\n", tax_amount);
        }
        else if (option == 6) /* quadratic forumla */
        {
            int a, b, c;
            double solution1, solution2;
            printf("Enter coefficient a: ");
            scanf("%d", &a);
            printf("Enter coefficient b: ");
            scanf("%d", &b);
            printf("Enter coefficient c: ");
            scanf("%d", &c);

            /* if there are solutions, print them */
            if (quadratic(a, b, c, &solution1, &solution2))
            {
                printf("Solutions: %lf\t%lf\n", solution1, solution2);
            }
            else
            {
                printf("There is no solution.\n");
            }
        }
        else if (option == 7) /* sum of squares */
        {
            int n;
            printf("Enter an integer n to see sum of squares from 1 to n: ");
            scanf("%d", &n);
            int sum = sum_squares(n);
            printf("%d\n", sum);
        }
        else if (option == 8) /* count characters in file */
        {
            char file[20];
            int c, b, l;
            printf("Enter a filename with type extension: ");
            scanf("%s", file);
            file_count(file, &c, &b, &l);
            printf("Characters: %d\nBlanks: %d\nLines: %d\n", c, b, l);
        }
        else if (option == 9) /* read student data from file, sort to output file */
        {
            char in[20];
            char out[20];
            printf("Enter an input file with type extension: ");
            scanf("%s", in);
            printf("Enter an output file with type extension: ");
            scanf("%s", out);
            file_sort(in, out);
            printf("Your output file is ready!\n");
        }
        else if (option == 10) /* read student data from file, print summary data and sorted info */
        {
            char in[20];
            printf("Enter an input file with type extension: ");
            scanf("%s", in);
            file_student(in);
        }
        else if (option == 11) /* quit */
        {
            printf("Have a nice day!");
            break;
        }
    }
    return 0; /* end of main */
}