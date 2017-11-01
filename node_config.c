#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include "libnrf/libnrf.h"
#include "node.h"

typedef enum {
    getConfigMode,
    setConfigMode
};

void nrf_setup() {
    char status;
    char ConfigAddr[] = {'A', 'D', 'D', 'R', '0'};
    nrf_init();
    nrf_clear_rx_dr(&status);
    nrf_clear_max_rt(&status);
    nrf_clear_tx_ds(&status);    
    nrf_flush_tx(&status);
    nrf_flush_rx(&status);
    nrf_set_rx_address(P0, ConfigAddr, &status);
    nrf_set_tx_address(ConfigAddr, &status);
	nrf_set_power_mode(POWER_ON, &status);
    nrf_set_data_rate(DR1MBPS, &status);
    printf("NRF initialisation done\n");
}

void getConfig() {
    // Send the getconfig request
        
    // Waiting for getconfig answer

    // Display the node remote configuration
}

void setConfig(char * nodeAddr, char * gwAddr, int rfPower, int rfChannel) {        
    // Format config frame
    
    // Send config frame
    
    // (optional) Control good config reception with a getconfig
}

int main(int argc, char *argv[]) {	
    char status;
    int  Mode;

    if ((argc == 2) && strcmp(argv[1],"gc")) {
        // Get config mode
        Mode = getConfigMode;
    } else if ((argc == 6) && strcmp(argv[1],"sc")) {
        // Set config mode
        Mode = setConfigMode;
    } else {
        printf("Usage : %s gc | %s sc node_address gateway_address rf_power rf_channel\n", argv[0], argv[0]);
		exit(-1);
    }
    
	nrf_setup();
    
    if (Mode == getConfigMode) {
        getConfig();
    } else if (Mode == setConfigMode) {
        char nodeAddr[5];
        char gwAddr[5];
        int rfPower;
        int rfChannel;
        
        // Extract parameters info
        setConfig(nodeAddr, gwAddr, rfPower, rfChannel);
    }

    sleep(1);
    nrf_set_power_mode(POWER_OFF, &status);

    return 0;
}
