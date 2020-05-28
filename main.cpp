// this is a program to generate pseudo random values
// based on the video by Veritasium
// https://www.youtube.com/watch?v=ovJcsL7vyrk


#define F_CPU 8000000

#include <stdio.h>
#include "uart.h"

#define PERIOD_MS 1000
#define INITIAL_POPULATION 0.5f
#define N_OUTPUTS 8

void CalculateMaxPopulation(double r, double *outputs, uint8_t nOutput)
{
    double population = INITIAL_POPULATION;
    for (int i = 0; i < 20 + nOutput; i++)
    {
        population = r * population * (1 - population);
        if (i >= 20)
            outputs[i - 20] = population;
    }
}

int main()
{
    char buffer[10];

    init_uart(9600);

    double outputs[N_OUTPUTS];

    while (1)
    {
        // for factors from 3.65 to 4.0
        for (uint16_t i = 36500; i < 40000; i++)
        {
            // calculate the N max population after 20th itteration
            CalculateMaxPopulation(i / 10000.0, outputs, N_OUTPUTS);
            if (outputs[0] == 0) // if deadend stop
            {
                SerialPrintln("End");
                sprintf(buffer, "%d", i);
                break;
            }
            for (int i = 0; i < N_OUTPUTS; i++) // display the calculated values
            {
                sprintf(buffer, "%u", (uint16_t)(outputs[i] * 10000.0));
                SerialPrintln(buffer);
            }
        }
        while (1)
        {
            // End
        }
    }
}
