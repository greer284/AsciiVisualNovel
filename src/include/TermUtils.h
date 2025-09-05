#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

class TermUtils {
private:
public:
    TermUtils() {};
    ~TermUtils() {};

    int kbhit(void);
    void initTermios(int echo);
    void resetTermios(void);
};