#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int fib(int a){
    if(a == 0){
        return 0;
    }else if(a == 1){
        return 1;
    }else{
        return fib(a-1) + fib(a-2);
    }
}

int main(int argc, char *argv[]){

    int res;
    int a = atoi(argv[1]);

    printf("Calculating %dth term of fibonnacci sequence.\n", a);

    clock_t before, after;
    float time;

    before = clock();

    res = fib(a);

    after = clock();

    time = 1000*((float)after-before)/CLOCKS_PER_SEC;

    printf("Result: %d\n", res);
    printf("Split result: %d, %d\n", (int)(res/256), res%256);
    printf("Time taken: %.10fms\n", time);

}