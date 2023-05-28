#include<iostream>
#include <random>
#include "SelectionSort.h";
#include "BubbleSort.h";
#include "CountingSort.h";
#include <thread>

size_t allocatedBytesALL = 0;

size_t allocatedBytes = 0;
void* operator new(size_t size) {
    allocatedBytes = allocatedBytes + size;
    return malloc(size);
}

size_t AverageRAM = 0;
size_t MaxRAM = 0;
int RAMcounter = 0;
HANDLE process = GetCurrentProcess();
void RAMMONITOR() {
    while (true) {
        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(process, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T physMemUsedByMe = pmc.PrivateUsage;
        MaxRAM = pmc.PeakWorkingSetSize;
        AverageRAM = AverageRAM + physMemUsedByMe;
        RAMcounter++;
    }
}

int CPUcounter = 0;
double AverageCPU = 0.0;
void CPUMONITOR() {
    FILETIME idleTime, kernelTime, userTime;
    ULARGE_INTEGER lastIdleTime{}, lastKernelTime{}, lastUserTime{};
    double cpuUsage = 0.0;

    while (true) {
        GetSystemTimes(&idleTime, &kernelTime, &userTime);
        ULARGE_INTEGER currentIdleTime = { idleTime.dwLowDateTime, idleTime.dwHighDateTime };
        ULARGE_INTEGER currentKernelTime = { kernelTime.dwLowDateTime, kernelTime.dwHighDateTime };
        ULARGE_INTEGER currentUserTime = { userTime.dwLowDateTime, userTime.dwHighDateTime };

        if (lastIdleTime.QuadPart != 0) {
            ULONGLONG idleDiff = currentIdleTime.QuadPart - lastIdleTime.QuadPart;
            ULONGLONG kernelDiff = currentKernelTime.QuadPart - lastKernelTime.QuadPart;
            ULONGLONG userDiff = currentUserTime.QuadPart - lastUserTime.QuadPart;

            ULONGLONG totalDiff = kernelDiff + userDiff;
            cpuUsage = (1.0 - (double)idleDiff / (double)totalDiff) * 100.0;
        }

        lastIdleTime = currentIdleTime;
        lastKernelTime = currentKernelTime;
        lastUserTime = currentUserTime;

        AverageCPU = AverageCPU + cpuUsage;
        CPUcounter++;
        Sleep(1000);
    }
}

void CalculateAverageCPU() {
    std::cout << "Average CPU usage: " << (AverageCPU / CPUcounter) << '%' << std::endl;
}

void CalculateAverageRAM() {
    std::cout << "Average RAM usage: " << (AverageRAM / RAMcounter) << " bytes" << std::endl;
}


const int ARRAY_SIZE = 100000;
int RandomArray[ARRAY_SIZE];

const int FirstSize = 1000;
const int SecondSize = 10000;
const int ThirdSize = 100000;

void FillRandomArray() {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1, 100);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        int random_integer = uni(rng);
        RandomArray[i] = random_integer;
    }

}

int main() {
    std::thread CpuMonitorThread(CPUMONITOR);
    std::thread ramMonitorThread(RAMMONITOR);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= 10; i++) {
        FillRandomArray();

        std::cout << "----------SelectiveSort----------" << std::endl;
        allocatedBytesALL = allocatedBytesALL + allocatedBytes;
        allocatedBytes = 0;
        SelectionSort* selection = new SelectionSort();
        selection->FillFirstArray(RandomArray);
        selection->FillSecondArray(RandomArray);
        selection->FillThirdArray(RandomArray);
        selection->selectionSort(selection->FirstSelectionSort, selection->SecondSelectionSort, selection->ThirdSelectionSort);
        std::cout << "SelectionSort ALLOCATED BYTES: " << allocatedBytes << std::endl;

        std::cout << "----------BubbleSort----------" << std::endl;
        allocatedBytesALL = allocatedBytesALL + allocatedBytes;
        allocatedBytes = 0;
        BubbleSort* bubblesort = new BubbleSort();
        bubblesort->FillFirstArray(RandomArray);
        bubblesort->FillSecondArray(RandomArray);
        bubblesort->FillThirdArray(RandomArray);
        bubblesort->bubbleSort(bubblesort->FirstBubbleSort, bubblesort->SecondBubbleSort, bubblesort->ThirdBubbleSort);
        std::cout << "BubbleSort ALLOCATED BYTES: " << allocatedBytes << std::endl;

        std::cout << "----------CountingSort----------" << std::endl;
        allocatedBytesALL = allocatedBytesALL + allocatedBytes;
        allocatedBytes = 0;
        CountingSort* countingsort = new CountingSort();
        countingsort->FillFirstArray(RandomArray);
        countingsort->FillSecondArray(RandomArray);
        countingsort->FillThirdArray(RandomArray);
        countingsort->countingSort(countingsort->FirstCountingSort, countingsort->SecondCountingSort, countingsort->ThirdCountingSort);
        std::cout << "CountingSort ALLOCATED BYTES: " << allocatedBytes << std::endl;


    }
    allocatedBytesALL = allocatedBytesALL + allocatedBytes;

    std::cout << "----------RESULTS----------" << std::endl;
    CalculateAverageRAM();
    CalculateAverageCPU();
    std::cout << "All Time ALLOCATED: " << allocatedBytesALL << " bytes" << std::endl;
    std::cout << "PEAK RAM USAGE: " << MaxRAM << " bytes" << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> endClock = end - start;
    std::cout << "Execution time: " << endClock.count() << " seconds";
    std::cout << std::endl;

    CloseHandle(process);
    exit(-1);
    return 0;
}