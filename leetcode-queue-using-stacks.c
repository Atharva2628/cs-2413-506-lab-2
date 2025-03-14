#define OVERFLOW_MAX_AVAIL 100

typedef struct {
    //element stack
    int element_stack[OVERFLOW_MAX_AVAIL];  
    int element_stack_top;     
    
    //push pop stack   
    int check_stack[OVERFLOW_MAX_AVAIL];  
    int check_stack_top;         
} MyQueue;


MyQueue* myQueueCreate() {
    printf("*Creating queue*\n");
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->element_stack_top = -1;  
    queue->check_stack_top = -1;
    printf("Queue created\n");
    printf("--------------------\n\n");
    return queue;
}


void myQueuePush(MyQueue* queue_object, int x) {
    printf("*Pushing element*\n");

    //check overflow

    if ((queue_object->element_stack_top + 1) + (queue_object->check_stack_top + 1) >= OVERFLOW_MAX_AVAIL) {
        printf("Queue overflow\n");
        printf("--------------------\n\n");
        return;
    }
    
    //increment element stack top and add x

    queue_object->element_stack[++queue_object->element_stack_top] = x;
    printf("Pushed element: %d\n", x);
    printf("--------------------\n\n");
}

int myQueuePop(MyQueue* queue_object) {
    printf("*Popping element*\n");

    //underflow check

    if (queue_object->element_stack_top == -1 && queue_object->check_stack_top == -1) {
        printf("Queue underflow\n");
        printf("--------------------\n\n");
        return -1;
    }

    //if check stack not empty, pop check stack

    if (queue_object->check_stack_top != -1) {
        int popped = queue_object->check_stack[queue_object->check_stack_top--];
        printf("Popped element: %d\n", popped);
        printf("--------------------\n\n");
        return popped;
    } else {

        //transfer all e from e stack to check stack

        while (queue_object->element_stack_top != -1) {
            int x = queue_object->element_stack[queue_object->element_stack_top--];
            queue_object->check_stack[++queue_object->check_stack_top] = x;
        }

        //pop check stack

        int popped = queue_object->check_stack[queue_object->check_stack_top--];
        printf("Popped element: %d\n", popped);
        printf("--------------------\n\n");
        return popped;
    }
}

int myQueuePeek(MyQueue* queue_object) {
    printf("*Getting front element*\n");

    //check underflow

    if (queue_object->element_stack_top == -1 && queue_object->check_stack_top == -1) {
        printf("Queue is empty\n");
        printf("--------------------\n\n");
        return -1;
    }

    //if check stack not empty, return top

    if (queue_object->check_stack_top != -1) {
        int front = queue_object->check_stack[queue_object->check_stack_top];
        printf("Front element: %d\n", front);
        printf("--------------------\n\n");
        return front;
    } else {
        
        //transfer all e from element stack to check stack

        while (queue_object->element_stack_top != -1) {
            int x = queue_object->element_stack[queue_object->element_stack_top--];
            queue_object->check_stack[++queue_object->check_stack_top] = x;
        }

        //return top of check stack

        int front = queue_object->check_stack[queue_object->check_stack_top];
        printf("Front element: %d\n", front);
        printf("--------------------\n\n");
        return front;
    }
}

bool myQueueEmpty(MyQueue* queue_object) {
    printf("*Checking if queue is empty*\n");
    if (queue_object->element_stack_top == -1 && queue_object->check_stack_top == -1) {
        printf("Queue is empty\n");
        printf("--------------------\n\n");
        return true;
    } else {
        printf("Queue is not empty\n");
        printf("--------------------\n\n");
        return false;
    }
}

void myQueueFree(MyQueue* queue_object) {
    free(queue_object);
}