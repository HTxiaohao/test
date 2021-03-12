#include <iostream>
#include <vector>
#include<limits.h>
#include <ctime>
#include<stdlib.h>
#define Random(low,up) (rand()%(up-low+1)) + low //宏函数，目的是生成一个位于[low,up]闭区间内的一个随机整数
using namespace std;
//插入排序
void insertion_sort(vector<int>&);
//选择排序
void selection_sort(vector<int>&);
//冒泡排序
void bubble_sort(vector<int>&);
//二路归并排序
void merge(vector<int>&, int, int, int);
void merge_sort(vector<int>&,int,int);
//堆排序
void max_heapify(vector<int>&,int,int);//同样为最大优先队列的核心操作
void bulid_max_heap(vector<int>&);//还有另一种方式：插入式建堆
void heap_sort(vector<int>&);
//快速排序
int partition(vector<int>&,int,int);//总是选取当前区间的最后一个元素为主元
int randrom_partition(vector<int>&, int, int);//随机选取当前区间的一个元素为主元
void quick_sort(vector<int>&,int,int);

int main()
{
	vector<int> v;
	cout << "依次输入待排序序列中的各个元素，以非数字字符作为结束符" << endl;
	int ele;
	while (cin >> ele)
		v.push_back(ele);


	//insertion_sort(v);
	//selection_sort(v);
	//bubble_sort(v);
	//merge_sort(v, 0, v.size() - 1);
	/*
	v.insert(v.begin(), 0);
	heap_sort(v);
	v.erase(v.begin());
	*/
	quick_sort(v, 0, v.size() - 1);


	cout << "排序结果为" << endl;
	for (auto& c : v) {
		cout << c << " ";
	}
}

