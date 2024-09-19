#include "Renderer.h"
#define PROFILER_HOST
#include "Profiler.h"
#include "Profiler.cpp"
#include <fstream>
#include <thread>
#include <vector>
#include <commdlg.h>
#include <filesystem>
using namespace std::chrono_literals;

bool OpenFileDialog(char* fileName)
{
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files\0*.txt\0\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = "txt";

    return GetOpenFileNameA(&ofn);
}

bool SaveFileDialog(char* fileName)
{
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files\0*.txt\0\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = "txt";

    return GetSaveFileNameA(&ofn);
}

void SaveFunction(Profiler::Function& function, std::ofstream& file)
{
    function.GetSamples().UnwindOffset();
    file.write((char*) &function, sizeof(function));
}

void SaveFunction(Profiler::Function& function, const char* filePath)
{
    std::ofstream file(filePath, std::ios_base::binary);
    SaveFunction(function, file);
}

Profiler::Function LoadFunction(std::ifstream& file, const char* funcName)
{
    Profiler::Function function("");
    if (file.is_open())
        file.read((char*) &function, sizeof(function));

    strncpy(function.GetName(), funcName, Profiler::maxFunctionNameLength);
    return function;
}

Profiler::Function LoadFunction(const char* filePath)
{
    std::ifstream file(filePath, std::ios_base::binary);
    std::string name = std::filesystem::path(filePath).stem().string();
    auto off = name.find(']', 0) + 1;
    char funcName[Profiler::maxFunctionNameLength];
    strncpy(funcName, &name.substr(off, name.size() - off)[0], Profiler::maxFunctionNameLength);
    return LoadFunction(file, funcName);
}

struct Settings
{
    float width;
    int height;
    int limit;
    std::vector<Profiler::Function> referances;
    std::vector<std::string> referancePaths;

    void Read(std::ifstream& file)
    {
        int count;
        file >> width >> height >> limit >> count;
        referances.resize(count);
        referancePaths.resize(count);
        file.get();
        for (int i = 0; i < count; i++)
        {
            std::getline(file, referancePaths[i]);
            referances[i] = LoadFunction(referancePaths[i].data());
        }
        file.get();
    }
    void Write(std::ofstream& file)
    {
        int count = referances.size();
        file << width << ' ' << height << ' ' << limit << ' ' << count << '\n';
        for (int i = 0; i < count; i++)
        {
            file << referancePaths[i] << '\n';
        }
        file << '\n';
    }
};

Settings settings[Profiler::maxFunctions];

static void ReadSettings()
{
    std::ifstream file("profilerSettings.txt");
    if (file.is_open())
    {
        for (int i = 0; i < Profiler::maxFunctions; i++)
            settings[i].Read(file);

        file.close();
    }
}

static void WriteSettings()
{
    std::ofstream file("profilerSettings.txt");
    if (file.is_open())
    {
        for (int i = 0; i < Profiler::GetFunctions().size(); i++)
            settings[i].Write(file);

        file.close();
    }
}

int GetOffset(Profiler::Function& function)
{
    return &function - &Profiler::GetFunctions()[0];
}

std::tuple<float, const char*> TransfomWithSuffix(float value, Profiler::FunctionType type)
{
    float sign = 1;
    if (value < 0)
    {
        value = -value;
        sign = -1;
    }
    switch (type)
    {
    case Profiler::Memory:
    {
        static const char* memSuffixes[4] = { "B","KB","MB","GB" };
        int suffixIndex = 1;
        if (value <= 100.0f / 1024)
        {
            suffixIndex--;
            value *= 1024;
        }
        for (int i = 0; i < 2; i++)
        {
            if (value >= 1024.0)
            {
                suffixIndex++;
                value /= 1024.0f;
            }
            else
                break;
        }
        return { sign * value,memSuffixes[suffixIndex] };
    }
    case Profiler::Time:
    {
        static const char* timeSuffixes[4] = { "ns","µs","ms","s" };
        int suffixIndex = 2;
        for (int i = 0; i < 2; i++)
        {
            if (value <= 100.0f / 1000.0f)
            {
                suffixIndex--;
                value *= 1000.0f;
            }
        }
        if (value >= 1000.0)
        {
            suffixIndex++;
            value /= 1000.0f;
        }
        return { sign * value,timeSuffixes[suffixIndex] };
    }
    default:
        return { 0,"" };
    }
}

