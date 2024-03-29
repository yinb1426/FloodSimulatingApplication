#pragma once
#include <vector>
using namespace std;

/**
 * @brief ģ�ͻ���
 * ��������ˮ��ģ�ͼ̳еĻ��࣬������������Ա�ͺ���
 * ���Ա��
 *     1.  sizeX��դ�����ͬ��width�� 
 *     2.  sizeY��դ��ߣ���ͬ��height��
 *     3.  deltaX��դ��λ���ȣ�Ĭ��Ϊ�����Σ�
 *     4.  deltaT��ʱ�䲽��
 *     5.  terrainHeight�����θ߶ȣ�5-12��Ϊ��άդ��ת��Ϊһά���飩
 *     6.  waterHeight��ˮ��߶�
 *     7.  damHeight���̰Ӹ߶�
 *     8.  drainRate����ˮ������ˮ����
 * 	   9.  gTerrainHeight�����θ߶ȣ�9-12Ϊ�����GPU�Դ��еĶ�Ӧ���ݣ���5-8һһ��Ӧ��
 * 	   10. gWaterHeight��ˮ��߶�
 * 	   11. gDamHeight���̰Ӹ߶�
 * 	   12. gDrainRate����ˮ������ˮ����
 */

class Model
{
protected:
	size_t sizeX;										// դ���
	size_t sizeY;										// դ���
	size_t deltaX;										// դ��λ����
	double deltaT;										// ʱ�䲽��
	vector<double> terrainHeight;						// ���θ߶�
	vector<double> waterHeight;							// ˮ��߶�
	vector<double> damHeight;							// �̰Ӹ߶�
	vector<double> drainRate;							// ��ˮ������ˮ����
	double* gTerrainHeight = nullptr;					// ���θ߶�(GPU)
	double* gWaterHeight = nullptr;						// ˮ��߶�(GPU)
	double* gDamHeight = nullptr;						// �̰Ӹ߶�(GPU)
	double* gDrainRate = nullptr;						// ��ˮ������ˮ����(GPU)

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
	virtual void InitDevice() {};								// ��ʼ��Device����GPU�з�����Ҫ���ڴ�
	virtual void SendAllDataToDevice() {};						// ��CPU�е����ݴ��䵽GPU��
	virtual void PreparationForSimulaion() {};					// ��ʼģ��ǰ������׼������
	virtual void RunSimulation(const size_t step) {};			// ����ִ��ģ�⣬stepΪ��ǰ���д���
	virtual void GetResultFromDevice() {};						// ��GPU�л�ȡ���
	virtual void FreeAllData() {};								// ����ʼ��ʱ������ڴ��ͷ�
};

