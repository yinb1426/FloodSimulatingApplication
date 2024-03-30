#include "Project.h"
#include <queue>

void Project::AddDam(const Dam d)
{
	damList.push_back(d);
}

Dam Project::GetDam(const size_t index) const
{
	if (index < 0 || index >= damList.size())
		throw("Index Wrong!");
	return damList[index];
}

void Project::ClearDamList()
{
	damList.clear();
}

void Project::UpdateDamHeight()
{
	size_t sizeX = model->GetSizeX();
	vector<double> raster(sizeX * model->GetSizeY());
	for (auto& d : damList)
	{
		size_t damNum = d.GetPointCount();
		for (size_t i = 0; i < damNum - 1; ++i)
		{
			int x0 = d.GetPosList()[i].GetX();
			int y0 = d.GetPosList()[i].GetY();
			int x1 = d.GetPosList()[i + 1].GetX();
			int y1 = d.GetPosList()[i + 1].GetY();
			int dx = fabs(x1 - x0), dy = fabs(y1 - y0);
			int sx = (x0 < x1) ? 1 : -1;
			int sy = (y0 < y1) ? 1 : -1;
			raster[y0 * sizeX + x0] = d.GetHeight();
			int xBase = x0, yBase = y0;
			int e = 0, d1 = 0, d2 = 0;
			if (dx >= dy)
			{
				e = dy * 2 - dx;
				d1 = 2 * dy;
				d2 = (dy - dx) * 2;
				while (xBase != x1)
				{
					if (e >= 0)
					{
						xBase += sx;
						yBase += sy;
						e += d2;
					}
					else
					{
						xBase += sx;
						e += d1;
					}
					raster[yBase * sizeX + xBase] = d.GetHeight();
				}
			}
			else
			{
				e = dx * 2 - dy;
				d1 = dx * 2;
				d2 = (dx - dy) * 2;
				while (yBase != y1)
				{
					if (e >= 0)
					{
						xBase += sx;
						yBase += sy;
						e += d2;
					}
					else
					{
						yBase += sy;
						e += d1;
					}
					raster[yBase * sizeX + xBase] = d.GetHeight();
				}
			}
		}
	}
	model->SetDamHeight(raster);
}

void Project::AddDrain(const Drain d)
{
	drainList.push_back(d);
}

Drain Project::GetDrain(const size_t index) const
{
	if (index < 0 || index >= drainList.size())
		throw("Index Wrong!");
	return drainList[index];
}

void Project::ClearDrainList()
{
	drainList.clear();
}

inline bool IsInRound(pair<int, int> p, int r)
{
	double d2 = p.first * p.first + p.second * p.second;
	return (d2 < r * r * 1.0) ? true : false;
}

void Project::UpdateDrainRate()
{
	double ratio = model->GetDeltaX();
	size_t sizeX = model->GetSizeX();
	vector<double> raster(sizeX * model->GetSizeY());
	for (auto& d : drainList)
	{
		int r = fmax(1, round(d.GetRadius() / ratio));
		int xc = d.GetPos().GetX(), yc = d.GetPos().GetY();
		int x0 = 0, y0 = r;
		int p = 1 - r;
		double rate = d.GetRate();
		while (x0 <= y0)
		{
			raster[( y0 + yc) * sizeX + ( x0 + xc)] = rate;
			raster[( y0 + yc) * sizeX + (-x0 + xc)] = rate;
			raster[(-y0 + yc) * sizeX + ( x0 + xc)] = rate;
			raster[(-y0 + yc) * sizeX + (-x0 + xc)] = rate;
			raster[( x0 + yc) * sizeX + ( y0 + xc)] = rate;
			raster[(-x0 + yc) * sizeX + ( y0 + xc)] = rate;
			raster[( x0 + yc) * sizeX + (-y0 + xc)] = rate;
			raster[(-x0 + yc) * sizeX + (-y0 + xc)] = rate;
		
			if (p < 0)
				p += 2 * x0 + 3;
			else
			{
				p += 2 * (x0 - y0) + 5;
				y0--;
			}
			x0++;
		}
		queue<pair<int, int>> indexQueue;
		indexQueue.push(pair<int, int>(xc, yc));
		while (!indexQueue.empty())
		{
			pair<int, int> currentIndex = indexQueue.front();
			indexQueue.pop();
			raster[currentIndex.second * sizeX + currentIndex.first] = rate;
			if (IsInRound(pair<int, int>(currentIndex.first + 1 - xc, currentIndex.second - yc), r) && raster[currentIndex.second * sizeX + (currentIndex.first + 1)] != rate)
			{
				indexQueue.push(pair<int, int>(currentIndex.first + 1, currentIndex.second));
				raster[currentIndex.second * sizeX + (currentIndex.first + 1)] = rate;
			}
			if (IsInRound(pair<int, int>(currentIndex.first - xc, currentIndex.second + 1 - yc), r) && raster[(currentIndex.second + 1) * sizeX + currentIndex.first] != rate)
			{
				indexQueue.push(pair<int, int>(currentIndex.first, currentIndex.second + 1));				
				raster[(currentIndex.second + 1) * sizeX + currentIndex.first] = rate;
			}
			if (IsInRound(pair<int, int>(currentIndex.first - 1 - xc, currentIndex.second - yc), r) && raster[currentIndex.second * sizeX + (currentIndex.first - 1)] != rate)
			{
				indexQueue.push(pair<int, int>(currentIndex.first - 1, currentIndex.second));
				raster[currentIndex.second * sizeX + (currentIndex.first - 1)] = rate;
			}
			if (IsInRound(pair<int, int>(currentIndex.first - xc, currentIndex.second - 1 - yc), r) && raster[(currentIndex.second - 1) * sizeX + currentIndex.first] != rate)
			{
				indexQueue.push(pair<int, int>(currentIndex.first, currentIndex.second - 1));
				raster[(currentIndex.second - 1) * sizeX + currentIndex.first] = rate;
			}
		}
	}
	model->SetDrainRate(raster);
}

shared_ptr<Model> Project::GetModel() const
{
	return shared_ptr<Model>(model);
}

void Project::Preparation()
{
	model->InitDevice();
	model->SendAllDataToDevice();
	model->PreparationForSimulaion();
}

void Project::RunSimulation(const size_t steps)
{
	size_t totalSteps = steps;
	if (steps < 0)
		totalSteps = std::numeric_limits<size_t>::max();
	size_t step = 0;
	while (step < totalSteps)
	{
		model->RunSimulation(step);
		++step;
	}
}

void Project::RunSimulationOneStep(const size_t step)
{
	if (step < 0)
		throw("Step Wrong!");
	model->RunSimulation(step);
}

vector<double> Project::GetWaterHeight()
{
	return model->GetWaterHeight();
}

void Project::GetResult()
{
	model->GetResultFromDevice();
}

void Project::Ending()
{
	model->FreeAllData();
}
