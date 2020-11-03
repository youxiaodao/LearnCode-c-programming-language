// 用指针的方式代替数组下标方式改写函数 day_of_year 和 month_day


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    leap = year % 4 == 0 && year % 100 !=0 || year % 400 ==0;
    p = daytab[leap];
    while (--month) {
        day += *++p;
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap;
    char *p;

    leap = year % 4 && year % 100 != 0 || year % 400 == 0;
    p = daytab[leap];
    while (yearday > *++p) {
        yearday -= *p;
    }
    *pmonth = p - *(daytab + leap); // daytab的指针 + leap    p是最后的月份的指针    相减的差就是月份 
    *pday = yearday;
}