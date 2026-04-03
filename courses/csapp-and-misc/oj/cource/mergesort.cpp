void mergesort(int* arr, int p, int r) {
    if(p < r) {
        int q = (p + r) / 2;
        mergesort(arr, p, q-1);
        mergesort(arr, q, r);
        merge(a, p, r);
    }
}
