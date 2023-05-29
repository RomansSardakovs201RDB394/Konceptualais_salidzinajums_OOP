#include "Vehicle.h"
#include "Car.h"
#include <Psapi.h>
#include <thread>

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

int main()
{
	std::thread CpuMonitorThread(CPUMONITOR);
	std::thread ramMonitorThread(RAMMONITOR);

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::string> audiElectroSystems = { "ABS","ESP" };
	std::map<short, short> audiEngine;
	audiEngine.insert(std::map<short, short>::value_type(1, 220));

	car* audi = new car("audi a6", audiEngine, "Black", 4, 13.2, 1248, 2000, 260);

	audi->setElectoSystem(audiElectroSystems);
	audi->setBody("sedan");

	audi->CheckElectroSystems();

	audi->startEngine();
	audi->accelerate(1, 10);
	audi->registrateVehicle();

	std::cout << std::endl;

	vehicle* myVehicle = new vehicle();

	myVehicle->setName("My Car");
	myVehicle->setWheels(4);
	myVehicle->setEngine(1, 80);
	myVehicle->setMaxSpeed(80);
	myVehicle->setMass(420);
	myVehicle->setBattery(8.2);
	myVehicle->setColor("green");


	myVehicle->startEngine();
	myVehicle->accelerate(1, 10);
	myVehicle->registrateVehicle();

	std::cout << "----------RESULTS----------" << std::endl;
	CalculateAverageRAM();
	CalculateAverageCPU();
	std::cout << "All Time ALLOCATED: " << allocatedBytes << " bytes" << std::endl;
	std::cout << "PEAK RAM USAGE: " << MaxRAM << " bytes" << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> endClock = end - start;
	std::cout << "Execution time: " << endClock.count() << " seconds";
	std::cout << std::endl;

	delete audi;
	delete myVehicle;
	CloseHandle(process);
	exit(-1);
	return 0;

}
