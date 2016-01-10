//
//  CSElectron.m
//  Clock Signal
//
//  Created by Thomas Harte on 04/01/2016.
//  Copyright © 2016 Thomas Harte. All rights reserved.
//

#import "CSElectron.h"

#import "Electron.hpp"
#import "CSMachine+Subclassing.h"

@implementation CSElectron {
	Electron::Machine _electron;
}

- (void)doRunForNumberOfCycles:(int)numberOfCycles {
	_electron.run_for_cycles(numberOfCycles);
}

- (void)setOSROM:(nonnull NSData *)rom {
	_electron.set_rom(Electron::ROMSlotOS, rom.length, (const uint8_t *)rom.bytes);
}

- (void)setBASICROM:(nonnull NSData *)rom {
	_electron.set_rom(Electron::ROMSlotBASIC, rom.length, (const uint8_t *)rom.bytes);
}

- (void)setCRTDelegate:(Outputs::CRT::CRTDelegate *)delegate{
	_electron.get_crt()->set_delegate(delegate);
}

- (void)setView:(CSCathodeRayView *)view {
	[super setView:view];
	[view setSignalDecoder:[NSString stringWithUTF8String:_electron.get_signal_decoder()] type:CSCathodeRayViewSignalTypeRGB];
}

@end
