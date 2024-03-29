#pragma once
#include <vector>
using namespace std;

/**
 * @brief 模型基类
 * 用于其他水文模型继承的基类，包含必需的类成员和函数
 * 类成员：
 *     1.  sizeX：栅格宽（等同于width） 
 *     2.  sizeY：栅格高（等同于height）
 *     3.  deltaX：栅格单位长度（默认为正方形）
 *     4.  deltaT：时间步长
 *     5.  terrainHeight：地形高度（5-12均为二维栅格转换为一维数组）
 *     6.  waterHeight：水面高度
 *     7.  damHeight：堤坝高度
 *     8.  drainRate：雨水井上下水速率
 * 	   9.  gTerrainHeight：地形高度（9-12为存放在GPU显存中的对应数据，与5-8一一对应）
 * 	   10. gWaterHeight：水面高度
 * 	   11. gDamHeight：堤坝高度
 * 	   12. gDrainRate：雨水井上下水速率
 */

class Model
{
protected:
	size_t sizeX;										// 栅格宽
	size_t sizeY;										// 栅格高
	size_t deltaX;										// 栅格单位长度
	double deltaT;										// 时间步长
	vector<double> terrainHeight;						// 地形高度
	vector<double> waterHeight;							// 水面高度
	vector<double> damHeight;							// 堤坝高度
	vector<double> drainRate;							// 雨水井上下水速率
	double* gTerrainHeight = nullptr;					// 地形高度(GPU)
	double* gWaterHeight = nullptr;						// 水面高度(GPU)
	double* gDamHeight = nullptr;						// 堤坝高度(GPU)
	double* gDrainRate = nullptr;						// 雨水井上下水速率(GPU)

public:
	Model(size_t _sizeX, size_t _sizeY, double _deltaX, double _deltaT, vector<double> _terrainHeight, vector<double> _waterHeight, vector<double> _damHeight, vector<double> _drainRate)
		: sizeX(_sizeX), sizeY(_sizeY), deltaX(_deltaX), deltaT(_deltaT), terrainHeight(_terrainHeight), waterHeight(_waterHeight), damHeight(_damHeight), drainRate(_drainRate)
	{}

	~Model() {}

	void SetSizeX(const size_t sizeX);
	size_t GetSizeX() const;
	void SetSizeY(const size_t sizeY);
	size_t GetSizeY() const;
	void SetDeltaX(const double deltaX);
	double GetDeltaX() const;
	void SetDeltaT(const double deltaT);
	double GetDeltaT() const;
	void SetTerrainHeight(const vector<double> terrainHeight);
	vector<double> GetTerrainHeight() const;
	void SetWaterHeight(const vector<double> waterHeight);
	vector<double> GetWaterHeight() const;
	void SetDamHeight(const vector<double> damHeight);
	vector<double> GetDamHeight() const;
	void SetDrainRate(const vector<double> drainRate);
	vector<double> GetDrainRate() const;

public:
	virtual void InitDevice() {};								// 初始化Device，在GPU中分配需要的内存
	virtual void SendAllDataToDevice() {};						// 将CPU中的数据传输到GPU中
	virtual void PreparationForSimulaion() {};					// 开始模拟前的数据准备工作
	virtual void RunSimulation(const size_t step) {};			// 单步执行模拟，step为当前运行次数
	virtual void GetResultFromDevice() {};						// 从GPU中获取结果
	virtual void FreeAllData() {};								// 将初始化时分配的内存释放
};

