#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */

    uint64_t mask = (1LU << i);

    res = ((nr & mask) != 0);

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    if( get_bit(nr, i))
    {
        uint64_t mask = ~(1LU << i);
        res = (nr & mask);
    }
    else
    {
        uint64_t mask = (1LU << i);
        res = (nr | mask);
    }
    

    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    uint64_t mask = (1LU << i);
    res = (nr | mask);

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    uint64_t mask = ~(1LU << i);
    res = (nr & mask);

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */
    uint8_t intermediar = nand_gate(a, b);
    res = nand_gate( intermediar, intermediar);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    res = nand_gate( nand_gate(a, a), nand_gate(b,b));

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    uint8_t intermediar = nand_gate(a, b);

    res = nand_gate( nand_gate(a, intermediar), nand_gate(b, intermediar));

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */ 
    uint8_t termen1suma = and_gate(not_gate(a), xor_gate(b, c));
    uint8_t termen2suma = and_gate(a, xor_gate(b, not_gate(c)));

    uint8_t suma = or_gate( termen1suma, termen2suma);

    uint8_t termen1carry = or_gate( and_gate( a, b ),and_gate( b, c));
    uint8_t carry = or_gate( termen1carry, and_gate(a, c));

    res = 0; // setez primii doi biti in functie de rezultat

    if( suma )
    {
        res = activate_bit(res, 1);
    }

    if( carry )
    {
        res = activate_bit(res, 0);
    }

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    uint8_t carry = 0;

    for(int i = 0; i < 64; i++)
    {
        uint8_t bit1 = get_bit(a,i);
        uint8_t bit2 = get_bit(b,i);
        uint8_t fullAdderOutput = full_adder(bit1, bit2, carry);

        if( get_bit(fullAdderOutput, 0))
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        if( get_bit(fullAdderOutput, 1))
        {
            res = activate_bit(res, i);
        }
        else
        {
            res = clear_bit(res, i);
        }

    }
    
    if( carry )
    {
        res = 0;
    }
        
    return res;
}
