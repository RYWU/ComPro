// ref: Merge Sort - http://www.cprogramming.com/tutorial/computersciencetheory/merge.html
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int cmp(int x, int y) ;
void merge_helper(int *input, int left, int right, int *scratch);
int mergesort(int *input, int size);
int delta(int x, int y, int c, long long e, int p);
long long fast_pow(long long a,long long n);
void build_pow_table(long long pow_table[], long long n, long long e);
void build_minux_table(long long x_minus_y[], long long c, long long n);

long long n = 0; // 2≤n≤200000
long long c = 0; // 1≤c<p
long long e = 0; // 0≤e≤10^18
long long p = 0; // 2n<p≤2×10^9
long long pow_table[400002] = {0};
long long x_minus_y[200000];

// ( int(c * (x-y) * pow(x+y, e)) % p + p) % p > float(p/2)

int main(){
    
    int total_number_of_testcases = 0;
    scanf("%d", &total_number_of_testcases);
    
    for (int i = 0; i < total_number_of_testcases; i++) {
        scanf("%lld", &n);
        scanf("%lld", &c);
        scanf("%lld", &e);
        scanf("%lld", &p);
        
        build_pow_table(pow_table, n, e);
        build_minux_table(x_minus_y, c, n);

        
        int in[200001] = {0};
        for (int i = 0; i < n; i++) {
            in[i] = i+1;
        }
        
        mergesort(in, int(n));
        
        for (int i = 0; i < n; i++) {
            printf("%d ", in[i]);
        }
        printf("\n");
    }
    
    return 0;
}

/*
 
 Sample Input
 
 3
 2 1 0 5
 3 5 8 13
 8 5 3 37
 Sample Output
 
 1 2
 1 2 3
 7 3 8 6 2 5 4 1
 */

void build_minux_table(long long x_minus_y[], long long c, long long n){
    for (int i = 0; i < n; ++i)
    {
        x_minus_y[i] = c * (i) % p;
    }
}

void build_pow_table(long long pow_table[], long long n, long long e){
    int isPrime = 1;
    pow_table[2] = fast_pow(2, e);
    pow_table[3] = fast_pow(3, e);
    for (int i = 4; i <= 2*n; ++i)
    {
        if (i & 1){ // is odd
            for (int j = 2; j < sqrt(i)+1; j++){
                if (i % j == 0){
                    pow_table[i] = pow_table[j] * pow_table[i/j] % p;
                    isPrime = 0;
                    break;
                }
            }
            if (isPrime){
                pow_table[i] = fast_pow(i, e) % p;
            }
            else{
            }
            
            isPrime = 1;
        }
        else { // id even
            pow_table[i] = pow_table[i/2] * pow_table[2] % p;
        }
    }
    //    printf("ncep: %lld %lld %lld %lld\n", n, c, e, p);
    //    for (int i = 2; i < 2*n; i++){
    //        printf("i table[i]: %d %lld\n", i, pow_table[i]);
    //    }
}

long long fast_pow(long long a,long long n)
{
    long long result = 1;
    long long power = n;
    long long value = a;
    
    while(power>0)
    {
        if(power&1) // is odd
        {
            result = result * value % p;
        }
        value = value * value % p;
        power /= 2;
        //power >>= 1;
    }
    return result;
}

int cmp(int x, int y)
{
    // ( int(c * (x-y) * pow(x+y, e)) % p + p) % p > float(p/2)
//    printf("x-y: %d, xminy: %lld\n", x-y, x_minus_y[x-y]);
    if(  ( -1 * x_minus_y[y-x] * pow_table[x+y] % p + p) > p/2  )
    {
        return x;
    }
    else
    {
        return y;
    }
    
    
}

/* left is the index of the leftmost element of the subarray; right is one
 * past the index of the rightmost element */
void merge_helper(int *input, int left, int right, int *scratch)
{
    /* base case: one element */
    if(right == left + 1)
    {
        return;
    }
    else
    {
        int i = 0;
        int length = right - left;
        int midpoint_distance = length/2;
        /* l and r are to the positions in the left and right subarrays */
        int l = left, r = left + midpoint_distance;
        
        /* sort each subarray */
        merge_helper(input, left, left + midpoint_distance, scratch);
        merge_helper(input, left + midpoint_distance, right, scratch);
        
        /* merge the arrays together using scratch for temporary storage */
        for(i = 0; i < length; i++)
        {
            /* Check to see if any elements remain in the left array; if so,
             * we check if there are any elements left in the right array; if
             * so, we compare them.  Otherwise, we know that the merge must
             * use take the element from the left array */
            if(l < left + midpoint_distance &&
               (r == right || cmp(input[l], input[r]) == input[l]))
            {
                scratch[i] = input[l];
                l++;
            }
            else
            {
                scratch[i] = input[r];
                r++;
            }
        }
        /* Copy the sorted subarray back to the input */
        for(i = left; i < right; i++)
        {
            input[i] = scratch[i - left];
        }
    }
}

/* mergesort returns true on success.  Note that in C++, you could also
 * replace malloc with new and if memory allocation fails, an exception will
 * be thrown.  If we don't allocate a scratch array here, what happens?
 *
 * Elements are sorted in reverse order -- greatest to least */

int mergesort(int *input, int size)
{
    int *scratch = (int *)malloc(size * sizeof(int));
    if(scratch != NULL)
    {
        merge_helper(input, 0, size, scratch);
        free(scratch);
        return 1;
    }
    else
    {
        return 0;
    }
}
