#pragma once
#include "cstring"
#include <windows.h>
#include <assert.h>
#include <cfloat>
#include <filesystem>
#include "Profiler.h"

int GetID()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);

    int id = 0;
    int mult = 1;
    for (int i = 0; path[i] != 0; i++)
    {
        id += path[i] * mult;
        mult *= 32;
    }
    return id;
}

Profiler::Samples::Samples() : totalSum(0.0f), totalMin(FLT_MAX), totalMax(-FLT_MAX), offset(0), totalSampleCount(0), sampleCount(0), sampleLimit(maxSampleCount), currentSample(0) {}

std::span<float> Profiler::Samples::Data()
{
    unsigned int min = sampleLimit - 1;
    if (sampleCount < min) min = sampleCount;
    return std::span<float>(&samples[0], &samples[min]);
}

std::span<const float> Profiler::Samples::Data() const
{
    unsigned int min = sampleLimit - 1;
    if (sampleCount < min) min = sampleCount;
    return std::span<const float>(&samples[0], &samples[min]);
}

int Profiler::Samples::GetOffset() const { return offset; }

float Profiler::Samples::GetMax() const
{
    float m = samples[0];
    for (auto&& s : Data()) if (s > m)m = s;
    return m;
}

float Profiler::Samples::GetMin() const
{
    float m = samples[0];
    for (auto&& s : Data()) if (s < m)m = s;
    return m;
}

float Profiler::Samples::GetAverage() const
{
    float m = samples[0];
    for (auto&& s : Data()) m += s;
    return m / Data().size();
}

float Profiler::Samples::GetTotalAverage() const { return totalSum / totalSampleCount; }

float Profiler::Samples::GetTotalMin() const { return totalMin; }

float Profiler::Samples::GetTotalMax() const { return totalMax; }

unsigned int Profiler::Samples::GetTotalSampleCount() const { return totalSampleCount; }

float Profiler::Samples::GetCurrent() const
{
    if (sampleCount < sampleLimit)
    {
        int index = sampleCount - 1;
        if (0 > index) index = 0;
        return samples[index];
    }
    return samples[offset];
}

unsigned int& Profiler::Samples::GetSampleLimit() { return sampleLimit; }

void Profiler::Samples::SetSampleLimit(unsigned int sampleLimit)
{
    assert(sampleLimit <= maxSampleCount);
    this->sampleLimit = sampleLimit;
    if (sampleLimit < sampleCount)
    {
        sampleCount = sampleLimit;
        offset = 0;
    }
    else if (sampleLimit > sampleCount)
        UnwindOffset();
}

void Profiler::Samples::UnwindOffset()
{
    int count = sampleCount;
    int offs = offset;
    float* temp = new float[count - offs];
    memcpy(temp, &samples[offs], (count - offs) * sizeof(samples[0]));
    memcpy(&samples[count - offs], &samples[0], offs * sizeof(samples[0]));
    memcpy(&samples[0], temp, (count - offs) * sizeof(samples[0]));
    delete[] temp;

    offset = 0;
}

void Profiler::Samples::BeginAccumulate()
{
    currentSample = 0;
}

void Profiler::Samples::Accumulate(float sample)
{
    currentSample += sample;
}

void Profiler::Samples::EndAccumulate()
{
    float sample = currentSample;

    totalSampleCount++;
    totalSum += sample;
    if (sample > totalMax) totalMax = sample;
    if (sample < totalMin) totalMin = sample;

    if (sampleCount < sampleLimit)
        samples[sampleCount++] = sample;
    else
    {
        samples[offset] = sample;
        offset = (offset + 1) % sampleLimit;
    }
}


Profiler::Function::Function(const char* name, Profiler::FunctionType type)
    :name{ 0 }, type(type), programID(GetID())
{
    strncpy(this->name, name, maxFunctionNameLength);
}
char* Profiler::Function::GetName() { return name; }

const char* Profiler::Function::GetName() const { return name; }

Profiler::FunctionType Profiler::Function::GetType() const { return type; }

int Profiler::Function::GetInvocations() const { return lastInvocations; }

Profiler::Samples& Profiler::Function::GetSamples() { return samples; }
const Profiler::Samples& Profiler::Function::GetSamples() const { return samples; }

