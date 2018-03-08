#pragma once

#include <string>
#include <map>
#include <common/types.h>
#include "inputconstants.h"

namespace engine { namespace input {

	class RangeConverter {
	private:
		struct Converter {
			Converter(F32 minIn, F32 maxIn, F32 minOut, F32 maxOut)
				: minimumInput(minIn), maximumInput(maxIn), 
				minimumOutput(minOut), maximumOutput(maxOut)
			{}

			F32 minimumInput, maximumInput, minimumOutput, maximumOutput;
			F32 convert(F32 invalue) const {
				// Clipping the input to be in the range
				F32 v = invalue;
				if (invalue < minimumInput)  v = minimumInput;			
				else if (v > maximumInput) v = maximumInput;

				F32 interpolationfactor = (v - minimumInput) / (maximumInput - minimumInput);
				return (interpolationfactor * (maximumOutput - minimumOutput) + minimumInput);
			}		
		};
		// MAP for holding all conversions	
		std::map<RANGE, Converter> conversionMap;
	public:
		F32 convert(RANGE rangeId, F32 invalue) const;
		explicit RangeConverter(std::string infile);
	};

}}

