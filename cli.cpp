#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

typedef std:: string String;
using namespace std;

struct ProcessInfo{
    int gpu;
    String gid;
    String cid;
    int pid;
    String type;
    String name;
    String memory;
};

std::vector<ProcessInfo> processes;
COORD coord;
String commandInput;

void currentTime(){
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char datetime[100];
    strftime(datetime, sizeof(datetime), "%a %b %d %H:%M:%S %Y", localtm);
    std::cout << datetime;
}

void printGPUInfo(){
    currentTime();
    printf("\n");
    printf("+-----------------------------------------------------------------------------------------+\n");
    printf("| NVIDIA-SMI 556.12                 Driver Version: 556.12         CUDA Version: 12.5     |\n");
    printf("|-----------------------------------------+------------------------+----------------------+\n");
    printf("| GPU  Name                  Driver-Model | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n");
    printf("| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n");
    printf("|                                         |                        |               MIG M. |\n");
    printf("|=========================================+========================+======================|\n");
    printf("|   0  NVIDIA GeForce GTX 1070 Ti   WDDM  |   00000000:01:00.0  On |                  N/A |\n");
    printf("| 20%%   56C    P0             42W /  180W |    1717MiB /   8192MiB |      0%%      Default |\n");
    printf("|                                         |                        |                  N/A |\n");
    printf("+-----------------------------------------+------------------------+----------------------+\n");
}

void processList(){
    int maxPid = 0;
    for (const auto& process: processes){
        int pidLength = std::to_string(process.pid).size();
        maxPid = std::max(maxPid, pidLength);
    }

    printGPUInfo();
    printf("\n");
    printf("+-----------------------------------------------------------------------------------------+\n");
    printf("| Processes:                                                                              |\n");
    printf("|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |\n");
    printf("|        ID   ID                                                               Usage      |\n");
    printf("|=========================================================================================|\n");
    
    for (const auto& process : processes) {
        String processName = process.name;

        if (processName.length() > 30) {
            processName = "..." + processName.substr(processName.length() - 27);
        }

        std::cout << "| " 
                  << std::setw(4) << process.gpu
                  << std::setw(6) << process.gid
                  << std::setw(5) << process.cid
                  << std::setw(8 + maxPid - 3) << process.pid
                  << std::setw(7) << process.type
                  << std::setw(3) << " "
                  << std::left << std::setw(33) << processName
                  << std::right << std::setw(17) << process.memory
                  << "   |" << std::endl;
    }

    printf("+-----------------------------------------------------------------------------------------+\n");
}

int main(){
    coord.Y = 7;
    processes.push_back({0, "N/A", "N/A", 832, "C+G", "Programs\\Microsoft VS Code\\Code.exe", "N/A"});
    processes.push_back({0, "N/A", "N/A", 2324, "C+G", "Program Files\\Mozilla Firefox\\firefox.exe", "N/A"});
    processes.push_back({0, "N/A", "N/A", 5920, "C+G", "AppData\\Roaming\\Spotify\\Spotify.exe", "N/A"});
    processes.push_back({0, "N/A", "N/A", 11128, "C+G", "games\\overwolf\\Overwolf.exe", "N/A"});
    processes.push_back({0, "N/A", "N/A", 11596, "C+G", "Windows\\explorer.exe", "N/A"});
    processes.push_back({0, "N/A", "N/A", 17732, "C+G", "Microsoft\\Edge\\Application\\msedge.exe", "N/A"});

    std::cout << "Enter a command: ";
    std::cin >> commandInput;

    while (commandInput != "nvidia-smi"){
        std::cout << "'" << commandInput << "' is not a recognized command. Enter a command: ";
        std::cin >> commandInput;
    }

    system("CLS");
    processList();

    return 0;
}