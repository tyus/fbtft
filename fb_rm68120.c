#include <linux/string.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <mach/platform.h>

#include "fbtft.h"

#define DRVNAME		"fb_rm68120"
#define WIDTH		800
#define HEIGHT		480
#define BPP		16
#define FPS		50

static int init_display(struct fbtft_par *par)
{
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "%s()\n", __func__);

	par->fbtftops.reset(par);

	if (par->gpio.cs != -1)
		gpio_set_value(par->gpio.cs, 0);  /* Activate chip */
	gpio_set_value(par->gpio.rd, 1);

	//ENABLE PAGE 1
	write_reg(par, 0xF000, 0x55);
	write_reg(par, 0xF001, 0xAA);
	write_reg(par, 0xF002, 0x52);
	write_reg(par, 0xF003, 0x08);
	write_reg(par, 0xF004, 0x01);

//GAMMA SETING  RED
	write_reg(par, 0xD100, 0x00);
	write_reg(par, 0xD101, 0x00);
	write_reg(par, 0xD102, 0x1b);
	write_reg(par, 0xD103, 0x44);
	write_reg(par, 0xD104, 0x62);
	write_reg(par, 0xD105, 0x00);
	write_reg(par, 0xD106, 0x7b);
	write_reg(par, 0xD107, 0xa1);
	write_reg(par, 0xD108, 0xc0);
	write_reg(par, 0xD109, 0xee);
	write_reg(par, 0xD10A, 0x55);
	write_reg(par, 0xD10B, 0x10);
	write_reg(par, 0xD10C, 0x2c);
	write_reg(par, 0xD10D, 0x43);
	write_reg(par, 0xD10E, 0x57);
	write_reg(par, 0xD10F, 0x55);
	write_reg(par, 0xD110, 0x68);
	write_reg(par, 0xD111, 0x78);
	write_reg(par, 0xD112, 0x87);
	write_reg(par, 0xD113, 0x94);
	write_reg(par, 0xD114, 0x55);
	write_reg(par, 0xD115, 0xa0);
	write_reg(par, 0xD116, 0xac);
	write_reg(par, 0xD117, 0xb6);
	write_reg(par, 0xD118, 0xc1);
	write_reg(par, 0xD119, 0x55);
	write_reg(par, 0xD11A, 0xcb);
	write_reg(par, 0xD11B, 0xcd);
	write_reg(par, 0xD11C, 0xd6);
	write_reg(par, 0xD11D, 0xdf);
	write_reg(par, 0xD11E, 0x95);
	write_reg(par, 0xD11F, 0xe8);
	write_reg(par, 0xD120, 0xf1);
	write_reg(par, 0xD121, 0xfa);
	write_reg(par, 0xD122, 0x02);
	write_reg(par, 0xD123, 0xaa);
	write_reg(par, 0xD124, 0x0b);
	write_reg(par, 0xD125, 0x13);
	write_reg(par, 0xD126, 0x1d);
	write_reg(par, 0xD127, 0x26);
	write_reg(par, 0xD128, 0xaa);
	write_reg(par, 0xD129, 0x30);
	write_reg(par, 0xD12A, 0x3c);
	write_reg(par, 0xD12B, 0x4A);
	write_reg(par, 0xD12C, 0x63);
	write_reg(par, 0xD12D, 0xea);
	write_reg(par, 0xD12E, 0x79);
	write_reg(par, 0xD12F, 0xa6);
	write_reg(par, 0xD130, 0xd0);
	write_reg(par, 0xD131, 0x20);
	write_reg(par, 0xD132, 0x0f);
	write_reg(par, 0xD133, 0x8e);
	write_reg(par, 0xD134, 0xff);
