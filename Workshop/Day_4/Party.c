# include<stdio.h>

int main()
{
    int n;
    printf("Enter the total number of guests in the party:");
    scanf("%d", &n);

    int entry[n], exit[n];
    for (int i=0; i<n; i++) scanf("%d", &entry[i]);
    for (int j=0; j<n; j++) scanf("%d", &exit[j]);

    int m = -1, c = 0;
    int i = 0, j=0;
    int time = entry[0];

    while(i<n && j<n)
    {
        if (entry[i]<=exit[j])
        {
            c+=1;
            if (m<c) 
            {
                m=c;
                time = entry[i];
            }
            i+=1;
        }
        else
        {
            c-=1;
            j+=1;
        }
    }

    printf("%d %d", m, time);
    return 0;
}