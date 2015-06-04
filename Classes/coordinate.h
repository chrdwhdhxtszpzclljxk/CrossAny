#ifndef __CROSSANY_COORDINATE_H_
#define __CROSSANY_COORDINATE_H_
#include "macro.h"

//NS_CROSSANY_BEGIN
namespace crossany{

	class CROSSANY_API pos2{
	public:
		pos2(){ x = 0; y = 0; };
		pos2(const double& _x, const double& _y){ x = _x; y = _y; };
		~pos2(){};
		double getx(){ return x; }
		double gety(){ return y; }
		double setx(const double& _x){ x = _x; return x; }
		double sety(const double& _y){ y = _y; return y; }
		void set(const double& _x, const double& _y){ x = _x; y = _y; };
		bool operator== (const pos2& _p) const{ return x == _p.x && y == _p.y; }
	private:
		double x,y;
	public:
		const static pos2 ZERO;
	};

	class CROSSANY_API size{
	public:
		size(){ w = 0; h = 0; };
		size(const double& _w, const double& _h){ w = _w; h = _h; };
		~size(){};
		double getw(){ return w; }
		double geth(){ return h; }
		double setw(const double& _w){ w = _w; return w; }
		double seth(const double& _h){ h = _h; return h; }
		void set(const double& _w, const double& _h){ w = _w; h = _h; };
		bool operator== (const size& _s) const{ return w == _s.w && h == _s.h; };
	private:
		double w, h;
	public:
		const static size ZERO;
	};

	class CROSSANY_API rect{
	public:
		rect(){};
		rect(const pos2& _pos,const size& _size):mpos(_pos),msize(_size){};
		~rect(){};
		bool operator== (const rect& ar) const{ return mpos == ar.mpos && msize == ar.msize; };
	private:
		pos2 mpos;
		size msize;
	public:
		const static rect ZERO;
	};


}
//NS_CROSSANY_END

#endif