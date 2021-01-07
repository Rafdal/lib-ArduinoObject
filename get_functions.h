

uint8_t ArduinoObject::_getUINT8(uint8_t _pos)
{
    return _readBuffer(idxOf(_pos));
}

uint16_t ArduinoObject::_getUINT16(uint8_t _pos)
{
    uint16_t buf=0;
    for (uint8_t i = 0; i < 2; i++)
    {
        uint8_t byt = _readBuffer(idxOf(_pos)+i);
        buf |= ((uint16_t)byt) << 8*(1-i);
    }
    return buf;
}

uint32_t ArduinoObject::_getUINT32(uint8_t _pos)
{

    uint32_t buf=0;
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t byt = _readBuffer(idxOf(_pos)+i);
        buf |= ((uint32_t)byt) << 8*(3-i);
    }
    return buf;
}

uint8_t ArduinoObject::getByte(uint8_t pos)
{
    return _getUINT8(pos);
}

float ArduinoObject::getFloat(uint8_t pos)
{
    float out = (float)_getUINT32(pos);
    out = out / (float)0xFFFF;
    return out;
}

unsigned long ArduinoObject::getULong(uint8_t pos)
{
    return (unsigned long)_getUINT32(pos);
}

/* BoolContainer ArduinoObject::getBoolContainer(uint8_t pos)
{
    BoolContainer container;
    uint16_t data = 0;
    data = _getUINT16(pos);
    container.parse((uint8_t)((data & 0xFF00) >> 8));
    container.used = (uint8_t)(data & 0xFF);
    return container;
} */

int ArduinoObject::getInt(uint8_t pos)
{
    return (int)_getUINT16(pos);
}