void DrawFunction(Profiler::Function& function)
{
    PROFILE_NAMED_FUNCTION("Draw Function");

    ImGui::PushID(GetOffset(function));

    auto& refFunction = settings[GetOffset(function)].referances;
    Profiler::Samples& samples = function.GetSamples();
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(function.GetName());
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 15.0f);
    ImGui::SliderInt("Height", &settings[GetOffset(function)].height, 110, 1000);
    ImGui::SliderInt("Limit", &settings[GetOffset(function)].limit, 1, Profiler::maxSampleCount);
    ImGui::SliderFloat("Line", &settings[GetOffset(function)].width, 0.2, 7, "%.1f");
    ImGui::PopStyleVar();
    if (ImGui::Button("Save"))
    {
        char fileName[MAX_PATH];
        strcat(fileName, "[");
        strncpy(fileName + 1, function.GetName(), Profiler::maxFunctionNameLength);
        strcat(fileName, "]");
        if (SaveFileDialog(fileName))
            SaveFunction(function, fileName);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        std::string path;
        path.resize(MAX_PATH);
        strcat(path.data(), "[");
        strncpy(path.data() + 1, function.GetName(), Profiler::maxFunctionNameLength);
        strcat(path.data(), "]");

        if (OpenFileDialog(path.data()))
        {
            auto last = path.find('\000', 0);
            path = path.substr(0, last);
            settings[GetOffset(function)].referancePaths.push_back(std::string(path));
            refFunction.push_back(LoadFunction(path.data()));
        }
        std::sort(refFunction.begin(), refFunction.end());
    }
    ImGui::SameLine();
    if (ImGui::Button("Pop"))
    {
        if (refFunction.size() != 0)
        {
            refFunction.pop_back();
            settings[GetOffset(function)].referancePaths.pop_back();
        }
    }
    function.GetSamples().SetSampleLimit(settings[GetOffset(function)].limit);
    ImGui::TableNextColumn();

    switch (function.GetType())
    {
    case Profiler::Memory:ImGui::Text("Allocations: %d", function.GetInvocations()); break;
    case Profiler::Time:ImGui::Text("Invocations: %d", function.GetInvocations()); break;
    default:break;
    }

    auto t = TransfomWithSuffix(samples.GetCurrent(), function.GetType());
    ImGui::Text("Current: %.3g%s", std::get<0>(t), std::get<1>(t));
    t = TransfomWithSuffix(samples.GetMax(), function.GetType());
    ImGui::Text("Max: %.3g%s", std::get<0>(t), std::get<1>(t));
    t = TransfomWithSuffix(samples.GetMin(), function.GetType());
    ImGui::Text("Min: %.3g%s", std::get<0>(t), std::get<1>(t));
    t = TransfomWithSuffix(samples.GetAverage(), function.GetType());
    ImGui::Text("Avg: %.3g%s", std::get<0>(t), std::get<1>(t));
    if (refFunction.size() != 0)
    {
        float diff = samples.GetAverage() - refFunction[0].GetSamples().GetAverage();
        if (diff > 0)
        {
            ImGui::PushStyleColor(0, { 255,0,0,255 });
            t = TransfomWithSuffix(diff, function.GetType());
            ImGui::Text("Avg: +%.3g%s", std::get<0>(t), std::get<1>(t));
        }
        else
        {
            ImGui::PushStyleColor(0, { 0,255,0,255 });
            t = TransfomWithSuffix(diff, function.GetType());
            ImGui::Text("Avg: %.3g%s", std::get<0>(t), std::get<1>(t));
        }

        ImGui::PopStyleColor();
    }
    ImGui::TableNextColumn();
    ImGui::Text("Samples: %d", samples.GetTotalSampleCount());
    t = TransfomWithSuffix(samples.GetTotalMax(), function.GetType());
    ImGui::Text("Max: %.3g%s", std::get<0>(t), std::get<1>(t));
    t = TransfomWithSuffix(samples.GetTotalMin(), function.GetType());
    ImGui::Text("Min: %.3g%s", std::get<0>(t), std::get<1>(t));
    t = TransfomWithSuffix(samples.GetTotalAverage(), function.GetType());
    ImGui::Text("Avg: %.3g%s", std::get<0>(t), std::get<1>(t));
    if (refFunction.size() != 0)
    {
        float diff = samples.GetTotalAverage() - refFunction[0].GetSamples().GetTotalAverage();
        if (diff > 0)
        {
            ImGui::PushStyleColor(0, { 255,0,0,255 });
            t = TransfomWithSuffix(diff, function.GetType());
            ImGui::Text("Avg: +%.3g%s", std::get<0>(t), std::get<1>(t));
        }
        else
        {
            ImGui::PushStyleColor(0, { 0,255,0,255 });
            t = TransfomWithSuffix(diff, function.GetType());
            ImGui::Text("Avg: %.3g%s", std::get<0>(t), std::get<1>(t));
        }

        ImGui::PopStyleColor();
    }
    ImGui::TableNextColumn();

    ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, settings[GetOffset(function)].width);

    if (ImPlot::BeginPlot("##LinePlots", { -1,(float) settings[GetOffset(function)].height }, ImPlotFlags_NoTitle | ImPlotFlags_NoFrame | ImPlotFlags_Crosshairs | (refFunction.size() == 0 ? ImPlotFlags_NoLegend : 0)))
    {
        int tickCount = settings[GetOffset(function)].height / 150 + 1;
        ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_PanStretch, (tickCount > 1 ? 0 : ImPlotAxisFlags_NoTickLabels) | ImPlotAxisFlags_NoGridLines);
        double max = samples.GetMax();
        double min = samples.GetMin();
        for (auto&& func : refFunction)
        {
            double refMax = func.GetSamples().GetMax();
            double refMin = func.GetSamples().GetMin();
            if (refMax > max) max = refMax;
            if (refMin < min) min = refMin;
        }

        ImPlot::SetupAxisLimits(ImAxis_Y1, min - (max - min) * 0.03, max + (max - min) * 0.03, ImPlotCond_Always);

        if (tickCount > 1)
        {
            if (tickCount == 1) tickCount = 2;
            std::vector<double> tickPositions(tickCount);
            std::vector<char*> tickLabels(tickCount);
            for (int i = 0; i < tickCount; ++i)
            {
                double tickPosition = min + (i * (max - min) / (tickCount - 1));
                tickPositions[i] = tickPosition;

                tickLabels[i] = new char[16];
                t = TransfomWithSuffix(tickPosition, function.GetType());
                snprintf(tickLabels[i], 16, "%.3g%s", std::get<0>(t), std::get<1>(t));
            }
            ImPlot::SetupAxisTicks(ImAxis_Y1, tickPositions.data(), tickCount, tickLabels.data());

            for (auto&& label : tickLabels)delete[] label;
        }
        ImPlot::PlotLine("Current", samples.Data().data(), samples.Data().size(), 1.0, 0.0, 0, samples.GetOffset());
        for (auto&& func : refFunction)
        {
            auto referance = func.GetSamples();
            int size = samples.Data().size();
            if (referance.Data().size() < size) size = referance.Data().size();
            ImPlot::PlotLine(func.GetName(), referance.Data().data(), size, 1.0, 0.0, 0, referance.GetOffset());
        }
        ImPlot::EndPlot();
    }
    ImPlot::PopStyleVar();
    ImGui::PopID();
}

