int x = 1, y = 2, z[10];
int *ip;        // ip是指向int类型的zhiz

ip = &x;        // ip现在指向x
y = *ip;        // y的值现在为1
*ip = 0;        // x的值现在为0
ip = &z[0];     // ip现在指向 z[0]
