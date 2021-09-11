// Add handler functions here

void SIGINT_handler(){
    printf("Received signal SIGINT!!!");
}
void SIGQUIT_handler(){
    printf("Received signal SIGQUIT!!!");
}
void SIGTERM_handler(){
    printf("Received signal SIGTERM!!!");
}
void SIGFPE_handler(){
    printf("Received signal SIGFPE!!!");
}
void SIGSEGV_handler(){
    printf("Received signal SIGSEGV!!!");
}
void SIGILL_handler(){
    printf("Received signal SIGILL!!!");
}
void setup_signal_handlers() {
    // Setup handlers here
    
    signal(SIGINT, SIGINT_handler);
    signal(SIGQUIT, SIGQUIT_handler);
    signal(SIGTERM, SIGTERM_handler);
    signal(SIGFPE, SIGFPE_handler);
    signal(SIGSEGV, SIGSEGV_handler);
    signal(SIGILL, SIGILL_handler);
    
}