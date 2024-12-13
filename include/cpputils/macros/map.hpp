#pragma once

#define _cpputils_map_1(_func, _x) _func(_x) 
#define _cpputils_map_2(_func, _x, ...) _func(_x)_cpputils_map_1(_func, __VA_ARGS__)
#define _cpputils_map_3(_func, _x, ...) _func(_x)_cpputils_map_2(_func, __VA_ARGS__)
#define _cpputils_map_4(_func, _x, ...) _func(_x)_cpputils_map_3(_func, __VA_ARGS__)
#define _cpputils_map_5(_func, _x, ...) _func(_x)_cpputils_map_4(_func, __VA_ARGS__)
#define _cpputils_map_6(_func, _x, ...) _func(_x)_cpputils_map_5(_func, __VA_ARGS__)
#define _cpputils_map_7(_func, _x, ...) _func(_x)_cpputils_map_6(_func, __VA_ARGS__)
#define _cpputils_map_8(_func, _x, ...) _func(_x)_cpputils_map_7(_func, __VA_ARGS__)
#define _cpputils_map_9(_func, _x, ...) _func(_x)_cpputils_map_8(_func, __VA_ARGS__)
#define _cpputils_map_10(_func, _x, ...) _func(_x)_cpputils_map_9(_func, __VA_ARGS__)
#define _cpputils_map_11(_func, _x, ...) _func(_x)_cpputils_map_10(_func, __VA_ARGS__)
#define _cpputils_map_12(_func, _x, ...) _func(_x)_cpputils_map_11(_func, __VA_ARGS__)
#define _cpputils_map_13(_func, _x, ...) _func(_x)_cpputils_map_12(_func, __VA_ARGS__)
#define _cpputils_map_14(_func, _x, ...) _func(_x)_cpputils_map_13(_func, __VA_ARGS__)
#define _cpputils_map_15(_func, _x, ...) _func(_x)_cpputils_map_14(_func, __VA_ARGS__)
#define _cpputils_map_16(_func, _x, ...) _func(_x)_cpputils_map_15(_func, __VA_ARGS__)

#define _cpputils_map_getn(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_name,...) _name 

#define cpputils_map(_func,...) \
  _cpputils_map_getn(__VA_ARGS__,_cpputils_map_16,_cpputils_map_15,_cpputils_map_14,_cpputils_map_13,_cpputils_map_12,_cpputils_map_11,_cpputils_map_10,_cpputils_map_9,_cpputils_map_8,_cpputils_map_7,_cpputils_map_6,_cpputils_map_5,_cpputils_map_4,_cpputils_map_3,_cpputils_map_2,_cpputils_map_1)(_func,__VA_ARGS__)