//GAMMA SETING GREEN
	write_reg(par, 0xD200, 0x00);
	write_reg(par, 0xD201, 0x00);
	write_reg(par, 0xD202, 0x1b);
	write_reg(par, 0xD203, 0x44);
	write_reg(par, 0xD204, 0x62);
	write_reg(par, 0xD205, 0x00);
	write_reg(par, 0xD206, 0x7b);
	write_reg(par, 0xD207, 0xa1);
	write_reg(par, 0xD208, 0xc0);
	write_reg(par, 0xD209, 0xee);
	write_reg(par, 0xD20A, 0x55);
	write_reg(par, 0xD20B, 0x10);
	write_reg(par, 0xD20C, 0x2c);
	write_reg(par, 0xD20D, 0x43);
	write_reg(par, 0xD20E, 0x57);
	write_reg(par, 0xD20F, 0x55);
	write_reg(par, 0xD210, 0x68);
	write_reg(par, 0xD211, 0x78);
	write_reg(par, 0xD212, 0x87);
	write_reg(par, 0xD213, 0x94);
	write_reg(par, 0xD214, 0x55);
	write_reg(par, 0xD215, 0xa0);
	write_reg(par, 0xD216, 0xac);
	write_reg(par, 0xD217, 0xb6);
	write_reg(par, 0xD218, 0xc1);
	write_reg(par, 0xD219, 0x55);
	write_reg(par, 0xD21A, 0xcb);
	write_reg(par, 0xD21B, 0xcd);
	write_reg(par, 0xD21C, 0xd6);
	write_reg(par, 0xD21D, 0xdf);
	write_reg(par, 0xD21E, 0x95);
	write_reg(par, 0xD21F, 0xe8);
	write_reg(par, 0xD220, 0xf1);
	write_reg(par, 0xD221, 0xfa);
	write_reg(par, 0xD222, 0x02);
	write_reg(par, 0xD223, 0xaa);
	write_reg(par, 0xD224, 0x0b);
	write_reg(par, 0xD225, 0x13);
	write_reg(par, 0xD226, 0x1d);
	write_reg(par, 0xD227, 0x26);
	write_reg(par, 0xD228, 0xaa);
	write_reg(par, 0xD229, 0x30);
	write_reg(par, 0xD22A, 0x3c);
	write_reg(par, 0xD22B, 0x4a);
	write_reg(par, 0xD22C, 0x63);
	write_reg(par, 0xD22D, 0xea);
	write_reg(par, 0xD22E, 0x79);
	write_reg(par, 0xD22F, 0xa6);
	write_reg(par, 0xD230, 0xd0);
	write_reg(par, 0xD231, 0x20);
	write_reg(par, 0xD232, 0x0f);
	write_reg(par, 0xD233, 0x8e);
	write_reg(par, 0xD234, 0xff);

//GAMMA SETING BLUE
	write_reg(par, 0xD300, 0x00);
	write_reg(par, 0xD301, 0x00);
	write_reg(par, 0xD302, 0x1b);
	write_reg(par, 0xD303, 0x44);
	write_reg(par, 0xD304, 0x62);
	write_reg(par, 0xD305, 0x00);
	write_reg(par, 0xD306, 0x7b);
	write_reg(par, 0xD307, 0xa1);
	write_reg(par, 0xD308, 0xc0);
	write_reg(par, 0xD309, 0xee);
	write_reg(par, 0xD30A, 0x55);
	write_reg(par, 0xD30B, 0x10);
	write_reg(par, 0xD30C, 0x2c);
	write_reg(par, 0xD30D, 0x43);
	write_reg(par, 0xD30E, 0x57);
	write_reg(par, 0xD30F, 0x55);
	write_reg(par, 0xD310, 0x68);
	write_reg(par, 0xD311, 0x78);
	write_reg(par, 0xD312, 0x87);
	write_reg(par, 0xD313, 0x94);
	write_reg(par, 0xD314, 0x55);
	write_reg(par, 0xD315, 0xa0);
	write_reg(par, 0xD316, 0xac);
	write_reg(par, 0xD317, 0xb6);
	write_reg(par, 0xD318, 0xc1);
	write_reg(par, 0xD319, 0x55);
	write_reg(par, 0xD31A, 0xcb);
	write_reg(par, 0xD31B, 0xcd);
	write_reg(par, 0xD31C, 0xd6);
	write_reg(par, 0xD31D, 0xdf);
	write_reg(par, 0xD31E, 0x95);
	write_reg(par, 0xD31F, 0xe8);
	write_reg(par, 0xD320, 0xf1);
	write_reg(par, 0xD321, 0xfa);
	write_reg(par, 0xD322, 0x02);
	write_reg(par, 0xD323, 0xaa);
	write_reg(par, 0xD324, 0x0b);
	write_reg(par, 0xD325, 0x13);
	write_reg(par, 0xD326, 0x1d);
	write_reg(par, 0xD327, 0x26);
	write_reg(par, 0xD328, 0xaa);
	write_reg(par, 0xD329, 0x30);
	write_reg(par, 0xD32A, 0x3c);
	write_reg(par, 0xD32B, 0x4A);
	write_reg(par, 0xD32C, 0x63);
	write_reg(par, 0xD32D, 0xea);
	write_reg(par, 0xD32E, 0x79);
	write_reg(par, 0xD32F, 0xa6);
	write_reg(par, 0xD330, 0xd0);
	write_reg(par, 0xD331, 0x20);
	write_reg(par, 0xD332, 0x0f);
	write_reg(par, 0xD333, 0x8e);
	write_reg(par, 0xD334, 0xff);


