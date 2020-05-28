#include <avr/io.h>

#define BAUD 9600 
// #define MYUBRR    F_CPU/8/BAUD-1

#define init_uart(baudRate) _init_uart(F_CPU/8/baudRate-1)

void _init_uart(unsigned short uValue  ){
    // setting the baud rate  based on the datasheet 
    UBRR0H =(unsigned char)  ( uValue>> 8);  // 0x00 
    UBRR0L =(unsigned char) uValue;  // 0x0C with 1Mhz
    // enabling TX & RX 
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0A = (1<<UDRE0)|(1<<U2X0);
    UCSR0C =  (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stop

}

unsigned char SerialAvailable()
{
    return (UCSR0A & (1<<RXC0));
}

unsigned char SerialRead( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
    ;
    /* Get and return received data from buffer */
    return UDR0;
}
void SerialPrint( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) )
    ;
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void SerialPrintStr(const char * data )
{
    /* Wait for empty transmit buffer */
    for (int i =0;data[i];i++)
        SerialPrint(data[i]);
}

void SerialPrintln(const char * data )
{
    SerialPrintStr(data);
    SerialPrint('\r');
    SerialPrint('\n');
}