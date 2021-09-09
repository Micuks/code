int loadmost(int* a, int n) { // 把装载问题改为01背包问题
    qsort(a, n);
    int sum = *a;
    int i = 2;
    while(sum < maxload) {
        sum += a[i++];
    }
    if(i < n)
        return sum - a[i];
    else return sum;
}

int main() {

}
