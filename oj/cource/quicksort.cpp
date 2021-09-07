void quicksort(int* arr, int p, int r) {
    if(p < r) {
        int q = arr[p];
        int i = j = p;
        for(int j = p+1; j <= r; j++) {
            if(arr[j] < q) {
                swap(arr[++i], arr[j]);
            }
        }
    }
}
