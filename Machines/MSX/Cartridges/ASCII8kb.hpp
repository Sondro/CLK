//
//  ASCII8kb.hpp
//  Clock Signal
//
//  Created by Thomas Harte on 04/01/2018.
//  Copyright 2018 Thomas Harte. All rights reserved.
//

#ifndef ASCII8kb_hpp
#define ASCII8kb_hpp

#include "../ROMSlotHandler.hpp"

namespace MSX {
namespace Cartridge {

class ASCII8kbROMSlotHandler: public ROMSlotHandler {
	public:
		ASCII8kbROMSlotHandler(MSX::MemoryMap &map, int slot) :
			map_(map), slot_(slot) {}

		void write(uint16_t address, uint8_t value, bool pc_is_outside_bios) override {
//			printf("A8 %04x ", address);
			switch(address >> 11) {
				default:
					if(pc_is_outside_bios) confidence_counter_.add_miss();
				break;
				case 0xc:
					if(pc_is_outside_bios) {
						if(address == 0x6000 || address == 0x60ff) confidence_counter_.add_hit(); else confidence_counter_.add_equivocal();
					}
					map_.map(slot_, value * 0x2000, 0x4000, 0x2000);
				break;
				case 0xd:
					if(pc_is_outside_bios) {
						if(address == 0x6800 || address == 0x68ff) confidence_counter_.add_hit(); else confidence_counter_.add_equivocal();
					}
					map_.map(slot_, value * 0x2000, 0x6000, 0x2000);
				break;
				case 0xe:
					if(pc_is_outside_bios) {
						if(address == 0x7000 || address == 0x70ff) confidence_counter_.add_hit(); else confidence_counter_.add_equivocal();
					}
					map_.map(slot_, value * 0x2000, 0x8000, 0x2000);
				break;
				case 0xf:
					if(pc_is_outside_bios) {
						if(address == 0x7800 || address == 0x78ff) confidence_counter_.add_hit(); else confidence_counter_.add_equivocal();
					}
					map_.map(slot_, value * 0x2000, 0xa000, 0x2000);
				break;
			}
		}

		virtual void print_type() override {
			printf("A8");
		}

	private:
		MSX::MemoryMap &map_;
		int slot_;
};

}
}

#endif /* ASCII8kb_hpp */