//GAMMA SETING  RED
	write_reg(par, 0xD400, 0x00);
	write_reg(par, 0xD401, 0x00);
	write_reg(par, 0xD402, 0x1b);
	write_reg(par, 0xD403, 0x44);
	write_reg(par, 0xD404, 0x62);
	write_reg(par, 0xD405, 0x00);
	write_reg(par, 0xD406, 0x7b);
	write_reg(par, 0xD407, 0xa1);
	write_reg(par, 0xD408, 0xc0);
	write_reg(par, 0xD409, 0xee);
	write_reg(par, 0xD40A, 0x55);
	write_reg(par, 0xD40B, 0x10);
	write_reg(par, 0xD40C, 0x2c);
	write_reg(par, 0xD40D, 0x43);
	write_reg(par, 0xD40E, 0x57);
	write_reg(par, 0xD40F, 0x55);
	write_reg(par, 0xD410, 0x68);
	write_reg(par, 0xD411, 0x78);
	write_reg(par, 0xD412, 0x87);
	write_reg(par, 0xD413, 0x94);
	write_reg(par, 0xD414, 0x55);
	write_reg(par, 0xD415, 0xa0);
	write_reg(par, 0xD416, 0xac);
	write_reg(par, 0xD417, 0xb6);
	write_reg(par, 0xD418, 0xc1);
	write_reg(par, 0xD419, 0x55);
	write_reg(par, 0xD41A, 0xcb);
	write_reg(par, 0xD41B, 0xcd);
	write_reg(par, 0xD41C, 0xd6);
	write_reg(par, 0xD41D, 0xdf);
	write_reg(par, 0xD41E, 0x95);
	write_reg(par, 0xD41F, 0xe8);
	write_reg(par, 0xD420, 0xf1);
	write_reg(par, 0xD421, 0xfa);
	write_reg(par, 0xD422, 0x02);
	write_reg(par, 0xD423, 0xaa);
	write_reg(par, 0xD424, 0x0b);
	write_reg(par, 0xD425, 0x13);
	write_reg(par, 0xD426, 0x1d);
	write_reg(par, 0xD427, 0x26);
	write_reg(par, 0xD428, 0xaa);
	write_reg(par, 0xD429, 0x30);
	write_reg(par, 0xD42A, 0x3c);
	write_reg(par, 0xD42B, 0x4A);
	write_reg(par, 0xD42C, 0x63);
	write_reg(par, 0xD42D, 0xea);
	write_reg(par, 0xD42E, 0x79);
	write_reg(par, 0xD42F, 0xa6);
	write_reg(par, 0xD430, 0xd0);
	write_reg(par, 0xD431, 0x20);
	write_reg(par, 0xD432, 0x0f);
	write_reg(par, 0xD433, 0x8e);
	write_reg(par, 0xD434, 0xff);

