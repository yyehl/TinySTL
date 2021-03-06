#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

/*
*   Author  @yyehl
*/

#include <cstring>
#include <utility>
#include "Allocator.h"
#include "Functional.h"
#include "Iterator.h"
#include "TypeTraits.h"
#include "Utility.h"


namespace TinySTL 
{
	/********************[ equal ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 如果第二个序列比第一个序列长，那么多余的部分将不予考虑
	// 如果需要判断两个序列完全一样，那么需要在调用equal函数之前先判断两个序列的长度是否一样长
	template<class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) 
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	}
	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate eq)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!eq(*first1, *first2))
				return false;

		}
		return true;
	}

	/********************[ fill ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val)
	{
		for (; first != last; ++first)
			*first = val;
	}

	/********************[ fill_n ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 如果n大于了序列的长度，那么将会造成不可预期的结果
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for ( ; n > 0; --n, ++first)
		{
			*first = value;
		}
		return first;
	}
	template<class Size>
	char* fill_n(char* first, Size n, const char& value) 
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t* fill_n(wchar_t* first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	/********************[ iter_swap ]***********************************/
	/********************[Algorithm Time Complexity: O(1)]************/
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 iter1, ForwardIterator2 iter2)
	{
		typename iterator_traits<ForwardIterator1>::value_type tmp = *iter1;
		*iter1 = *iter2;
		*iter2 = tmp;
	}

	/********************[ lexicographical_compare ]***********************************/
	/********************[Algorithm Time Complexity: O(n)]************/
	// 字典排列方式排序
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			// 还继续进行就说明当前两序列相等
		}
		return first1 == last1 && first2 != last2;
	}
	template<class InputIterator1, class InputIterator2, class BinaryCompare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, BinaryCompare cmp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (cmp(*first1, *first2))
				return true;
			if (cmp(*first2, *first2))
				return false;
			// 还继续进行就说明当前两序列相等
		}
		return first1 == last1 && first2 != last2;
	}

	/********************[ max ]***********************************/
	/********************[Algorithm Time Complexity: O(1)]************/
	template<class T>
	inline const T& max(const T& x, const T& y)
	{
		return x < y ? y : x;
	}
	template<class T, class Compare>
	inline const T& max(const T& x, const T& y, Compare cmp)
	{
		return cmp(x, y) ? y : x;
	}

	/********************[ min ]***********************************/
	/********************[Algorithm Time Complexity: O(1)]************/
	template<class T>
	inline const T& min(const T& x, const T& y)
	{
		return x < y ? x : y;
	}
	template<class T, class Compare>
	inline const T& min(const T& x, const T& y, Compare cmp)
	{
		return cmp(x, y) ? x : y;
	}


	/********************[ mismatch ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 返回两个序列首次出现不同的地方，返回一个pair
	template<class InputIterator1, class InputIterator2>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}
	template<class InputIterator1, class InputIterator2, class BinaryEqual>
	pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryEqual eq)
	{
		while (first1 != last1 && eq(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return pair<InputIterator1, InputIterator2>(first1, first2);
	}

	/********************[ copy ]***********************************/
	/********************[Algorithm Time Complexity: O(n)]************/
	/*
	     copy将[first, last)里面的元素拷贝到[result, result + (last - first))之中，返回result + (last - first)
	     如果result位于[first, last) 之中，那么将会出现未可知的结果
	*/
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		for (; first != last; ++first, ++result)
			*result = *first;
		return result;
	}

	/********************[ copy_backward ]***********************************/
	/********************[Algorithm Time Complexity: O(n)]************/
	/*
		将[first, last)逆序复制到以[ xxx, result), result - 1 为起点的容器中
	*/
	template<class BidirectionIterator>
	BidirectionIterator copy_backward(BidirectionIterator first, BidirectionIterator last, BidirectionIterator result)
	{
		if (first == last) return result;
		BidirectionIterator iter = last - 1;
		for (; iter != first; --iter)
		{
			*--result = *iter;
		}
		*--result = *iter;   // 此时， *iter == *first
		return result;
	}




	//********** [make_heap] ***************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class RandomAccessIterator, class Compare>
	//heap上溯算法
	static void up(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator head, Compare comp) {//1.[first, last], 2.headr points the header of the heap
		if (first != last) {
			int index = last - head;
			auto parentIndex = (index - 1) / 2;
			for (auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index - 1) / 2) {
				auto parent = head + parentIndex;//get parent
				if (comp(*parent, *cur))
					TinySTL::swap(*parent, *cur);
				cur = parent;
				index = cur - head;
			}
		}
	}
	template<class RandomAccessIterator, class Compare>
	//heap下降算法
	static void down(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator head, Compare comp) {//1.[first, last], 2.headr points the header of the heap
		if (first != last) {
			auto index = first - head;
			auto leftChildIndex = index * 2 + 1;
			for (auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex = index * 2 + 1) {
				auto child = head + leftChildIndex;//get the left child
				if ((child + 1) <= last && *(child + 1) > *child)//cur has a right child
					child = child + 1;
				if (comp(*cur, *child))
					TinySTL::swap(*cur, *child);
				cur = child;
				index = cur - head;
			}
		}
	}
	template <class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
		TinySTL::make_heap(first, last,
			typename TinySTL::less<TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		const auto range = last - first;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur) {
			TinySTL::down(cur, last - 1, first, comp);
			if (cur == first) return;
		}
	}
	//********* [push_heap] ***************
	//********* [Algorithm Complexity: O(lgN)] ****************
	template <class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
		TinySTL::push_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		TinySTL::up(first, last - 1, first, comp);
	}
	//********* [pop_heap] ***************
	//********* [Algorithm Complexity: O(lgN)] ****************
	template <class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
		TinySTL::pop_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		TinySTL::swap(*first, *(last - 1));
		if (last - first >= 2)
			TinySTL::down(first, last - 2, first, comp);
	}
	//********* [sort_heap] ***************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return TinySTL::sort_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		for (auto cur = last; cur != first; --cur) {
			TinySTL::pop_heap(first, cur, comp);
		}
	}
	//********* [is_heap] ***************
	//********* [Algorithm Complexity: O(N)] ****************
	template <class RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return TinySTL::is_heap(first, last,
			TinySTL::less<typename TinySTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		const auto range = last - first;
		auto index = range / 2 - 1;
		for (auto cur = first + range / 2 - 1; cur >= first; --cur, --index) {
			if (*(first + (index * 2 + 1)) > *cur ||//left child > cur
				((first + (index * 2 + 2)) <= last && *(first + (index * 2 + 2)) > *cur))//right child > cur
				return false;
			if (cur == first)
				break;
		}
		return true;
	}
	

	/****************************************************************************************[set相关]*************************************/
	/********************[ set_union ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		求两个有序set的并集，可重复，如果s1中x元素重复m次，s2中x元素重复m次，那么最终结果x元素的次数为max（m，n）
		输出结果中，并集中保持两个原集合的相对顺序
		返回值为一个指向输出区间尾端的迭代器
	*/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
			}
			else
			{
				*result = *first1;
				++first1;
				++first2;
			}
			++result;
		}
		return copy(first1, last1, copy(first2, last2, result));
	}

	/********************[ set_intersection ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		求两个有序set的交集，可重复，如果s1中x元素重复m次，s2中x元素重复m次，那么最终结果x元素的次数为min（m，n）
		输出结果中，并集中保持两个原集合的相对顺序
		返回值为一个指向输出区间尾端的迭代器
	*/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_insertsection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				++first1;
			else if (*first2 < *first1)
				++first2;
			else
			{
				*result = *first1;
				++first1;
				++first2;
				++result;
			}
		}
		return result;
	}

	/********************[ set_difference ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		求两个有序set的差集，可重复，如果s1中x元素重复m次，s2中x元素重复m次，那么最终结果x元素的次数为max（m-n，0）
		输出结果中，并集中保持两个原集合的相对顺序
		返回值为一个指向输出区间尾端的迭代器
	*/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (*first2 < *first1)
				++first2;
			else
			{
				++first1; 
				++first2;
			}
		}
		return copy(first1, last1, result);
	}

	/********************[ set_symmetric_difference ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		求两个有序set的对称差集，可重复，如果s1中x元素重复m次，s2中x元素重复m次，那么最终结果x元素的次数为max（|m-n|，0）
		即在s1中出现但在s2中不出现，以及在s2中出现在s1中不出现的并集
		即s1，s2两个集合中都只出现了一次的元素，可重复
		输出结果中，并集中保持两个原集合的相对顺序
		返回值为一个指向输出区间尾端的迭代器
	*/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result = first1;
				++first1;
			}
			else if (*first2 < *first1)
			{
				*result = *first2;
				++first2;
			}
			else
			{
				++first1;
				++first2;
			}
		}
		return copy(first1, last1, copy(first2, last2, result));
	}


	/********************[ count ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 计算[first, last)中元素值等于val的数量
	template<class InputIterator, class T>
	size_t count(InputIterator first, InputIterator last, const T& val)
	{
		if (first == last) return 0;
		size_t i = 0;
		for (; first != last; ++first)
		{
			if (*first == val)
				++i;
		}
		return i;
	}
	
	/********************[ find ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 返回[first, last)中元素值等于val的第一个迭代器
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val)
	{
		while (first != last && *first != val)
			++first;
		return first;
	}


	/********************[ for_each ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function f)
	{
		for (; first != last; ++first)
			f(*first);
		return f;
	}

	/********************[ includes ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class InputIterator1, class InputIterator2>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1) return false;
			else if (*first1 < *first2) ++first1;
			else {
				++first1;
				++first2;
			}
		}
		return first2 == last2;
	}

	/********************[ max_element ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)  return first;
		ForwardIterator ret = first;
		for (++first; first != last; ++first)
		{
			if (*first > *ret)
				ret = first;
		}
		return ret;
	}

	/********************[ min_element ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)  return first;
		ForwardIterator ret = first;
		while (++first != last)
		{
			if (*first < ret)
				ret = first;
		}
		return ret;
	}

	/********************[ merge ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	template<class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator ret)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*ret = *first1;
				++first1;
				++ret;
			}
			else
			{
				*ret = *first2;
				++first2;
				++ret;
			}
		}
		return copy(first1, last1, copy(first2, last2, ret));
	}


	/********************[ partitiom ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		将[first, last)的元素重新排序，使的Pred为true在前半段，使得Pred为false的在后半段
		这个算法不保证元素的原始相对位置（比如说x1在x2前面，x1,x2两元素都从前半段移动到后半段
										不能保证x1还在x2的前面）
	
	*/
	template<class BidirectionIterator, class Pred>
	BidirectionIterator partition(BidirectionIterator first, BidirectionIterator last, Pred pred)
	{
		while (1)
		{
			while (1)
			{
				if (first == last)
					return first;
				else if (pred(*first))  // 满足不移动条件
					++first;
				else                  // 满足移动条件，*first将会被移动到后半段
					break;  
			}
			--last;
			while (1)
			{
				if (first == last)
					return first;
				else if (!pred(*last))
					--last;
				else
					break;
			}
			iter_swap(first, last);
			++first;
		}
	}


	/********************[ search ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	/*
		寻找序列[first2, last2)在序列[first1, last1)第一次出现的点
		返回第一次出现的点的末尾元素后一位置
	*/
	template<class ForwardIterator1, class ForwardIterator2>
	ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2)
	{
		int d1 = last1 - first1;
		int d2 = last2 - first2; 
		if (d1 < d2) return last1;  // 如果序列2比序列1都长，那不可能成为其子序列

		ForwardIterator1 cur1 = first1;
		ForwardIterator2 cur2 = first2;

		while (cur2 != last2)
		{
			if (*cur1 == *cur2)  // 如果当前元素相等。则比较下一元素
			{
				++cur1;
				++cur2;
			}
			else       // 如果当前元素不相等
			{
				if (d1 == d2)  // 并且d1，d2相等，那么就说明不可能成为其子序列了
					return last1;     // 如果没有找到，就返回序列1的last1
				else
				{
					cur1 = ++first1;
					cur2 = first2;       // 准备在新的起点再找一次，cur2必须要重新回到first2
					--d1;
				}
			}
		}
		return first1;    // 如果找到了，就返回序列1中第一次出现序列2的地方的首位置
	}

	/********************[ lower_bound ]***********************************/
	/********************[Algorithm Time Complexity: O(logN)]************/
	/*
		另一种版本的二分查找
		返回值是，在不破坏排序状态的情况下，可插入value的第一个位置
	*/
	template<class ForwardIterator, class T>
	ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& val)
	{
		if (first == last)  return first;
		int len = last - first;
		int half = 0;
		ForwardIterator mid = first;
		while (len > 0)
		{
			half = len >> 1;  //  half = len / 2;
			mid = first;
			mid = first + half;
			if (*mid < val)
			{
				first = mid;
				++first;
				half = len - half - 1;
			}
			else
			{
				len = half;
			}
			return first;
		}


	}

	/********************[ upper_bound ]***********************************/
	/********************[Algorithm Time Complexity: O(logN)]************/
	/*
		另一种版本的二分查找
		返回值是，在不破坏排序状态的情况下，可插入value的第一个位置
	*/
	template<class ForwardIterator, class T>
	ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& val)
	{
		if (first == last)  return first;
		int len = last - first;
		int half = 0;
		ForwardIterator mid;

		while (len > 0)
		{
			half = len >> 1;
			mid = first + half;
			if (val < *mid)
			{
				len = half;
			}
			else
			{
				first = mid;
				++first;
				len = len - half - 1;
			}
		}
		return first;

	}

	/********************[ binary_search ]***********************************/
	/********************[Algorithm Time Complexity: O(logN)]************/
	// 二分查找，查找到元素等于val返回true， 未查找到返回false
	template<class ForwardIterator, class T>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& val)
	{
		if (first == last) return false;
		while (first != last)
		{
			mid = first + (last - first) / 2;
			if (*mid < val)
			{
				first = mid;
				++first;
			}
			else if (val < *mid)
			{
				last = mid;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	/********************[ random_shuffle ]***********************************/
	/********************[Algorithm Time Complexity: O(N)]************/
	// 将序列中的元素重新随机排列
	template<class RandomIterator>
	inline void random_shuffle(RandomIterator first, RandomIterator last)
	{
		if (first == last)  return;
		int l = last - first;
		for (RandomIterator i = first + 1; i != last; ++i)
		{
			iter_swap(i, first + rand() % ((i - first) + 1));
		}
	}

	/************************************************************* sort相关 ************************************************************************/

	/*****************************[ insert_sort ]**************************************/ 
	/*****************************[Algorithm Time Complexity: O(N^2)]**************************************/
	// STLsort函数中内部使用函数，当数据量较小时，使用插入排序可以避免快排的递归调用带来的过大的负荷
	template<class RandomIterator>
	void _insert_sort(RandomIterator first, RandomIterator last)
	{
		if (first == last) return;

		for (RandomIterator iter = first + 1; iter != last; ++iter)
		{
			iterator_traits<RandomIterator>::value_type value = *iter;
			if (value < *first)
				copy_backward(first, iter, iter + 1);
			else
			{       // 到这里，说明value 一定比 *first 小，也就是一定不会越界
				RandomIterator next = iter;
				--next;
				while (value < *next)
				{
					*(next + 1) = *next;
					--next;
				}
				*(next + 1) = value;
			}
		}
	}
	
	/*****************************[ qucik_sort ]**************************************/
	/*****************************[Algorithm Time Complexity: O(NlogN)]**************************************/
	// 当数据量很大且数据随机的时候，快排是最快的
	/* 内部函数， 三点中值 first， last， middle 取中值 */
	template<class T>
	inline const T& _median(const T& a, const T& b, const T& c)
	{
		if (a < b)
		{
			if (b < c)                // a < b < c
				return b;
			else
			{
				if (c < a)            // c < a < b
					return a;
				else                   // a <= c < b
					return c;
			}
		}
		else     // b <= a
		{
			if (c < b)                 // c < b <= a
				return b;
			else   // b <= c
			{ 
				if (a < c)            //  b <= a < c
					return a;
				else                 //  b <= c <= a
					return c;
			}
		}
	}
	/* 分割函数， 以pivot为轴， 交换左边大于pivot，右边小于pivot的元素*/
	/* 返回first， first左边的元素都小于pivot */
	template<class RandomIterator, class T>
	RandomIterator _partial_quick_sort(RandomIterator first, RandomIterator last, T pivot)   // [first, last)
	{
		while (first < last)
		{
			while (*first < pivot)
				++first;
			--last;
			while (pivot < *last)
				--last;
			if (first < last)
				TinySTL::iter_swap(first, last);
			else
				return first;
			++first;
		}
		return first;
	}

	template<class RandomIterator>
	void _quick_sort(RandomIterator first, RandomIterator last)
	{
		if (last < first || first == last || first + 1 == last)
			return;
		RandomIterator cut = _partial_quick_sort(first, last, _median(*first, *(last - 1), *(first + (last - first) / 2)));
		_quick_sort(first, cut);
		_quick_sort(cut, last);
	}


	template<class RandomIterator>
	inline void sort(RandomIterator first, RandomIterator last)
	{
		if (first == last) return;
		else if (last - first < 16)
			_insert_sort(first, last);
		else
			_quick_sort(first, last);
	}


	/************************************************************* sort相关 ************************************************************************/

	/*****************************[ advance ]**************************************/
	/*****************************[Algorithm Time Complexity: O(N)]**************************************/
	template<class ForwardIterator>
	inline void advance(ForwardIterator iter, size_t n)
	{
		while (n > 0)
		{
			++iter;
		}
	}

	/*****************************[ equal_range ]**************************************/
	/*****************************[Algorithm Time Complexity: O(logN)]**************************************/
	template<class ForwardIterator, class T>
	pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& val)
	{
		int len = last - first;
		int half;
		ForwardIterator left, mid, right;

		while (len > 0)
		{
			half = len >> 1;
			mid = first;
			advance(mid, half);
			if (*mid < val)
			{
				first = mid + 1;
				half = len - half - 1;
			}
			else if (val < *mid)
			{
				len = half;
			}
			else  //  val == *mid
			{
				left = lower_bound(first, mid, val);
				advance(first, len);
				right = upper_bound(++mid, first, val);
				return pair<ForwardIterator, ForwardIterator>(left, right);
			}
		}
		return pair<ForwardIterator, ForwardIterator>(first, first);
	}




}   // namespace TinySTL

/****************************************[数值类算法]***********************************************/

#include "Detail\Numeric.h"

#endif  // _ALGORITHM_H_
