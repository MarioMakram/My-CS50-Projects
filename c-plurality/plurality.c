#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void mergeSort(candidate arr[], int left, int right);
void merge(candidate arr[], int left, int mid, int right);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    // If no match, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Find the maximum number of votes
    int left = 0;
    int right = candidate_count - 1;

    mergeSort(candidates, left, right);

    // Print name of winner/s.
    printf("%s\n", candidates[right].name);

    for (int i = right; i > 0; i--)
    {
        if (candidates[i - 1].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i - 1].name);
        }
        else
        {

            return;
        }
    }

    return;
}

// Recursive merge sort function
void mergeSort(candidate arr[], int left, int right)
{
    if (left < right)
    {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to merge two halves
void merge(candidate arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    candidate L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
    {
        L[i].name = arr[left + i].name;
        L[i].votes = arr[left + i].votes;
    }

    for (int j = 0; j < n2; j++)
    {
        R[j].name = arr[mid + 1 + j].name;
        R[j].votes = arr[mid + 1 + j].votes;
    }

    // Merge the temp arrays back into arr[]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].votes <= R[j].votes)
        {
            arr[k].name = L[i].name;
            arr[k++].votes = L[i++].votes;
        }
        else
        {
            arr[k].name = R[j].name;
            arr[k++].votes = R[j++].votes;
        }
    }

    // Copy the remaining elements
    while (i < n1)
    {
        arr[k].name = L[i].name;
        arr[k].votes = L[i].votes;
        k++;
        i++;
    }
    while (j < n2)
    {
        arr[k].name = R[j].name;
        arr[k].votes = R[j].votes;
        k++;
        j++;
    }
}
