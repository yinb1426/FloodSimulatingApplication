#pragma once
#include "Point.h"

/**
 * @brief ��ˮ����
 * �������û����Ƶ���ˮ��
 * ���Ա��
 *     1. pos����ˮ��λ��
 *     2. rate������ˮ���ʣ�ˮ���Ϊ������ˮ����Ϊ����
 *	   3. radius����ˮ���뾶
 */

class Drain
{
private:
	Point<double> pos;	     // ��ˮ��λ��
	double rate;			 // ����ˮ����
	double radius;			 // ��ˮ���뾶
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