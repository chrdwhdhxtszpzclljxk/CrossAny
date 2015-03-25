#ifndef __CROSSANY_MACRO_H_
#define __CROSSANY_MACRO_H_

#define NS_CROSSANY_BEGIN namespace crossany {
#define NS_CROSSANY_END };
#define USE_NS_CROSSANY using namespace crossany;

#define CROSSANY_EXPORTS

#ifdef CROSSANY_EXPORTS
#define CROSSANY_API __declspec(dllexport)
#else
#define CROSSANY_API __declspec(dllimport)
#endif


#endif