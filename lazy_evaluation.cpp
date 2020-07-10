#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <variant>
#include <tuple>
using namespace std;

/*
1. Type traits
Type traits that return information about a type as a boolean or an integer value: end with _v
Type traits that return a new type: end with _t
*/

/*
2. std::tuple
    a heterogenous container with a fixed size and fixed element positions
*/
//Structured bindings
// Prerequisite
auto make_bond() { return std::make_tuple(std::string{"James"}, 7, true); } 
 
void tupletest()
{
    const auto& [name, id, kill_license] = make_bond(); 
    std::cout << name << ", " << id << ", " << kill_license << '\n'; 

    auto agents = { 
    std::make_tuple("James", 7, true), 
    std::make_tuple("Nikita", 108, false) 
    };
    for(auto&& [name, id, kill_license]: agents) { 
        std::cout << name << ", " << id << ", " << kill_license << '\n'; }
}

/*
3. std::variant
*/
void varianttest()
{
    using VariantType = std::variant<int, std::string, bool>; 
    auto c = std::vector<VariantType> { 42, std::string{"needle"}, true }; 
    for (const auto& val: c) { 
      std::visit([](const auto& v){ std::cout << v << '\n';}, val); 
    } 
    auto num_bools = std::count_if(c.begin(), c.end(),  
      [](const auto& v){ 
        return std::holds_alternative<bool>(v); 
      } 
    );
    cout << "number of bools: " << num_bools << endl;
    auto contains_needle_string = std::any_of( 
      c.begin(),  
      c.end(),  
      [](const auto& v){ 
        return  
          std::holds_alternative<std::string>(v) && 
          std::get<std::string>(v) == "needle";
      } 
    );
    cout << "contain needle: " << contains_needle_string << endl;

}

/*
4. && modifier
The && modifier works just like a const modifier, but where a const modifier forces the member 
function to not modify the class, the && modifier forces the function to only invoke on temporary classes.
*/
float dist_sqrd_ = 1;
// operator float() const && { return std::sqrt(dist_sqrd_); } 

/*
5. overload pipeline operator
   overload The infix operator: overload < and >
*/
template <typename T>
struct ContainsProxy { const T& value_; };

template <typename Range, typename T>
auto operator|(const Range& r, const ContainsProxy<T>& proxy) {
  const auto& v = proxy.value_;
  return std::find(r.begin(), r.end(), v) != r.end();
}

template <typename T>
auto contains(const T& v) { return ContainsProxy<T>{v}; }

void containproxytest()
{
    auto numbers = std::vector<int>{1,3,5,7,9}; 
    auto seven = 7; 
    auto proxy = ContainsProxy<decltype(seven)>{seven}; 
    bool has_seven = numbers | proxy;
    cout << "has_seven: " << has_seven << endl;
    auto penguins = std::vector<std::string>{"Ping","Roy","Silo"}; 
    bool has_silo = penguins | contains("Silo");
    cout << "has_silo: " << has_silo << endl;
}


int main()
{
    // tupletest();
    // varianttest();
    containproxytest();
    return 0;
}