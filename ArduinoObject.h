// #include <BoolContainer.h>

/* 
 * Estructura del ArduinoObject
 * 
 $       format      0      datos
 @    [A][B][C][D]  {0}  (A)(B)(C)(D)
 * 
 */


#ifndef ARDUINO_OBJECT
#define ARDUINO_OBJECT

typedef uint8_t format_t[];

enum formats{
    _NONE_,
    F_BYTE,
    F_FLOAT,
    F_ULONG,
    F_INT,
    F_BOOLCONTAINER,
};

// #define DEBUG_PRINT

class ArduinoObject
{
private:
    uint8_t buf_size_max=0;
    uint8_t elements=0;
    
    uint8_t *buffer; //

    void error(String a = ""){ Serial.print(F("ARDUINO OBJECT ERROR idx = ")); Serial.println(a);}

    void _writeBuffer(uint8_t idx, uint8_t data){
        if (idx < buf_size_max)
            buffer[idx] = data;
        else
            {error(String(idx));}
    }
    uint8_t _readBuffer(uint8_t idx){
        if (idx < buf_size_max)
            return buffer[idx];
        else
            {error(String(idx));}
        return 0;
    }

    uint8_t _getUINT8(uint8_t pos);
    uint16_t _getUINT16(uint8_t pos);
    uint32_t _getUINT32(uint8_t pos);

    void _add_UINT8(uint8_t pos, uint8_t data);
    void _add_UINT16(uint8_t pos, uint16_t data);
    void _add_UINT32(uint8_t pos, uint32_t data);

    uint8_t _sizeof(uint8_t type){
        if (type == F_BYTE)
            {return 1;}        
        if (type == F_FLOAT || type == F_ULONG)
            {return 4;}
        if (type == F_INT || type == F_BOOLCONTAINER)
            {return 2;}  
        return 0;      
    }

    uint8_t idxOf(uint8_t _idx);

public:
    ArduinoObject(uint8_t data[], uint8_t size); // Crea un Objeto con datos
    ArduinoObject(format_t format);
    ~ArduinoObject();

    // add a new element
    void set(uint8_t pos, uint8_t data);
    void set(uint8_t pos, float data);
    void set(uint8_t pos, unsigned long data);
    void set(uint8_t pos, int data);
    // void set(uint8_t pos, BoolContainer container);
    // void add(String data);

    uint8_t getByte(uint8_t pos);
    float getFloat(uint8_t pos);
    unsigned long getULong(uint8_t pos);
    // BoolContainer getBoolContainer(uint8_t pos);
    int getInt(uint8_t pos);


    uint8_t size() { return buf_size_max; } // Size of buffer
    
    uint8_t length() { return elements; } // Amount of elements
    uint8_t data(uint8_t _idx);

    void clear();


    // void printTree();
    void printBuffer();
    void serialize();
};

uint8_t ArduinoObject::idxOf(uint8_t pos)
{
    if (pos < elements)
    {
        uint8_t _idx=elements+1;

        for (uint8_t i = 0; i < pos; i++)
        {
            _idx += _sizeof(_readBuffer(i));
        }
        return _idx;
    }
    else
    {
        return 0;
    }
}

#include <add_functions.h>

// New Static Arduino Object Container
ArduinoObject::ArduinoObject(uint8_t data[], uint8_t size)
{
    buf_size_max = size;
    for (elements = 0; elements < size/2; elements++)
    {
        if (data[elements] == 0)
        {
            break;
        }
    }
    
    buffer = new uint8_t[buf_size_max+1];
    for (uint8_t i = 0; i < buf_size_max; i++)
        buffer[i] = data[i];

}


// New Static Arduino Object Container
ArduinoObject::ArduinoObject(format_t format)
{
    elements = sizeof((uint8_t*)format);
    buf_size_max = elements+1;
    for (uint8_t i = 0; i < elements; i++)
    {
        buf_size_max += _sizeof(format[i]);
    }

    buffer = new uint8_t[buf_size_max+1];

    // Cargo el footprint
    for (uint8_t i = 0; i < elements; i++)
        buffer[i] = format[i];

    buffer[elements] = 0;

    // Limpio el objeto
    for (uint8_t i = elements+1; i < buf_size_max; i++)
        buffer[i] = 0;

}

ArduinoObject::~ArduinoObject()
{
    Serial.println(F("OBJECT DESTRUCTOR"));
    for (uint8_t i = 0; i < buf_size_max; i++)
    {
        buffer[i] = 0;
    }
    
    if (buffer)
		delete[] buffer;
}

// Devuelve bytes del buffer
uint8_t ArduinoObject::data(uint8_t _idx)
{
    return _readBuffer(_idx);
}

void ArduinoObject::clear()
{
    for (uint8_t i = 0; i < buf_size_max; i++)
    {
        buffer[i] = 0;
    }
}

#include <get_functions.h>

void ArduinoObject::serialize()
{
    Serial.println(F("[type]\t[value]"));
    for (uint8_t pos = 0; pos < elements; pos++)
    {
        switch (_readBuffer(pos))
        {
        case F_BYTE:
            {
                Serial.print(F("byte \t"));
                Serial.println(getByte(pos));
            }
            break;

        case F_FLOAT:
            {
                Serial.print(F("float\t"));
                Serial.println(String(getFloat(pos), 4));
            }
            break;

        case F_ULONG:
            {
                Serial.print(F("ulong\t"));
                Serial.println(getULong(pos));
            }
            break;

        case F_INT:
            {
                Serial.print(F("int  \t"));
                Serial.println(getInt(pos));
            }
            break;
        
        default:
            break;
        }
    }
    
}

void ArduinoObject::printBuffer()
{
    for (uint8_t i = 0; i < buf_size_max; i++)
    {
        Serial.print(buffer[i]);
        Serial.print(F(","));
    }
    Serial.print("\telements: ");
    Serial.println(elements);
}

/* void ArduinoObject::serialize()
{
    uint8_t _idx = 0;
    uint8_t pos = 0;
    for (uint8_t i = 0; i < buf_size_max/2 && _idx < buf_size_max; i++)
    {
        switch (buffer[_idx])
        {
        case 1:
            Serial.print(getByte(pos));
            break;
        
        case 2:
            Serial.print(String(getFloat(pos), 3));
            break;

        case 3:
            Serial.print(getULong(pos));
            break;

        case 4:
            {
                BoolContainer con = getBoolContainer(pos);
                for (uint8_t i = 0; i < con.used; i++)
                {
                    Serial.print(con.read(i));
                    Serial.print(F(","));
                }
            }
            break;

        default:
            {
                Serial.print(F("\r\n"));
                return;
            }
            break;
        }
        _idx = nextIdx(_idx);
        pos++;
        Serial.print(F("\t"));
    }
} */


#endif