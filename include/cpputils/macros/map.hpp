#pragma once

#define _cpputils_map1(_func, _sep, _x) _func(_x)
#define _cpputils_map2(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map1(_func, _sep, __VA_ARGS__)
#define _cpputils_map3(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map2(_func, _sep, __VA_ARGS__)
#define _cpputils_map4(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map3(_func, _sep, __VA_ARGS__)
#define _cpputils_map5(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map4(_func, _sep, __VA_ARGS__)
#define _cpputils_map6(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map5(_func, _sep, __VA_ARGS__)
#define _cpputils_map7(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map6(_func, _sep, __VA_ARGS__)
#define _cpputils_map8(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map7(_func, _sep, __VA_ARGS__)
#define _cpputils_map9(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map8(_func, _sep, __VA_ARGS__)
#define _cpputils_map10(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map9(_func, _sep, __VA_ARGS__)
#define _cpputils_map11(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map10(_func, _sep, __VA_ARGS__)
#define _cpputils_map12(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map11(_func, _sep, __VA_ARGS__)
#define _cpputils_map13(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map12(_func, _sep, __VA_ARGS__)
#define _cpputils_map14(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map13(_func, _sep, __VA_ARGS__)
#define _cpputils_map15(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map14(_func, _sep, __VA_ARGS__)
#define _cpputils_map16(_func, _sep, _x, ...) _func(_x)_sep()_cpputils_map15(_func, _sep, __VA_ARGS__)

#define _cpputils_mapGetMap(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_name,...) _name 

#define cpputils_mapWithSep(_func,_sep,...) \
  _cpputils_mapGetMap(__VA_ARGS__,_cpputils_map16,_cpputils_map15,_cpputils_map14,_cpputils_map13,_cpputils_map12,_cpputils_map11,_cpputils_map10,_cpputils_map9,_cpputils_map8,_cpputils_map7,_cpputils_map6,_cpputils_map5,_cpputils_map4,_cpputils_map3,_cpputils_map2,_cpputils_map1)(_func,_sep,__VA_ARGS__)

#define cpputils_mapNoSep()

#define cpputils_map(_func,...) cpputils_mapWithSep(_func, cpputils_mapNoSep, __VA_ARGS__)