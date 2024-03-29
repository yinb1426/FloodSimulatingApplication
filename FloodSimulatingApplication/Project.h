#pragma once
#include "Dam.h"
#include "Drain.h"
#include "Model.h"
#include <iostream>

/**
 * @brief 工程类
 * 类成员：
 *     1. model：工程所用到的水文模型，用户自定义
 * 	   2. damList：堤坝列表，可由用户绘制、添加与删除
 * 	   3. drainList：雨水井列表，可由用户绘制、添加与删除
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
	void UpdateDamHeight();    // 将堤坝列表中的堤坝绘制到模型中的堤坝栅格中

	void AddDrain(const Drain d);
	Drain GetDrain(const size_t index) const;
	void ClearDrainList();
	void UpdateDrainRate();    // 将雨水井列表中的雨水井绘制到模型中的雨水井栅格中 

	shared_ptr<Model> GetModel() const;

	void Preparation();
	void RunSimulation(const size_t steps);
	void RunSimulationOneStep(const size_t step);
	vector<double> GetWaterHeight();
	void GetResult();
	void Ending();

};