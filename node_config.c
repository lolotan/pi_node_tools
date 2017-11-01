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
    char ConfigAddr[] = {'A', 'D', 'D', 'R', '0'}; // Address for tx/rx
    nrf_init();
    nrf_clear_rx_dr(&status);
    nrf_clear_max_rt(&status);
    nrf_clear_tx_ds(&status);    
    nrf_flush_tx(&status);
    nrf_flush_rx(&status);
    nrf_set_rx_address(P0, ConfigAddr, &status);
    nrf_enable_dynamic_payload(P0, &status);
    nrf_set_tx_address(ConfigAddr, &status);
	nrf_set_power_mode(POWER_ON, &status);
    nrf_set_data_rate(DR1MBPS, &status);
    nrf_set_auto_retransmit_count(5, &status);
	nrf_set_auto_retransmit_delay(15, &status);
    printf("NRF initialisation done\n");
}

void getConfig() {
    char status;
    const char * getconfstr = "config_request";
    nrf_set_mode_ptx(&status);
    
    // Send the getconfig request    
    nrf_write_tx_payload(getconfstr, strlen(getconfstr), &status);
    nrf_tx_payload();
    sleep(1);
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

    if ((argc == 2) && (strcmp(argv[1],"gc") == 0)) {
        // Get config mode
        Mode = getConfigMode;
    } else if ((argc == 6) && (strcmp(argv[1],"sc") == 0)) {
        // Set config mode
        Mode = setConfigMode;
    } else {
        printf("Usage : %s gc | %s sc node_address gateway_address rf_power rf_channel\n", argv[0], argv[0]);
		exit(-1);
    }
    
	nrf_setup();
    
    if (Mode == getConfigMode) {
        printf("Get configuration requested\n");
        getConfig();
    } else if (Mode == setConfigMode) {
        char nodeAddr[5];
        char gwAddr[5];
        int rfPower;
        int rfChannel;
        printf("Set configuration requested\n");
        // Extract parameters info
        setConfig(nodeAddr, gwAddr, rfPower, rfChannel);
    }

    sleep(1);
    nrf_set_power_mode(POWER_OFF, &status);

    return 0;
}
