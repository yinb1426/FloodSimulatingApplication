#pragma once
#include <vector>
#include "Point.h"

class Dam
{
protected:
	std::vector<Point<double>> posList;
	double height;

public:
	Dam() : posList(std::vector<Point<double>>(0)), height(0.0) {}
	Dam(std::vector<Point<double>> _posList, double _height) : posList(_posList), height(_height) {}
	Dam(double _height) : posList(std::vector<Point<double>>(0)), height(_height) {}
	~Dam() {}

public:
	void SetPosList(std::vector<Point<double>> pl)
	{
		this->posList = pl;
	}
	std::vector<Point<double>> GetPosList() const
	{
		return this->posList;
	}
	void SetHeight(const double height)
	{
		this->height = height;
	}
	double GetHeight() const
	{
		return this->height;
	}

	void AddPoint(const Point<double> p)
	{
		this->posList.push_back(p);
	}
	void ClearPosList()
	{
		this->posList.clear();
	}

	size_t GetPointCount()
	{
		return this->posList.size();
	}
	Point<double> GetSelectedPoint(size_t index)
	{
		if (index >= this->posList.size() || index < 0)
			throw "Index Wrong";
		return this->posList[index];
	}
};