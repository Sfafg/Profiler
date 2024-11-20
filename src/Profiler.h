#pragma once
#include <span>
#include <stack>
#include <chrono>
#include <source_location>
#include <thread>

class Profiler
{
public:
    static const unsigned int maxFunctions = 32;
    static const unsigned int maxFunctionNameLength = 128;
    static const unsigned int maxSampleCount = 16384;

    class Function;
    static void BeginFrame();
    static void EndFrame();
    class Samples
    {
        double totalSum;
        float totalMin;
        float totalMax;
        unsigned int offset;
        unsigned int sampleCount;
        unsigned int totalSampleCount;
        unsigned int sampleLimit;
        float currentSample;
        float samples[maxSampleCount];
        friend Function;
        friend void Profiler::BeginFrame();
        friend void Profiler::EndFrame();

    public:
        Samples();

        std::span<float> Data();
        std::span<const float> Data() const;
        int GetOffset() const;
        float GetMax() const;
        float GetMin() const;
        float GetAverage() const;
        float GetTotalAverage() const;
        float GetTotalMin() const;
        float GetTotalMax() const;
        unsigned int GetTotalSampleCount() const;
        float GetCurrent() const;
        unsigned int& GetSampleLimit();
        void SetSampleLimit(unsigned int sampleLimit);
        void UnwindOffset();

    private:
        void BeginAccumulate();
        void Accumulate(float sample);
        void EndAccumulate();
    };

    enum FunctionType
    {
        Time, Memory, Count
    };

    class Function
    {
        int programID;
        FunctionType type;
        char name[maxFunctionNameLength];
        Samples samples;
        int invocations;
        int lastInvocations;
        std::chrono::high_resolution_clock::time_point sampleStart;

    public:
        Function(const char* name = "", FunctionType type = FunctionType::Time);

        char* GetName();
        const char* GetName() const;
        FunctionType GetType() const;
        int GetInvocations() const;
        Samples& GetSamples();
        const Samples& GetSamples() const;

        void AddSample(float sample);
        void BeginSample();
        void EndSample();

        bool operator <(const Function& rhs) const;
        bool operator >(const Function& rhs) const { return !this->operator<(rhs); }

        friend Profiler;
    };

    struct ScopedFunction
    {
        Function* function;
        ScopedFunction(const char* name);
        ~ScopedFunction();
    };

    static void SetHightPriority();
    static Function* AddFunction(const char* name, FunctionType type = FunctionType::Time);
    static Function* GetFunction(const char* name);
    static void RemoveFunction(const char* name);
    static std::span<Function> GetFunctions();

    static void BeginFunction(const char* name = std::source_location::current().function_name());
    static void EndFunction(const char* name = std::source_location::current().function_name());

private:
    struct Header
    {
        int functionCount;
        Function functions[maxFunctions];
    };
    const int a = sizeof(Header);

    struct HeaderHandle
    {
        void* fileHandle;
        Header* header;

        HeaderHandle() :fileHandle(nullptr), header(nullptr) {}
        bool Create();
        bool Open();
        ~HeaderHandle();
    };
    static bool InitHeader();
    static HeaderHandle headerHandle;
    static bool isFrameActive;
};

#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )
#define PROFILE_NAMED_FUNCTION(name) Profiler::ScopedFunction MACRO_CONCAT(___SCOPED_FUNCTION_OBJECT___, __COUNTER__)(name)
#define PROFILE_FUNCTION() Profiler::ScopedFunction MACRO_CONCAT(___SCOPED_FUNCTION_OBJECT___, __COUNTER__)(std::source_location::current().function_name())


inline bool Profiler::InitHeader()
{
    if (headerHandle.header)
        return true;

#ifdef PROFILER_HOST
    return headerHandle.Create();
#else
    return headerHandle.Open();
#endif
}