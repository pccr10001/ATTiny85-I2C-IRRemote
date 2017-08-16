#include <Arduino.h>
#include <tiny_IRremote.h>
#include <TinyWireS.h>

IRsend irsend;

#define I2C_SLAVE_ADDR  0x18

uint8_t data[21] = {0};
uint8_t i=0;

void setup()
{
	TinyWireS.begin(I2C_SLAVE_ADDR);
}

void loop() {

	if (TinyWireS.available()){
		data[i++]=TinyWireS.receive();
	}
	if(i>21)
		i=0;

	if(i>=7)
	{
		if(data[i-7]==0xff && data[i-2]==0x00 && data[i-1]==0xff)
		{
			uint32_t ir_code = data[i-3];
			ir_code |= ((uint32_t)data[i-4])<<8;
			ir_code |= ((uint32_t)data[i-5])<<16;
			ir_code |= ((uint32_t)data[i-6])<<24;
			irsend.sendNEC(ir_code,32);
			i=0;
		}
	}


}
