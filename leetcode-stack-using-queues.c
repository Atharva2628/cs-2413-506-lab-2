#define OVERFLOW_MAX_AVAIL 100

typedef struct {
    //main q
    int data_queue[OVERFLOW_MAX_AVAIL];
    int data_queue_size;      

    //temp operations q
    int op_queue[OVERFLOW_MAX_AVAIL];    
    int op_queue_size;     
} MyStack;


void enqueue(int* queue, int* size, int x) {
    queue[*size] = x;
    (*size)++;
}

int dequeue(int* queue, int* size) {
    int x = queue[0];
    for (int i = 1; i < *size; i++) {
        queue[i - 1] = queue[i];
    }
    (*size)--;
    return x;
}


MyStack* myStackCreate() {
    printf("*Creating stack*\n");
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->data_queue_size = 0;
    stack->op_queue_size = 0;
    printf("Stack created\n");
    printf("--------------------\n\n");
    return stack;
}


void myStackPush(MyStack* stack_object, int x) {
    printf("*Pushing element*\n");

    //overflow check

    if (stack_object->data_queue_size == OVERFLOW_MAX_AVAIL) {
        printf("Stack overflow\n");
        printf("--------------------\n\n");
        return;
    }
    
    //move from data q to op q

    while (stack_object->data_queue_size > 0) {
        int temp = dequeue(stack_object->data_queue, &stack_object->data_queue_size);
        enqueue(stack_object->op_queue, &stack_object->op_queue_size, temp);
    }
    
    //add to data q

    enqueue(stack_object->data_queue, &stack_object->data_queue_size, x);
    
    //move back elements from op q to data q

    while (stack_object->op_queue_size > 0) {
        int temp = dequeue(stack_object->op_queue, &stack_object->op_queue_size);
        enqueue(stack_object->data_queue, &stack_object->data_queue_size, temp);
    }

    printf("Pushed element: %d\n", x);
    printf("--------------------\n\n");
}


int myStackPop(MyStack* stack_object) {
    printf("*Popping element*\n");

    //check underflow

    if (stack_object->data_queue_size == 0) {
        printf("Stack underflow\n");
        printf("--------------------\n\n");
        return -1;
    }

    //if stack not empy, de q and return front

    printf("Popped element: %d\n", stack_object->data_queue[0]);
    printf("--------------------\n\n");
    return dequeue(stack_object->data_queue, &stack_object->data_queue_size);
}

int myStackTop(MyStack* stack_object) {
    printf("*Getting top element*\n");

    //check underflow
    if (stack_object->data_queue_size == 0) {
        printf("Stack is empty\n");
        printf("--------------------\n\n");
        return -1;
    }
    // get top from data q
    printf("Top element: %d\n", stack_object->data_queue[0]);
    printf("--------------------\n\n");
    return stack_object->data_queue[0];
}

bool myStackEmpty(MyStack* stack_object) {
    printf("*Checking if stack is empty*\n");
    if(stack_object->data_queue_size == 0){
        printf("Stack is empty\n");
        printf("--------------------\n\n");
        return true;
    }else{
        printf("Stack is not empty\n");
        printf("--------------------\n\n");
        return false;
    }
}

void myStackFree(MyStack* stack_object) {
    free(stack_object);
}