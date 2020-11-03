// 函数 day_of_year 和 month_day 没有进行错误检查, 请解决该问题
/*
    1. 在day_of_year中, 我们首先要确定变量month 和day的取值是合理的
        如果变量month的取值小于0或者大于12, 函数将返回-1, 
        如果变量day的值小于1或者大于该月份的实际天数, 函数也将返回-1
    2. 在month_day函数中, 我们必须保证year不是一个负数
*/

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 ==0;
    if (month < 1 || month > 12) {
        return -1;
    }
    if (day < 1 || day > daytab[leap][month]) {
        return -1;
    }
    for (i=1; i<month;i++) {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    if (year < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i <= 12 && yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
        if (i > 12 && yearday > daytab[leap][12]) {
            *pmonth = -1;
            *pday = -1;   
        } else {
            *pmonth = i;
            *pday = yearday;;
        }
    }
}