#include <stdio.h>
/*
#define LEN 8
int a[LEN] = { 5, 2, 4, 7, 1, 3, 2, 6 };

void merge(int start, int mid, int end)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int left[n1], right[n2];
	int i, j, k;

	for (i = 0; i < n1; i++) //left holds a[start..mid] 
		left[i] = a[start+i];
	for (j = 0; j < n2; j++) // right holds a[mid+1..end] 
		right[j] = a[mid+1+j];

	i = j = 0;
	k = start;
	while (i < n1 && j < n2)
		if (left[i] < right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];

	while (i < n1) // left[] is not exhausted 
		a[k++] = left[i++];
	while (j < n2) //right[] is not exhausted 
		a[k++] = right[j++];
}

void sort(int start, int end)
{
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
		sort(start, mid);
		sort(mid+1, end);
		merge(start, mid, end);
		printf("merge (%d-%d, %d-%d) to %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	}
}

int main(void)
{
	sort(0, LEN-1);
	return 0;
}
*/
/*
int a[] = {5,2,4,7,1,3,2,6};
int start_1 = 0;
int end_1 = 7;

int partition(int start, int end)
{
	int pivot_value = a[end]; // Use the last element as pivot
	int i = start - 1;
	int j, temp;
	
	for (j = start; j < end; j++) {
		if (a[j] <= pivot_value) {
			i++;
			// Swap a[i] and a[j]
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		printf("%d %d %d %d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	}
	
	// Swap a[i+1] and a[end] to put pivot in correct position
	temp = a[i + 1];
	a[i + 1] = a[end];
	a[end] = temp;
	
	return i + 1; // Return the partition point
}

void quicksort(int start, int end)
{
	if(start<end)
	{
		int pivot=partition(start,end);
		quicksort(start,pivot-1);
		quicksort(pivot+1,end);
	}
}

int main(void)
{
	quicksort(start_1,end_1);
	printf("%d %d %d %d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	return 0;
}
*/
/*
int arr[] = {5,2,4,7,1,3,2,6};
int find_min(int* arr, int n) {
	int min = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

int find_min2(int* arr, int n)
{
	int min=find_min(arr,n);
	int arr1[n-1];
	int j=0;
	for(int i=0;i<n;i++)
	{
		if(arr[i]!=min)
		{
			arr1[j]=arr[i];
			j++;
		}
	}
	return find_min(arr1,n-1);
}
*/
/*
int a[] = {5,2,4,7,1,3,2,6};
int pivot;
int partition(int start, int end)
{
	int pivot_value = a[end]; // Use the last element as pivot
	int i = start - 1;
	int j, temp;
	
	for (j = start; j < end; j++) {
		if (a[j] <= pivot_value) {
			i++;
			// Swap a[i] and a[j]
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
		printf("%d %d %d %d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]);
	}
	
	// Swap a[i+1] and a[end] to put pivot in correct position
	temp = a[i + 1];
	a[i + 1] = a[end];
	a[end] = temp;
	
	return i + 1; // Return the partition point
}
int order_static(int start,int end,int k)
{
	
	pivot = partition(start,end);
	if(pivot==k)
		return a[pivot];
	else if(pivot>k)
		return order_static(start,pivot-1,k);
	else
		return order_static(pivot+1,end,k);
	return 0;
}

int main(void)
{
	printf("The 3rd smallest element is %d\n",order_static(0,7,3));
	return 0;
}
*/
#include <math.h>
#define  LEN 8
int a[LEN] = {1,2,2,2,5,6,8,9};
/*
int binarysearch(int number)
{
	int mid, start = 0, end = LEN-1;
	int result = -1; // Initialize result to "not found"
	
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (a[mid] == number)
		{
			result = mid; // Found a match, but continue searching to the left
			end = mid - 1; // Look for earlier occurrences in the left half
		}
		else if (a[mid] < number)
			start = mid + 1; // Search in the right half
		else
			end = mid - 1; // Search in the left half
	}
	return result; // Return the leftmost match, or -1 if not found
}

double doublesearch(double y)
{
	double mid, start = 0, end = y;
	printf("%f %f %f\n",start,end,mid);
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (fabs(mid*mid-y)<=0.000001)
			return mid; // Found exact match
		else if (fabs(mid*mid-y)>0.000001 && mid*mid-y<0)
			start = mid + 0.0001; // Search in the right half
		else
			end = mid - 0.0001; // Search in the left half
	printf("%f %f %f\n",start,end,mid);
	}
	return mid; // Return the closest approximation
}

int main(void)
{
	printf("%f\n",doublesearch(2));
	return 0;
}
*/

// 递归实现的快速幂算法
double mypow_recursive(double x, int n)
{
    // 基本情况
    if (n == 0)
        return 1.0;
    if (n == 1)
        return x;
        
    // 递归计算 x^(n/2)
    double half = mypow_recursive(x, n / 2);
    
    if (n % 2 == 0)
        // 如果 n 是偶数，返回 (x^(n/2))^2
        return half * half;
    else
        // 如果 n 是奇数，返回 x * (x^(n/2))^2
        return x * half * half;
}

// 循环实现的快速幂算法
double mypow_iterative(double x, int n)
{
    double result = 1.0;
    
    // 处理负指数情况
    if (n < 0) {
        x = 1.0 / x;
        n = -n;
    }
    
    while (n > 0) {
        // 如果当前 n 是奇数，将当前的 x 乘到结果中
        if (n % 2 == 1)
            result *= x;
            
        // 将 x 平方
        x *= x;
        
        // 将 n 除以2（向下取整）
        n /= 2;
    }
    
    return result;
}

int main(void)
{
    // 测试递归版本
    printf("使用递归算法计算 2^8 = %f\n", mypow_recursive(2, 8));
    printf("使用递归算法计算 3^7 = %f\n", mypow_recursive(3, 7));
    printf("使用递归算法计算 2.5^6 = %f\n", mypow_recursive(2.5, 6));
    
    // 测试循环版本
    printf("\n使用循环算法计算 2^8 = %f\n", mypow_iterative(2, 8));
    printf("使用循环算法计算 3^7 = %f\n", mypow_iterative(3, 7));
    printf("使用循环算法计算 2.5^6 = %f\n", mypow_iterative(2.5, 6));
    
    // 测试边界情况
    printf("\n特殊情况测试:\n");
    printf("2^0 = %f\n", mypow_iterative(2, 0));
    printf("2^(-3) = %f\n", mypow_iterative(2, -3));
    
    return 0;
}


