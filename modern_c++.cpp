#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
1. Forwarding reference
It's important to note that only auto&& and T&& in a template method are forwarding references.
Using the && syntax with an explicit type, for example std::string&& is an r-value and does not 
have the properties of a forwarding reference 
*/

/*
2. Lambda function
*/
auto lambdafunc1() {
  auto v = 7;
  auto lambda = [v]() mutable { // by default, lambda funcs are const
    std::cout << v << " ";
    ++v;
  };
  assert(v == 7);
  lambda();
  lambda();
  assert(v == 7);
  std::cout << v << endl;
}

auto lambdafunc2() {
  auto v = 7;
  auto lambda = [&v]() { // as captured by reference, mutable is not needed
    std::cout << v << " ";
    ++v;
  };
  assert(v == 7);
  lambda();
  lambda();
  assert(v == 9);
  std::cout << v << endl;
}
void lambdatest()
{
    lambdafunc1();
    lambdafunc2();
}

//Assigning C function pointers to lambdas
/*
auto func() {
  auto lambda = +[](int result, const char* str) {}; // using '+' to convert to a regular fun pointer 
                                                    // without any capture
  download_webpage("http://www.packt.com", lambda);
}
*/
//Lambda and std::function
// Create an unassigned std::function object
/*
auto func = std::function<void(int)>{};  
// Assign a lambda without capture to the std::function object 
func = [](int v) { std::cout << v; }; 
func(12); // Prints 12 
 
// Assign a lambda with capture to the same std::function object 
auto forty_two = 42; 
func = [forty_two](int v) { std::cout << (v + forty_two); }; 
func(12); // Prints 54 
*/
//polymorphic lambdas
auto farm = std::vector<std::pair<std::string, int>>{ 
  {"Bear", 5}, 
  {"Deer", 0}, 
  {"Pig", 4} 
}; 
 
enum class Continent { Europe, Asia, America }; 
auto countries = std::vector<std::pair<std::string, Continent>>{ 
  {"Sweden", Continent::Europe}, 
  {"India", Continent::Asia}, 
  {"Belarus", Continent::Europe}, 
  {"Mexico", Continent::America} 
}; 

//the template function is_second_equal is utilized as a proxy to make the capture type a template. 
// Then, the returned polymorphic lambda does not need to know about the full type of the pair.
template <typename T> 
auto is_second_equal(const T& x) { 
  // A lambda capturing x is returned
  return [&x](const auto& p) { return p.second == x; }; 
} 

void polylambda()
{
    auto missing_animals = std::count_if(farm.begin(), farm.end(), is_second_equal(0)); 
    // missing_animals equals 1 as there are no deers in the farm 
    cout << missing_animals << endl;
    auto num_european_countries = std::count_if( 
    countries.begin(),  
    countries.end(),  
    is_second_equal(Continent::Europe));
    cout << num_european_countries << endl;  
}

// Const propagation for pointer
namespace exp = std::experimental;
class Foo { 
public:
  auto set_ptr(int* p) const { 
    ptr_ = p;  // Will not compile, as expected
  }
  auto set_val(int v) const { 
    val_ = v;  // Will not compile, as expected
  }
  auto set_ptr_val(int v) const { 
    *ptr_ = v; // Will not compile, const is propagated
  }
private:
  exp::propagate_const<int*> ptr_ = nullptr; 
  int val_{}; 
}; 

//Applying the && modifier to class member functions
// only permitted to be executed on an r-value.

/*
3. std::optional
   a stack-allocated container with a max size of one.
*/

int main()
{
    // lambdatest();
    polylambda();
    return 0;
}
