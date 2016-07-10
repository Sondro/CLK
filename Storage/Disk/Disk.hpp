//
//  Disk.hpp
//  Clock Signal
//
//  Created by Thomas Harte on 10/07/2016.
//  Copyright © 2016 Thomas Harte. All rights reserved.
//

#ifndef Disk_hpp
#define Disk_hpp

#include <memory>
#include "../Storage.hpp"

namespace Storage {

/*!
	Models a single track on a disk as a series of events, each event being of arbitrary length
	and resulting in either a flux transition or the sensing of an index hole.
	
	Subclasses should implement @c get_next_event.
*/
class Track {
	public:
		struct Event {
			enum {
				IndexHole, FluxTransition
			} type;
			Time length;
		};

		virtual Event get_next_event() = 0;
};

/*!
	Models a disk as a collection of tracks, providing a range of possible track positions and allowing
	a point sampling of the track beneath any of those positions (if any).

	The intention is not that tracks necessarily be evenly spaced; a head_position_count of 3 wih track
	A appearing in positions 0 and 1, and track B appearing in position 2 is an appropriate use of this API
	if it matches the media.

	The track returned is point sampled only; if a particular disk drive has a sufficiently large head to
	pick up multiple tracks at once then the drive responsible for asking for multiple tracks and for
	merging the results.
*/
class Disk {
	public:

		/*!
			Returns the number of discrete positions that this disk uses to model its complete surface area.

			This is not necessarily a track count. There is no implicit guarantee that every position will
			return a distinct track, or — if the media is holeless — will return any track at all.
		*/
		virtual unsigned int get_head_position_count() = 0;

		/*!
			Returns the @c Track at @c position if there are any detectable events there; returns @c nullptr otherwise.
		*/
		virtual std::shared_ptr<Track> get_track_at_position(unsigned int position) = 0;
};

}

#endif /* Disk_hpp */
