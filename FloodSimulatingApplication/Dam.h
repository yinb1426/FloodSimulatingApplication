#pragma once
#include <vector>
#include "Point.h"

/**
 * @brief 堤坝类
 * 保存由用户绘制的堤坝
 * 类成员：
 *     1. posList：保存堤坝折线的所有折点坐标
 *     2. height：描述堤坝高于地表的高度，用于和地表高度累加
 */

class Dam
{
private:
	std::vector<Point<double>> posList;  // 堤坝折线折点集
	double height;						 // 堤坝高度

public:
	Dam() : posList(std::vector<Point<double>>(0)), height(0.0) {}
	Dam(std::vector<Point<double>> _posList, double _height) : posList(_posList), height(_height) {}
	Dam(double _height) : posList(std::vector<Point<double>>(0)), height(_height) {}
	~Dam() {}

public:
	void SetPosList(std::vector<Point<double>> posList)
	{
		this->posList = posList;
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

	// 获取折点总数
	size_t GetPointCount()
	{
		return this->posList.size();
	}

	// 获取指定index的Point<double>点
	Point<double> GetSelectedPoint(size_t index)
	{
		if (index >= this->posList.size() || index < 0)
			throw "Index Wrong";
		return this->posList[index];
	}
};