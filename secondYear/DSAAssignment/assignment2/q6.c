#include<stdio.h>
#include <limits.h>
// INT_MIN  INT_MAX
#define arr_size 5

typedef struct{
    int arr[arr_size];
    int length;
    int capacity;
}Queue;

Queue createQueue(){
    Queue q;
    q.length = 0;
    q.capacity = arr_size;
    return q;
}

void push_queue(int data,Queue* q){
    if(q->length == q->capacity) return;
    else{
        q->arr[q->length++]=data;
    }
}
int pop_queue(Queue* q){
    if(q->length==0) return INT_MIN;
    int top = q->arr[0];

    for(int i=0;i<q->capacity-1;i++) q->arr[i] = q->arr[i+1];
    q->length-- ;
    return top;
}

int sortedArr[arr_size] = { INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN }; // 5 elements cause arr_size = 5

void insert_and_delete(int inst, int delt){
    //Delete maintaining sorted order, 
    int index = 0;
    while (index < arr_size){
        if (sortedArr[index] == delt) break;
        else index++;
    }
    for (int i = index;i < (arr_size - 1);i++){
        sortedArr[i] = sortedArr[i + 1];
    }
    sortedArr[arr_size - 1] = INT_MAX; //May help to insertion sort

    //Insert maintaining sorted order
    for (index = arr_size - 1; index > 0;index--){
        if (sortedArr[index - 1] > inst){
            sortedArr[index] = sortedArr[index - 1];
        }
        else{
            break;
        }
    }
    sortedArr[index] = inst;
}

int main(){
    FILE* source = fopen("random_number.txt", "r");
    FILE* dest = fopen("output_numbers.txt", "w");
    if(source == NULL || dest==NULL) return 0;
    int next;
    Queue queue=createQueue();

    for(int i=0;i<arr_size;i++){
        fscanf(source,"%d",&next);
        push_queue(next,&queue);

        insert_and_delete(next,INT_MIN);
    }

    float avg;
    avg = (float)(sortedArr[0] + sortedArr[1] + sortedArr[2] + sortedArr[3] + sortedArr[4])/arr_size ;
    fprintf(dest,"%d %d %d %f\n",sortedArr[arr_size-1],sortedArr[0],sortedArr[(arr_size+1)/2],avg); //Max, min, meadian, average

    while(fscanf(source,"%d",&next) == 1){
        int prev = pop_queue(&queue);
        insert_and_delete(next,prev);
        avg = (avg - prev/(float)arr_size + next/(float)arr_size);
        fprintf(dest, "%d %d %d %f\n", sortedArr[arr_size - 1], sortedArr[0], sortedArr[(arr_size + 1) / 2], avg);
        push_queue(next,&queue);
    }

    //For end boundary values, last average value is used.
    do{
        int prev = pop_queue(&queue);
        insert_and_delete(avg, prev); // push average as next element
        avg = (avg - prev / (float)arr_size + next / (float)arr_size);
        fprintf(dest, "%d %d %d %f\n", sortedArr[arr_size - 1], sortedArr[0], sortedArr[(arr_size + 1) / 2], avg);
    }while(queue.length > 1);

    fclose(source);
    fclose(dest);

    return 0;
}