//GAMMA SETING GREEN
	write_reg(par, 0xD500, 0x00);
	write_reg(par, 0xD501, 0x00);
	write_reg(par, 0xD502, 0x1b);
	write_reg(par, 0xD503, 0x44);
	write_reg(par, 0xD504, 0x62);
	write_reg(par, 0xD505, 0x00);
	write_reg(par, 0xD506, 0x7b);
	write_reg(par, 0xD507, 0xa1);
	write_reg(par, 0xD508, 0xc0);
	write_reg(par, 0xD509, 0xee);
	write_reg(par, 0xD50A, 0x55);
	write_reg(par, 0xD50B, 0x10);
	write_reg(par, 0xD50C, 0x2c);
	write_reg(par, 0xD50D, 0x43);
	write_reg(par, 0xD50E, 0x57);
	write_reg(par, 0xD50F, 0x55);
	write_reg(par, 0xD510, 0x68);
	write_reg(par, 0xD511, 0x78);
	write_reg(par, 0xD512, 0x87);
	write_reg(par, 0xD513, 0x94);
	write_reg(par, 0xD514, 0x55);
	write_reg(par, 0xD515, 0xa0);
	write_reg(par, 0xD516, 0xac);
	write_reg(par, 0xD517, 0xb6);
	write_reg(par, 0xD518, 0xc1);
	write_reg(par, 0xD519, 0x55);
	write_reg(par, 0xD51A, 0xcb);
	write_reg(par, 0xD51B, 0xcd);
	write_reg(par, 0xD51C, 0xd6);
	write_reg(par, 0xD51D, 0xdf);
	write_reg(par, 0xD51E, 0x95);
	write_reg(par, 0xD51F, 0xe8);
	write_reg(par, 0xD520, 0xf1);
	write_reg(par, 0xD521, 0xfa);
	write_reg(par, 0xD522, 0x02);
	write_reg(par, 0xD523, 0xaa);
	write_reg(par, 0xD524, 0x0b);
	write_reg(par, 0xD525, 0x13);
	write_reg(par, 0xD526, 0x1d);
	write_reg(par, 0xD527, 0x26);
	write_reg(par, 0xD528, 0xaa);
	write_reg(par, 0xD529, 0x30);
	write_reg(par, 0xD52A, 0x3c);
	write_reg(par, 0xD52B, 0x4a);
	write_reg(par, 0xD52C, 0x63);
	write_reg(par, 0xD52D, 0xea);
	write_reg(par, 0xD52E, 0x79);
	write_reg(par, 0xD52F, 0xa6);
	write_reg(par, 0xD530, 0xd0);
	write_reg(par, 0xD531, 0x20);
	write_reg(par, 0xD532, 0x0f);
	write_reg(par, 0xD533, 0x8e);
	write_reg(par, 0xD534, 0xff);

//GAMMA SETING BLUE
	write_reg(par, 0xD600, 0x00);
	write_reg(par, 0xD601, 0x00);
	write_reg(par, 0xD602, 0x1b);
	write_reg(par, 0xD603, 0x44);
	write_reg(par, 0xD604, 0x62);
	write_reg(par, 0xD605, 0x00);
	write_reg(par, 0xD606, 0x7b);
	write_reg(par, 0xD607, 0xa1);
	write_reg(par, 0xD608, 0xc0);
	write_reg(par, 0xD609, 0xee);
	write_reg(par, 0xD60A, 0x55);
	write_reg(par, 0xD60B, 0x10);
	write_reg(par, 0xD60C, 0x2c);
	write_reg(par, 0xD60D, 0x43);
	write_reg(par, 0xD60E, 0x57);
	write_reg(par, 0xD60F, 0x55);
	write_reg(par, 0xD610, 0x68);
	write_reg(par, 0xD611, 0x78);
	write_reg(par, 0xD612, 0x87);
	write_reg(par, 0xD613, 0x94);
	write_reg(par, 0xD614, 0x55);
	write_reg(par, 0xD615, 0xa0);
	write_reg(par, 0xD616, 0xac);
	write_reg(par, 0xD617, 0xb6);
	write_reg(par, 0xD618, 0xc1);
	write_reg(par, 0xD619, 0x55);
	write_reg(par, 0xD61A, 0xcb);
	write_reg(par, 0xD61B, 0xcd);
	write_reg(par, 0xD61C, 0xd6);
	write_reg(par, 0xD61D, 0xdf);
	write_reg(par, 0xD61E, 0x95);
	write_reg(par, 0xD61F, 0xe8);
	write_reg(par, 0xD620, 0xf1);
	write_reg(par, 0xD621, 0xfa);
	write_reg(par, 0xD622, 0x02);
	write_reg(par, 0xD623, 0xaa);
	write_reg(par, 0xD624, 0x0b);
	write_reg(par, 0xD625, 0x13);
	write_reg(par, 0xD626, 0x1d);
	write_reg(par, 0xD627, 0x26);
	write_reg(par, 0xD628, 0xaa);
	write_reg(par, 0xD629, 0x30);
	write_reg(par, 0xD62A, 0x3c);
	write_reg(par, 0xD62B, 0x4A);
	write_reg(par, 0xD62C, 0x63);
	write_reg(par, 0xD62D, 0xea);
	write_reg(par, 0xD62E, 0x79);
	write_reg(par, 0xD62F, 0xa6);
	write_reg(par, 0xD630, 0xd0);
	write_reg(par, 0xD631, 0x20);
	write_reg(par, 0xD632, 0x0f);
	write_reg(par, 0xD633, 0x8e);
	write_reg(par, 0xD634, 0xff);

