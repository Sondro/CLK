//
//  Z80Storage.cpp
//  Clock Signal
//
//  Created by Thomas Harte on 01/09/2017.
//  Copyright 2017 Thomas Harte. All rights reserved.
//

#include "../Z80.hpp"

using namespace CPU::Z80;

void ProcessorBase::reset_power_on() {
	request_status_ &= ~Interrupt::PowerOn;
	last_request_status_ &= ~Interrupt::PowerOn;
}

uint16_t ProcessorBase::get_value_of_register(Register r) {
	switch (r) {
		case Register::ProgramCounter:			return pc_.full;
		case Register::StackPointer:			return sp_.full;

		case Register::A:						return a_;
		case Register::Flags:					return get_flags();
		case Register::AF:						return static_cast<uint16_t>((a_ << 8) | get_flags());
		case Register::B:						return bc_.bytes.high;
		case Register::C:						return bc_.bytes.low;
		case Register::BC:						return bc_.full;
		case Register::D:						return de_.bytes.high;
		case Register::E:						return de_.bytes.low;
		case Register::DE:						return de_.full;
		case Register::H:						return hl_.bytes.high;
		case Register::L:						return hl_.bytes.low;
		case Register::HL:						return hl_.full;

		case Register::ADash:					return afDash_.bytes.high;
		case Register::FlagsDash:				return afDash_.bytes.low;
		case Register::AFDash:					return afDash_.full;
		case Register::BDash:					return bcDash_.bytes.high;
		case Register::CDash:					return bcDash_.bytes.low;
		case Register::BCDash:					return bcDash_.full;
		case Register::DDash:					return deDash_.bytes.high;
		case Register::EDash:					return deDash_.bytes.low;
		case Register::DEDash:					return deDash_.full;
		case Register::HDash:					return hlDash_.bytes.high;
		case Register::LDash:					return hlDash_.bytes.low;
		case Register::HLDash:					return hlDash_.full;

		case Register::IXh:						return ix_.bytes.high;
		case Register::IXl:						return ix_.bytes.low;
		case Register::IX:						return ix_.full;
		case Register::IYh:						return iy_.bytes.high;
		case Register::IYl:						return iy_.bytes.low;
		case Register::IY:						return iy_.full;

		case Register::R:						return ir_.bytes.low;
		case Register::I:						return ir_.bytes.high;
		case Register::Refresh:					return ir_.full;

		case Register::IFF1:					return iff1_ ? 1 : 0;
		case Register::IFF2:					return iff2_ ? 1 : 0;
		case Register::IM:						return static_cast<uint16_t>(interrupt_mode_);

		case Register::MemPtr:					return memptr_.full;

		default: return 0;
	}
}

void ProcessorBase::set_value_of_register(Register r, uint16_t value) {
	switch (r) {
		case Register::ProgramCounter:	pc_.full = value;				break;
		case Register::StackPointer:	sp_.full = value;				break;

		case Register::A:				a_ = static_cast<uint8_t>(value);			break;
		case Register::AF:				a_ = static_cast<uint8_t>(value >> 8);		// deliberate fallthrough...
		case Register::Flags:			set_flags(static_cast<uint8_t>(value));		break;

		case Register::B:				bc_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::C:				bc_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::BC:				bc_.full = value;								break;
		case Register::D:				de_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::E:				de_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::DE:				de_.full = value;								break;
		case Register::H:				hl_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::L:				hl_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::HL:				hl_.full = value;								break;

		case Register::ADash:			afDash_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::FlagsDash:		afDash_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::AFDash:			afDash_.full = value;								break;
		case Register::BDash:			bcDash_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::CDash:			bcDash_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::BCDash:			bcDash_.full = value;								break;
		case Register::DDash:			deDash_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::EDash:			deDash_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::DEDash:			deDash_.full = value;								break;
		case Register::HDash:			hlDash_.bytes.high = static_cast<uint8_t>(value);	break;
		case Register::LDash:			hlDash_.bytes.low = static_cast<uint8_t>(value);	break;
		case Register::HLDash:			hlDash_.full = value;								break;

		case Register::IXh:				ix_.bytes.high = static_cast<uint8_t>(value);		break;
		case Register::IXl:				ix_.bytes.low = static_cast<uint8_t>(value);		break;
		case Register::IX:				ix_.full = value;									break;
		case Register::IYh:				iy_.bytes.high = static_cast<uint8_t>(value);		break;
		case Register::IYl:				iy_.bytes.low = static_cast<uint8_t>(value);		break;
		case Register::IY:				iy_.full = value;									break;

		case Register::R:				ir_.bytes.low = static_cast<uint8_t>(value);		break;
		case Register::I:				ir_.bytes.high = static_cast<uint8_t>(value);		break;
		case Register::Refresh:			ir_.full = value;									break;

		case Register::IFF1:			iff1_ = !!value;				break;
		case Register::IFF2:			iff2_ = !!value;				break;
		case Register::IM:				interrupt_mode_ = value % 3;	break;

		case Register::MemPtr:			memptr_.full = value;			break;

		default: break;
	}
}
