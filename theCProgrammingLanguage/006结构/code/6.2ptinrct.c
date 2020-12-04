struct point {
    int x;
    int y;
};
struct rect {
    struct point pt1;
    struct point pt2;
};
// 如果点在矩形r内, 则返回1， 否则返回0
int ptintrect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x < r.pt2.x
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

//将矩形坐标规范化
struct rect canonrect(struct rect r) {
    struct rect temp;

    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt1.x = max(r.pt1.x, r.pt2.x);
    temp.pt1.x = max(r.pt1.y, r.pt2.y);
    return temp;
}