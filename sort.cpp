//十大排序算法c++

//冒泡排序
vector<int> bubbleSort(vector<int>& arr) {
    int len = arr.size();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {       // 相邻元素两两对比
                int temp = arr[j + 1];       // 元素交换
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return arr;
}

//快速排序
class Solution {
    int partition(vector<int>& nums, int left, int right) { // 快速排序 C++
        int pivot = nums[right]; // 选一个数值作为pivot
        int i = left - 1; //变量在for循环外面
        for (int j = left; j <= right - 1; j++) { // 将数组中的数值按照选中的pivot大小进行划分，小于等于的在一起，大于的在一起
            if (nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]); // 交换位置
            }
        }
        swap(nums[i + 1], nums[right]); // 这一行代码的意义是：把一开始就搁置的pivot再拉回来，放回中间的位置。左边是小于等于的元素，右边是大于的。
        return i + 1; // 输出pivot位置
    }
    void quicksort(vector<int>& nums, int left, int right) {
        if (left < right) { // 快速排序
            int pos = partition(nums, left, right);
            quicksort(nums, left, pos - 1);
            quicksort(nums, pos + 1, right);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};


//插入排序
vector<int> insertionSort(vector<int>& arr) {
    int len = arr.size();
    int preIndex, current;
    for(int i = 1; i < len; i++) {
        preIndex = i - 1;
        current = arr[i];
        while(preIndex >= 0 && arr[preIndex] > current) {
            arr[preIndex + 1] = arr[preIndex];
            preIndex--;
        }
        arr[preIndex + 1] = current;
    }
    return arr;
}

//希尔排序
    void shellSort(vector<int>& arr) {
        // 增量gap，并逐步缩小增量
       for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
           // 从第gap个元素，逐个对其所在组进行直接插入排序操作
           for (int i = gap; i < arr.size(); i++){
               int j = i;
               while (j - gap >= 0 && arr[j] < arr[j-gap]) {           
                   swap(arr[j], arr[j - gap]);
                   j -= gap;
               }
           }
       }
    }


//选择排序
//每次选择最小的元素放置在已派序列末尾
vector<int> selectionSort(vector<int>& arr) {
    int len = arr.size();
    int minIndex, temp;
    for(int i = 0; i < len - 1; i++) {
        minIndex = i;
        for(int j = i + 1; j < len; j++) {
            if(arr[j] < arr[minIndex]) {    // 寻找最小的数
                minIndex = j;                // 将最小数的索引保存
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    return arr;
} 

//堆排序
class Solution {
public:
    void heapify (vector<int>& arr, int index, int len) { // 建堆
        int left = 2 * index + 1; // 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
        int right = 2 * index + 2; // 根据堆的结构，可知有这样的left和right数值
        int maxIndex = index; // 因为是大根堆，所以关注max
        if ((left < len) && (arr[maxIndex] < arr[left])) { // 两个if判断，为了把三个节点的最大值找到。同时left和right不可超出索引
            maxIndex = left;
        }
        if ((right < len) && (arr[maxIndex] < arr[right])) {
            maxIndex = right;
        } 
        if (maxIndex != index) { // 如果有变动了
            swap(arr[maxIndex], arr[index]); // 那就把数值进行交换。这边的交换就是堆结构中节点的交换。把大的数值放在上面，小的当子节点。
            heapify(arr, maxIndex, len); // 递归调用，继续让该上浮的元素上浮
        }
    }
    void heapSort (vector<int>& arr, int size) { // 排序
        for (int i = size / 2 - 1; i >=0; i--) { // 第一个for循环用来从非叶子节点开始构建大根堆；
		//从尾巴开始。倒序的原因和堆的结构与我们的定义有关。堆的顶端是我们要的，那个数值是
        // 经过全局比较得到的最大值或最小值。这样一来，最小的索引对应全局的比较，那么我们需要倒序的方式建堆。
            heapify(arr, i, size);
        }
        for (int i = size - 1; i >= 1; i--) { // 将最大的数值放在数组的末尾。堆排序的过程是弹出最大值。我们每次都把最大值放最后，
        // 得到的效果就是递增数组。
            swap(arr[0], arr[i]); // 将弹出的最大值放最后
            heapify(arr, 0, i); // 接下来把弹出的值排除在外，对堆的内部进行移动，得到新的弹出的最大值。
        // 这一段移动的代码还是很巧妙的 因为此时除了下标为0的非叶子节点，其它非叶子节点都已经满足了大根堆的性质，
		//因此只需要从下标为0的非叶子节点
		//继续构建大根堆
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums, nums.size());
        return nums;
    }
};

//归并排序
/*
归并排序是建立在归并操作上的一种有效的排序算法.
该算法是采用 分治法（Divide and Conquer） 的一个非常典型的应用。
将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。
若将两个有序表合并成一个有序表，称为2-路归并。
*/
#include <cstdio>
#include <iostream>
 
using namespace std;
 
// Function to Merge Arrays L and R into A.
// lefCount = number of elements in L
// rightCount = number of elements in R.
void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;
 
	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;
 
	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}
 
// Recursive function to sort an array of integers.
void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing.
 
	mid = n/2;  // find the mid index.
 
	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = new int[mid];
	R = new int [n - mid];
 
	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray
 
	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
	// the delete operations is very important
	delete [] R;
	delete [] L;
}
 
int main() {
	/* Code to test the MergeSort function. */
 
	int A[] = {6,2,3,1,9,10,15,13,12,17}; // creating an array of integers.
	int i,numberOfElements;
 
	// finding number of elements in array as size of complete array in bytes divided by size of integer in bytes.
	// This won't work if array is passed to the function because array
	// is always passed by reference through a pointer. So sizeOf function will give size of pointer and not the array.
	// Watch this video to understand this concept - http://www.youtube.com/watch?v=CpjVucvAc3g
	numberOfElements = sizeof(A)/sizeof(A[0]);
 
	// Calling merge sort to sort the array.
	MergeSort(A,numberOfElements);
 
	//printing all elements in the array once its sorted.
	for(i = 0;i < numberOfElements;i++)
	   cout << " " << A[i];
	return 0;
}

//前面7种都是基于比较的排序的算法
//接下来是基于非比较的排序算法

//计数排序
/*
计数排序不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。 
作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。
1.找出待排序的数组中最大和最小的元素；
2.统计数组中每个值为i的元素出现的次数，存入数组C的第i项；
3.对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）；
4.反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1。

分析：
计数排序是一个稳定的排序算法。当输入的元素是n个0到k之间的整数时，时间复杂度是O(n+k)，
空间复杂度也是O(n+k)，其排序速度快于任何比较排序算法。当k不是很大并且序列比较集中时，
计数排序是一个很有效的排序算法。
*/

#include <iostream>
#include <vector>
using namespace std;
 
void countingSort(vector<int> &arr, int maxVal) {
	int len = arr.size();
	if (len < 1) return;
	vector<int> count(maxVal+1, 0);
	vector<int> tmp(arr); // 把原数组备份，后面反向填充的时候要用到
	for (auto x : arr)
		count[x]++;
	for (int i = 1; i <= maxVal; ++i)
		count[i] += count[i - 1];
	for (int i = len - 1; i >= 0; i--) { // 反向填充目标数组
		arr[count[tmp[i]] - 1] = tmp[i]; // 进行排序
		count[tmp[i]]--;    // 排好了一个元素，这边需要减一
	}
}
 
int main()
{
	vector<int> arr = { 1,5,3,7,6,2,8,9,4,3,3 };
	int maxVal = 9;
	countingSort(arr,maxVal);
	for (auto x : arr)
		cout << x << " ";
	cout << endl;
	return 0;
}

/*
基数排序
基数排序按照低位先排序，然后收集；
再按照高位排序，然后再收集；依次类推，直到最高位。
*/

int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int maxData = data[0];              // 最大数
    // 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
/*  int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;*/
}
void radixsort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}

