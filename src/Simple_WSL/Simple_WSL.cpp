#include <iostream>
#include <Windows.h>

void installWSL() {
    system("wsl --install");
}

void listDistros() {
    system("wsl --list");
}

void listVerbose() {
    system("wsl --list --verbose");
}

void setDefaultDistro(const std::string& distro) {
    if (distro.empty()) {
        std::cerr << "Missing argument: -default <distro>\n";
        return;
    }
    std::string cmd = "wsl --set-default " + distro;
    system(cmd.c_str());
}

void setWSLVersion(const std::string& version) {
    if (version.empty()) {
        std::cerr << "Missing argument: -set_version <version>\n";
        return;
    }
    std::string cmd = "wsl --set-default-version " + version;
    system(cmd.c_str());
}

void KillWSLDistro(const std::string& distro_name) {
    if (distro_name.empty()) {
        std::cerr << "Missing argument: -kill_distro <distro>\n";
        return;
    }
    std::string cmd = "wsl --terminate " + distro_name;
    system(cmd.c_str());

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

    std::string arg = argv[1]; 
    std::string third_arg = argc > 2 ? argv[2] : "";

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
    else if (arg == "-help") {
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