int main()
{
    Renderer::Init();
    for (int i = 0; i < Profiler::maxFunctions; i++)
    {
        settings[i].width = 2.4;
        settings[i].height = 110;
        settings[i].limit = Profiler::maxSampleCount;
    }
    ReadSettings();

    while (!glfwWindowShouldClose(Renderer::window))
    {
        Profiler::BeginFrame();
        {
            PROFILE_NAMED_FUNCTION("Profiler Draw");
            Renderer::StartFrame();

            ImGui::Begin("Profiler", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            ImGui::SetWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Always);
            ImGui::GetStyle().WindowRounding = 0.0f;
            ImGui::SetWindowPos({ 0,0 });
            ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable;
            if (ImGui::BeginTable("Profiler", 4, tableFlags))
            {
                ImGui::TableSetupColumn("Function Name", ImGuiTableColumnFlags_WidthFixed, 150.0f);
                ImGui::TableSetupColumn("Stats", ImGuiTableColumnFlags_WidthFixed, 125.0f);
                ImGui::TableSetupColumn("Total Stats", ImGuiTableColumnFlags_WidthFixed, 125.0f);
                ImGui::TableSetupColumn("Samples");
                ImGui::TableHeadersRow();
                ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(0, 0));

                for (auto& i : Profiler::GetFunctions())
                    DrawFunction(i);

                ImPlot::PopStyleVar();
                ImGui::EndTable();
            }
            ImGui::End();
            Renderer::EndFrame();
        }
        Profiler::EndFrame();
    }
    Renderer::Quit();
    WriteSettings();
}