void Profiler::Function::AddSample(float sample)
{
    if (!isFrameActive)
        samples.BeginAccumulate();

    invocations++;
    samples.Accumulate(sample);

    if (!isFrameActive)
    {
        lastInvocations = invocations;
        invocations = 0;
        samples.EndAccumulate();
    }
}

void Profiler::Function::BeginSample()
{
    if (!isFrameActive)
        samples.BeginAccumulate();

    invocations++;
    sampleStart = std::chrono::high_resolution_clock::now();
}

void Profiler::Function::EndSample()
{
    auto sampleEnd = std::chrono::high_resolution_clock::now();
    float sample = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(sampleEnd - sampleStart).count();
    samples.Accumulate(sample);

    if (!isFrameActive)
    {
        lastInvocations = invocations;
        invocations = 0;
        samples.EndAccumulate();
    }
}


bool Profiler::Function::operator <(const Profiler::Function& rhs) const
{
    if (GetType() != rhs.GetType())
        return GetType() < rhs.GetType();

    return GetSamples().GetAverage() < rhs.GetSamples().GetAverage();
}


Profiler::ScopedFunction::ScopedFunction(const char* name)
{
    function = AddFunction(name);
    if (!function)return;
    function->BeginSample();
}

Profiler::ScopedFunction::~ScopedFunction()
{
    if (!function)return;
    function->EndSample();
    function = nullptr;
}

void Profiler::SetHightPriority()
{
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
}

void Profiler::BeginFrame()
{
    isFrameActive = true;
    int id = GetID();
    for (auto&& i : GetFunctions())
        if (i.programID == id)
            i.GetSamples().BeginAccumulate();
}
void Profiler::EndFrame()
{
    isFrameActive = false;
    for (auto&& i : GetFunctions())
        if (i.programID == GetID())
        {
            i.lastInvocations = i.invocations;
            i.invocations = 0;
            i.GetSamples().EndAccumulate();
        }
}

Profiler::Function* Profiler::AddFunction(const char* name, Profiler::FunctionType type)
{
    if (!Profiler::InitHeader())
        return nullptr;

    if (Profiler::Function* function = Profiler::GetFunction(name))
        return function;

    assert(Profiler::headerHandle.header->functionCount < Profiler::maxFunctions);
    return new (&Profiler::headerHandle.header->functions[Profiler::headerHandle.header->functionCount++]) Profiler::Function(name, type);
}

Profiler::Function* Profiler::GetFunction(const char* name)
{
    if (!Profiler::InitHeader() || name[0] == 0)
        return nullptr;

    for (auto&& func : GetFunctions())
        if (strcmp(name, func.name) == 0)
            return &func;

    return nullptr;
}

void Profiler::RemoveFunction(const char* name)
{
    if (!Profiler::InitHeader() || name[0] == 0)
        return;

    for (auto&& func : GetFunctions())
    {
        if (strcmp(name, func.name) == 0)
        {
            std::swap(func, GetFunctions().back());
            Profiler::headerHandle.header->functionCount--;
            return;
        }
    }
}

std::span<Profiler::Function> Profiler::GetFunctions()
{
    if (!Profiler::InitHeader())
        return std::span<Profiler::Function>();

    return std::span<Profiler::Function>(&Profiler::headerHandle.header->functions[0], &Profiler::headerHandle.header->functions[Profiler::headerHandle.header->functionCount]);
}

void Profiler::BeginFunction(const char* name)
{
    Function* func = AddFunction(name);
    if (!func)return;
    func->BeginSample();
}

void Profiler::EndFunction(const char* name)
{
    Function* func = AddFunction(name);
    if (!func)return;
    func->EndSample();
}


bool Profiler::HeaderHandle::Create()
{
    fileHandle = (void*) CreateFileMappingA((HANDLE) -1, NULL, PAGE_READWRITE, 0, sizeof(Profiler::Header), "Profiler/Header");
    header = (Profiler::Header*) (LPTSTR) MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Profiler::Header));
    header->functionCount = 0;

    return fileHandle;
}

bool Profiler::HeaderHandle::Open()
{
    fileHandle = (void*) OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "Profiler/Header");
    header = (Profiler::Header*) (LPTSTR) MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Profiler::Header));

    return fileHandle;
}

Profiler::HeaderHandle::~HeaderHandle()
{
    UnmapViewOfFile(header);
    CloseHandle(fileHandle);
}

inline Profiler::HeaderHandle Profiler::headerHandle;
inline bool Profiler::isFrameActive = false;