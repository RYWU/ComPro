//
//  main.cpp
//  4
//
//  Created by RYWU on 10/16/15.
//  Copyright (c) 2015 吳瑞洋公司. All rights reserved.
//  
/*  Attribution:
    
    Huge Thanks to 古耕竹 助教！

*/
/*
 Problem Description:
 Count the number of lucky number in [l, r].
 A number is lucky number if fulfilling the following three rules:
 * The integer n is divisible by 7.
 * The decimal representation of n contains at least three digits 7.
 * The decimal representation of n contains more digits 7 than digits
 ref: http://stackoverflow.com/questions/11045090/how-to-optimize-dynamic-programming
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

long long dp[20][20][20][7] = {0}; /* e.g. dp[18][18][9][6] 
                                    位數、七個數、四個數、餘數 */
void dp_init(long long dp[20][20][20][7]);
long long dp_build(int d, int a, int b, int c);
long long dp_lookup(long long n, int digit_pointer, 
                    int num_of_seven, int num_of_four, 
                    int remainder);
long long lucky_num_func(long long n);
                    
int main(int argc, const char * argv[]) {
    int T = 0;
    long long lucky_number_n1 = 0;
    long long lucky_number_n2 = 0;
    dp_init(dp);
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%lld", &lucky_number_n1);
        scanf("%lld", &lucky_number_n2);
        printf("%lld\n", lucky_num_func(lucky_number_n2)-lucky_num_func(lucky_number_n1-1));
    }return 0;
}

long long lucky_num_func(long long n){
    /*
     This function calculate the lucky number in [1, n].
     @param (long long) n: the lucky number you want to find.
     @return (long long): number of the lucky number in [1, n]
     */
    int digit_pointer = 0;
    int num_of_seven = 0;
    int num_of_four = 0;
    int remainder = 0;
    
    long long tmp = n;
    while (tmp / 10 != 0) {
        digit_pointer++;
        tmp /= 10;
    }    
    return dp_lookup(n, digit_pointer, num_of_seven, num_of_four, remainder);
}


long long dp_build(int d, int a, int b, int c){
    /*
     This function build the dp table from dp[d][a][b][c].
     @param (long long) d: digit pointer.
     @param (long long) a: num_of_seven.
     @param (long long) b: num_of_four.
     @param (long long) c: remainder.
     @return (int): number of lucky numbers in dp[d][a][b][c].
     */
    if (dp[d][a][b][c] != -1) return dp[d][a][b][c];    
     
    if (d == 0){
        dp[d][a][b][c] = 0;
        for (int i = 0; i < 10; i++) {
            if (i == 4) {
                if ((10*c+i) % 7 == 0 && a >= 3 && a > (b+1)){
                    dp[d][a][b][c] += 1;
                }
            }
            else if (i == 7) {
                if ((10*c+i) % 7 == 0 && (a+1) >= 3 && (a+1) > b){
                    dp[d][a][b][c] += 1;
                }
            }
            else {
                if ((10*c+i) % 7 == 0 && a >= 3 && a > b){
                    dp[d][a][b][c] += 1;
                }
            }
        }
    }
    else { // d != 0
        dp[d][a][b][c] = 0;
        for (int i = 0; i < 10; i++){
            if (i == 4) {
                dp[d][a][b][c] += dp_build(d-1, a, b+1, (10*c+i)%7);
            }
            else if (i == 7) {
                dp[d][a][b][c] += dp_build(d-1, a+1, b, (10*c+i)%7);
            }
            else {
                dp[d][a][b][c] += dp_build(d-1, a, b, (10*c+i)%7);
            }
        }
    }
    return dp[d][a][b][c];
}

long long dp_lookup(long long n, int digit_pointer, int num_of_seven, int num_of_four, int remainder){
    /*
     This function look up the dp[].
     @param (long long) n: the number for search.
     @param (long long) digit_pointer: 指到第一位數時, pointer = 0;
                                       指到第二位數時, pointer = 1, etc.
     @param (long long) num_of_seven: number of seven.
     @param (long long) num_of_four: number of four.
     @return (int): the amount of lucky number in the condition of 
                    [digit_pointer, num_of seven, num_of_four, remainder].
     */
    long long ret = 0;
    int pointed_num = 0;
    
    long long tmp = n;
    for (int i = 0; i < digit_pointer; i++) {
        tmp /= 10;
    }
    pointed_num = (int)tmp;
        
    if (digit_pointer == 0) {
        for (int i = 0; i <= pointed_num; i++) {
            if (i == 4){
                if (num_of_seven >= 3 && num_of_seven > (num_of_four+1) && (remainder*10+i)%7 == 0){
                    ret ++;
                }
            } else if (i == 7){
                if ((num_of_seven+1) >= 3 && (num_of_seven+1) > (num_of_four) && (remainder*10+i)%7 == 0){
                    ret ++;
                }
            } else { // i not 4, not 7.
                if ((num_of_seven) >= 3 && (num_of_seven) > (num_of_four) && (remainder*10+i)%7 == 0){
                    ret ++;
                }
            }
        }
    } else {
    
        for (int i = 0; i < pointed_num; i++) {
            if (i == 4){
                if (dp[digit_pointer-1][num_of_seven][num_of_four+1][(remainder*10+i)%7] == -1){
                    ret += dp_build(digit_pointer-1, num_of_seven, num_of_four+1, (remainder*10+i)%7);
                }
                else { // != -1
                    ret += dp[digit_pointer-1][num_of_seven][num_of_four+1][(remainder*10+i)%7];
                }
            }
            else if (i == 7){
                if (dp[digit_pointer-1][num_of_seven+1][num_of_four][(remainder*10+i)%7] == -1){
                    ret += dp_build(digit_pointer-1, num_of_seven+1, num_of_four, (remainder*10+i)%7);
                }
                else {
                    ret += dp[digit_pointer-1][num_of_seven+1][num_of_four][(remainder*10+i)%7];
                }
            }
            else { // i not 4, not 7.
                if (dp[digit_pointer-1][num_of_seven][num_of_four][(remainder*10+i)%7]){
                    ret += dp_build(digit_pointer-1, num_of_seven, num_of_four, (remainder*10+i)%7);
                }
                else {
                    ret += dp[digit_pointer-1][num_of_seven][num_of_four][(remainder*10+i)%7];
                }
            }
        }
    }
    // Shift one digit leftward.
    long long new_num = n - pointed_num * (long long)pow(10, digit_pointer);
    if (digit_pointer > 0) {
        if (pointed_num == 4){
            ret += dp_lookup(new_num, digit_pointer-1, num_of_seven, num_of_four+1, (remainder*10+pointed_num)%7);
        }
        else if (pointed_num == 7){
            ret += dp_lookup(new_num, digit_pointer-1, num_of_seven+1, num_of_four, (remainder*10+pointed_num)%7);
        }
        else {
            ret += dp_lookup(new_num, digit_pointer-1, num_of_seven, num_of_four, (remainder*10+pointed_num)%7);
        }
    }
    
    return ret;
}

void dp_init(long long dp[20][20][20][7]){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 20; k++) {
                for (int l = 0; l < 7; l++) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }
}