//AVDD VOLTAGE SETTING
	write_reg(par, 0xB000, 0x05);
	write_reg(par, 0xB001, 0x05);
	write_reg(par, 0xB002, 0x05);
//AVEE VOLTAGE SETTING
	write_reg(par, 0xB100, 0x05);
	write_reg(par, 0xB101, 0x05);
	write_reg(par, 0xB102, 0x05);

//AVDD Boosting
	write_reg(par, 0xB600, 0x34);
	write_reg(par, 0xB601, 0x34);
	write_reg(par, 0xB603, 0x34);
//AVEE Boosting
	write_reg(par, 0xB700, 0x24);
	write_reg(par, 0xB701, 0x24);
	write_reg(par, 0xB702, 0x24);
//VCL Boosting
	write_reg(par, 0xB800, 0x24);
	write_reg(par, 0xB801, 0x24);
	write_reg(par, 0xB802, 0x24);
//VGLX VOLTAGE SETTING
	write_reg(par, 0xBA00, 0x14);
	write_reg(par, 0xBA01, 0x14);
	write_reg(par, 0xBA02, 0x14);
//VCL Boosting
	write_reg(par, 0xB900, 0x24);
	write_reg(par, 0xB901, 0x24);
	write_reg(par, 0xB902, 0x24);
//Gamma Voltage
	write_reg(par, 0xBc00, 0x00);
	write_reg(par, 0xBc01, 0xa0);//vgmp=5.0
	write_reg(par, 0xBc02, 0x00);
	write_reg(par, 0xBd00, 0x00);
	write_reg(par, 0xBd01, 0xa0);//vgmn=5.0
	write_reg(par, 0xBd02, 0x00);
	//VCOM Setting
	write_reg(par, 0xBe01, 0x3d);//3
	//ENABLE PAGE 0
	write_reg(par, 0xF000, 0x55);
	write_reg(par, 0xF001, 0xAA);
	write_reg(par, 0xF002, 0x52);
	write_reg(par, 0xF003, 0x08);
	write_reg(par, 0xF004, 0x00);
	//Vivid Color Function Control
	write_reg(par, 0xB400, 0x10);
	//Z-INVERSION
	write_reg(par, 0xBC00, 0x05);
	write_reg(par, 0xBC01, 0x05);
	write_reg(par, 0xBC02, 0x05);

	//*************** add on 20111021**********************//
	write_reg(par, 0xB700, 0x22);//GATE EQ CONTROL
	write_reg(par, 0xB701, 0x22);//GATE EQ CONTROL

	write_reg(par, 0xC80B, 0x2A);//DISPLAY TIMING CONTROL
	write_reg(par, 0xC80C, 0x2A);//DISPLAY TIMING CONTROL
	write_reg(par, 0xC80F, 0x2A);//DISPLAY TIMING CONTROL
	write_reg(par, 0xC810, 0x2A);//DISPLAY TIMING CONTROL
	//*************** add on 20111021**********************//
	//PWM_ENH_OE =1
	write_reg(par, 0xd000, 0x01);
	//DM_SEL =1
	write_reg(par, 0xb300, 0x10);
	//VBPDA=07h
	write_reg(par, 0xBd02, 0x07);
	//VBPDb=07h
	write_reg(par, 0xBe02, 0x07);
	//VBPDc=07h
	write_reg(par, 0xBf02, 0x07);
	//ENABLE PAGE 2
	write_reg(par, 0xF000, 0x55);
	write_reg(par, 0xF001, 0xAA);
	write_reg(par, 0xF002, 0x52);
	write_reg(par, 0xF003, 0x08);
	write_reg(par, 0xF004, 0x02);
	//SDREG0 =0
	write_reg(par, 0xc301, 0xa9);
	//DS=14
	write_reg(par, 0xfe01, 0x94);
	//OSC =60h
	write_reg(par, 0xf600, 0x60);
	//TE ON
	write_reg(par, 0x3500, 0x00);
	//SLEEP OUT 
	write_reg(par, 0x1100);
	mdelay(120);
	//DISPLY ON
	write_reg(par, 0x2900);
	mdelay(100);

	gpio_set_value(par->gpio.led[0], 1); 

	write_reg(par, 0x3A00, 0x55);
	write_reg(par, 0x3600, 0xA8);

}

