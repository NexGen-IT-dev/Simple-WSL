#include <iostream>
#include <Windows.h>
#include <fstream>


void RunCMDCommand(const std::string& command) {

    std::wstring wideCommand = std::wstring(command.begin(), command.end());

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };


    std::wstring fullCommand = L"cmd.exe /c " + wideCommand;


    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

    if (CreateProcess(
        NULL,                
        &fullCommand[0],     
        NULL,                
        NULL,                  
        TRUE,                 
        0,                    
        NULL,                
        NULL,                
        &si,                   
        &pi                 
    ) == 0) {
        std::cerr << "CreateProcess failed. Error: " << GetLastError() << std::endl;
        return;
    }


    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void installWSL() {
    RunCMDCommand("wsl -install");
}

void listDistros() {
    RunCMDCommand("wsl --list");
}

void listVerbose() {
    RunCMDCommand("wsl --list --verbose");
}

void setDefaultDistro(const std::string& distro) {
    if (distro.empty()) {
        std::cerr << "Missing argument: -default <distro>\n";
        return;
    }
    std::string cmd = "wsl --set-default " + distro;
    RunCMDCommand(cmd);
}

void setWSLVersion(const std::string& version) {
    if (version.empty()) {
        std::cerr << "Missing argument: -set_version <version>\n";
        return;
    }
    std::string cmd = "wsl --set-default-version " + version;
    RunCMDCommand(cmd);
}

void KillWSLDistro(const std::string& distro_name) {
    if (distro_name.empty()) {
        std::cerr << "Missing argument: -kill_distro <distro>\n";
        return;
    }
    std::string cmd = "wsl --terminate " + distro_name;
    RunCMDCommand(cmd);

}

void showHelp() {
    std::cout << "Commands               | Description                          " << std::endl;
    std::cout << "-----------------------|--------------------------------------" << std::endl;
    std::cout << "-install               | Installs WSL                         " << std::endl;
    std::cout << "-list                  | Shows installed distros              " << std::endl;
    std::cout << "-list_distro_info      | Displays information about installed distros " << std::endl;
    std::cout << "-default               | Sets the default distro              " << std::endl;
    std::cout << "--set_version          | Sets the default WSL version         " << std::endl;
    std::cout << "-help                  | Displays available commands          " << std::endl;
    std::cout << "-kill_distro           | Terminates a running distro          " << std::endl;

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        showHelp();
        return 1;
    }

    // initialize important variables (trust me bro)
    /*
    Dev Notes:
    If you're reading this and didn't know argv[0] is the program name...
    go touch some C++ tutorials. But hey, you're here now you're learning hopefully.
    */

    std::ofstream log("log.txt", std::ios::app);

    if (!log) {
        std::ofstream log("log.txt");
    }

    std::string arg = argv[1]; 
    std::string third_arg = argc > 2 ? argv[2] : "";

    log << "\n" << arg << " " << third_arg;

    log.close();

    if (arg == "-install") {
        installWSL();
    }
    else if (arg == "-list") {
        listDistros();
    }
    else if (arg == "-list_distro_info") {
        listVerbose();
    }
    else if (arg == "-default") {
        setDefaultDistro(third_arg);
    }
    else if (arg == "-set_version") {
        setWSLVersion(third_arg);
    }
    else if (arg == "-help" || arg == "-h") {
        showHelp();
    }
    else if (arg == "-kill_distro") {
        KillWSLDistro(third_arg);
    }
    else {
        std::cerr << "Unknown command: " << arg << "\n";
        showHelp();
    }

    return 0; //returns 0
}
