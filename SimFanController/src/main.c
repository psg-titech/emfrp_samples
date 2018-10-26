#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "SimFanController.h"

#define SBUFLEN 100

double t = 30.0, h = 60.0;
double dt = 0.5, dh = 1.0;

void Input(double* tmp, double* hmd) {
    if (t > 35.0 || t < 20.0) dt = -dt;
    if (h > 80.0 || h < 50.0) dh = -dh;
    t += dt;
    h += dh;
    *tmp = t;
    *hmd = h;
}

void Output(double *di, int* fan) {
    static char sbuf[SBUFLEN];
    snprintf(sbuf, SBUFLEN,
            "tmp=%2.2f, hmd=%2.2f, di=%2.2f, fan: %-3s",
            t, h, *di, *fan ? "ON" : "OFF");
    printf("%s", sbuf);
    fflush(stdout);
    int n = strlen(sbuf);
    for (int i = 0; i < n; i++)
        putchar(010);
    usleep(200000);
}

int main() {
    ActivateSimFanController();
}
