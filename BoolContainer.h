#ifndef BOOL_CONTAINER
#define BOOL_CONTAINER

class BoolContainer
{
private:
    uint8_t container;
public:
    BoolContainer();
    ~BoolContainer();

    bool read(uint8_t idx); // Leet bit <idx>
    void write(uint8_t idx, bool value); // Escribir bit <idx>

    uint8_t get(); // (pos)
    void parse(uint8_t data); // (block data)

    uint8_t used = 0; // Variable used for printing (i.e: Logs)
};

// crear un contenedor de 8 bits
BoolContainer::BoolContainer()
{
    /* if (_blocks <= 4) { blocks = _blocks; }
    else { blocks = 4; }
    ! ESTE CODIGO TIENE ERROR
    container = new uint8_t[_blocks];
    
    for (uint8_t i = 0; i < _blocks; i++)
        container[i] = 0; */
}

BoolContainer::~BoolContainer()
{
    // !if (container)
	// 	!delete[] container;
}

// escribir un bit
void BoolContainer::write(uint8_t idx, bool value)
{
    if (idx < 8)
    {
        // !uint8_t pos = idx%8; // id en el bloque
        // !uint8_t block = idx/8; // bloque (?)
        // Serial.println("(pos, block) write");
        // Serial.println(pos);
        // Serial.println(block);
        if (value)
        {
            // !container[block] |= (0x1 << pos);
            container |= (0x1 << idx);
            return;
        }
        // !container[block] &= (0x0 << pos);
        container &= (0x0 << idx);
    }
}

// Leer un bit
bool BoolContainer::read(uint8_t idx)
{
    if (idx < 8)
    {
        // !uint8_t pos = idx%8; // id en el bloque
        // !uint8_t block = idx/8; // bloque (?)
        // Serial.println("(pos, block) read");
        // Serial.println(pos);
        // Serial.println(block);
        // !return (container[block] & (0x1 << pos));
        return (container & (0x1 << idx));
    }
    return false;
}

// Devuelve un bloque contenedor
uint8_t BoolContainer::get() // (pos)
{
    /* if (block < blocks)
    {
    !    return container[block];   
    } 
    return 0;
    */
    return container;
}

// Graba un bloque contenedor
/* void BoolContainer::parse(uint8_t block, uint8_t data) // (pos, block data)
{
    if (block < blocks)
    {
        container[block] = data;
    }
} */

// Devuelve un bloque contenedor
/* uint8_t BoolContainer::get() // ()
{
    return get(0);
} */

// Graba un bloque contenedor
void BoolContainer::parse(uint8_t data) // (block data)
{
    // parse(0, data);
    container = data;
}

#endif