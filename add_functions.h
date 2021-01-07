
void ArduinoObject::_add_UINT8(uint8_t pos, uint8_t data)
{
    _writeBuffer(idxOf(pos), data);
}

void ArduinoObject::_add_UINT16(uint8_t pos, uint16_t data) // @ wip
{
    for (uint8_t i = 0; i < 2; i++)
    {
        _writeBuffer(idxOf(pos)+1-i, (uint8_t)((data & ((uint16_t)0x00FF << 8*i)) >> 8*i));
    }
}

void ArduinoObject::_add_UINT32(uint8_t pos, uint32_t data)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        _writeBuffer(idxOf(pos)+3-i, (uint8_t)((data & ((uint32_t)0x000000FF << 8*i)) >> 8*i));
    }
}


void ArduinoObject::set(uint8_t pos, uint8_t data) // 1
{
    // Serial.println("add uint8_t");
    if (_readBuffer(pos) == F_BYTE && pos < elements) // test
    {
        _add_UINT8(pos, data);
    }
}

void ArduinoObject::set(uint8_t pos, float data) // 2
{
    // Serial.println("add float");
    if (_readBuffer(pos) == F_FLOAT && pos < elements) // mem free test
    {
        data *= 0xFFFF;
        _add_UINT32(pos, (uint32_t)data);
    }
}

void ArduinoObject::set(uint8_t pos, unsigned long data) // 3
{
    // Serial.println("add ULong");
    if (_readBuffer(pos) == F_ULONG && pos < elements) // mem free test
    {
        _add_UINT32(pos, (uint32_t)data);
    }
}

// unused
/* void ArduinoObject::set(uint8_t pos, BoolContainer container) // 4
{
    // Serial.println("add BoolContainer");
    if (_readBuffer(pos) == F_BOOLCONTAINER && pos < elements) // mem free test
    {
        buffer[idx] = F_BOOLCONTAINER; // BoolContainer (1 block)
        uint16_t data = 0;
        data = (((uint16_t)container.get()) << 8) | container.used;
        _add_UINT16(data);
    }
    return;
} */

void ArduinoObject::set(uint8_t pos, int data) // 4
{
    // Serial.println("add BoolContainer");
    if (_readBuffer(pos) == F_INT && pos < elements) // mem free test
    {
        _add_UINT16(pos, (uint16_t)data);
    }
    return;
}