#define WRITE_WIN(par, xs, ys, xe, ye) \
	write_reg(par, 0x2a00, xs>>8); \
	write_reg(par, 0x2a01, xs); \
	write_reg(par, 0x2a02, xe>>8); \
	write_reg(par, 0x2a03, xe); \
	write_reg(par, 0x2b00, ys>>8); \
	write_reg(par, 0x2b01, ys); \
	write_reg(par, 0x2b02, ye>>8); \
	write_reg(par, 0x2b03, ye); \

static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	fbtft_par_dbg(DEBUG_SET_ADDR_WIN, par,
		"%s(xs=%d, ys=%d, xe=%d, ye=%d)\n", __func__, xs, ys, xe, ye);
	switch (par->info->var.rotate) {

	case 0:
		WRITE_WIN(par, xs, ys, xe, ye);
		break;
	case 180:
		WRITE_WIN(par, WIDTH - 1 - xs, HEIGHT - 1 - ys, xe, ye);
		break;
	case 270:
		WRITE_WIN(par, xs, WIDTH - 1 - ys, xe, ye);
		break;
	case 90:
		WRITE_WIN(par, HEIGHT - 1 - xs, ys, xe, ye);
		break;
	}
	write_reg(par, 0x2c00); /* Write Data to GRAM */
}

static int set_var(struct fbtft_par *par)
{
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "%s()\n", __func__);

	switch (par->info->var.rotate) {
	/* AM: GRAM update direction */
	case 0:
		write_reg(par, 0x03, 0x0003 | (par->bgr << 12));
		break;
	case 180:
		write_reg(par, 0x03, 0x0000 | (par->bgr << 12));
		break;
	case 270:
		write_reg(par, 0x03, 0x000A | (par->bgr << 12));
		break;
	case 90:
		write_reg(par, 0x03, 0x0009 | (par->bgr << 12));
		break;
	}

	return 0;
}

/*
  Gamma string format:
    PKP0 PKP1 PKP2 PKP3 PKP4 PKP5 PKP6 PKP7 PKP8 PKP9 PKP10 PKP11 VRP0 VRP1
    PKN0 PKN1 PKN2 PKN3 PKN4 PKN5 PKN6 PKN7 PRN8 PRN9 PRN10 PRN11 VRN0 VRN1
*/
#define CURVE(num, idx)  curves[num*par->gamma.num_values + idx]
static int set_gamma(struct fbtft_par *par, unsigned long *curves)
{
	unsigned long mask[] = {
		0b111111, 0b111111, 0b111111, 0b111111, 0b111111, 0b111111, 
		0b111111, 0b111111, 0b111111, 0b111111, 0b111111, 0b111111,
		0b11111, 0b11111,
		0b111111, 0b111111, 0b111111, 0b111111, 0b111111, 0b111111,
		0b111111, 0b111111, 0b111111, 0b111111, 0b111111, 0b111111,
		0b11111, 0b11111 };
	int i, j;

	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "%s()\n", __func__);

	/* apply mask */
	for (i = 0; i < 2; i++)
		for (j = 0; j < 14; j++)
			CURVE(i, j) &= mask[i*par->gamma.num_values + j];

	write_reg(par, 0x0030, CURVE(0, 1) << 8 | CURVE(0, 0));
	write_reg(par, 0x0031, CURVE(0, 3) << 8 | CURVE(0, 2));
	write_reg(par, 0x0032, CURVE(0, 5) << 8 | CURVE(0, 3));
	write_reg(par, 0x0033, CURVE(0, 7) << 8 | CURVE(0, 6));
	write_reg(par, 0x0034, CURVE(0, 9) << 8 | CURVE(0, 8));
	write_reg(par, 0x0035, CURVE(0, 11) << 8 | CURVE(0, 10));

	write_reg(par, 0x0036, CURVE(1, 1) << 8 | CURVE(1, 0));
	write_reg(par, 0x0037, CURVE(1, 3) << 8 | CURVE(1, 2));
	write_reg(par, 0x0038, CURVE(1, 5) << 8 | CURVE(1, 4));
	write_reg(par, 0x0039, CURVE(1, 7) << 8 | CURVE(1, 6));
	write_reg(par, 0x003A, CURVE(1, 9) << 8 | CURVE(1, 8));
	write_reg(par, 0x003B, CURVE(1, 11) << 8 | CURVE(1, 10));

	write_reg(par, 0x003C, CURVE(0, 13) << 8 | CURVE(0, 12));
	write_reg(par, 0x003D, CURVE(1, 13) << 8 | CURVE(1, 12));

	return 0;
}
#undef CURVE

