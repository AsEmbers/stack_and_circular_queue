#include <stdio.h>

/**
 * 栈和循环队列的实现:
 *      新建一个栈，读取标准输入3个整数3 4 5，入栈3 4 5，依次出栈，打印 5 4 3；
 *      新建循环队列（Maxsize为5），读取标准输入3 4 5 6 7，入队7时，队满，打印false，然后依次出队，输出 3 4 5 6
 */

#define MAXSIZE 5 //结尾不能加";"
/**
 * 栈结构体定义
 * 特点：后进先出或者先进后出，数组实现
 */
typedef int ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int top;//栈顶标记位：栈帧
} SequenceStack;
/**
 * 循环队列结构体定义
 * 特点：先进先出
 * 最大存储元素个数为：MAXSIZE-1，牺牲一个存储单元用来实现队列是否已满的判断
 * front 队列头标记位
 * rear 队列尾标记位
 */
typedef struct {
    ElemType data[MAXSIZE];
    int front, rear;
} CircularQueue;

void InitStack(SequenceStack &sequence_stack) {
    sequence_stack.top = -1;//初始化栈为空
}

bool IsEmptyStack(SequenceStack sequence_stack) {
    return -1 == sequence_stack.top;
}

bool IsFullStack(SequenceStack sequence_stack) {
    return MAXSIZE - 1 == sequence_stack.top;//数组下标等于长度（即元素个数）减一
}

bool Push(SequenceStack &sequence_stack, ElemType m) {
    if (IsFullStack(sequence_stack)) {
        return false;
    }
    sequence_stack.data[++sequence_stack.top] = m;
    return true;
}

//在子函数中改变m的值，因此需要加引用
bool Pop(SequenceStack &sequence_stack, ElemType &m) {
    if (IsEmptyStack(sequence_stack)) {
        return false;
    }
    m = sequence_stack.data[sequence_stack.top--];
    return true;
}

//初始化队列
void InitQueue(CircularQueue &circular_queue) {
    circular_queue.rear = circular_queue.front = 0;
}

bool IsEmptyQueue(CircularQueue circular_queue) {
    return circular_queue.rear == circular_queue.front;
}

bool IsFullQueue(CircularQueue circular_queue) {
    //判断是否队列已满
    return circular_queue.front == (circular_queue.rear + 1) % MAXSIZE;
}
//入队
bool EnQueue(CircularQueue &circular_queue, ElemType m) {
    if (IsFullQueue(circular_queue)) {
        return false;
    }
    circular_queue.data[circular_queue.rear] = m;
    //记住取模，相同的两个数取模结果为0，当rear等于MAXSIZE时，rear被重置为0，让队列再次从0开始入队元素，即实现了循环的过程
    circular_queue.rear = (circular_queue.rear + 1) % MAXSIZE;
    return true;
}
//出队
bool DeQueue(CircularQueue &circular_queue, ElemType &m) {
    if (IsEmptyQueue(circular_queue)) {
        return false;
    }
    m = circular_queue.data[circular_queue.front];
    //队头+1，即让队头标记指向下一个元素，使上一个元素无法取到，从而视为上一个元素出队
    circular_queue.front = (circular_queue.front + 1) % MAXSIZE;
    return true;
}

int main() {
    SequenceStack sq_stack;//声明栈
    InitStack(sq_stack);//初始化栈
    ElemType a, b, c, d, e;
    scanf("%d %d %d", &a, &b, &c);
    bool flag;
    //压栈
    Push(sq_stack, a);
    Push(sq_stack, b);
    Push(sq_stack, c);
    ElemType m;//存储打印的出栈元素
    //弹栈
    flag = Pop(sq_stack, m);
    if (flag) printf("%2d",m);

    flag = Pop(sq_stack, m);
    if (flag) printf("%2d",m);

    flag = Pop(sq_stack, m);
    if (flag) printf("%2d\n",m);
    //CLion的DEBUG环境调试时，不是一次输入一次输出，会全部读取完成再输出，在下一次读取输入前加fflush(),可以达到一次输入一次输出的效果
    fflush(stdout);

    //初始化循环队列，数组实现
    CircularQueue circular_queue;
    InitQueue(circular_queue);//初始化队列
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    //入队
    EnQueue(circular_queue, a);
    EnQueue(circular_queue, b);
    EnQueue(circular_queue, c);
    EnQueue(circular_queue, d);
    flag = EnQueue(circular_queue, e);
    if (!flag) printf("false\n");//如果队满，即入队失败，输出false

    //出队
    flag = DeQueue(circular_queue,m);
    if (flag) printf("%2d",m);

    flag = DeQueue(circular_queue,m);
    if (flag) printf("%2d",m);

    flag = DeQueue(circular_queue,m);
    if (flag) printf("%2d",m);

    flag = DeQueue(circular_queue,m);
    if (flag) printf("%2d",m);
    return 0;
}
