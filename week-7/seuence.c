#include <stdio.h>

void print(int f[], int n)
{
    for(int i=0;i<n;i++)
        (f[i]==-1)? printf("- ") : printf("%d ",f[i]);
    printf("\n");
}

void FIFO(int p[], int n, int f)
{
    int fr[f], k=0, pf=0;

    for(int i=0;i<f;i++) fr[i]=-1;

    printf("\nFIFO Page Replacement Process:\n");

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<f;j++)
            if(fr[j]==p[i]) found=1;

        if(!found)
        {
            fr[k]=p[i];
            k=(k+1)%f;
            pf++;

            printf("PF No. %d: ",pf);
            print(fr,f);
        }
    }
    printf("FIFO Page Faults: %d\n",pf);
}

void LRU(int p[], int n, int f)
{
    int fr[f], time[f], pf=0, c=0;

    for(int i=0;i<f;i++)
        fr[i]=-1, time[i]=0;

    printf("\nLRU Page Replacement Process:\n");

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<f;j++)
        {
            if(fr[j]==p[i])
            {
                time[j]=++c;
                found=1;
            }
        }

        if(!found)
        {
            int pos=0;

            for(int j=1;j<f;j++)
                if(time[j]<time[pos]) pos=j;

            fr[pos]=p[i];
            time[pos]=++c;
            pf++;

            printf("PF No. %d: ",pf);
            print(fr,f);
        }
    }
    printf("LRU Page Faults: %d\n",pf);
}

void OPT(int p[], int n, int f)
{
    int fr[f], pf=0;

    for(int i=0;i<f;i++) fr[i]=-1;

    printf("\nOptimal Page Replacement Process:\n");

    for(int i=0;i<n;i++)
    {
        int found=0;

        for(int j=0;j<f;j++)
            if(fr[j]==p[i]) found=1;

        if(!found)
        {
            int pos=-1, far=-1;

            for(int j=0;j<f;j++)
            {
                int k;

                for(k=i+1;k<n;k++)
                    if(fr[j]==p[k]) break;

                if(k>far)
                    far=k, pos=j;
            }

            fr[pos]=p[i];
            pf++;

            printf("PF No. %d: ",pf);
            print(fr,f);
        }
    }
    printf("Optimal Page Faults: %d\n",pf);
}

int main()
{
    int f,n;

    printf("Enter the number of Frames: ");
    scanf("%d",&f);

    printf("Enter the length of reference string: ");
    scanf("%d",&n);

    int p[n];

    printf("Enter the reference string: ");

    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    FIFO(p,n,f);
    LRU(p,n,f);
    OPT(p,n,f);

    return 0;
}
