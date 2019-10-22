/**
    Copyright (C) 2019  Abhilash Chowdhary

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
**/

#include <type_traits>
#include <cmath>
using namespace std;

// template< class ... > using void_t = void;                                         
template<typename... > struct Voider { using Type = void; };
template<typename... TArgs> using void_t = typename Voider<TArgs...>::Type;


// type traits for conditionals
template <typename... Conds>
struct and_ : std::true_type {};

template <typename... Conds>
struct or_ : std::false_type {};

template <typename Cond, typename... Conds>
struct and_<Cond, Conds...>
    : std::conditional<Cond::value, and_<Conds...>, std::false_type>::type {};

template <typename Cond, typename... Conds>
struct or_<Cond, Conds...>
    : std::conditional<Cond::value, std::true_type, or_<Conds...>>::type {};

// Preprocessors for creating type_traits for any member named "X"
#define CREATE_MEMBER_DETECTOR(X)                                                                          \
template< class , class = void >                                                                           \
struct Has_MVar_##X : std::false_type                                                                      \
{ };                                                                                                       \
                                                                                                           \
/* specialized as Has_Var_##X< T , void > or discarded (sfinae)    */                                      \
template< class T >                                                                                        \
struct Has_MVar_##X< T , void_t<decltype(T::X) > > : std::true_type                                        \
{ };                                                         


#define CREATE_MEMBER_FUNC_DETECTOR(X)                                                                      \
template<class, typename, class = void>                                                                     \
struct Has_MFunc_##X : false_type {};                                                                       \
                                                                                                            \
template< class T,  typename Ret, typename... Args>                                                         \
struct Has_MFunc_##X<T,                                                                                     \
               Ret(Args...),                                                                                \
               void_t<decltype(std::declval<Ret&>() =                                                       \
                               std::declval<T>().X(std::declval<Args>()...))> >                             \
                    : std::is_same<decltype(std::declval<T>().X(std::declval<Args>()...)),                  \
                                   Ret>::type {}; 

// generating the type_traits for member variables "x"/"x_" and member functions "x()"/"getX()"

CREATE_MEMBER_FUNC_DETECTOR(x);
CREATE_MEMBER_FUNC_DETECTOR(getX);
CREATE_MEMBER_DETECTOR(x);
CREATE_MEMBER_DETECTOR(x_);

CREATE_MEMBER_FUNC_DETECTOR(y);
CREATE_MEMBER_FUNC_DETECTOR(getY);
CREATE_MEMBER_DETECTOR(y);
CREATE_MEMBER_DETECTOR(y_);

CREATE_MEMBER_FUNC_DETECTOR(z);
CREATE_MEMBER_FUNC_DETECTOR(getZ);
CREATE_MEMBER_DETECTOR(z);
CREATE_MEMBER_DETECTOR(z_);

// generating type_traits for "Has_Xaxis"/"Has_Yaxis"/"Has_Zaxis"
template<typename T>
  using Has_Xaxis = or_<Has_MVar_x<T>, Has_MVar_x_<T>, Has_MFunc_x<T, float(void)>, Has_MFunc_getX<T, float(void)>>;

template<typename T>
  using Has_Yaxis = or_<Has_MVar_y<T>, Has_MVar_y_<T>, Has_MFunc_y<T, float(void)>, Has_MFunc_getY<T, float(void)>>;
  
template<typename T>
  using Has_Zaxis = or_<Has_MVar_z<T>, Has_MVar_z_<T>, Has_MFunc_z<T, float(void)>, Has_MFunc_getZ<T, float(void)>>;
  
template<typename T>
  using Is_Vector2D = and_<Has_Xaxis<T>, Has_Yaxis<T>>;

template<typename T>
  using Is_Vector3D = and_<Has_Xaxis<T>, Has_Yaxis<T>, Has_Zaxis<T>>;
  
