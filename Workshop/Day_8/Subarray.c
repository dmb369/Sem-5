#include <stdio.h>
#include <string.h>

#define L 100 // Defining the maximum length of each string

void find(char words[][L], int n) 
{
    int i, j;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            if (i != j && strstr(words[j], words[i]) != NULL) 
            {
                printf("%s ", words[i]);
                break; // Breaking out of inner loop to move to next word
            }
        }
    }
}

int main() {
    int n, i;
    
    printf("Enter number of words: ");
    scanf("%d", &n);

    char w[n][L];
    
    printf("Enter the words one by one:\n");
    for (i = 0; i < n; i++) scanf("%s", w[i]);
    
    printf("Substrings found in other words:\n");
    find(w, n);
    
    return 0;
}
