#include <iostream>
#include <windows.h>
#include <vector>

void find_drives() {
    std::vector<char> drives(GetLogicalDriveStrings(0, NULL));
    if (drives.empty()) {
        std::cerr << "Failed to get drive letters." << std::endl;
        return;
    }

    GetLogicalDriveStrings(drives.size(), drives.data());

    for (const auto& drive : drives) {
        if (drive == '\0') break;
        std::cout << "Found drive: " << drive << std::endl;
    }
}

int main() {
    find_drives();
    return 0;
}