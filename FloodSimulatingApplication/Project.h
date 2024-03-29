#pragma once
#include "Dam.h"
#include "Drain.h"
#include "Model.h"
#include <iostream>

/**
 * @brief ������
 * ���Ա��
 *     1. model���������õ���ˮ��ģ�ͣ��û��Զ���
 * 	   2. damList���̰��б������û����ơ������ɾ��
 * 	   3. drainList����ˮ���б������û����ơ������ɾ��
 */

class Project
{
private:
	shared_ptr<Model> model;
	std::vector<Dam> damList;
	std::vector<Drain> drainList;

public:
	Project() : model(nullptr), damList(std::vector<Dam>(0)), drainList(std::vector<Drain>(0)) {}
	Project(shared_ptr<Model> _model) : model(_model), damList(std::vector<Dam>(0)), drainList(std::vector<Drain>(0)) {}
	~Project() {}

public:
	void AddDam(const Dam d);
	Dam GetDam(const size_t index) const;
	void ClearDamList();
	void UpdateDamHeight();    // ���̰��б��еĵ̰ӻ��Ƶ�ģ���еĵ̰�դ����

	void AddDrain(const Drain d);
	Drain GetDrain(const size_t index) const;
	void ClearDrainList();
	void UpdateDrainRate();    // ����ˮ���б��е���ˮ�����Ƶ�ģ���е���ˮ��դ���� 

	shared_ptr<Model> GetModel() const;

	void Preparation();
	void RunSimulation(const size_t steps);
	void RunSimulationOneStep(const size_t step);
	vector<double> GetWaterHeight();
	void GetResult();
	void Ending();

};