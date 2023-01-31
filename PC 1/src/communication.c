#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */
uint8_t criptare_cod( char cod )
{
    uint8_t res = -1;

    res = ((uint8_t)cod) - 64;

    return res;
}

char decriptare_cod( uint8_t cod)
{
    char res;

    res = (char)(cod + 64);

    return res;
}

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */
    char mesaj[4] = {'R', 'I', 'C', 'K'};
    for(int i = 0; i < 4; i++)
    {
        uint8_t cod = criptare_cod( mesaj[i] );
        send_squanch(cod);
    }
    
}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    for(int i = 0; i < 5; i++)
    {
        uint8_t cod = recv_squanch();

        char decodat = decriptare_cod( cod );

        fprintf( stdout, "%c", decodat);
    }
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    for(int i = 0; i < 10; i++)
    {
        uint8_t cod = recv_squanch();

        send_squanch(cod);
        send_squanch(cod);
    }
}


/* Task 2 - Waiting for the Message */

// functie pentru verificarea valorii unui bit
uint8_t get_bit(uint8_t nr, uint8_t i)
{
    uint8_t res = -1;
    uint8_t mask = (1 << i);

    res = ((nr & mask) != 0);

    return res;
}

// functie pentru activarea unui bit
uint8_t activate_bit(uint8_t nr, uint8_t i)
{
    uint8_t res = 0xFF;
    uint8_t mask = (1 << i);
    res = (nr | mask);

    return res;
}

//functie pentru dezactivarea unui bit
uint8_t clear_bit(uint8_t nr, uint8_t i)
{
    uint8_t res = -1;
    uint8_t mask = ~(1 << i);
    res = (nr & mask);

    return res;
}

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */

    uint8_t length = 0;
    
    for(int i = 0; i < 4; i++)
    {
        if( get_bit(10, i) )
        {
            length = activate_bit(length, i + 2);
        }
        else
        {
            length = clear_bit( length, i + 2);
        }
    }

    send_squanch( length );
    send_squanch( criptare_cod('H') );
    send_squanch( criptare_cod('E') );
    send_squanch( criptare_cod('L') );
    send_squanch( criptare_cod('L') );
    send_squanch( criptare_cod('O') );
    send_squanch( criptare_cod('T') );
    send_squanch( criptare_cod('H') );
    send_squanch( criptare_cod('E') );
    send_squanch( criptare_cod('R') );
    send_squanch( criptare_cod('E') );
    
    
}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */

    return res;
}
