#include<iostream>  
#include <vector>

using namespace std;
void quickSort(vector<int> &num, int l, int r);
int main()
{
    int array[] = { 34,65,12,43,67,5,78,10,3,70 }, k;
    int len = sizeof(array) / sizeof(int);
    cout << "The orginal arrayare:" << endl;
    vector<int> num(array, array + len);
    for (k = 0; k<num.size(); k++)
        cout << num[k] << ",";
    cout << endl;
    quickSort(, 0, len - 1);
    cout << "The sorted arrayare:" << endl;
    for (k = 0; k<num.size(); k++)
        cout << num[k] << ",";
    cout << endl;
    system("pause");
    return 0;
}

void quickSort(int num[] int l, int r) {
    if (l >= r)     //先检查左右条件
        return;
    int i = l, j = r, x = num[l];
    while (i < j) {
        while (i < j && num[j] >= x)//从右向左找到第一个小于x的
            j--;
        if (i < j)
            num[i++] = num[j];//填坑之后i++
        while (i < j && num[i] <= x)//从左向右找第一个大于x的数
            i++;
        if (i < j)
            num[j--] = num[i];
    }
    num[i] = x;     //把最开始取出来的x放到i处
    quickSort(num, l, i - 1);//以i为中间值，分左右两部分递归调用
    quickSort(num, i + 1, r);
}
