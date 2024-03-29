#include "Model.h"

void Model::SetSizeX(const size_t sizeX)
{
    this->sizeX = sizeX;
}

size_t Model::GetSizeX() const
{
    return this->sizeX;
}

void Model::SetSizeY(const size_t sizeY)
{
    this->sizeY = sizeY;
}

size_t Model::GetSizeY() const
{
    return this->sizeY;
}

void Model::SetDeltaX(const double deltaX)
{
    this->deltaX = deltaX;
}

double Model::GetDeltaX() const
{
    return this->deltaX;
}

void Model::SetDeltaT(const double deltaT)
{
    this->deltaT = deltaT;
}

double Model::GetDeltaT() const
{
    return this->deltaT;
}

void Model::SetTerrainHeight(const vector<double> terrainHeight)
{
    this->terrainHeight = terrainHeight;
}

vector<double> Model::GetTerrainHeight() const
{
    return this->terrainHeight;
}

void Model::SetWaterHeight(const vector<double> waterHeight)
{
    this->waterHeight = waterHeight;
}

vector<double> Model::GetWaterHeight() const
{
    return this->waterHeight;
}

void Model::SetDamHeight(const vector<double> damHeight)
{
    this->damHeight = damHeight;
}

vector<double> Model::GetDamHeight() const
{
    return this->damHeight;
}

void Model::SetDrainRate(const vector<double> drainRate)
{
    this->drainRate = drainRate;
}

vector<double> Model::GetDrainRate() const
{
    return this->drainRate;
}
