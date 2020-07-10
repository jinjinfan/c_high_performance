#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <list>
#include <set>
using namespace std;

/*
1. Computer memory
temporal locality:
    Accessing data that has recently been used and, therefore, 
    potentially already resides in the cache will make your program faster. 
    This is known as .

spatial locality:
    accessing data that is located near some other data you are using will increase
    the likelihood that the data you need is already in a cache line fetched from main memory earlier. 
*/

/*
2. Iterator
*/
template <typename Iterator>
auto iterator_distance(Iterator a, Iterator b) {
  using Traits = typename std::iterator_traits<Iterator>;
  using Category = typename Traits::iterator_category;
  using Difference = typename Traits::difference_type;
  constexpr auto is_random_access = 
    std::is_same_v<Category, std::random_access_iterator_tag>;
  if constexpr(is_random_access) {
    return b - a;
  }
  else {
    auto steps = Difference{};
    while(a != b) { ++steps; ++a; }
    return steps;
  }
}

void interatortest()
{
    std::vector a{1,2,3,4,5};
    std::cout << iterator_distance(a.begin(), a.end()) << endl;
    std::list alist{1,2,3,4,5};
    std::cout << iterator_distance(alist.begin(), alist.end()) << endl;
}

/*
3. Algorithm insert
*/
void insertertest()
{
    auto square_func = [](int v) { return v * v; };
    auto c = std::vector<int>{1,2,3};
    // Insert into back of vector using std::back_inserter
    auto squared_vec = std::vector<int>{};
    auto dst_vec = std::back_inserter(squared_vec);
    std::transform(c.begin(), c.end(), dst_vec, square_func);
    for_each(squared_vec.begin(), squared_vec.end(), [](auto p) {cout << p << endl;});
    // Insert into a std::set using std::inserter
    auto squared_set = std::set<int>{};
    auto dst_set = std::inserter(squared_set, squared_set.end());
    std::transform(c.begin(), c.end(), dst_set, square_func);
    for_each(squared_set.begin(), squared_set.end(), [](auto p) {cout << p << endl;});
}

/*
All algorithms use std::swap and std::move when moving elements around, but only if the move-constructor 
and move-assignment are marked noexcept,otherwise elements will be copied instead.
std::swap will utilize customized move operator, no need to overload std::swap.
*/

/*
4. Ranges library: c++20
https://github.com/ericniebler/range-v3
*/

/*
5.
The virtual address space
Addresses in the virtual address space that programmers see are mapped to physical addresses
by the operating system and the memory management unit (MMU), which is a part of the processor.
This mapping or translation happens each time we access a memory address.

This extra layer of indirection makes it possible for the operating system to use physical memory
for the parts of a process that are currently being used and back up the rest of the virtual memory
on-disk. In this sense, we can see the physical main memory as a cache for the virtual memory space,
which resides on secondary storage. The areas of the secondary storage that are used for backing up
memory pages are usually called swap space, swap file, or, simply, 
pagefile depending on the operating system.

Memory pages
The most common way to implement virtual memory today is to divide the address space in fixed sized 
blocks called memory pages. When a process accesses memory at a virtual address, the operating system 
checks whether the memory page is backed by physical memory (a page frame). If the memory page is not 
mapped in the main memory, a hardware exception occurs and the page is loaded from disk into memory. 
This type of hardware exception is called a page fault. This is not an error but a necessary interrupt
in order to load data from disk to memory. 

Paging
When there are no more available page frames in the main memory, a page frame has to be evicted. 
If the page to be evicted is dirty, that is, it has been modified since it was last loaded from disk,
it needs to be written to disk before it can be replaced. 

Stack
The stack is a contiguous memory block.
It has a fixed maximum size. If a program exceeds the maximum stack size, the program will crash.
The stack memory never becomes fragmented.
Allocating memory from the stack is always fast.
Each thread in a program has its own stack. 
*/
//Placement new
#include <memory>
auto memory = std::malloc(sizeof(User));
auto user_ptr = reinterpret_cast<User*>(memory);
std::uninitialized_fill_n(user_ptr, 1, User{"john"});
std::destroy_at(user_ptr);
std::free(memory);

int main()
{
    insertertest();
    return 0;
}