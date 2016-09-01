/*
 * FB driver for the R61525 LCD Controller
 *
 * Copyright (C) 2013 Roman Rolinsky
 *
 * Based on fb_ili9325.c by Noralf Tronnes
 * Based on ili9325.c by Jeroen Domburg
 * Init code from UTFT library by Henning Karlsen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <mach/platform.h>

#include "fbtft.h"

#define DRVNAME		"fb_r61525"
#define WIDTH		320
#define HEIGHT		240
#define BPP		16
#define FPS		60

static int init_display(struct fbtft_par *par)
{
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "%s()\n", __func__);

	par->fbtftops.reset(par);

	if (par->gpio.cs != -1)
		gpio_set_value(par->gpio.cs, 0);  /* Activate chip */
	gpio_set_value(par->gpio.rd, 1);

	/* Initialization sequence from Lib_UTFT */
	write_reg(par, 0xB0, 0x00);
	write_reg(par, 0xB3, 0x00, 0x00, 0x00, 0x01);
	write_reg(par, 0xB4, 0x00);//RGB=11,MCU=00
	write_reg(par, 0xC0, 0x03, 0x63, 0x00, 0x00, 
			0x02, 0x00, 0x00, 0x44);
	write_reg(par, 0xC1, 0x08, 0x12, 0x08, 0x08);
	write_reg(par, 0xC4, 0x11, 0x02, 0x13, 0x01);
	//Blue GAMMA SET A
	write_reg(par, 0xC8, 0x01, 0x06, 0x16, 
			0x16, 0x17, 0x10, 0x0A, 0x02, 0x02, 
			0x08, 0x00, 0x02, 0x02, 0x0A, 0x10, 
			0x17, 0x16, 0x16, 0x06, 0x01, 0x00, 0x08);
	//GGAMMA SET B
	write_reg(par, 0xC9, 0x01, 0x06, 0x16, 
			0x16, 0x17, 0x10, 0x0A, 0x02, 0x02, 
			0x08, 0x00, 0x02, 0x02, 0x0A, 0x10, 
			0x17, 0x16, 0x16, 0x06, 0x01, 0x00, 0x08);
	//R GAMMA SET C
	write_reg(par, 0xCA, 0x01, 0x06, 0x16, 
			0x16, 0x17, 0x10, 0x0A, 0x02, 0x02, 
			0x08, 0x00, 0x02, 0x02, 0x0A, 0x10, 
			0x17, 0x16, 0x16, 0x06, 0x01, 0x00, 0x08);
	write_reg(par, 0x35, 0x01);
	write_reg(par, 0x3A, 0x55);
//	write_reg(par, 0x3A, 0x77);
	write_reg(par, 0x36, 0x60);
	//write_reg(par, 0x44, 0x00, 0x01);
	write_reg(par, 0x11);
	mdelay(120);
	write_reg(par, 0x13);
	//POWER SETTING
	write_reg(par, 0xD0, 0x07, 0x07, 0x2A, 0x03);
	udelay(100);
	//VCOM SETTING
	write_reg(par, 0xD1, 0x03, 0x56, 0x65);
	//Power Setting for Normal Mode
	write_reg(par, 0xD2, 0x02, 0x24, 0x04);	
	udelay(150);

	write_reg(par, 0x29);
	udelay(10);
	//set source count
	write_reg(par, 0x2A, 0x00, 0x00, 0x00, 0xEF);
	//set gate count
	write_reg(par, 0x2B, 0x00, 0x00, 0x01, 0xAF);

	write_reg(par, 0x2C);

	return 0;
}

void reset(struct fbtft_par *par)
{
	if (par->gpio.reset == -1)
		return;

	fbtft_dev_dbg(DEBUG_RESET, par, par->info->device, "%s()\n", __func__);

	gpio_set_value(par->gpio.reset, 0);
	mdelay(1.2);
	gpio_set_value(par->gpio.reset, 1);
	mdelay(6);
}

