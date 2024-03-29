#pragma once
#include "Point.h"

/**
 * @brief 雨水井类
 * 保存由用户绘制的雨水井
 * 类成员：
 *     1. pos：雨水井位置
 *     2. rate：上下水速率，水溢出为正数，水流入为负数
 *	   3. radius：雨水井半径
 */

class Drain
{
private:
	Point<double> pos;	     // 雨水井位置
	double rate;			 // 上下水速率
	double radius;			 // 雨水井半径
public:
	Drain() : pos(Point<double>(0.0, 0.0)), rate(0.0), radius(0.0) {}
	Drain(double _x, double _y, double _rate, double _radius) : pos(Point<double>(_x, _y)), rate(_rate), radius(_radius) {}
	~Drain() {}

public:
	void SetPos(const Point<double> p)
	{
		this->pos = p;
	}
	Point<double> GetPos() const
	{
		return this->pos;
	}
	void SetRate(const double rate)
	{
		this->rate = rate;
	}
	double GetRate() const
	{
		return this->rate;
	}
	void SetRadius(const double radius)
	{
		this->radius = radius;
	}
	double GetRadius() const
	{
		return this->radius;
	}
};