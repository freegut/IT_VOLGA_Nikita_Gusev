#include <iostream>
#include <windows.h>
#include <lm.h>

void find_network_shares() {
    PSHARE_INFO_502 bufPtr, tmpBufPtr;
    NET_API_STATUS status;
    DWORD entriesRead = 0;
    DWORD totalEntries = 0;
    DWORD resumeHandle = 0;

    do {
        status = NetShareEnum(NULL, 502, (LPBYTE*)&bufPtr, MAX_PREFERRED_LENGTH, &entriesRead, &totalEntries, &resumeHandle);

        if ((status == NERR_Success) || (status == ERROR_MORE_DATA)) {
            tmpBufPtr = bufPtr;

            for (DWORD i = 0; i < entriesRead; i++) {
                std::cout << "Share name: " << tmpBufPtr->shi502_netname << std::endl;
                tmpBufPtr++;
            }
        } else {
            std::cerr << "Failed to enumerate shares. Error code: " << status << std::endl;
        }

        if (bufPtr != NULL) {
            NetApiBufferFree(bufPtr);
            bufPtr = NULL;
        }
    } while (status == ERROR_MORE_DATA);
}

int main() {
    find_network_shares();
    return 0;
}