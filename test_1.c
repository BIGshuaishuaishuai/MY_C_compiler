void quicksort(int* arr, int left, int right) {
    if (left < right){
        int i = left, j = right, pivot = arr[left];  // 初始化基准元素
        while (i < j) {
            while (i < j && arr[j] >= pivot) j--;  // 从右往左找第一个小于基准元素的数
            if (i < j) arr[i++] = arr[j];  // 将该数移到左边
            while (i < j && arr[i] < pivot) i++;  // 从左往右找第一个大于等于基准元素的数
            if (i < j) arr[j--] = arr[i];  // 将该数移到右边
        }
        arr[i] = pivot;  // 将基准元素放到中间位置
        quicksort(arr, left, i - 1);  // 递归处理左边的子序列
        quicksort(arr, i + 1, right);  // 递归处理右边的子序列
    }

}

int main(){
    int arr[9] = {5, 2, 8, 3, 6, 1, 9, 4, 7};
    int len = sizeof(arr) / sizeof(int);
    quicksort(arr, 0, len - 1);
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}