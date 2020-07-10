#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <variant>
#include <tuple>
using namespace std;

/*
1.context switch
    The context switch stores the current state of the running thread and loads the state of the thread 
    that should be executed.
  critical section
    a place in the code that must not be executed simultaneously since it updates or reads shared memory
    that potentially could generate data races.
  contention
    The state where the second thread is blocked by the first thread to finish its work is called contention.
    This is something we strive to minimize, because it hurts the scalability of a concurrent program.
*/
/*
2. Thread
*/
/*
  A thread is not joinable if it has been:
    Default constructed; that is, if it has nothing to execute
    Moved from (its associated running thread has been transferred to another std::thread object)
    Detached by a call to detach()
    Already joined by a call to join()
  priority inversion
    It happens when a thread with high priority is waiting to acquire a lock that is currently held by a low priority thread. 
  False sharing
    or destructive interference, can degrade performance. It occurs when two threads use some data
    (that is not logically shared between the threads) but happen to be located in the same cache line.
    The threads will invalidate the cache line for each other although there is no true sharing of data between the threads
*/
int main()
{
    return 0;
}