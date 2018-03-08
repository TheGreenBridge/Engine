#pragma once

#include <common/types.h>
#include <math/Vec3.h>


namespace engine {	namespace audio {

	class AudioSource {
	private:
		Vec3 *m_position;
		U32 m_sourceID;
		U8 m_pitch;
		U8 m_gain;
		F32 m_volume;	

	public:
		AudioSource();
		~AudioSource();

		void play() const;

		void setVolume(const F32 volume);
		F32 getVolume() const;

		void setSettings(U8 pitch, U8 gain);
		U8 getGain() const;
		U8 getPitch() const;

		U32 getSourceID() const;
		void setPosition(Vec3 *position);
	};

}}