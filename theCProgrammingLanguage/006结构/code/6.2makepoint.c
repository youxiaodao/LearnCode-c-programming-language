// makepoint函数：通过x,y坐标构造一个点
struct point {
    int x;
    int y;
};
// 必须要声明点

struct point makepoint(int x, int y) {
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
};


struct rect {
    struct point pt1;
    struct point pt2;
};

struct rect screen;
struct point middle;
struct point makepoint(int, int);

screen.pt1 = makepoint(0, 0);
screen.pt2 = makepoint(XMAX, YMAX);

middle = makepoint(
    (screen.pt1.x + screen.pt2.x) / 2, 
    (screen.pt1.y + screen.pt2.y) / 2
);