void insertion_sort(vector<int>& sequence) {
	for (int j = 1; j < sequence.size(); j++) {
		int key = sequence[j];
		int i = j - 1;
		while (i >= 0 && key < sequence[i]) {
			sequence[i + 1] = sequence[i];
			i = i - 1;
		}
		sequence[i + 1] = key;
	}
}
void selection_sort(vector<int>& sequence) {
	for (int i = 0; i < sequence.size() - 1; i++) {
		int min = sequence[i];
		int min_index = i;
		for (int j = i; j < sequence.size() - 1; j++) {
			if (min > sequence[j + 1]) {
				min_index = j + 1;
				min = sequence[j + 1];
			}
		}
		sequence[min_index] = sequence[i];
		sequence[i] = min;
	}
}
void bubble_sort(vector<int>& sequence) {
	bool exchange;
	for (int j = 0; j < sequence.size() - 1; j++) {
		exchange = false;
		for (int i = 0; i < sequence.size() - j - 1; i++) {
			if (sequence[i] > sequence[i + 1]) {
				int temp = sequence[i];
				sequence[i] = sequence[i + 1];
				sequence[i + 1] = temp;
				exchange = true;
			}
		}
		if (!exchange) break;
	}
}
void merge_sort(vector<int>& sequence, int p, int r) {
	//p与r大小关系的两种可能情况：p<r或p==r，前者表示当前数组长度大于1，可分（递归未触底），后者表示当前数组长度为1，不可分（递归触底）
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(sequence,p,q);//目的是使[p,q]有序
		merge_sort(sequence, q + 1, r);//目的是使[q+1,r]有序
		//此时[p,q]与[q+1,r]均有序，执行完merge后[p,r]整体有序
		merge(sequence, p, q, r);
	}
}
void merge(vector<int>& sequence, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<int> L(n1 + 1);
	vector<int> R(n2 + 1);
	for (int i = 0; i < n1; i++)
		L[i] = sequence[p + i];
	for (int i = 0; i < n2; i++)
		R[i] = sequence[q + 1 + i];
	//加入哨兵，避免每次都要判断边界
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	int i = 0, j = 0;
	for (int k = p; k <= r; k++) {
		if (L[i] <= R[j]) {
			sequence[k] = L[i];
			i = i + 1;
		}
		else {
			sequence[k] = R[j];
			j = j + 1;
		}
	}
}
void max_heapify(vector<int>& sequence, int i,int heap_size) {
	//此递归函数只有在以i为根的树的左右子树都是最大堆时才能使用，目的是将以i为根的树整体变成最大堆
	int l = 2 * i;
	int r = l + 1;
	int largest;
	if (l <= heap_size && sequence[i] < sequence[l])
		largest = l;
	else
		largest = i;
	if (r <= heap_size && sequence[largest] < sequence[r])
		largest = r;
	if (largest != i) {
		sequence[0] = sequence[largest];
		sequence[largest] = sequence[i];
		sequence[i] = sequence[0];
		max_heapify(sequence, largest, heap_size);
	}
}
void bulid_max_heap(vector<int>& sequence) {
	//从最后一个非叶结点开始到根结点，循环执行max_heapify操作，目的是将输入数组变成一个最大堆
	int i = (sequence.size() - 1) / 2;
	while (i >= 1) {
		max_heapify(sequence, i , sequence.size()-1);
		i = i -1;
	}
}
void heap_sort(vector<int>& sequence) {
	//首先将带排序数组变成一个最大堆（最大堆不一定有序，堆所在的数组区域为无序区)
	bulid_max_heap(sequence);
	//然后每次将堆底元素与堆顶元素（一定是当前堆中最大的）进行交换，然后再将堆规模缩减（缩减元素所在数组区域为有序区）
	for (int i = sequence.size() - 1; i >= 2; i--) {
		sequence[0] = sequence[1];
		sequence[1] = sequence[i];
		sequence[i] = sequence[0];
		//不断减少堆的规模
		max_heapify(sequence, 1, i - 1);
	}
}
int partition(vector<int>& sequence, int p, int r) {
	//选取当前数组末尾元素为主元
	int key = sequence[r];
	//i的作用是标定小数区右边界和大数区左边界，j的作用是标定大数区右边界和充当循环工作指针
	int i = p - 1, j = p;
	while (j < r) {
		//j所指元素大于主元，此元素应被放在大数区
		if (sequence[j] > key) {
			j = j + 1;
		}
		//j所指元素小于等于主元，此元素应被放在小数区
		else {
			i = i + 1;
			int temp = sequence[i];
			sequence[i] = sequence[j];
			sequence[j] = temp;
			j = j + 1;
		}
	}
	//循环体执行完后j必定=r，i必定<r,i的具体值不确定，i的值有下面三种情况：
	/*
	* 1.i=p-1 此时小数区间为空，大数区间为[p+1,r],主元被放到了p处(当前数组头部)（此时p=i+1）
	  2.i=r-1 此时大数区间为空，小数区间为[p,r-1],主元位置无需改变(仍在数组尾部)（此时r=i+1=j）
	  3.p-1<i<r-1 此时两区间均不为空，小数区间为[p,i],大数区间为[i+2,r],主元被放到了i+1处(当前数组非头非尾的其他位置)
	  注：这三种情况里主元的最终归属位置均在i+1处
	*/
	//安置主元到i+1处
	int temp = sequence[i+1];
	sequence[i+1] = sequence[r];
	sequence[r] = temp;
	//返回主元的位置
	return i + 1;
}
int randrom_partition(vector<int>& sequence, int p, int r) {
	srand((unsigned)time(NULL));
	int i = Random(p,r);
	int temp = sequence[i];
	sequence[i] = sequence[r];
	sequence[r] = temp;
	return partition(sequence, p, r);
}
void quick_sort(vector<int>& sequence, int p, int r) {
	if (p < r) {
		int q = randrom_partition(sequence, p, r);
		quick_sort(sequence, p, q - 1);
		quick_sort(sequence, q + 1, r);
	}
}