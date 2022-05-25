#include <iostream>

namespace my{
    template <typename T1, typename T2>
    class Pair{
    public:
        Pair() : first() , second(){}
        ~Pair() = default;
        Pair(const T1& f, const T2& s) : first(f) , second(s) {}
        Pair(const Pair& p) = default;
        Pair(Pair&& p) = default;
        template<typename U, typename V>
        Pair(const Pair<U, V>& p) : first(p.first) , second(p.second) {}
        template <typename U, typename V>
        Pair(Pair<U, V>&& p) : first(std::move(p.first)) , second(std::move(p.second)) {}
        template<typename U, typename V> 
        Pair(U&& f, V&& s) : first(std::move(f)) , second(std::move(s)) {}
        template <typename... Args1, typename... Args2>
        Pair(std::piecewise_construct_t arg, std::tuple<Args1...> f_a, std::tuple<Args2...> s_a) : Pair(arg, f_a, s_a,
            typename std::__make_tuple_indices<sizeof...(Args1)>::type(),
            typename std::__make_tuple_indices<sizeof...(Args2) >::type()) {}

    public:
        Pair& operator=(const Pair& p) { first = p.first; second = p.second; return *this;}
        Pair& operator=(Pair&& p){ first = std::move(p.first); second = std::move(p.second); return *this;}
        bool operator==(const Pair& oth) { return (this->first == oth.first) && (this->second == oth.second);}
        bool operator!=(const Pair& oth) { return !(*this == oth); }
        bool operator<(const Pair& oth) { return (this->first < oth.first) || !(oth.first < this->first) || (this->second < oth.second); } 
        bool operator>(const Pair& oth) { return oth < (*this); }
        bool operator<=(const Pair& oth) { return !(oth < (*this)); }
        bool operator>=(const Pair& oth) { return !(*this < oth); } 
    public:
        void swap(Pair& p){ std::swap(first, p.first);  std::swap(second, p.second);}
    public:
        T1 first;
        T2 second;
    };
}

template<size_t index>
struct get_
{
    template <typename T1, typename T2>
    T1 get(const my::Pair<T1, T2>&);
};

template<> 
struct get_<0>
{
    template <typename T1, typename T2>
    static T1 get(const my::Pair<T1, T2>& p){ return p.first;} 
};

template<>
struct get_<1>
{
    template <typename T1, typename T2>
    static T2 get(const my::Pair<T1, T2>& p){ return p.second;}
};

template <typename T1, typename T2>
my::Pair<T1, T2> Make_Pair(T1 f, T2 s) 
{ 
    return my::Pair<T1 , T2>(f , s); 
}

template <typename T1, typename T2> 
std::ostream& operator<<(std::ostream& out, const my::Pair<T1,T2>& p)
{
    return out << "[" << p.first << "," << p.second << "]";
}

 