#define GPIOSET(no, ishigh)           \
do {                                  \
	if (ishigh)                   \
		set |= (1 << (no));   \
	else                          \
		reset |= (1 << (no)); \
} while (0)

int write(struct fbtft_par *par, void *buf, size_t len)
{
	unsigned int set = 0;
	unsigned int reset = 0;
	u16 data;

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
		"%s(len=%d): ", __func__, len);

	while (len) {
		len -= 2;
		data = *(u16 *) buf;
		buf += 2;

		/* Set data */
		GPIOSET(par->gpio.db[0],  (data&0x0001));
		GPIOSET(par->gpio.db[1],  (data&0x0002));
		GPIOSET(par->gpio.db[2],  (data&0x0004));
		GPIOSET(par->gpio.db[3],  (data&0x0008));
		GPIOSET(par->gpio.db[4],  (data&0x0010));
		GPIOSET(par->gpio.db[5],  (data&0x0020));
		GPIOSET(par->gpio.db[6],  (data&0x0040));
		GPIOSET(par->gpio.db[7],  (data&0x0080));

		GPIOSET(par->gpio.db[8],  (data&0x0100));
		GPIOSET(par->gpio.db[9],  (data&0x0200));
		GPIOSET(par->gpio.db[10], (data&0x0400));
		GPIOSET(par->gpio.db[11], (data&0x0800));
		GPIOSET(par->gpio.db[12], (data&0x1000));
		GPIOSET(par->gpio.db[13], (data&0x2000));
		GPIOSET(par->gpio.db[14], (data&0x4000));
		GPIOSET(par->gpio.db[15], (data&0x8000));

		writel(set, __io_address(GPIO_BASE+0x1C));
		writel(reset, __io_address(GPIO_BASE+0x28));

		/* Start writing by pulling up /WR */
		gpio_set_value(par->gpio.wr, 1);

		/* Pulldown /WR */
		gpio_set_value(par->gpio.wr, 0);

		set = 0;
		reset = 0;
	}

	return 0;
}

void reset(struct fbtft_par *par)
{
	if (par->gpio.reset == -1)
		return;

	fbtft_dev_dbg(DEBUG_RESET, par, par->info->device, "%s()\n", __func__);

	gpio_set_value(par->gpio.reset, 0);
	udelay(10);
	gpio_set_value(par->gpio.reset, 1);
	udelay(10);
}


static struct fbtft_display display = {
	.regwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
//	.gamma_num = 2,
//	.gamma_len = 14,
//	.gamma = DEFAULT_GAMMA,
	.fbtftops = {
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		// .write_register = write_register,
		.write = write,
//		.reset = reset,
//		.set_var = set_var,
		// .set_gamma = set_gamma,
	},
};
FBTFT_REGISTER_DRIVER(DRVNAME, "raydium,rm68120", &display);

// MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
// MODULE_ALIAS("spi:rm68120");
MODULE_ALIAS("platform:rm68120");

MODULE_DESCRIPTION("FB driver for the rm68120 LCD Controller");
MODULE_AUTHOR("Rany Huang");
MODULE_LICENSE("GPL");
