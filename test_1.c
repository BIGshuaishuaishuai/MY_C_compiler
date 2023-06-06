void quicksort(int ptr arr, int left, int right) {
    if (left < right){
        int i = left, j = right, pivot = arr[left];  // 初始化基准元素
        while (i < j) {
            while (i < j && arr[j] >= pivot) {
                j = j - 1;  // 从右往左找第一个小于基准元素的数
            }
            if (i < j) {
                arr[i] = arr[j];  // 将该数移到左边
                i = i + 1;
            }
            while (i < j && arr[i] < pivot) {
                i = i + 1;  // 从左往右找第一个大于等于基准元素的数
            }
            if (i < j) {
                arr[j] = arr[i];  // 将该数移到右边
                j = j - 1;
            }
        }
        arr[i] = pivot;  // 将基准元素放到中间位置
        quicksort(arr, left, i - 1);  // 递归处理左边的子序列
        quicksort(arr, i + 1, right);  // 递归处理右边的子序列
    }

}

int main(){
    int array[9] arr = {5, 2, 8, 3, 6, 1, 9, 4, 7};
    int len = 9;
    int i;
    quicksort(arr, 0, len - 1);
    for (i = 0; i < len; i = i + 1) {
        arr[i];
    }
}