/*
桶排序
桶排序是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。
桶排序的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

为了使桶排序更加高效，我们需要做到这两点：

在额外空间充足的情况下，尽量增大桶的数量；
使用的映射函数能够将输入的 N 个数据均匀的分配到 K 个桶中。
1.设置一个定量的数组当作空桶；
2.遍历输入数据，并且把数据一个一个放到对应的桶里去；
3.对每个不是空的桶进行排序；
4.从不是空的桶里把排好序的数据拼接起来。
*/

#include<iterator>
#include<iostream>
#include<vector>
using namespace std;
const int BUCKET_NUM = 10;

struct ListNode{
        explicit ListNode(int i=0):mData(i),mNext(NULL){}
        ListNode* mNext;
        int mData;
};

ListNode* insert(ListNode* head,int val){
        ListNode dummyNode;
        ListNode *newNode = new ListNode(val);
        ListNode *pre,*curr;
        dummyNode.mNext = head;
        pre = &dummyNode;
        curr = head;
        while(NULL!=curr && curr->mData<=val){
                pre = curr;
                curr = curr->mNext;
        }
        newNode->mNext = curr;
        pre->mNext = newNode;
        return dummyNode.mNext;
}


ListNode* Merge(ListNode *head1,ListNode *head2){
        ListNode dummyNode;
        ListNode *dummy = &dummyNode;
        while(NULL!=head1 && NULL!=head2){
                if(head1->mData <= head2->mData){
                        dummy->mNext = head1;
                        head1 = head1->mNext;
                }else{
                        dummy->mNext = head2;
                        head2 = head2->mNext;
                }
                dummy = dummy->mNext;
        }
        if(NULL!=head1) dummy->mNext = head1;
        if(NULL!=head2) dummy->mNext = head2;
       
        return dummyNode.mNext;
}

void BucketSort(int n,int arr[]){
        vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));
        for(int i=0;i<n;++i){
                int index = arr[i]/BUCKET_NUM;
                ListNode *head = buckets.at(index);
                buckets.at(index) = insert(head,arr[i]);
        }
        ListNode *head = buckets.at(0);
        for(int i=1;i<BUCKET_NUM;++i){
                head = Merge(head,buckets.at(i));
        }
        for(int i=0;i<n;++i){
                arr[i] = head->mData;
                head = head->mNext;
        }
}

