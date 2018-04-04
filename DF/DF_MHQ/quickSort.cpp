#include "quickSort.h"

int part(wordCount a, int left, int right)
{
    int pivot = a[(left + right) / 2].count;
    int i = left - 1, j = right + 1;
    wordcount tmp;

    while (true)
    {
        do
        {
            i++;
        } while (a[i].count > pivot);
        do
        {
            j--;
        } while (a[j].count < pivot);

        if (i >= j)
            break;
        tmp.count = a[i].count;
        tmp.wordName = a[i].wordName;
        a[i].count = a[j].count;
        a[i].wordName = a[j].wordName;
        a[j].count = tmp.count;
        a[j].wordName = tmp.wordName;
    }
    return j;
}

int acompare(wordcount lhs, wordcount rhs) { return lhs.count > rhs.count; }
void seq(wordCount a, int left, int right)
{
    std::sort(&(a[left]), &(a[right + 1]), acompare);
}

void quicksort(wordCount a, int left, int right)
{
    if (!(right - left <= CUTOFF))
    {
        int p = part(a, left, right);
#pragma omp task
        quicksort(a, left, p);
#pragma omp task
        quicksort(a, p + 1, right);
#pragma omp taskwait
    }
    else
    {
        seq(a, left, right);
    }
}

void printArray(wordCount a, int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout
            << a[i].wordName << "\t" << a[i].count << "\n";
}

bool isArraySorted(wordCount a, int n)
{
    int i;
    for (i = 1; i < n; i++)
        if (a[i].count > a[i - 1].count)
            return false;
    return true;
}