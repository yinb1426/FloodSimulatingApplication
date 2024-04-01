#pragma once
#include "Model.h"
#include "Utils.h"

class VPM final : public Model
{
private:
	double pipeLength;
	double gravity;
	double Ke;
	size_t numRainfallLayer;
	vector<double> buildingHeight;
	vector<double> rainfallRate;
	vector<Vec3> riverInflow;
	vector<Vec2> waterVelocity;
	vector<FlowField> flowField;
	vector<FlowField> newFlowField;
	double* gBuildingHeight;
	double* gRainfallRate;
	Vec3* gRiverInflow;
	Vec2* gWaterVelocity;
	FlowField* gFlowField;
	FlowField* gNewFlowField;

public:
	VPM(size_t _sizeX, size_t _sizeY, size_t _deltaX, double _deltaT, double _pipeLength, double _gravity, double _Ke,
		vector<double> _terrainHeight, vector<double> _buildingHeight, vector<double> _damHeight, vector<double> _waterHeight,
		vector<double> _rainfallRate, vector<double> _drainRate, vector<Vec3> _riverInflow)
		: Model(_sizeX, _sizeY, _deltaX, _deltaT, _terrainHeight, _waterHeight, _damHeight, _drainRate), pipeLength(_pipeLength), gravity(_gravity), Ke(_Ke),
		buildingHeight(_buildingHeight), rainfallRate(_rainfallRate), riverInflow(_riverInflow)
	{
		numRainfallLayer = rainfallRate.size() / (_sizeX * _sizeY);
		waterVelocity = vector<Vec2>(_sizeX * _sizeY);
		flowField = vector<FlowField>(_sizeX * _sizeY);
		newFlowField = vector<FlowField>(_sizeX * _sizeY);
	}

	VPM(int _sizeX, int _sizeY, size_t _deltaX, vector<double> _terrainHeight, vector<double> _buildingHeight, vector<double> _damHeight, vector<double> _waterHeight,
		vector<double> _rainfallRate, vector<double> _drainRate, vector<Vec3> _riverInflow)
		: Model(_sizeX, _sizeY, _deltaX, 0.5, _terrainHeight, _waterHeight, _damHeight, _damHeight), buildingHeight(_buildingHeight),
		rainfallRate(_rainfallRate), riverInflow(_riverInflow)
	{
		pipeLength = 15.0;
		gravity = 9.8;
		Ke = 0.00001;
		numRainfallLayer = rainfallRate.size() / (_sizeX * _sizeY);
		waterVelocity = vector<Vec2>(_sizeX * _sizeY);
		flowField = vector<FlowField>(_sizeX * _sizeY);
		newFlowField = vector<FlowField>(_sizeX * _sizeY);
	}

public:
	void SetPipeLength(const double newPipeLength);
	double GetPipeLength() const;

	void SetGravity(const double newGravity);
	double GetGravity() const;

	void SetKe(const double newKe);
	double GetKe() const;

	void InitDevice() override final;
	void SendAllDataToDevice() override final;
	void PreparationForSimulaion() override final;
	void RunSimulation(const size_t step) override final;
	void GetResultFromDevice() override final;
	void FreeAllData() override final;
};