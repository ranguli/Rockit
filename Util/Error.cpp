void fatal_error() {
    // Turn on the status LED and halt the rest of program execution and enter an idle loop. 
    // TODO: We should investigate setting the RP2040 to a low power mode in this case. 
    turnOnStatusLED();
    while(1);
}