#include <INTRINS.H>	//_nop_()
void Delayxms(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;
	while(x)
	{
		_nop_();
		i = 2;
		j = 245;
		do
		{
			while (--j);
		} while (--i);
		x--;
	} 
}