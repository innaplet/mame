// license:BSD-3-Clause
// copyright-holders:Sandro Ronco
/**********************************************************************

    Mephisto Modular

*********************************************************************/

#ifndef MAME_MACHINE_MMBOARD_H
#define MAME_MACHINE_MMBOARD_H

#pragma once


#include "sound/beep.h"
#include "video/hd44780.h"
#include "screen.h"
#include "speaker.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_MEPHISTO_SENSORS_BOARD_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MEPHISTO_SENSORS_BOARD, 0) \

#define MCFG_MEPHISTO_BOARD_UPDATE_ALL_LEDS(_val) \
	mephisto_board_device::static_set_upd_all_leds(*device, _val);

#define MCFG_MEPHISTO_DISPLAY_MODUL_ADD(_tag) \
	MCFG_DEVICE_ADD(_tag, MEPHISTO_DISPLAY_MODUL, 0)


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> mephisto_board_device

class mephisto_board_device : public device_t
{
public:
	// construction/destruction
	mephisto_board_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	// static configuration helpers
	static void static_set_upd_all_leds(device_t &device, bool _upd_all_leds) { mephisto_board_device &dev=downcast<mephisto_board_device &>(device); dev.m_upd_all_leds = _upd_all_leds; }

	DECLARE_READ8_MEMBER(input_r);
	DECLARE_WRITE8_MEMBER(led_w);
	DECLARE_READ8_MEMBER(mux_r);
	DECLARE_WRITE8_MEMBER(mux_w);
	DECLARE_WRITE8_MEMBER(led_upd_w);
	DECLARE_WRITE8_MEMBER(mux_upd_w);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	void update_leds();

private:
	required_ioport_array<8> m_sensors;
	bool                     m_upd_all_leds;
	uint8_t                  m_mux;
	uint8_t                  m_leds;
};

// ======================> mephisto_sensors_board_device

class mephisto_sensors_board_device : public mephisto_board_device
{
public:
	// construction/destruction
	mephisto_sensors_board_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;
};


// ======================> mephisto_display_modul_device

class mephisto_display_modul_device : public device_t
{
public:
	// construction/destruction
	mephisto_display_modul_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	DECLARE_WRITE8_MEMBER(latch_w);
	DECLARE_WRITE8_MEMBER(io_w);

	DECLARE_PALETTE_INIT(lcd_palette);

protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	optional_device<hd44780_device> m_lcdc;
	required_device<beep_device> m_beeper;
	uint8_t m_latch;
	uint8_t m_ctrl;
};


// device type definition
DECLARE_DEVICE_TYPE(MEPHISTO_SENSORS_BOARD, mephisto_sensors_board_device)
DECLARE_DEVICE_TYPE(MEPHISTO_DISPLAY_MODUL, mephisto_display_modul_device)


#endif // MAME_MACHINE_MMBOARD_H