static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	fbtft_par_dbg(DEBUG_SET_ADDR_WIN, par,
		"%s(xs=%d, ys=%d, xe=%d, ye=%d)\n", __func__, xs, ys, xe, ye);

	write_reg(par, 0x2a, xs >> 8, xs & 0xff, 
		xe >> 8, xe & 0xff);
	write_reg(par, 0x2b, ys >> 8, ys & 0xff,
		ye >> 8, ye & 0xff);

	write_reg(par, 0x2c); /* Write Data to GRAM */
}

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
	u8 data;

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, 
			len,
			"%s(len=%d): ", __func__, len);

	while (len--) {
		data = *(u8 *) buf;
		buf++;

		/* Set data */
		GPIOSET(par->gpio.db[0], (data&0x01));
		GPIOSET(par->gpio.db[1], (data&0x02));
		GPIOSET(par->gpio.db[2], (data&0x04));
		GPIOSET(par->gpio.db[3], (data&0x08));
		GPIOSET(par->gpio.db[4], (data&0x10));
		GPIOSET(par->gpio.db[5], (data&0x20));
		GPIOSET(par->gpio.db[6], (data&0x40));
		GPIOSET(par->gpio.db[7], (data&0x80));

		writel(set, __io_address(GPIO_BASE+0x1C));
		writel(reset, __io_address(GPIO_BASE+0x28));

		/* Pulldown /WR */
		gpio_set_value(par->gpio.wr, 0);
		/* Start writing by pulling up /WR */
		gpio_set_value(par->gpio.wr, 1);

		set = 0;
		reset = 0;
	}

	return 0;
}

/* 24 bit pixel over 8-bit databus */
int fbtft_write_vmem24_bus8(struct fbtft_par *par, size_t offset, size_t len)
{
	u16 *vmem16;
	u16 *txbuf16 = (u16 *)par->txbuf.buf;
	size_t remain;
	size_t to_copy;
	size_t tx_array_size;
	int i;
	int ret = 0;
	size_t startbyte_size = 0;

	fbtft_par_dbg(DEBUG_WRITE_VMEM, par, "%s(offset=%zu, len=%zu)\n",
			__func__, offset, len);

	remain = len / 2;
	vmem16 = (u16 *)(par->info->screen_base + offset);

	if (par->gpio.dc != -1)
		gpio_set_value(par->gpio.dc, 1);

	/* non buffered write */
	if (!par->txbuf.buf)
		return par->fbtftops.write(par, vmem16, len);

	/* buffered write */
	tx_array_size = par->txbuf.len / 2;

	if (par->startbyte) {
		txbuf16 = (u16 *)(par->txbuf.buf + 1);
		tx_array_size -= 2;
		*(u8 *)(par->txbuf.buf) = par->startbyte | 0x2;
		startbyte_size = 1;
	}

	while (remain) {
		to_copy = remain > tx_array_size ? tx_array_size : remain;
		dev_dbg(par->info->device, "    to_copy=%zu, remain=%zu\n",
				to_copy, remain - to_copy);

		for (i = 0; i < to_copy; i++)
			txbuf16[i] = cpu_to_be16(vmem16[i]);

		vmem16 = vmem16 + to_copy;
		ret = par->fbtftops.write(par, par->txbuf.buf,
				startbyte_size + to_copy * 2);
		if (ret < 0)
			return ret;
		remain -= to_copy;
	}

	return ret;
}

static struct fbtft_display display = {
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
	.fbtftops = {
		.init_display = init_display,
		.set_addr_win = set_addr_win,
//		.write = write,
		.reset = reset,
//		.set_var = set_var,
//		.set_gamma = set_gamma,
	},
};
FBTFT_REGISTER_DRIVER(DRVNAME, "RenesasSP,r61525", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:r61525");
MODULE_ALIAS("platform:r61525");

MODULE_DESCRIPTION("FB driver for the R61525 LCD Controller");
MODULE_AUTHOR("Rany Huang");
MODULE_LICENSE("GPL");
