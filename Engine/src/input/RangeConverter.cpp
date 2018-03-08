#include "RangeConverter.h"

namespace engine {	namespace input {

	F32 RangeConverter::convert(RANGE rangeId, F32 invalue) const {
		std::map<RANGE, Converter>::const_iterator iter = conversionMap.find(rangeId);
		if (iter == conversionMap.end())
			return invalue;

		return iter->second.convert(invalue);
	}

	RangeConverter::RangeConverter(std::string infile) {
		// Read range conversions
		
		conversionMap.insert(std::make_pair(RANGE::camera_x, Converter(0, 700, 0, 700)));
		conversionMap.insert(std::make_pair(RANGE::camera_y, Converter(0, 500, 0, 500)));
	}
}}