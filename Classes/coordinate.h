#ifndef __CROSSANY_COORDINATE_H_
#define __CROSSANY_COORDINATE_H_
#include "macro.h"

//NS_CROSSANY_BEGIN
namespace crossany{

	class CROSSANY_API pos2{
	public:
		pos2(const double& _x, const double& _y){ x = _x; y = _y; };
		~pos2();
		double getx(){ return x; }
		double gety(){ return y; }
		double setx(const double& _x){ x = _x; }
		double sety(const double& _y){ y = _y; }
		void set(const double& _x, const double& _y){ x = _x; y = _y; };
	private:
		double x,y;
	};

	class CROSSANY_API size{
	public:
		size(const double& _w, const double& _h){ w = _w; h = _h; };
		~size();
		double getw(){ return w; }
		double geth(){ return h; }
		double setw(const double& _w){ w = _w; }
		double seth(const double& _h){ h = _h; }
		void set(const double& _w, const double& _h){ w = _w; h = _h; };
	private:
		double w, h;
	};
}
//NS_CROSSANY_END

#endif